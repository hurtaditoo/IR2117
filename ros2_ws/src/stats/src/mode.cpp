#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

"""std::vector<float> numbers;
std::map<int, int> dic;
int max = 0;
std::vector<int> mode;

rclcpp::Publisher<std_msgs::msg::Float32MultiArray>::SharedPtr publisher;

void topic_callback(const std_msgs::msg::Int32::SharedPtr msg)
{
	numbers.push_back(msg->data);
	int number = msg->data;
	numbers[number]++;
	for (auto i : dic) {
		if (i.second > max) {
			max = i.second;
		}
	}

	for (auto i : dic) {
		if (i.second == max) {
			mode.push_back(i.first);
		}
	}
	std_msgs::msg::Float32MultiArray mode_msg;
  mode_msg.data = mode;
  publisher->publish(mode_msg);
}

int main(int argc, char * argv[])
{
	rclcpp::init(argc, argv);
	auto node = rclcpp::Node::make_shared("mode");
	auto subscription =
		node->create_subscription<std_msgs::msg::Int32>("number", 10, topic_callback);
  publisher = node->create_publisher<std_msgs::msg::Float32MultiArray>("mode", 10);
	rclcpp::spin(node);
 	rclcpp::shutdown();
  return 0;
}"""

