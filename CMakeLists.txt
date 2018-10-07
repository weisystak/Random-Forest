project(run)

file(COPY
  "${PROJECT_SOURCE_DIR}/sample_data"
  DESTINATION "${PROJECT_BINARY_DIR}/"
  )

include_directories(${PROJECT_SOURCE_DIR})

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS  "-std=c++17")
add_executable(run main.cpp randomforest.cpp dtree.cpp bag.cpp item.cpp)
# target_link_libraries(run gtest pthread gtest_main)