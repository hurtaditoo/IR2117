#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/float64.hpp"
#include <iostream>

double count = 0;
double mean = 0;
double sum = 0;

std::shared_ptr< rclcpp::Publisher<std_msgs::msg::Float64> > publisher;

void topic_callback(const std_msgs::msg::Int32::SharedPtr msg)
{
    count += 1;
    sum += msg->data;
    double mean = sum / count;
    std_msgs::msg::Float64 mean_msg;
    mean_msg.data = mean;
    publisher->publish(mean_msg);
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("mean");
    auto subscription = 
	node->create_subscription<std_msgs::msg::Int32>("number", 10, topic_callback);
    publisher = node->create_publisher<std_msgs::msg::Float64>("mean", 10);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
