# Version minimale de CMake requise
cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(systeme_solaire)

# Utiliser la norme C++11
set(CMAKE_CXX_STANDARD 11)

# Trouver les paquets nécessaires
find_package(OpenGL REQUIRED)   # Trouver la bibliothèque OpenGL
find_package(GLEW REQUIRED)     # Trouver la bibliothèque GLEW
find_package(GLUT REQUIRED)     # Trouver la bibliothèque GLUT

# Utiliser pkg-config pour trouver GLFW3
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

# Inclure les répertoires de fichiers d'en-tête
include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
include_directories(/usr/include/SOIL)

# Ajouter l'exécutable
add_executable(systeme_solaire src/main.cpp src/Planet.cpp src/Camera.cpp)

# Lier les bibliothèques nécessaires à l'exécutable
target_link_libraries(systeme_solaire ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} ${GLUT_LIBRARIES} SOIL)
