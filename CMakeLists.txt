cmake_minimum_required(VERSION 3.15)

project(
  libmatrix-obs
  VERSION 1.0
  DESCRIPTION "OBS Studio plugin for Schönherz Mátrix streaming"
  HOMEPAGE_URL "kszk.bme.hu"
  LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(
  Qt5
  COMPONENTS Core Gui
  REQUIRED)

find_package(libobs REQUIRED)
find_package(libmueb 2.0 REQUIRED)

# libmueb_global.h needs this to work
add_compile_definitions(DLL_CONFIG)

add_library(matrix-obs SHARED src/matrix-obs.cpp  src/output.cpp)
target_link_libraries(matrix-obs Qt5::Core Qt5::Gui libobs libmueb::muebtransmitter)
