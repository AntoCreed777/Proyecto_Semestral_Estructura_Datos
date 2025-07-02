#Compilador
CC = gcc
CXX = g++

# Flags de compilación
FLAGS_BASE = -I ./include -Wall
CXXFLAGS_WARNINGS = -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wfloat-equal
CXXFLAGS_OPTIMIZATIONS = -O2 -march=native -mtune=native
CXXFLAGS_DEBUGGING = -g #-ggdb	# Descomentar para depurar con GDB

# Flags de compilación para diferentes configuraciones
CXXFLAGS_RELEASE = $(FLAGS_BASE) $(CXXFLAGS_OPTIMIZATIONS) #$(CXXFLAGS_WARNINGS)
CXXFLAGS_DEBUG = $(FLAGS_BASE) $(CXXFLAGS_DEBUGGING) #$(CXXFLAGS_WARNINGS)

# Configuración de compilación
CXXFLAGS = $(CXXFLAGS_DEBUG)	 # Cambiar a $(CXXFLAGS_RELEASE) para compilación de producción

# Directorios y archivos
OBJ_DIR = build
TARGET = main.out

# Buscar todos los archivos .cpp en el directorio src
SOURCES_CPP = $(wildcard ./src/*.cpp)
SOURCES_C = $(wildcard ./src/*.c)
SOURCES = $(SOURCES_CPP) $(SOURCES_C)
OBJECTS_CPP = $(patsubst ./src/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES_CPP))
OBJECTS_C = $(patsubst ./src/%.c, $(OBJ_DIR)/%.o, $(SOURCES_C))
OBJECTS = $(OBJECTS_CPP) $(OBJECTS_C)

# Indica que las siguientes reglas no son archivos y deben ser ejecutadas desde 0 siempre
.PHONY: all clean run debug

# Regla por defecto: compilar el programa
all: $(TARGET)

# Regla para compilar el programa
$(TARGET): $(OBJECTS)
	@echo "Compilando el programa..."
	@$(CXX) $(OBJECTS) -o $(TARGET) $(CXXFLAGS)

# Regla para compilar los archivos objeto y guardarlos en build/
$(OBJ_DIR)/%.o: ./src/%.cpp | $(OBJ_DIR)
	@echo "Compilando $<..."
	@$(CXX) -c $< -o $@ $(CXXFLAGS)

$(OBJ_DIR)/%.o: ./src/%.c | $(OBJ_DIR)
	@echo "Compilando $<..."
	@$(CC) -c $< -o $@ $(FLAGS_BASE)

# Crear el directorio obj si no existe
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Regla para ejecutar el programa
run: $(TARGET)
	@echo "Ejecutando el programa...\n"
	@./$(TARGET)

# Regla para debuggear el programa
debug: $(TARGET)
	@gdb ./$(TARGET)

# Regla para investigar las fugas de memoria
memoria: $(TARGET)
	@valgrind --leak-check=full --track-origins=yes ./$(TARGET)

# Regla para limpiar los archivos generados
clean:
	@rm -rf $(OBJ_DIR) $(TARGET)
