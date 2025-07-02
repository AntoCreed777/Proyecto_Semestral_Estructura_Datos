# 🔍 Proyecto: Algoritmos de Búsqueda de Patrones

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)
![Make](https://img.shields.io/badge/Make-427819?style=for-the-badge&logo=gnu&logoColor=white)

Sistema de benchmarking y análisis de algoritmos de búsqueda de patrones en texto

</div>

## 👥 Integrantes del Equipo

| Nombre | GitHub | Matrícula |
|--------|--------|-----------|
| Antonio Jesus Benavides Puentes | [@AntoCreed777](https://github.com/AntoCreed777) | 2023455954 |
| Lucas Daniel Morales Oyanedel | [@Falling-Bridge](https://github.com/Falling-Bridge) | 2023441490 |
| Javier Alejandro Campos Contreras | [@huebitoo](https://github.com/huebitoo) | 2023432857 |

## 📋 Tabla de Contenidos

- [🚀 Inicio Rápido](#-inicio-rápido)
- [📋 Requisitos Previos](#-requisitos-previos)
- [⚙️ Instalación](#️-instalación)
- [🔧 Configuración](#-configuración)
- [🏗️ Compilación](#️-compilación)
- [▶️ Ejecución](#️-ejecución)
- [📊 Análisis de Resultados](#-análisis-de-resultados)
- [🛠️ Solución de Problemas](#️-solución-de-problemas)
- [📚 Documentación](#-documentación)

## 🚀 Inicio Rápido

> [!IMPORTANT]
> **Prerrequisitos:** GCC 8.0+, Make, Python 3.8+ (para análisis)

```bash
# Clonar el repositorio
git clone https://github.com/AntoCreed777/Proyecto_Semestral_Estructura_Datos
cd Proyecto_Semestral_Estructura_Datos

# Compilar el proyecto
make clean && make

# Ejecutar benchmarks
./main.out

# Analizar resultados (requiere Python y matplotlib)
cd analisis
pip3 install -r requirements.txt
python3 analisis.py
```

> [!WARNING]
> Asegúrate de tener archivos `.txt` en la carpeta `test/textos/` antes de ejecutar los benchmarks. Sin estos archivos, el programa no funcionará correctamente.

## 🛠️ Tecnologías Utilizadas

<div align="center">

### Herramientas de desarrollo y control de versiones
<a href="https://skillicons.dev">
  <img src="https://skillicons.dev/icons?i=git,github,vscode&perline=5" />
</a>

### Lenguajes de programación
<a href="https://skillicons.dev">
  <img src="https://skillicons.dev/icons?i=cpp,python&perline=5" />
</a>

### Herramientas de compilación y análisis
<a href="https://skillicons.dev">
  <img src="https://skillicons.dev/icons?i=cmake,linux&perline=5" />
</a>

</div>

## 📋 Requisitos Previos

### Para Compilación y Ejecución
- **GCC/G++ 8.0+** con soporte para C++17
- **Make** para gestión de compilación
- **Sistema operativo:** Linux, macOS, o Windows con WSL

### Para Análisis de Resultados
- **Python 3.8+**
- **matplotlib** para visualización de gráficos
- **pip** para gestión de paquetes Python

> [!TIP]
> El análisis de resultados es opcional pero **altamente recomendado** para visualizar el rendimiento comparativo de los algoritmos. Los gráficos facilitan significativamente la interpretación de los resultados.

> [!NOTE]
> Si solo necesitas ejecutar los benchmarks sin análisis visual, puedes omitir la instalación de Python. Los resultados JSON estarán disponibles en `test/json/`.

## ⚙️ Instalación

### 1️⃣ Clonar el Repositorio

```bash
git clone https://github.com/AntoCreed777/Proyecto_Semestral_Estructura_Datos
cd Proyecto_Semestral_Estructura_Datos
```

### 2️⃣ Verificar Dependencias

<details>
<summary>🐧 Linux (Ubuntu/Debian)</summary>

```bash
# Instalar compilador y herramientas de desarrollo
sudo apt update
sudo apt install -y build-essential g++ make

# Para análisis Python
sudo apt install -y python3 python3-pip
cd analisis && pip3 install -r requirements.txt
```

</details>

<details>
<summary>🐧 Linux (Fedora/RHEL/CentOS)</summary>

```bash
# Instalar compilador y herramientas de desarrollo
sudo dnf install -y gcc-c++ make

# Para análisis Python
sudo dnf install -y python3 python3-pip
cd analisis && pip3 install -r requirements.txt
```

</details>

<details>
<summary>🍎 macOS</summary>

```bash
# Instalar Xcode Command Line Tools
xcode-select --install

# O usar Homebrew
brew install gcc make

# Para análisis Python
brew install python3
cd analisis && pip3 install -r requirements.txt
```

</details>

<details>
<summary>🪟 Windows (WSL)</summary>

```bash
# En WSL (Ubuntu)
sudo apt update
sudo apt install -y build-essential g++ make python3 python3-pip
cd analisis && pip3 install -r requirements.txt
```

</details>

## 🔧 Configuración

### Estructura del Proyecto

> [!TIP]
> **Navegación rápida:** Los archivos más importantes para entender el proyecto son `src/main.cpp` y `analisis/analisis.py`.

```
Proyecto_Semestral_Estructura_Datos/
├── include/           # Archivos de cabecera (.hpp)
│   ├── definiciones.hpp
│   ├── class_base.hpp
│   ├── boyer_moore.hpp
│   ├── knuth_morris_pratt.hpp
│   ├── robin_karp.hpp
│   ├── fm_index.hpp
│   ├── suffix_arrays.hpp
│   ├── suffix_trees.hpp
│   ├── utilities.hpp
│   └── medidor.hpp
├── src/               # Código fuente (.cpp)
│   ├── main.cpp
│   ├── boyer_moore.cpp
│   ├── knuth_morris_pratt.cpp
│   ├── robin_karp.cpp
│   ├── fm_index.cpp
│   ├── suffix_arrays.cpp
│   ├── suffix_trees.cpp
│   ├── utilities.cpp
│   └── medidor.cpp
├── build/             # Archivos objeto (.o)
├── test/              # Archivos de prueba
│   ├── textos/        # Archivos .txt para testing
│   └── json/          # Resultados JSON generados
├── analisis/          # Scripts de análisis Python
│   ├── analisis.py
│   └── requirements.txt
├── Makefile           # Configuración de compilación
└── conventions.md     # Convenciones de código
```

### Configuración del Makefile

El proyecto utiliza diferentes configuraciones de compilación:

```makefile
# Para desarrollo y debugging
make clean && make

# Para producción optimizada
make clean && make CXXFLAGS="$(CXXFLAGS_RELEASE)"
```

> [!WARNING]
> La compilación optimizada (`CXXFLAGS_RELEASE`) puede hacer que el debugging sea más difícil. Usa la versión debug durante el desarrollo.

## 🏗️ Compilación

### Comandos Básicos

```bash
# Compilación estándar (debug)
make

# Compilación limpia
make clean && make

# Compilación optimizada para producción
make clean && make CXXFLAGS="$(CXXFLAGS_RELEASE)"

# Solo limpiar archivos objeto
make clean
```

### Opciones de Compilación

- **Debug:** Incluye símbolos de depuración (`-g`)
- **Release:** Optimizaciones de rendimiento (`-O2 -march=native`)
- **Warnings:** Advertencias adicionales (disponible en Makefile)

> [!IMPORTANT]
> Para benchmarks precisos, usa la compilación Release. Para debugging, usa la compilación Debug.

## ▶️ Ejecución

> [!IMPORTANT]
> **Antes de ejecutar:** Verifica que existan archivos `.txt` en `test/textos/`. El programa procesará automáticamente todos los archivos de esta carpeta.

### Ejecutar Benchmarks

```bash
# Ejecutar programa principal
./main.out

# El programa solicitará:
# 1. Patrón a buscar
# 2. Procesará archivos .txt en test/textos/
# 3. Generará resultados JSON en test/json/
```

### Parámetros de Ejecución

- **ITERACIONES:** 40 por defecto (definido en `main.cpp`)
- **Archivos de prueba:** Se procesan automáticamente desde `test/textos/`
- **Algoritmos evaluados:**
  - Boyer-Moore
  - Knuth-Morris-Pratt
  - Robin-Karp
  - FM-Index
  - Suffix Arrays
  - Suffix Trees

### Métricas Recolectadas

- **Tiempo de búsqueda** (milisegundos)
- **Tiempo de construcción** (milisegundos para estructuras)
- **Uso de memoria** (KB)
- **Número de ocurrencias** encontradas

> [!NOTE]
> Los resultados se promedian automáticamente sobre **40 iteraciones** para mayor precisión estadística y reducir el impacto de variaciones del sistema.

> [!TIP]
> **Interpretación de resultados:** Los algoritmos con tiempo de construcción alto pero búsqueda rápida (como FM-Index) son ideales para múltiples búsquedas en el mismo texto.

## 📊 Análisis de Resultados

> [!WARNING]
> **Ejecuta primero los benchmarks:** El script de análisis requiere que existan archivos JSON en `test/json/`. Ejecuta `./main.out` antes de proceder con el análisis.

### Dependencias Python

**Opción 1: Usando requirements.txt (Recomendado)**
```bash
cd analisis
pip3 install -r requirements.txt
```

**Opción 2: Instalación manual**
```bash
pip3 install matplotlib
```

> [!TIP]
> **Usar `requirements.txt`** garantiza que tengas la versión exacta de matplotlib utilizada en el desarrollo del proyecto, evitando posibles incompatibilidades.

### Ejecutar Análisis Python

```bash
cd analisis
python3 analisis.py
```

### Gráficos Generados

El script de análisis genera automáticamente:

1. **Tiempo de Búsqueda:** Comparación de algoritmos
2. **Tiempo de Construcción:** Solo para estructuras de datos
3. **Comparación Búsqueda vs Construcción:** Análisis de trade-offs
4. **Uso de Memoria en Búsqueda:** Consumo por algoritmo
5. **Uso de Memoria en Construcción:** Consumo en preprocessing
6. **Comparación de Memoria:** Búsqueda vs Construcción

### Formato de Datos JSON

Los resultados se guardan en formato JSON:

```json
{
    "archivo_test_N": [
        {
            "Nombre": "BoyerMoore",
            "Tipo": "Algoritmo",
            "tiempo_busqueda_mili": 0.543,
            "tiempo_construccion_mili": 0.001,
            "memoria_busqueda_fin_kb": 1024,
            "memoria_construccion_fin_kb": 1024
        }
    ]
}
```

> [!NOTE]
> **Archivos automáticos:** Los archivos JSON se generan automáticamente en `test/json/` con nombres tipo `archivo_N.json` donde N es el número de iteración.

> [!TIP]
> **Análisis manual:** Si prefieres analizar los datos manualmente, los archivos JSON son fáciles de procesar con cualquier herramienta de análisis de datos (Python pandas, R, Excel, etc.).

## 🛠️ Solución de Problemas

> [!WARNING]
> **Problemas comunes:** La mayoría de errores se deben a: dependencias faltantes, archivos de prueba inexistentes, o problemas de permisos. Revisa estos puntos antes de reportar problemas.

<details>
<summary>⚠️ Error de compilación: "command not found"</summary>

### Problema
```bash
make: g++: command not found
```

### Solución
```bash
# Linux
sudo apt install build-essential

# macOS
xcode-select --install

# Windows
# Usar WSL o MinGW
```

> [!TIP]
> En Windows, WSL (Windows Subsystem for Linux) es la opción más recomendada para desarrollo C++.

</details>

<details>
<summary>⚠️ Error: "No such file or directory"</summary>

### Problema
```bash
fatal error: definiciones.hpp: No such file or directory
```

### Solución
```bash
# Verificar estructura de directorios
ls include/
ls src/

# Compilar desde directorio raíz
pwd  # Debe mostrar .../Proyecto_Semestral_Estructura_Datos
make clean && make
```

</details>

<details>
<summary>⚠️ Error Python: "No module named 'matplotlib'"</summary>

### Problema
```bash
ModuleNotFoundError: No module named 'matplotlib'
```

### Solución
```bash
# Opción 1: Usar requirements.txt (Recomendado)
cd analisis
pip3 install -r requirements.txt

# Opción 2: Instalación manual
pip3 install matplotlib

# O usar gestor de paquetes del sistema
sudo apt install python3-matplotlib  # Linux
brew install python3-matplotlib      # macOS
```

> [!IMPORTANT]
> **Entornos virtuales:** Si usas entornos virtuales de Python, asegúrate de activar el entorno correcto antes de instalar las dependencias.

</details>

<details>
<summary>⚠️ No se encuentran archivos de prueba</summary>

### Problema
```bash
Error: La carpeta test/textos no existe
```

### Solución
```bash
# Crear directorio y agregar archivos .txt
mkdir -p test/textos
# Copiar archivos de texto para testing
```

> [!WARNING]
> **Tamaño de archivos:** Para obtener mediciones precisas, usa archivos de texto de al menos 1KB. Archivos muy pequeños pueden dar resultados inconsistentes.

</details>

<details>
<summary>⚠️ Errores de memoria en ejecución</summary>

### Problema
Segmentation fault o errores de memoria.

### Solución
```bash
# Compilar con debug para más información
make clean && make CXXFLAGS="$(CXXFLAGS_DEBUG)"

# Usar valgrind para detectar memory leaks
valgrind --leak-check=full ./main.out

# Verificar tamaño de archivos de prueba
ls -lh test/textos/
```

> [!IMPORTANT]
> **Debugging:** Si experimentas errores de memoria frecuentes, compila en modo debug y usa herramientas como `valgrind` o `gdb` para identificar el problema.

</details>

## 📚 Documentación

### Archivos de Documentación

- **`conventions.md`:** Convenciones de código C++
- **Headers (.hpp):** Documentación Doxygen en archivos de cabecera
- **`analisis.py`:** Documentación completa del sistema de análisis

### Generar Documentación

```bash
# Si se configura Doxygen (opcional)
doxygen Doxyfile
```

### Convenciones de Código

- **Archivos:** `snake_case` (ej: `boyer_moore.cpp`)
- **Clases:** `PascalCase` (ej: `BoyerMoore`)
- **Variables:** `snake_case` (ej: `longitud_patron`)
- **Constantes:** `MAYUSCULAS` (ej: `ITERACIONES`)

## 🚀 Algoritmos Implementados

> [!NOTE]
> **Clasificación:** Los algoritmos se dividen en dos categorías principales: **algoritmos de búsqueda simple** (sin preprocessing) y **estructuras de datos avanzadas** (con preprocessing intensivo).

### Algoritmos de Búsqueda Simple
- **Boyer-Moore:** Búsqueda eficiente con saltos
- **Knuth-Morris-Pratt:** Preprocesamiento del patrón
- **Robin-Karp:** Hashing para comparación rápida

### Estructuras de Datos Avanzadas
- **FM-Index:** Índice comprimido con BWT
- **Suffix Arrays:** Arrays de sufijos ordenados
- **Suffix Trees:** Árboles de sufijos compactos

> [!TIP]
> **Cuándo usar cada uno:**
> - **Búsquedas únicas:** Boyer-Moore, KMP, Robin-Karp
> - **Múltiples búsquedas:** FM-Index, Suffix Arrays, Suffix Trees
> - **Memoria limitada:** Boyer-Moore, KMP
> - **Velocidad máxima:** FM-Index (después del preprocessing)

### Características
- ✅ Búsqueda exacta de patrones
- ✅ Medición de rendimiento automática
- ✅ Análisis comparativo de algoritmos
- ✅ Documentación completa con Doxygen
- ✅ Sistema de testing automatizado

## 📈 Resultados y Análisis

El proyecto permite comparar:

- **Tiempo de ejecución** entre diferentes algoritmos
- **Uso de memoria** durante búsqueda y construcción
- **Trade-offs** entre preprocessing y búsqueda
- **Escalabilidad** con diferentes tamaños de texto
- **Eficiencia** para diferentes tipos de patrones

---

<div align="center">

**Desarrollado con ❤️ para el curso de Estructura de Datos**

📚 **Universidad:** Universidad de Concepción  
🎓 **Curso:** Estructura de Datos  
📋 **Código curso:** 503220-1  
📅 **Semestre:** 2025-1

</div>
