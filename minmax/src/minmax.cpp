#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

std::vector<int> numbers;
std::map<int, int> dic;
int max = 0;
std::vector<int> minmax;

rclcpp::Publisher<std_msgs::msg::Int32MultiArray>::SharedPtr publisher;

void topic_callback(const std_msgs::msg::Int32::SharedPtr msg)
{	
	numbers.push_back(msg->data);
	int number = msg->data;
	int min = number;
	numbers[number]++;
	for (auto i : dic) {
		if (i.second > max) {
			max = i.second;
		}
	}

	for (auto i : dic) {
		if (i.second < min) {
			min = i.first;
		}
	}

	std_msgs::msg::Int32MultiArray minmax_msg;
  minmax_msg.data = numbers[number];
	publisher->publish(minmax_msg);
}

int main(int argc, char * argv[])
{
	rclcpp::init(argc, argv);
	auto node = rclcpp::Node::make_shared("minmax");
	auto subscription = 
		node->create_subscription<std_msgs::msg::Int32>("number", 10, topic_callback);
	publisher = node->create_publisher<std_msgs::msg::Int32MultiArray>("minmax", 10);
	rclcpp::spin(node);
 	rclcpp::shutdown();
  return 0;
}


