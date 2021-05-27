cmake_minimum_required(VERSION 3.5)
project(more_interfaces)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
include_directories(include ${Boost_INCLUDE_DIRS})
# find dependencies
find_package(Boost COMPONENTS system log thread log_setup date_time REQUIRED)
find_package(ament_cmake REQUIRED)
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)
find_package(rosidl_default_generators REQUIRED)
find_package(rclcpp REQUIRED)
# find_package(BOOST COMPONENTS system log thread log_setup date_time REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(json REQUIRED IMPORTED_TARGET  jsoncpp)
pkg_check_modules(modbus REQUIRED IMPORTED_TARGET libmodbus)

# set a name for msg files
set(msg_files
  "msg/AddressBook.msg"
  "msg/NestedBook.msg"
)
# target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

# generate interfaces
rosidl_generate_interfaces(${PROJECT_NAME} ${msg_files})

ament_export_dependencies(rosidl_default_runtime)

add_executable(publish_address_book src/publish_address_book.cpp src/userdefined_modbus_library.cpp)

add_executable(subscribe_address_book src/subscriber_address_book.cpp)

# target_link_libraries(subscribe_address_book PUBLIC PkgConfig::json PkgConfig::modbus)

target_link_libraries(publish_address_book ${Boost_LIBRARIES})

ament_target_dependencies(subscribe_address_book "rclcpp" json modbus)

ament_target_dependencies(publish_address_book "rclcpp" json modbus )

install(TARGETS publish_address_book subscribe_address_book DESTINATION lib/${PROJECT_NAME})
 
rosidl_target_interfaces(publish_address_book ${PROJECT_NAME} "rosidl_typesupport_cpp")

rosidl_target_interfaces(subscribe_address_book ${PROJECT_NAME} "rosidl_typesupport_cpp")

if(BUILD_TESTING)
find_package(ament_lint_auto REQUIRED)
ament_lint_auto_find_test_dependencies()
endif()
ament_package()