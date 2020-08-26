# The name of the project
PROJECT (nn4mc
	LANGUAGES C CXX)

# Minimum version of cmake required
CMAKE_MINIMUM_REQUIRED (VERSION 3.5.0)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# Boost library:
SET (Boost_USE_STATIC_LIBS OFF)
SET (Boost_USE_MULTITHREAD ON)
SET (Boost_USE_STATIC_RUNTIME OFF)

IF(APPLE)
    SET(CMAKE_MACOSX_RPATH 1)
ENDIF()

OPTION(NN4MP_USE_EXTERNAL_JSON "Use an external JSON library" OFF)

# Packages needed for this project
FIND_PACKAGE (HDF5 REQUIRED)
FIND_PACKAGE (Boost COMPONENTS thread system filesystem REQUIRED)
FIND_PACKAGE (Boost CONFIG)

MESSAGE(STATUS "HDF5 INCLUDE LOCATION:  " ${HDF5_INCLUDE_DIRS})
MESSAGE(STATUS "HDF5 LIBRARIES:  " ${HDF5_LIBRARIES})
MESSAGE(STATUS "HDF5 HL LIBRARIES:  " ${HDF5_HL_LIBRARIES})
MESSAGE(STATUS "HDF5_CXX_LIBRARIES:  " ${HDF5_CXX_LIBRARIES})
MESSAGE(STATUS "version" ${HDF5_VERSION})

# Boost library:
MESSAGE(STATUS "Boost version: ${Boost_VERSION}")

# Add other flags to the compiler
SET (CMAKE_CXX_FLAGS "-g")

# Use C++11
SET (CMAKE_CXX_STANDARD 11)

# Version Number
SET (nn4mc_VERSION_MAJOR 0)
SET (nn4mc_VERSION_MINOR 0)

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
ADD_LIBRARY (nn4mc_core SHARED ${CORE_LIB})

TARGET_LINK_LIBRARIES(nn4mc_core PRIVATE nlohmann_json::nlohmann_json)
TARGET_LINK_LIBRARIES(nn4mc_core PUBLIC ${HDF5_HL_LIBRARIES} ${HDF5_CXX_LIBRARIES} ${HDF5_LIBRARIES})
TARGET_LINK_LIBRARIES(nn4mc_core PRIVATE hdf5_cpp)
TARGET_LINK_LIBRARIES(nn4mc_core PRIVATE ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})

# Add the executable
ADD_EXECUTABLE (generate_code examples/generator_test_actual_file.cpp)

TARGET_LINK_LIBRARIES (generate_code nn4mc_core)
TARGET_LINK_LIBRARIES (generate_code nlohmann_json::nlohmann_json)
TARGET_LINK_LIBRARIES (generate_code hdf5_cpp)
TARGET_LINK_LIBRARIES (generate_code ${HDF5_HL_LIBRARIES} ${HDF5_CXX_LIBRARIES} ${HDF5_LIBRARIES})

