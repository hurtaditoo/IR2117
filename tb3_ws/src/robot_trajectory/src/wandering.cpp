#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include <vector>

using namespace std::chrono_literals;

std::vector<float> vector;
float min_09, min_359;
bool obstacle = false;
float angular;
bool turn_left = false, turn_right = false;

void topic_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg)
{
	vector = msg -> ranges;
	
	for (int i=0; i<10; i++) 
	{
    min_09 = std::min(min_09, vector[i]);
  }

  for (int i=350; i<360; i++) 
	{
    min_359 = std::min(min_359, vector[i]);
  }
	
	if (vector[0] < 1){
    	obstacle = true;
  } else {
    	obstacle = false;
	}

	std::cout << "Minimum value[0-9]: " << min_09 << std::endl;
  std::cout << "Minimum value[350-359]: " << min_359 << std::endl;

	std::cout << vector[0] << std::endl;
}

int main(int argc, char *argv[])
{
	rclcpp::init(argc, argv);
	auto node = rclcpp::Node::make_shared("publisher");
	auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
  	auto subscription = node->create_subscription<sensor_msgs::msg::LaserScan>(
    "scan", 10, topic_callback);
	geometry_msgs::msg::Twist message;
	rclcpp::WallRate loop_rate(10ms);
	
	while (rclcpp::ok())
	{
		
		if (!turn_left && !turn_left) 
		{
			while (rclcpp::ok() && obstacle==false) 
			{
				message.linear.x = 0.25;
				message.angular.z = 0;
				publisher->publish(message);
				rclcpp::spin_some(node);
				loop_rate.sleep();
			}
			
			if (min_09 > min_359) {
		 		turn_left = true;
	 		} else {
	 			turn_right = true;
			}
			
		}
		
		if (turn_left)
		{

			while (rclcpp::ok() && obstacle==true) 
			{
				message.linear.x = 0;
				message.angular.z = angular;
				publisher->publish(message);
				rclcpp::spin_some(node);
				loop_rate.sleep();
			}
			turn_left = false;
		}
		
		if (turn_right)
		{

			while (rclcpp::ok() && obstacle==true) 
			{
				message.linear.x = 0;
				message.angular.z = angular;
				publisher->publish(message);
				rclcpp::spin_some(node);
				loop_rate.sleep();
			}
			turn_right = false;
		}
	}
	
	message.angular.z = 0;
	publisher->publish(message);
	rclcpp::spin_some(node);
	loop_rate.sleep();

	rclcpp::shutdown();
	return 0;
}
