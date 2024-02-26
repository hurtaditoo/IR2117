#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

std::vector<int> numbers;
std::map<int, int> dic;

rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher;

void topic_callback(const std_msgs::msg::Int32::SharedPtr msg)
{	
	numbers.push_back(msg->data);
	int number = msg->data;
	int min = number;
	for (std::size_t i=0; i < numbers.size(); i++) {
  	if (dic[numbers[i]] < min) {
			min = numbers[number]++;
		}
	}

	std_msgs::msg::Int32 min_msg;
  min_msg.data = min;
	publisher->publish(min_msg);
}

int main(int argc, char * argv[])
{
	rclcpp::init(argc, argv);
	auto node = rclcpp::Node::make_shared("min");
	auto subscription = 
		node->create_subscription<std_msgs::msg::Int32>("number", 10, topic_callback);
	publisher = node->create_publisher<std_msgs::msg::Int32>("min", 10);
	rclcpp::spin(node);
 	rclcpp::shutdown();
  return 0;
}


