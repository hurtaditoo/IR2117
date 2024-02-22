#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include <iostream>
#include <vector>

std::vector<int> numbers;

void topic_callback(const std_msgs::msg::Int32::SharedPtr msg)
{
	numbers.push_back(msg->data);
  std::sort(numbers.begin(), numbers.end());
  for (std::size_t i=0; i < numbers.size(); i++) {
  	std::cout << numbers[i] << " ";
  }
  std::cout << std::endl; 
}

int main(int argc, char * argv[])
{
	rclcpp::init(argc, argv);
	auto node = rclcpp::Node::make_shared("subscriber");
	auto subscription = 
		node->create_subscription<std_msgs::msg::Int32>("number", 10, topic_callback);
	rclcpp::spin(node);
 	rclcpp::shutdown();
  return 0;
}

