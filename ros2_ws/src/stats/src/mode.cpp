#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/float32.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

std::vector<float> numbers;
std::map<int, int> dic;

rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher;

void topic_callback(const std_msgs::msg::Int32::SharedPtr msg)
{
	int number = msg->data;
	for (std::size_t i=0; i < numbers.size(); i++) {
		numbers[number]++;
	}

	std_msgs::msg::Float32 mode_msg;
  mode_msg.data = numbers[number];
  publisher->publish(mode_msg);
}

int main(int argc, char * argv[])
{
	rclcpp::init(argc, argv);
	auto node = rclcpp::Node::make_shared("mode");
	auto subscription = 
		node->create_subscription<std_msgs::msg::Int32>("number", 10, topic_callback);
  publisher = node->create_publisher<std_msgs::msg::Float32>("mode", 10);
	rclcpp::spin(node);
 	rclcpp::shutdown();
  return 0;
}

