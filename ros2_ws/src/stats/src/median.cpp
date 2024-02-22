#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/float32.hpp"
#include <iostream>
#include <vector>

double median;

std::vector<int> numbers;
rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher;

void topic_callback(const std_msgs::msg::Int32::SharedPtr msg)
{
	numbers.push_back(msg->data);
  std::sort(numbers.begin(), numbers.end());
  for (std::size_t i=0; i < numbers.size(); i++) {
  	std::cout << numbers[i];
  }

  if (numbers.size() % 2 == 0) {
      median = (numbers[numbers.size() / 2 - 1] + numbers[numbers.size() / 2]) / 2.0;
  } else {
      median = numbers[numbers.size() / 2];
  }

	std_msgs::msg::Float32 median_msg;
  median_msg.data = median;
  publisher->publish(median_msg);
}

int main(int argc, char * argv[])
{
	rclcpp::init(argc, argv);
	auto node = rclcpp::Node::make_shared("median");
	auto subscription = 
		node->create_subscription<std_msgs::msg::Int32>("number", 10, topic_callback);
  publisher = node->create_publisher<std_msgs::msg::Float32>("median", 10);
	rclcpp::spin(node);
 	rclcpp::shutdown();
  return 0;
}

