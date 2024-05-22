from launch import LaunchDescription 
from launch_ros.actions import Node
import launch.actions

def generate_launch_description():
	return LaunchDescription([
		Node(
			package='intrusion',
			executable='monitor',
		),
		Node(
			package='obstacles',
			executable='detector',
			namespace='north',
			parameters=[
				{"obs_angle_min"},
				{"obs_angle_max"},
				{"obs_threshold":  2.0}],
			remappings=[("obstacle", "/north/obstacle")]
		),
		Node(
			package='persons',
			executable='detector',
			namespace='west',
			parameters=[
				{"obs_angle_min"},
				{"obs_angle_max"},
				{"obs_threshold":  2.0}],
			remappings=[("obstacle", "/west/obstacle")]
		), 
		Node(
			package='persons',
			executable='detector',
			namespace='northeast',
			parameters=[
				{"obs_angle_min"},
				{"obs_angle_max"},
				{"obs_threshold":  2.0}],
			remappings=[("obstacle", "/northeast/obstacle")]
		),
		Node(
			package='persons',
			executable='detector',
			namespace='northwest',
			parameters=[
				{"obs_angle_min"},
				{"obs_angle_max"},
				{"obs_threshold":  2.0}],
			remappings=[("obstacle", "/northwest/obstacle")]
		),
		Node(
			package='persons',
			executable='detector',
			namespace='east',
			parameters=[
				{"obs_angle_min"},
				{"obs_angle_max"},
				{"obs_threshold":  2.0}],
			remappings=[("obstacle", "/east/obstacle")]
		),
		Node(
			package='persons',
			executable='detector',
			namespace='southwest',
			parameters=[
				{"obs_angle_min"},
				{"obs_angle_max"},
				{"obs_threshold":  2.0}],
			remappings=[("obstacle", "/southwest/obstacle")]
		),
		Node(
			package='persons',
			executable='detector',
			namespace='southeast',
			parameters=[
				{"obs_angle_min"},
				{"obs_angle_max"},
				{"obs_threshold":  2.0}],
			remappings=[("obstacle", "/southeast/obstacle")]
		),
		Node(
			package='persons',
			executable='detector',
			namespace='south',
			parameters=[
				{"obs_angle_min"},
				{"obs_angle_max"},
				{"obs_threshold":  2.0}],
			remappings=[("obstacle", "/south/obstacle")]
		),
	])
