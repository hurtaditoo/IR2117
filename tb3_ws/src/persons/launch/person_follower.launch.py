from launch import LaunchDescription 
from launch_ros.actions import Node
import launch.actions

def generate_launch_description():
	return LaunchDescription([
		Node(
        package='persons',
        executable='detector',
        namespace='front',
        parameters=[
          {"person_distance_min"},
          {"person_distance_max"},
          {"person_angle_min"},
          {"person_angle_max"}],
        remappings=[("person", "/front/person")]
      ),
      Node(
        package='persons',
        executable='detector',
        namespace='left',
        parameters=[
          {"person_distance_min"},
          {"person_distance_max"},
          {"person_angle_max"},
          {"person_angle_min"}],
				remappings=[("person", "/left/person")]
      ),
      Node(
        package='persons',
        executable='detector',
        namespace='right',
        parameters=[
          {"person_distance_min"},
          {"person_distance_max"},
          {"person_angle_min"},
          {"person_angle_max"}],
        remappings=[("person", "/right/person")]
      ), 
      Node(
        package='persons',
        executable='follower'
      )
        
	])
