cmake_minimum_required(VERSION 3.20)
project(PROGETTO_FINALE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

enable_testing()

find_package(Eigen3 REQUIRED)
# Versione CON De Pina
set(SRC_DEPINA prova_matrici_depina.cpp)
add_executable(eseguibile_depina ${SRC_DEPINA})
target_include_directories(eseguibile_depina PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(eseguibile_depina PRIVATE Eigen3::Eigen)

# Versione SENZA De Pina (Solo DFS)
set(SRC_STANDARD prova_matrici.cpp)
add_executable(eseguibile_standard ${SRC_STANDARD})
target_include_directories(eseguibile_standard PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(eseguibile_standard PRIVATE Eigen3::Eigen)

# test lettura netlist
set(SRC_NETLIST test_netlist.cpp)
add_executable(eseguibile_netlist ${SRC_NETLIST})
target_include_directories(eseguibile_netlist PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(eseguibile_netlist PRIVATE Eigen3::Eigen)

#test de pina
set(SRC_TEST test_depina.cpp)
add_executable(test_depina ${SRC_TEST})
target_include_directories(test_depina PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(test_depina PRIVATE Eigen3::Eigen)

# Main Programma
set(SRC_MAIN main.cpp)
add_executable(progetto_finale ${SRC_MAIN})
target_include_directories(progetto_finale PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(progetto_finale PRIVATE Eigen3::Eigen)