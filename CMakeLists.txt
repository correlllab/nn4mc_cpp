# The name of the project
PROJECT (nn4mp)

# Minimum version of cmake required
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# Boost library:
SET (Boost_USE_STATIC_LIBS OFF)
SET (Boost_USE_MULTITHREAD ON)
SET (Boost_USE_STATIC_RUNTIME OFF)

OPTION(NN4MP_USE_EXTERNAL_JSON "Use an external JSON library" OFF)

# Packages needed for this project
FIND_PACKAGE (HDF5 REQUIRED)
FIND_PACKAGE (Boost COMPONENTS thread system filesystem REQUIRED)

MESSAGE(STATUS "HDF5 INCLUDE LOCATION:  " ${HDF5_INCLUDE_DIRS})
MESSAGE(STATUS "HDF5 LIBRARIES:  " ${HDF5_LIBRARIES})
MESSAGE(STATUS "HDF5 HL LIBRARIES:  " ${HDF5_HL_LIBRARIES})
MESSAGE(STATUS "HDF5_CXX_LIBRARIES:  " ${HDF5_CXX_LIBRARIES})
MESSAGE(STATUS "version" ${HDF5_VERSION})

# Boost library:
MESSAGE(STATUS "Boost version: ${Boost_VERSION}")

# Add other flags to the compiler
SET (CMAKE_CXX_FLAGS "-g")
#set(CMAKE_BUILD_TYPE Debug)

# Use C++11
SET (CMAKE_CXX_STANDARD 11)

# Version Number
SET (nn4mp_VERSION_MAJOR 0)
SET (nn4mp_VERSION_MINOR 0)

# Add the library directory
ADD_SUBDIRECTORY(lib)

# Bring the headers and source files into the project
INCLUDE_DIRECTORIES (src)
INCLUDE_DIRECTORIES (data)
INCLUDE_DIRECTORIES (include)
INCLUDE_DIRECTORIES (libraries)

INCLUDE_DIRECTORIES (${HDF5_INCLUDE_DIRS})
INCLUDE_DIRECTORIES (${Boost_INCLUDE_DIR})

SET(LIBS_TO_LINK ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

FILE (GLOB CORE_LIB src/*.cpp src/datastructures/*.cpp src/parser/*.cpp src/generator/*.cpp)

# Build libraries
ADD_LIBRARY (nn4mp_core SHARED ${CORE_LIB})

TARGET_LINK_LIBRARIES(nn4mp_core PRIVATE nlohmann_json::nlohmann_json)
TARGET_LINK_LIBRARIES(nn4mp_core PUBLIC ${HDF5_HL_LIBRARIES} ${HDF5_CXX_LIBRARIES} ${HDF5_LIBRARIES})
TARGET_LINK_LIBRARIES(nn4mp_core PRIVATE hdf5 hdf5_cpp)
TARGET_LINK_LIBRARIES(nn4mp_core PRIVATE ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})

# Add the executable
ADD_EXECUTABLE (tensor_test examples/tensor_test.cpp)
ADD_EXECUTABLE (generator_test examples/generator_test.cpp)
ADD_EXECUTABLE (generator_test_v2 examples/generator_test_v2.cpp)
ADD_EXECUTABLE (nn_test examples/nn_test.cpp)
ADD_EXECUTABLE (json_test examples/json_test.cpp)
ADD_EXECUTABLE (parser_test examples/parser_example.cpp)
ADD_EXECUTABLE (h5cpp_test examples/h5cpp_test.cpp)
ADD_EXECUTABLE (iterator_test examples/iterator_test.cpp)
ADD_EXECUTABLE (file_creator_test examples/file_creator_test.cpp)
ADD_EXECUTABLE (generator_test_file examples/generator_test_actual_file.cpp)


TARGET_LINK_LIBRARIES (iterator_test nn4mp_core)
TARGET_LINK_LIBRARIES (tensor_test nn4mp_core)
TARGET_LINK_LIBRARIES (generator_test nn4mp_core)
TARGET_LINK_LIBRARIES (nn_test nn4mp_core)
TARGET_LINK_LIBRARIES (json_test nn4mp_core)
TARGET_LINK_LIBRARIES (generator_test_v2 nn4mp_core)
TARGET_LINK_LIBRARIES (generator_test_file nn4mp_core)
TARGET_LINK_LIBRARIES (generator_test_file nlohmann_json::nlohmann_json)
TARGET_LINK_LIBRARIES (generator_test_file hdf5 hdf5_cpp)
TARGET_LINK_LIBRARIES (generator_test_file ${HDF5_HL_LIBRARIES} ${HDF5_CXX_LIBRARIES} ${HDF5_LIBRARIES})
TARGET_LINK_LIBRARIES (json_test nlohmann_json::nlohmann_json)
TARGET_LINK_LIBRARIES (parser_test nn4mp_core)
TARGET_LINK_LIBRARIES (parser_test nlohmann_json::nlohmann_json)
TARGET_LINK_LIBRARIES (parser_test hdf5 hdf5_cpp)
TARGET_LINK_LIBRARIES (parser_test ${HDF5_HL_LIBRARIES} ${HDF5_CXX_LIBRARIES} ${HDF5_LIBRARIES})
TARGET_LINK_LIBRARIES (h5cpp_test ${HDF5_HL_LIBRARIES} ${HDF5_CXX_LIBRARIES} ${HDF5_LIBRARIES})
TARGET_LINK_LIBRARIES (h5cpp_test hdf5 hdf5_cpp)
TARGET_LINK_LIBRARIES (file_creator_test nn4mp_core ${Boost_LIBRARIES})
