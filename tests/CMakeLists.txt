cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(MyProject)

# Spécifie la version de C++ à utiliser
set(CMAKE_CXX_STANDARD 20)

# Recherche Google Test et Google Benchmark
find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

# Si find_package échoue, spécifie manuellement le répertoire d'inclusion et de bibliothèque
include_directories(${GTEST_INCLUDE_DIRS} ${BENCHMARK_INCLUDE_DIRS})

# Ajouter le répertoire contenant les en-têtes de bcrypt
include_directories(${CMAKE_SOURCE_DIR}/bcrypt)

# Ajouter le répertoire contenant la bibliothèque statique libbcrypt.a
link_directories(${CMAKE_SOURCE_DIR}/bcrypt)

# Ajoute un chemin explicite pour les bibliothèques de Google Benchmark
link_directories(/usr/local/lib)


# Ajoute l'exécutable à générer
add_executable(prog test_password.cpp)

# Ajouter les bibliothèques nécessaires
target_link_libraries(prog 
    /usr/local/lib/libgtest.a 
    /usr/local/lib/libgtest_main.a 
    pthread 
    bcrypt 
    ssl 
    crypto
)

# Ajouter des flags de compilation
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -g -fsanitize=address")

# Ajouter des flags pour le linker
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
