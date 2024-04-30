#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

#include <iostream>
#include <cmath>

using namespace std::chrono_literals;

int main(int argc, char *argv[])
{
	rclcpp::init(argc, argv);
	auto node = rclcpp::Node::make_shared("square");
	auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
	node->declare_parameter("linear_speed", 0.8);
	node->declare_parameter("angular_speed", 0.5);
	node->declare_parameter("segment_size", 0.5);
	node->declare_parameter("number_segments", 4);
	geometry_msgs::msg::Twist message;
	rclcpp::WallRate loop_rate(10ms);
	
	double linear_speed = node->get_parameter("linear_speed").get_parameter_value().get<double>();
	double angular_speed = node->get_parameter("angular_speed").get_parameter_value().get<double>();
	double segment_size = node->get_parameter("segment_size").get_parameter_value().get<double>();
	int number_segments = node->get_parameter("number_segments").get_parameter_value().get<int>();

	for(int j=0; j<number_segments; j++)
	{
		int i=0;
		double n = segment_size / (0.01 * linear_speed);
		while (rclcpp::ok() && i<n) {
			i++;
			message.linear.x = linear_speed;
			publisher->publish(message);
			rclcpp::spin_some(node);
			loop_rate.sleep();
		}

		message.linear.x = 0;
		int k=0;
		double m = ((360 * M_PI / 180) / number_segments) / (0.01 * angular_speed);
		while (rclcpp::ok() && k<m) {
			k++;
			message.angular.z = angular_speed;
			publisher->publish(message);
			rclcpp::spin_some(node);
			loop_rate.sleep();
		}
		message.angular.z = 0;
	}

	publisher->publish(message);
	rclcpp::shutdown();
	return 0;
}
