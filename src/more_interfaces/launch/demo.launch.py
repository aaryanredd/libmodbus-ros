from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    ld = LaunchDescription()

    talker_node = Node(
        package="more_interfaces",
        executable="publish_address_book",
    )

    listener_node = Node(
        package="more_interfaces",
        executable="subscribe_address_book"
    )

    ld.add_action(talker_node)
    ld.add_action(listener_node)

    return ld