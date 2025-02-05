# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(MyProject CXX)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 20)

# Enable warnings and debugging
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -g -fsanitize=address")

# Set linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")

# Ajouter le répertoire contenant bcrypt.h
# Nous utilisons ici le répertoire 'libs/bcrypt' comme exemple
include_directories(${CMAKE_SOURCE_DIR}/libs/bcrypt)

# Ajouter le répertoire contenant la bibliothèque statique libbcrypt.a
link_directories(${CMAKE_SOURCE_DIR}/libs/bcrypt)

# Find Boost (ensure it is installed)
find_package(Boost 1.78 REQUIRED)

# Check if Boost is found
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Boost not found!")
endif()

# Include directories for MySQL Connector/C++
include_directories(/usr/include/mysql)
link_directories(/usr/lib)

# Include directories for spdlog
include_directories(/usr/local/include/spdlog)
link_directories(/usr/local/lib)

# Find OpenSSL (ensure it is installed)
find_package(OpenSSL REQUIRED)

# Include OpenSSL headers
include_directories(${OPENSSL_INCLUDE_DIR})

# Include directories for custom source files (such as src/config)
include_directories(${CMAKE_SOURCE_DIR}/src/config)

# Find all .cpp files in src and src/config
file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/config/*.cpp)

# Add the executable target
add_executable(main src/start.cpp ${SOURCE_FILES})

# Link libraries
target_link_libraries(main 
    PRIVATE
    /usr/local/lib/libgtest.a
    /usr/local/lib/libgtest_main.a
    pthread
    bcrypt  # Nous l'avons inclus ici comme une bibliothèque statique
    ssl
    crypto
    mysqlcppconn
    ${Boost_LIBRARIES}
    spdlog
    OpenSSL::SSL
    OpenSSL::Crypto
)
