#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include <iostream>
#include <vector>

std::vector<int> numbers;
//std::shared_ptr< rclcpp::Publisher<std_msgs::msg::Int32> > publisher;

void topic_callback(const std_msgs::msg::Int32::SharedPtr msg)
{	
	numbers.push_back(msg->data);
	for (std::size_t i=0; i < numbers.size(); i++) {
  	std::cout << numbers[i] << std::endl;
	}
}

int main(int argc, char * argv[])
{
	rclcpp::init(argc, argv);
	auto node = rclcpp::Node::make_shared("subscriber");
	auto subscription = 
		node->create_subscription<std_msgs::msg::Int32>("number", 10, topic_callback);
	//publisher = node->create_publisher<std_msgs::msg::Int32>("datos", 10);
	rclcpp::spin(node);
 	rclcpp::shutdown();
  return 0;
}


