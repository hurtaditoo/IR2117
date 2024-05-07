from launch import LaunchDescription 
from launch_ros.actions import Node
import launch.actions

def generate_launch_description():
	return LaunchDescription([
		Node(
			package='olympic',
			executable='rings',
			remappings=[
				('/cmd_vel', '/turtle1/cmd_vel'),
			],
			parameters=[
				{"radius": 2.0},
				{"angular_speed": 1.0}
			]
		)
	])
