"""
@file analisis.py
@brief Análisis y visualización de resultados de algoritmos de búsqueda de patrones.

Este módulo consume los datos JSON generados por el programa C++ de benchmarking
de algoritmos de búsqueda de patrones y genera visualizaciones comparativas.

Funcionalidades principales:
- Lectura y procesamiento de archivos JSON con métricas de rendimiento
- Generación de gráficos de barras para tiempos de búsqueda y construcción
- Análisis comparativo de uso de memoria entre algoritmos
- Procesamiento de múltiples iteraciones para obtener promedios estadísticos

Estructura de datos JSON esperada:
================================

El programa C++ genera archivos JSON con la siguiente estructura:
{
    "nombre_archivo_N": [
        {
            "Nombre": "NombreAlgoritmo",
            "Tipo": "Algoritmo" | "Estructura", 
            "tiempo_busqueda_mili": float,
            "tiempo_construccion_mili": float,
            "memoria_busqueda_fin_kb": int,
            "memoria_construccion_fin_kb": int
        },
        ...
    ]
}

Donde:
- N es el número de iteración (0-39 por defecto)
- Los algoritmos tienen tiempo de construcción mínimo
- Las estructuras pueden tener tiempo de construcción significativo
- Todas las métricas de memoria están en kilobytes
- Todos los tiempos están en milisegundos

@date 2025
@note Requiere matplotlib para visualización y archivos JSON en ../test/json/
"""

import json
import matplotlib.pyplot as plt
import os
from typing import List, Tuple, Dict, Any

class Graficos:
    """
    Clase utilitaria que contiene métodos estáticos para generar visualizaciones
    de las métricas de rendimiento de algoritmos de búsqueda de patrones.
    
    Esta clase encapsula todas las funciones de graficación necesarias para
    analizar y comparar el rendimiento de diferentes algoritmos y estructuras
    de datos en términos de tiempo de ejecución y uso de memoria.
    
    Métodos disponibles:
    - tiempoBusqueda: Gráfico de barras para tiempos de búsqueda
    - tiempoConstruccion: Gráfico de barras para tiempos de construcción  
    - comparacionBusquedaConstruccion: Comparación lado a lado de tiempos
    - memoriaBusqueda: Gráfico de uso de memoria en búsqueda
    - memoriaConstruccion: Gráfico de uso de memoria en construcción
    - comparacionMemoria: Comparación de uso de memoria
    """
    
    @staticmethod
    def tiempoBusqueda(nombres: List[str], tiempos_busqueda: List[float]) -> None:
        """
        Genera un gráfico de barras mostrando los tiempos promedio de búsqueda
        para cada algoritmo/estructura de datos.

        Args:
            nombres: Lista con los nombres de los algoritmos/estructuras.
            tiempos_busqueda: Lista con los tiempos promedio de búsqueda en milisegundos.
            
        Returns:
            None: Muestra el gráfico usando matplotlib.
            
        Note:
            Los tiempos deben estar en milisegundos para mantener consistencia
            con las métricas generadas por el programa C++.
        """
        # Configuración del gráfico con formato profesional
        plt.figure(figsize=(10, 5))
        plt.bar(nombres, tiempos_busqueda, color='skyblue', edgecolor='navy', alpha=0.7)
        plt.title("Tiempo Promedio de Búsqueda por Algoritmo", fontsize=14, fontweight='bold')
        plt.ylabel("Tiempo (ms)", fontsize=12)
        plt.xlabel("Algoritmos/Estructuras", fontsize=12)
        plt.xticks(rotation=45, ha='right')
        plt.grid(axis='y', linestyle='--', alpha=0.7)
        plt.tight_layout()
        plt.show()

    @staticmethod
    def tiempoConstruccion(nombres_estructuras: List[str], tiempos_construccion_estructuras: List[float]) -> None:
        """
        Genera un gráfico de barras mostrando los tiempos promedio de construcción
        para estructuras de datos (no aplicable a algoritmos simples).

        Args:
            nombres_estructuras: Lista con los nombres de las estructuras de datos.
            tiempos_construccion_estructuras: Lista con los tiempos de construcción en milisegundos.
            
        Returns:
            None: Muestra el gráfico usando matplotlib.
            
        Note:
            Solo las estructuras de datos complejas (FM-Index, Suffix Arrays y Suffix Trees)
            requieren tiempo de construcción significativo.
        """
        plt.figure(figsize=(10, 5))
        plt.bar(nombres_estructuras, tiempos_construccion_estructuras, color='orange', edgecolor='darkorange', alpha=0.7)
        plt.title("Tiempo Promedio de Construcción de Estructuras", fontsize=14, fontweight='bold')
        plt.ylabel("Tiempo (ms)", fontsize=12)
        plt.xlabel("Estructuras de Datos", fontsize=12)
        plt.xticks(rotation=45, ha='right')
        plt.grid(axis='y', linestyle='--', alpha=0.7)
        plt.tight_layout()
        plt.show()

    @staticmethod
    def comparacionBusquedaConstruccion(nombres: List[str], tiempos_busqueda: List[float], tiempos_construccion: List[float]) -> None:
        """
        Genera un gráfico de barras doble comparando tiempos de búsqueda vs construcción
        para algoritmos y estructuras de datos.

        Args:
            nombres: Lista con los nombres de algoritmos/estructuras.
            tiempos_busqueda: Lista con tiempos de búsqueda en milisegundos.
            tiempos_construccion: Lista con tiempos de construcción en milisegundos.
            
        Returns:
            None: Muestra el gráfico comparativo usando matplotlib.
            
        Note:
            Para algoritmos simples, el tiempo de construcción será mínimo.
            Para estructuras complejas, puede ser significativo comparado con la búsqueda.
        """
        plt.figure(figsize=(12, 6))
        x = range(len(nombres))
        ancho_barra = 0.35
        
        # Barras para tiempos de búsqueda y construcción con colores distintivos
        plt.bar([i - ancho_barra/2 for i in x], tiempos_busqueda, 
                width=ancho_barra, label='Tiempo de Búsqueda', 
                color='skyblue', edgecolor='navy', alpha=0.7)
        plt.bar([i + ancho_barra/2 for i in x], tiempos_construccion, 
                width=ancho_barra, label='Tiempo de Construcción', 
                color='lightcoral', edgecolor='darkred', alpha=0.7)
        
        plt.xticks(x, nombres, rotation=45, ha='right')
        plt.ylabel("Tiempo (ms)", fontsize=12)
        plt.title("Comparación: Tiempo de Búsqueda vs Construcción", fontsize=14, fontweight='bold')
        plt.legend(fontsize=11)
        plt.grid(axis='y', linestyle='--', alpha=0.7)
        plt.tight_layout()
        plt.show()
    
    @staticmethod
    def memoriaBusqueda(nombres: List[str], memorias: List[float]) -> None:
        """
        Genera un gráfico de barras mostrando el uso promedio de memoria
        durante la fase de búsqueda para cada algoritmo/estructura.

        Args:
            nombres: Lista con los nombres de algoritmos/estructuras.
            memorias: Lista con el uso de memoria en kilobytes.
            
        Returns:
            None: Muestra el gráfico usando matplotlib.
        """
        plt.figure(figsize=(10, 5))
        plt.bar(nombres, memorias, color='mediumseagreen', edgecolor='darkgreen', alpha=0.7)
        plt.title("Uso de Memoria Durante la Búsqueda", fontsize=14, fontweight='bold')
        plt.ylabel("Memoria (KB)", fontsize=12)
        plt.xlabel("Algoritmos/Estructuras", fontsize=12)
        plt.xticks(rotation=45, ha='right')
        plt.grid(axis='y', linestyle='--', alpha=0.7)
        plt.tight_layout()
        plt.show()
    
    @staticmethod
    def memoriaConstruccion(nombres_estructuras: List[str], memorias: List[float]) -> None:
        """
        Genera un gráfico de barras mostrando el uso promedio de memoria
        durante la fase de construcción de estructuras de datos.

        Args:
            nombres_estructuras: Lista con los nombres de las estructuras de datos.
            memorias: Lista con el uso de memoria en kilobytes.
            
        Returns:
            None: Muestra el gráfico usando matplotlib.
        """
        plt.figure(figsize=(10, 5))
        plt.bar(nombres_estructuras, memorias, color='mediumpurple', edgecolor='indigo', alpha=0.7)
        plt.title("Uso de Memoria Durante la Construcción", fontsize=14, fontweight='bold')
        plt.ylabel("Memoria (KB)", fontsize=12)
        plt.xlabel("Estructuras de Datos", fontsize=12)
        plt.xticks(rotation=45, ha='right')
        plt.grid(axis='y', linestyle='--', alpha=0.7)
        plt.tight_layout()
        plt.show()

    @staticmethod
    def comparacionMemoria(nombres: List[str], mem_busqueda: List[float], mem_construccion: List[float]) -> None:
        """
        Genera un gráfico de barras doble comparando el uso de memoria
        durante búsqueda vs construcción para todos los algoritmos/estructuras.

        Args:
            nombres: Lista con los nombres de algoritmos/estructuras.
            mem_busqueda: Lista con uso de memoria durante búsqueda en KB.
            mem_construccion: Lista con uso de memoria durante construcción en KB.
            
        Returns:
            None: Muestra el gráfico comparativo usando matplotlib.
        """
        plt.figure(figsize=(12, 6))
        x = range(len(nombres))
        ancho_barra = 0.35
        
        # Barras para memoria de búsqueda y construcción con colores distintivos
        plt.bar([i - ancho_barra/2 for i in x], mem_busqueda, 
                width=ancho_barra, label='Memoria en Búsqueda', 
                color='mediumseagreen', edgecolor='darkgreen', alpha=0.7)
        plt.bar([i + ancho_barra/2 for i in x], mem_construccion, 
                width=ancho_barra, label='Memoria en Construcción', 
                color='mediumpurple', edgecolor='indigo', alpha=0.7)
        
        plt.xticks(x, nombres, rotation=45, ha='right')
        plt.ylabel("Memoria (KB)", fontsize=12)
        plt.title("Comparación: Uso de Memoria en Búsqueda vs Construcción", fontsize=14, fontweight='bold')
        plt.legend(fontsize=11)
        plt.grid(axis='y', linestyle='--', alpha=0.7)
        plt.tight_layout()
        plt.show()


def extraer_archivos_json() -> List[str]:
    """
    Extrae y retorna las rutas de todos los archivos JSON de resultados
    del directorio ../test/json/ relativo a este script.

    Returns:
        List[str]: Lista de rutas absolutas a archivos JSON encontrados.
        
    Raises:
        FileNotFoundError: Si el directorio ../test/json/ no existe.
        OSError: Si hay problemas de permisos al acceder al directorio.
        
    Note:
        Los archivos JSON deben seguir el formato generado por el programa C++
        de benchmarking con nombres tipo "archivo_N.json" donde N es el número
        de iteración.
    """
    
    # Determinar ruta del directorio JSON relativa a este script
    ruta_jsones = os.path.join(os.path.dirname(__file__), '../test/json')
    
    # Verificar que el directorio existe
    if not os.path.exists(ruta_jsones):
        raise FileNotFoundError(f"El directorio {ruta_jsones} no existe. "
                              "Ejecute primero el programa C++ para generar los archivos JSON.")
    
    archivos_json = []

    # Buscar todos los archivos .json en el directorio
    for archivo in os.listdir(ruta_jsones):
        if archivo.endswith(".json"):
            ruta_completa = os.path.join(ruta_jsones, archivo)
            archivos_json.append(ruta_completa)

    if not archivos_json:
        raise FileNotFoundError("No se encontraron archivos JSON en el directorio. "
                              "Ejecute el programa C++ para generar datos de prueba.")

    return archivos_json


def main() -> None:
    """
    Función principal que procesa todos los archivos JSON y genera visualizaciones.
    
    Proceso de ejecución:
    1. Extrae todos los archivos JSON del directorio de pruebas
    2. Los ordena alfabéticamente para procesamiento consistente  
    3. Para cada archivo de prueba (40 iteraciones):
       - Carga y parsea los datos JSON
       - Acumula métricas para calcular promedios
       - Genera gráficos cuando cambia el archivo de prueba
    4. Genera gráficos finales para el último conjunto de datos
    
    Raises:
        FileNotFoundError: Si no existen archivos JSON o directorios requeridos.
        json.JSONDecodeError: Si los archivos JSON tienen formato inválido.
        KeyError: Si los archivos JSON no tienen la estructura esperada.
        
    Note:
        Asume 40 iteraciones por archivo de prueba (constante ITERACIONES en C++).
        Los promedios se calculan dividiendo entre este número fijo.
    """
    # Extraer y ordenar todos los archivos JSON para procesamiento consistente
    archivos_json = extraer_archivos_json()
    archivos_json = sorted(archivos_json)

    # Variables para control de iteración y acumulación de datos
    contador_iteraciones = 0
    
    # Listas para almacenar nombres de algoritmos y estructuras
    nombres_algoritmos = []
    nombres_estructuras = []
    
    # Arrays para acumular métricas (6 algoritmos/estructuras total)
    # Índices: 0-2 = Algoritmos (Boyer-Moore, KMP, Robin-Karp)
    # Índices: 3-5 = Estructuras (FM-Index, Suffix Arrays, Suffix Trees)
    tiempos_busqueda_acumulados = [0.0] * 6
    tiempos_construccion_acumulados = [0.0] * 6  
    tiempos_construccion_estructuras_acumulados = [0.0] * 3  # Solo estructuras
    memoria_busqueda_acumulada = [0.0] * 6
    memoria_construccion_acumulada = [0.0] * 6
    
    # Control para detectar cambio de archivo de prueba
    nombre_archivo_anterior = ""
    
    # Constante: número de iteraciones por archivo (debe coincidir con C++)
    ITERACIONES_POR_ARCHIVO = 40

    for ruta_archivo_json in archivos_json:
        try:
            # Abrir y cargar datos del archivo JSON actual
            with open(ruta_archivo_json, 'r', encoding='utf-8') as archivo:
                datos_json = json.load(archivo)
            
            # Extraer la clave principal (nombre del archivo de prueba)
            clave_principal = next(iter(datos_json))
            metricas_algoritmos = datos_json[clave_principal]
            
            # Extraer nombre base del archivo (sin número de iteración)
            nombre_archivo_actual = os.path.basename(ruta_archivo_json).split('_')[0]

            if contador_iteraciones == 0:
                nombre_archivo_anterior = nombre_archivo_actual
                
            if nombre_archivo_actual != nombre_archivo_anterior:
                # Calcular promedios finales para el archivo anterior
                tiempos_busqueda_promedio = [t / ITERACIONES_POR_ARCHIVO for t in tiempos_busqueda_acumulados]
                tiempos_construccion_promedio = [t / ITERACIONES_POR_ARCHIVO for t in tiempos_construccion_acumulados]
                tiempos_construccion_estructuras_promedio = [t / ITERACIONES_POR_ARCHIVO for t in tiempos_construccion_estructuras_acumulados]
                memoria_busqueda_promedio = [m / ITERACIONES_POR_ARCHIVO for m in memoria_busqueda_acumulada]
                memoria_construccion_promedio = [m / ITERACIONES_POR_ARCHIVO for m in memoria_construccion_acumulada]
                
                # Generar todos los gráficos para el archivo anterior
                print(f"Generando gráficos para archivo: {nombre_archivo_anterior}")
                Graficos.tiempoBusqueda(nombres_algoritmos, tiempos_busqueda_promedio)
                Graficos.tiempoConstruccion(nombres_estructuras, tiempos_construccion_estructuras_promedio)
                Graficos.comparacionBusquedaConstruccion(nombres_algoritmos, tiempos_busqueda_promedio, tiempos_construccion_promedio)
                Graficos.memoriaBusqueda(nombres_algoritmos, memoria_busqueda_promedio)
                Graficos.memoriaConstruccion(nombres_algoritmos, memoria_construccion_promedio)
                Graficos.comparacionMemoria(nombres_algoritmos, memoria_busqueda_promedio, memoria_construccion_promedio)
                
                # Reiniciar acumuladores para el nuevo archivo
                nombre_archivo_anterior = nombre_archivo_actual
                tiempos_busqueda_acumulados = [0.0] * 6
                tiempos_construccion_acumulados = [0.0] * 6
                tiempos_construccion_estructuras_acumulados = [0.0] * 3
                memoria_busqueda_acumulada = [0.0] * 6
                memoria_construccion_acumulada = [0.0] * 6

            # Separar estructuras de datos de algoritmos simples
            metricas_estructuras = [m for m in metricas_algoritmos if m["Tipo"] == "Estructura"]
            
            # Extraer nombres en la primera iteración
            if contador_iteraciones == 0:
                nombres_algoritmos = [m["Nombre"] for m in metricas_algoritmos]
                nombres_estructuras = [m["Nombre"] for m in metricas_estructuras]

            # Extraer métricas actuales de todos los algoritmos/estructuras
            tiempos_busqueda_actuales = [m["tiempo_busqueda_mili"] for m in metricas_algoritmos]
            tiempos_construccion_actuales = [m["tiempo_construccion_mili"] for m in metricas_algoritmos]
            tiempos_construccion_estructuras_actuales = [m["tiempo_construccion_mili"] for m in metricas_estructuras]
            memoria_busqueda_actual = [m["memoria_busqueda_fin_kb"] for m in metricas_algoritmos]
            memoria_construccion_actual = [m["memoria_construccion_fin_kb"] for m in metricas_algoritmos]
            
            # Acumular métricas para calcular promedios
            for i in range(6):  # 6 algoritmos/estructuras en total
                tiempos_busqueda_acumulados[i] += tiempos_busqueda_actuales[i]
                tiempos_construccion_acumulados[i] += tiempos_construccion_actuales[i]
                memoria_busqueda_acumulada[i] += memoria_busqueda_actual[i]
                memoria_construccion_acumulada[i] += memoria_construccion_actual[i]
                
                # Acumular tiempos de construcción solo para estructuras (primeras 3)
                if i < 3:
                    tiempos_construccion_estructuras_acumulados[i] += tiempos_construccion_estructuras_actuales[i]
                    
            contador_iteraciones += 1
            
        except (json.JSONDecodeError, KeyError, IndexError) as e:
            print(f"Error procesando archivo {ruta_archivo_json}: {e}")
            continue
        except Exception as e:
            print(f"Error inesperado procesando {ruta_archivo_json}: {e}")
            continue
    
    # Generar gráficos finales para el último archivo procesado
    if contador_iteraciones > 0:
        tiempos_busqueda_promedio = [t / ITERACIONES_POR_ARCHIVO for t in tiempos_busqueda_acumulados]
        tiempos_construccion_promedio = [t / ITERACIONES_POR_ARCHIVO for t in tiempos_construccion_acumulados]
        tiempos_construccion_estructuras_promedio = [t / ITERACIONES_POR_ARCHIVO for t in tiempos_construccion_estructuras_acumulados]
        memoria_busqueda_promedio = [m / ITERACIONES_POR_ARCHIVO for m in memoria_busqueda_acumulada]
        memoria_construccion_promedio = [m / ITERACIONES_POR_ARCHIVO for m in memoria_construccion_acumulada]
        
        print(f"Generando gráficos finales para archivo: {nombre_archivo_anterior}")
        Graficos.tiempoBusqueda(nombres_algoritmos, tiempos_busqueda_promedio)
        Graficos.tiempoConstruccion(nombres_estructuras, tiempos_construccion_estructuras_promedio)
        Graficos.comparacionBusquedaConstruccion(nombres_algoritmos, tiempos_busqueda_promedio, tiempos_construccion_promedio)
        Graficos.memoriaBusqueda(nombres_algoritmos, memoria_busqueda_promedio)
        Graficos.memoriaConstruccion(nombres_algoritmos, memoria_construccion_promedio)
        Graficos.comparacionMemoria(nombres_algoritmos, memoria_busqueda_promedio, memoria_construccion_promedio)
    
    print("Análisis completado. Todos los gráficos han sido generados.")


if __name__ == "__main__":
    """
    Punto de entrada principal del programa de análisis.
    
    Ejecuta el análisis completo de los datos JSON generados por el programa C++
    y muestra todas las visualizaciones correspondientes.
    
    Usage:
        python analisis.py
        
    Prerequisites:
        - Archivos JSON generados por el programa C++ en ../test/json/
        - matplotlib instalado para visualización
        - Python 3.6+ para type hints y f-strings
    """
    try:
        main()
    except FileNotFoundError as e:
        print(f"Error: {e}")
        print("Asegúrese de ejecutar primero el programa C++ para generar los datos de prueba.")
    except Exception as e:
        print(f"Error inesperado durante el análisis: {e}")
        print("Verifique que los archivos JSON tengan el formato correcto.")
