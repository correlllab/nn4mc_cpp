# The name of the project
PROJECT (nn4mp)

# Minimum version of cmake required
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

OPTION(NN4MP_USE_EXTERNAL_JSON "Use an external JSON library" OFF)

# Packages needed for this project
FIND_PACKAGE (HDF5 REQUIRED COMPONENTS C CXX)

# Where to look for libraries and headers

# Add other flags to the compiler

# Use C++11
SET (CMAKE_CXX_STANDARD 11)
# Version Number
SET (nn4mp_VERSION_MAJOR 0)
SET (nn4mp_VERSION_MINOR 0)

# Add the library directory
ADD_SUBDIRECTORY(lib)

# Bring the headers and source files into the project
INCLUDE_DIRECTORIES (src)
INCLUDE_DIRECTORIES (include)
INCLUDE_DIRECTORIES (libraries)

FILE (GLOB CORE_LIB src/*.cpp src/datastructures/*.cpp src/generator/*.cpp)# src/parser/*.cpp)

# Build libraries
ADD_LIBRARY (nn4mp_core SHARED ${CORE_LIB})

TARGET_LINK_LIBRARIES(nn4mp_core PRIVATE nlohmann_json::nlohmann_json)

# Add the executable
ADD_EXECUTABLE (tensor_test examples/tensor_test.cpp)
ADD_EXECUTABLE (generator_test examples/generator_test.cpp)
ADD_EXECUTABLE (nn_test examples/nn_test.cpp)
ADD_EXECUTABLE (json_test examples/json_test.cpp)

TARGET_LINK_LIBRARIES (tensor_test nn4mp_core)
TARGET_LINK_LIBRARIES (generator_test nn4mp_core)
TARGET_LINK_LIBRARIES (nn_test nn4mp_core)
TARGET_LINK_LIBRARIES (json_test nn4mp_core)
TARGET_LINK_LIBRARIES (json_test nlohmann_json::nlohmann_json)