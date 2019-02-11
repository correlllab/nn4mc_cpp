# The name of the project
PROJECT (nn4mp)

# Minimum version of cmake required
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# Packages needed for this project
# FIND_PACKAGE (h5cpp REQUIRED)

# Where to look for libraries and headers

# Add other flags to the compiler

# Use C++11
SET (CMAKE_CXX_STANDARD 11)

# Version Number
SET (nn4mp_VERSION_MAJOR 0)
SET (nn4mp_VERSION_MINOR 0)


# Bring the headers and source files into the project
INCLUDE_DIRECTORIES (include)

FILE (GLOB CORE_LIB src/datastructures/*.cpp)

# Build libraries
ADD_LIBRARY (nn4mp_datastructures SHARED ${CORE_LIB})

# Add the executable
ADD_EXECUTABLE (tensor_test src/tensor_test.cpp)
TARGET_LINK_LIBRARIES (tensor_test nn4mp_datastructures)


# Link the output files, and GTK+ libraries

# add the install targets
# add_executable(src HDF5Parser.cpp)
# target_link_libraries(src h5cpp)
