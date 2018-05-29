cmake_minimum_required(VERSION 2.8.3)
project(callbackqueue_clear_example)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(callbackqueue_clear_example src/callbackqueue_clear_example.cpp)
add_dependencies(callbackqueue_clear_example ${catkin_EXPORTED_TARGETS})
target_link_libraries(callbackqueue_clear_example ${catkin_LIBRARIES})

add_executable(callbackqueue_clear_global_example src/callbackqueue_clear_global_example.cpp)
add_dependencies(callbackqueue_clear_global_example ${catkin_EXPORTED_TARGETS})
target_link_libraries(callbackqueue_clear_global_example ${catkin_LIBRARIES})

add_executable(callbackqueue_clear_inside_callback_example src/callbackqueue_clear_inside_callback_example.cpp)
add_dependencies(callbackqueue_clear_inside_callback_example ${catkin_EXPORTED_TARGETS})
target_link_libraries(callbackqueue_clear_inside_callback_example ${catkin_LIBRARIES})
