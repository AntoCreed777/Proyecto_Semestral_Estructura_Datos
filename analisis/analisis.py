import json
import matplotlib.pyplot as plt
import os

class Graficos:

    @staticmethod
    def tiempoBusqueda(nombres: list, tiempos_busqueda: list) -> None:
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


def extraerArchivos() -> list:
    
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

    for archivos_json in jsons:
        # Abrir el archivo y cargar la data xd
        with open(archivos_json, 'r') as f:
            data = json.load(f)
        
        clave = next(iter(data))

        datos = data[clave]

        # Cargamos todos los datos necesarios para la creacion de los graficos
        nombres = [d["Nombre"] for d in datos]
        tiempos_busqueda = [d["tiempo_busqueda_mili"] for d in datos]
        tiempos_construccion = [d["tiempo_construccion_mili"] for d in datos]

        estructuras = [d for d in datos if d["Tipo"] == "Estructura"]
        nombres_estructuras = [d["Nombre"] for d in estructuras]
        tiempos_construccion_estructuras = [d["tiempo_construccion_mili"] for d in estructuras]

        # Creacion de los graficos
        Graficos.tiempoBusqueda(nombres, tiempos_busqueda)
        Graficos.tiempoConstruccion(nombres_estructuras, tiempos_construccion_estructuras)
        Graficos.comparacionBusquedaConstruccion(nombres, tiempos_busqueda, tiempos_construccion)
    

if __name__ == "__main__":
    main()