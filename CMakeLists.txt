cmake_minimum_required(VERSION 3.25)
project(DLite)

set(CMAKE_CXX_STANDARD 17)

# wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

# libcurl
find_package(CURL REQUIRED)

add_executable(dlite
    src/main.cpp
    src/DMainFrame.cpp
    src/dman.cpp
)
target_include_directories(dlite PRIVATE ${CURL_INCLUDE_DIR})
target_include_directories(dlite PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(dlite
    ${wxWidgets_LIBRARIES}
    ${CURL_LIBRARIES}
)

set_target_properties(dlite PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin"
)
