#include "../include/definiciones.hpp"
#include "../include/medidor.hpp"

#include <mutex>
#include <set>
#include <fstream>
#include <iomanip>
#include <filesystem>

namespace fs = std::filesystem;

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#else
#include <sys/resource.h>
#include <unistd.h>
#endif

using json = nlohmann::json;

#define NOMBRE_CARPETA_JSON fs::path("test/json")

static json resultados_array = json::array();
static json resultado_actual;
static std::string medicion_nombre;
static std::string medicion_tipo;
static std::string medicion_patron;

static std::mutex mtx;
static size_t memoria_acumulada_kb = 0;

static void acumularMemoria(size_t mem_usada) {
    memoria_acumulada_kb += mem_usada;
}

size_t getMemoryUsage() {
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
        return pmc.WorkingSetSize / 1024;
    }
    return 0;
#else
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        return usage.ru_maxrss; // KB en Linux
    }
    return 0;
#endif
}

std::chrono::high_resolution_clock::time_point iniciarTimer() {
    return std::chrono::high_resolution_clock::now();
}

std::chrono::high_resolution_clock::time_point detenerTimer() {
    return std::chrono::high_resolution_clock::now();
}

std::chrono::duration<double, std::milli> calcularDuracion(
    std::chrono::high_resolution_clock::time_point inicio,
    std::chrono::high_resolution_clock::time_point fin
) {
    return std::chrono::duration<double, std::milli>(fin - inicio);
}

size_t obtenerMemoriaMaximaKb() {
    return getMemoryUsage();
}

void iniciarMedicion(const std::string& nombre, const std::string& tipo, const std::string& patron) {
    std::lock_guard<std::mutex> lock(mtx);
    medicion_nombre = nombre;
    medicion_tipo = tipo;
    medicion_patron = patron;

    resultado_actual = json::object();
    resultado_actual["Nombre"] = nombre;
    resultado_actual["Tipo"] = tipo;
}

void registrarConstruccion(size_t mem_inicio, size_t mem_fin, std::chrono::duration<double, std::milli> duracion) {
    std::lock_guard<std::mutex> lock(mtx);
    resultado_actual["memoria_construccion_inicio_kb"] = mem_inicio;
    resultado_actual["memoria_construccion_fin_kb"] = mem_fin;
    size_t usada = (mem_fin > mem_inicio) ? mem_fin - mem_inicio : 0;
    resultado_actual["memoria_construccion_usada_kb"] = usada;
    resultado_actual["tiempo_construccion_mili"] = duracion.count();

    acumularMemoria(usada);
}

void registrarBusqueda(size_t mem_inicio, size_t mem_fin, std::chrono::duration<double, std::milli> duracion, unsigned int ocurrencias) {
    std::lock_guard<std::mutex> lock(mtx);
    resultado_actual["memoria_busqueda_inicio_kb"] = mem_inicio;
    resultado_actual["memoria_busqueda_fin_kb"] = mem_fin;
    size_t usada = (mem_fin > mem_inicio) ? mem_fin - mem_inicio : 0;
    resultado_actual["memoria_busqueda_usada_kb"] = usada;
    resultado_actual["tiempo_busqueda_mili"] = duracion.count();

    acumularMemoria(usada);
}

void guardarResultado() {
    std::lock_guard<std::mutex> lock(mtx);
    resultados_array.push_back(resultado_actual);
    resultado_actual = json::object();
}

void validarCarpetaGuardado() {
    if (!std::filesystem::exists(NOMBRE_CARPETA_JSON)) {
        if(!std::filesystem::create_directory(NOMBRE_CARPETA_JSON)){
            throw std::runtime_error("La carpeta no pudo ser creada: " + NOMBRE_CARPETA_JSON.string());
        }
    }

    if (!std::filesystem::is_directory(NOMBRE_CARPETA_JSON)) {
        throw std::runtime_error("La ruta para guardar los tests ya existe y no es una carpeta: " + NOMBRE_CARPETA_JSON.string());
    }
}

void guardarResultadosFinales(const std::string& nombre_archivo, const std::string& patron, unsigned int ocurrencias, size_t /*memoria_maxima_kb*/) {
    std::lock_guard<std::mutex> lock(mtx);

    std::string clave = "patron: " + patron
                      + ", ocurrencias: " + std::to_string(ocurrencias)
                      + ", memoria_total_usada_kb: " + std::to_string(memoria_acumulada_kb);

    json salida;
    salida[clave] = resultados_array;

    try {
        validarCarpetaGuardado();
    } catch (const std::exception &e) {
        throw e;
    }

    fs::path archivo = NOMBRE_CARPETA_JSON / (nombre_archivo + ".json");
    std::ofstream out(archivo);
    if (!out) {
        throw std::runtime_error("Error abriendo archivo " + archivo.string() + " para escritura\n");
    }

    out << std::setw(4) << salida << std::endl;
    out.close();

    resultados_array.clear();
    memoria_acumulada_kb = 0;
}

// Función para medir algoritmo
unsigned int medirAlgoritmo(const std::string& nombre, unsigned int(*func)(const std::string&, const std::string&), 
                            const std::string& texto, const std::string& patron) {
    try {
        iniciarMedicion(nombre, "Algoritmo", patron);

        size_t mem_inicio = getMemoryUsage();
        auto t_inicio = iniciarTimer();

        unsigned int ocurrencias = func(texto, patron);

        auto t_fin = detenerTimer();
        size_t mem_fin = getMemoryUsage();

        registrarConstruccion(0, 0, std::chrono::duration<double, std::milli>(0)); // sin construcción
        registrarBusqueda(mem_inicio, mem_fin, calcularDuracion(t_inicio, t_fin), ocurrencias);
        guardarResultado();

        return ocurrencias;
    } catch (...) {
        iniciarMedicion(nombre, "Algoritmo", patron);
        registrarConstruccion(0, 0, std::chrono::duration<double, std::milli>(0));
        registrarBusqueda(0, 0, std::chrono::duration<double, std::milli>(0), 0);
        guardarResultado();
        return 0;
    }
}

// Función para medir estructura
unsigned int medirEstructura(const std::string& nombre, std::function<std::unique_ptr<BaseStructure>(const std::string&)> constructor,
                             const std::string& texto, const std::string& patron) {
    try {
        iniciarMedicion(nombre, "Estructura", patron);

        size_t mem_inicio_const = getMemoryUsage();
        auto t_inicio_const = iniciarTimer();

        auto estructura = constructor(texto);

        auto t_fin_const = detenerTimer();
        size_t mem_fin_const = getMemoryUsage();

        auto t_inicio_busq = iniciarTimer();
        unsigned int ocurrencias = estructura->buscar(patron);
        auto t_fin_busq = detenerTimer();
        size_t mem_fin_busq = getMemoryUsage();

        registrarConstruccion(mem_inicio_const, mem_fin_const, calcularDuracion(t_inicio_const, t_fin_const));
        registrarBusqueda(mem_fin_const, mem_fin_busq, calcularDuracion(t_inicio_busq, t_fin_busq), ocurrencias);
        guardarResultado();

        return ocurrencias;
    } catch (...) {
        iniciarMedicion(nombre, "Estructura", patron);
        registrarConstruccion(0, 0, std::chrono::duration<double, std::milli>(0));
        registrarBusqueda(0, 0, std::chrono::duration<double, std::milli>(0), 0);
        guardarResultado();
        return 0;
    }
}