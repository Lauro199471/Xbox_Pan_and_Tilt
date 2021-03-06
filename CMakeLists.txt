cmake_minimum_required(VERSION 2.8.3)
project(Xbox_Pan_and_Tilt)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  cmake_modules
  roscpp
  std_msgs
)

find_package(Boost REQUIRED COMPONENTS system)
FIND_LIBRARY(WIRINGPI_LIBRARY wiringPi /opt/wiringPi)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES seven_dof_arm_test
#  CATKIN_DEPENDS cmake_modules interactive_markers moveit_core moveit_ros_perception moveit_ros_planning_interface pluginlib roscpp std_msgs
#  DEPENDS system_lib
  CATKIN_DEPENDS message_runtime
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(${catkin_INCLUDE_DIRS} ${WIRINGPI_LIBRARY})

## Declare a cpp executable
add_executable(xbox_publisher src/xbox_publisher.cpp)
add_executable(minimal_pwm src/minimal_pwm.cpp)
add_executable(xbox_to_pwm_S0 src/xbox_to_pwm_S0.cpp)
add_executable(xbox_to_pwm_S1 src/xbox_to_pwm_S1.cpp)
add_executable(xbox_button_led src/xbox_button_led.cpp)

## Add cmake target dependencies of the executable/library
add_dependencies(xbox_publisher minimal_nodes_generate_messages_cpp wiringPi)
add_dependencies(minimal_pwm minimal_nodes_generate_messages_cpp wiringPi)
add_dependencies(xbox_to_pwm_S0 minimal_nodes_generate_messages_cpp wiringPi)
add_dependencies(xbox_to_pwm_S1 minimal_nodes_generate_messages_cpp wiringPi)
add_dependencies(xbox_button_led minimal_nodes_generate_messages_cpp wiringPi)


## Specify libraries to link a library or executable target against
target_link_libraries(xbox_publisher  ${catkin_LIBRARIES} )
target_link_libraries(minimal_pwm  ${catkin_LIBRARIES} ${WIRINGPI_LIBRARY})
target_link_libraries(xbox_to_pwm_S0  ${catkin_LIBRARIES} ${WIRINGPI_LIBRARY})
target_link_libraries(xbox_to_pwm_S1  ${catkin_LIBRARIES} ${WIRINGPI_LIBRARY})
target_link_libraries(xbox_button_led  ${catkin_LIBRARIES} ${WIRINGPI_LIBRARY})




