# CMake version check
CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
# project name
PROJECT(PBR_engine)
#Enable C++11 support
SET(CMAKE_CXX_STANDARD 11)
# head file path
#INCLUDE_DIRECTORIES(./src)
# source directory
AUX_SOURCE_DIRECTORY(./src/shape DIR_SRC)
AUX_SOURCE_DIRECTORY(./src/util DIR_SRC)

# build
ADD_EXECUTABLE(intersect_test ${DIR_SRC})