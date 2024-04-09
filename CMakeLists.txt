cmake_minimum_required(VERSION 3.10)
project(server VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES "src/*.cpp" )

# Generate an executable from specified sources
add_executable(server ${SOURCES})

target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )

# Find Boost and specify the components you need
find_package(Boost 1.65.0 REQUIRED COMPONENTS system json)
if(Boost_FOUND)
    target_include_directories(server PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(server ${Boost_LIBRARIES})
endif()

# pthreads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(server Threads::Threads)

# Additional compiler flags
target_compile_options(server PRIVATE -Wall -Wpedantic -Wextra)

# Optional: Install rules
install(TARGETS server
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin # For Windows DLLs
)
install(DIRECTORY include/ DESTINATION include)

