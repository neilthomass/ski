cmake_minimum_required(VERSION 3.16)
project(ski_interpreter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_compile_options(-Wall -Wextra -Wpedantic)

# ---- Core library (everything except main) ----
add_library(ski_core
  src/term.cpp
  src/parser.cpp
  src/evaluator.cpp
)
target_include_directories(ski_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# ---- REPL / CLI executable ----
add_executable(ski src/main.cpp)
target_link_libraries(ski PRIVATE ski_core)

# ---- Tests ----
enable_testing()
add_executable(ski_tests tests/test_main.cpp)
target_link_libraries(ski_tests PRIVATE ski_core)
add_test(NAME ski_tests COMMAND ski_tests)
