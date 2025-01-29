cmake_minimum_required(VERSION 3.15)
project("C-RPG" LANGUAGES C)


# Quellen und Header hinzufügen
set(SOURCES "${CMAKE_SOURCE_DIR}/src/")
set(HEADERS "${CMAKE_SOURCE_DIR}/include/")

# Setze den Pfad zu den SDL3-Headern
include_directories("${CMAKE_SOURCE_DIR}/lib/SDL3-3.2.0/x86_64-w64-mingw32/include/")
link_directories("${CMAKE_SOURCE_DIR}/lib/SDL3-3.2.0/x86_64-w64-mingw32/lib")

add_executable(rpg ${SOURCES})
target_link_libraries(rpg SDL3)
set_target_properties(rpg PROPERTIES LINKER_LANGUAGE C)
