cmake_minimum_required(VERSION 3.15)
project("C-RPG" LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Quellen und Header hinzufügen
set(SOURCES src/*.c)
set(HEADERS include/)

set(SDL3_PATH "C:/libs/SDL3")
include_directories(${SDL3_PATH}/include)
link_directories(${SDL3_PATH}/lib)

# Include-Verzeichnisse setzen
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${HEADERS})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3.dll.a)
