cmake_minimum_required(VERSION 2.8.3)
project(uav_commander)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(Eigen REQUIRED)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  nav_msgs
  std_msgs
  geometry_msgs
  dynamic_reconfigure
  visualeyez_tracker
  message_generation
  ardrone_autonomy
  actionlib
  actionlib_msgs
)
find_package(Boost REQUIRED COMPONENTS system)
## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend and a run_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependencies might have been
##     pulled in transitively but can be declared for certainty nonetheless:
##     * add a build_depend tag for "message_generation"
##     * add a run_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
add_message_files(
    FILES
    Gains.msg
    ControlInfo.msg
    AllTopic.msg
)

## Generate services in the 'srv' folder
add_service_files(
   FILES
   GoSrv.srv
)

## Generate actions in the 'action' folder
add_action_files(
  DIRECTORY action
  FILES WayPoint.action
)

## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   std_msgs
   nav_msgs
   geometry_msgs
   ardrone_autonomy
   actionlib_msgs
 )

generate_dynamic_reconfigure_options(
config/PIDControl.cfg
config/PIDControl_Fe.cfg)


###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES uav_commander
   CATKIN_DEPENDS roscpp rospy std_msgs geometry_msgs message_runtime actionlib_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(include
  ${catkin_INCLUDE_DIRS}
  ${Eigen_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)


## Declare a cpp library
# add_library(uav_commander
#   src/${PROJECT_NAME}/uav_commander.cpp
# )

## Declare a cpp executable
#add_executable(position_controller src/uav_commander.cpp)
add_executable(position_controller src/PositionControl.cpp)
add_executable(position_controller_Fe src/PositionControl_Fe.cpp)
add_executable(chirp_goal_commander src/ChirpGoalCommander.cpp)
add_executable(go_server src/GoServer.cpp)
add_executable(go_client src/GoClient.cpp)
add_executable(chirp_controler src/ChirpAndControl.cpp)
add_executable(adaptive_control src/AdaptiveX.cpp)
add_executable(way_point_client src/WayPointClient.cpp)

## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
#add_dependencies(position_controller uav_commander_generate_messages_cpp)
add_dependencies(position_controller uav_commander_generate_messages_cpp ${PROJECT_NAME}_gencfg)
add_dependencies(position_controller_Fe ${PROJECT_NAME}_gencfg)
add_dependencies(chirp_goal_commander uav_commander_generate_messages_cpp)
add_dependencies(chirp_controler uav_commander_generate_messages_cpp)
add_dependencies(adaptive_control uav_commander_generate_messages_cpp)
add_dependencies(way_point_client uav_commander_generate_messages_cpp)

add_dependencies(go_server ${PROJECT_NAME}_gencfg)
add_dependencies(go_client ${PROJECT_NAME}_gencfg)

## Specify libraries to link a library or executable target against
#target_link_libraries(position_controller ${catkin_LIBRARIES} -lpq )
target_link_libraries(position_controller  ${catkin_LIBRARIES} -lpq )
target_link_libraries(position_controller_Fe  ${catkin_LIBRARIES} -lpq )
target_link_libraries(chirp_goal_commander ${catkin_LIBRARIES} -lpq )
target_link_libraries(chirp_controler ${catkin_LIBRARIES} -lpq )
target_link_libraries(adaptive_control ${catkin_LIBRARIES} -lpq )
target_link_libraries(go_server ${catkin_LIBRARIES} -lpq )
target_link_libraries(go_client ${catkin_LIBRARIES} -lpq )
target_link_libraries(way_point_client ${catkin_LIBRARIES} -lpq )

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS uav_commander uav_commander_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_uav_commander.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
