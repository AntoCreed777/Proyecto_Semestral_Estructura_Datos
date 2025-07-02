import json
import matplotlib.pyplot as plt
import os

class Graficos:
    
    @staticmethod
    def tiempoBusqueda(nombres: list, tiempos_busqueda: list) -> None:
        """
        Funcion encargada de graficar los promedios de los tiempos de busqueda

        """
        plt.figure(figsize=(10, 5))
        plt.bar(nombres, tiempos_busqueda, color='skyblue')
        plt.title(f"Tiempo de Búsqueda")
        plt.ylabel("Tiempo (ms)")
        plt.xticks(rotation=45)
        plt.grid(axis='y', linestyle='--')
        plt.tight_layout()
        plt.show()

    @staticmethod
    def tiempoConstruccion(nombres_estructuras: list, tiempos_construccion_estructuras: list) -> None:
        """
        Funcion encargada de graficar los promedios de los tiempos de construccion

        """
        plt.figure(figsize=(10, 5))
        plt.bar(nombres_estructuras, tiempos_construccion_estructuras, color='orange')
        plt.title(f"Tiempo de Construcción")
        plt.ylabel("Tiempo (ms)")
        plt.xticks(rotation=45)
        plt.grid(axis='y', linestyle='--')
        plt.tight_layout()
        plt.show()

    @staticmethod
    def comparacionBusquedaConstruccion(nombres: list, tiempos_busqueda: list, tiempos_construccion: list) -> None:
        """
        Funcion encargadad de graficar los promedios de los tiempos de construccion comparador con los tiempos de busqueda
    
        """
        plt.figure(figsize=(10, 5))
        x = range(len(nombres))
        plt.bar(x, tiempos_busqueda, width=0.4, label='Búsqueda', align='center')
        plt.bar([i + 0.4 for i in x], tiempos_construccion, width=0.4, label='Construcción', align='center')
        plt.xticks([i + 0.2 for i in x], nombres, rotation=45)
        plt.ylabel("Tiempo (ms)")
        plt.title(f"Búsqueda vs Construcción")
        plt.legend()
        plt.grid(axis='y', linestyle='--')
        plt.tight_layout()
        plt.show()
    
    @staticmethod
    def memoriaBusqueda(nombres: list, memorias: list) -> None:
        """ 
        Funcion encargada para graficar los promedios de la memoria usada en la busqueda
        
        """
        plt.figure(figsize=(10, 5))
        plt.bar(nombres, memorias, color='mediumseagreen')
        plt.title("Memoria Usada en Búsqueda")
        plt.ylabel("Memoria (KB)")
        plt.xticks(rotation=45)
        plt.grid(axis='y', linestyle='--')
        plt.tight_layout()
        plt.show()
    
    @staticmethod
    def memoriaConstruccion(nombres_estructuras: list, memorias: list) -> None:
        """
        Funcion encargada para graficar los promedios de la memoria usada en la construccion de los algoritmos
        
        """
        plt.figure(figsize=(10, 5))
        plt.bar(nombres_estructuras, memorias, color='mediumseagreen')
        plt.title("Memoria Usada en Construcción")
        plt.ylabel("Memoria (KB)")
        plt.xticks(rotation=45)
        plt.grid(axis='y', linestyle='--')
        plt.tight_layout()
        plt.show()

    @staticmethod
    def comparacionMemoria(nombres: list, mem_busqueda: list, mem_construccion: list) -> None:
        """
        Funcion encargada para graficar la comparacion entre la memoria usada en la busqueda y la memoria usada en la construccion de los algoritmos

        """
        plt.figure(figsize=(10, 5))
        x = range(len(nombres))
        plt.bar(x, mem_busqueda, width=0.4, label='Búsqueda', align='center')
        plt.bar([i + 0.4 for i in x], mem_construccion, width=0.4, label='Construcción', align='center')
        plt.xticks([i + 0.2 for i in x], nombres, rotation=45)
        plt.ylabel("Memoria (KB)")
        plt.title("Memoria: Búsqueda vs Construcción")
        plt.legend()
        plt.grid(axis='y', linestyle='--')
        plt.tight_layout()
        plt.show()

def extraerArchivos() -> list:
    """
    Funcion que extrae los archivos .json de la carpeta /test/json

    """
    # Ruta de los json
    ruta_jsones = os.path.join(os.path.dirname(__file__), '../test/json')

    archivos = []

    # Veo todos los archivos de la carpeta papu
    for archivo in os.listdir(ruta_jsones):
        if archivo.endswith(".json"):
            # Ruta completa
            archivos.append(os.path.join(ruta_jsones, archivo))

    return archivos

def main() -> None:
    # Extraer todos los json
    jsons = extraerArchivos()
    
    jsons = sorted(jsons)

    # Iterador
    interador = iter(jsons)
    contador = 0

    nombres = []
    nombres_estructuras = []
    tiempos_busquedas_promedio = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0,]
    tiempos_construccion_promedio = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
    tiempos_construccion_estructuras_promedio = [0.0 , 0.0, 0.0]
    memoria_busqueda_promedio = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
    memoria_construccion_promedio = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
    
    nombres_archivos_antiguos = ""

    for archivos_json in jsons:
        # Abrir el archivo y cargar la data xd
        with open(archivos_json, 'r') as f:
            data = json.load(f)
        
        clave = next(iter(data))
        datos = data[clave]
        
        nombre_actual = archivos_json.split('/')[-1].split('_')[0]

        
        if contador == 0: nombres_archivos_antiguos = nombre_actual       
        if(nombre_actual != nombres_archivos_antiguos): 
            nombres_archivos_antiguos = nombre_actual
            
            # Visualizar
            Graficos.tiempoBusqueda(nombres, tiempos_busquedas_promedio)
            Graficos.tiempoConstruccion(nombres_estructuras, tiempos_construccion_estructuras_promedio)
            Graficos.comparacionBusquedaConstruccion(nombres, tiempos_busquedas_promedio, tiempos_construccion_promedio)
            Graficos.memoriaBusqueda(nombres, memoria_busqueda_promedio)
            Graficos.memoriaConstruccion(nombres, memoria_construccion_promedio)
            Graficos.comparacionMemoria(nombres, memoria_busqueda_promedio, memoria_construccion_promedio)
            
            # Reinicio
            tiempos_busquedas_promedio = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0,]
            tiempos_construccion_promedio = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
            tiempos_construccion_estructuras_promedio = [0.0 , 0.0, 0.0]
            memoria_busqueda_promedio = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
            memoria_construccion_promedio = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0]

        # Cargamos todos los datos necesarios para la creacion de los graficos
        estructuras = [d for d in datos if d["Tipo"] == "Estructura"]
        
        if contador == 0: 
            nombres = [d["Nombre"] for d in datos]
            nombres_estructuras = [d["Nombre"] for d in estructuras]

        tiempos_busqueda = [d["tiempo_busqueda_mili"] for d in datos]
        tiempos_construccion = [d["tiempo_construccion_mili"] for d in datos]
        tiempos_construccion_estructuras = [d["tiempo_construccion_mili"] for d in estructuras]
        mem_busqueda = [d["memoria_busqueda_fin_kb"] for d in datos]
        mem_construccion = [d["memoria_construccion_fin_kb"] for d in datos]
        
        for i in range(6):
            if i < 3: 
                tiempos_construccion_estructuras_promedio[i] += tiempos_construccion_estructuras[i] / 40
            tiempos_busquedas_promedio[i] += tiempos_busqueda[i] / 40
            tiempos_construccion_promedio[i] += tiempos_construccion[i] / 40
            memoria_busqueda_promedio[i] += mem_busqueda[i] / 40
            memoria_construccion_promedio[i] += mem_construccion[i] / 40
        contador += 1
    
    # Creacion de los graficos
    Graficos.tiempoBusqueda(nombres, tiempos_busquedas_promedio)
    Graficos.tiempoConstruccion(nombres_estructuras, tiempos_construccion_estructuras_promedio)
    Graficos.comparacionBusquedaConstruccion(nombres, tiempos_busquedas_promedio, tiempos_construccion_promedio)
    Graficos.memoriaBusqueda(nombres, memoria_busqueda_promedio)
    Graficos.memoriaConstruccion(nombres, memoria_construccion_promedio)
    Graficos.comparacionMemoria(nombres, memoria_busqueda_promedio, memoria_construccion_promedio)

if __name__ == "__main__":
    main()
