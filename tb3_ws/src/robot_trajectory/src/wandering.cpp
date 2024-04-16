#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include <vector>

using namespace std::chrono_literals;

std::vector<float> vector;
float min;
bool stop = false;

void topic_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg)
{
	vector = msg -> ranges;
	
	for (int i=0; i<10; i++) 
	{
    	min = std::min(min, vector[i]);
    }

    for (int i=350; i<360; i++) 
	{
    	min = std::min(min, vector[i]);
    }
	
	if (vector[0] < 1){
    	stop = true;
    } else {
    	stop = false;
	}

	std::cout << "Minimum value: " << min << std::endl;

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
	
	while (rclcpp::ok() && stop==false) 
	{
		message.linear.x = 0.25;
		message.angular.z = 0;
		publisher->publish(message);
		rclcpp::spin_some(node);
		loop_rate.sleep();
	}
	
	message.linear.x = 0;
	publisher->publish(message);
	rclcpp::spin_some(node);
	loop_rate.sleep();

	while (rclcpp::ok() && stop==true) 
	{
		message.linear.x = 0;
		message.angular.z = 0.25;
		publisher->publish(message);
		rclcpp::spin_some(node);
		loop_rate.sleep();
	}
	
	message.angular.z = 0;
	publisher->publish(message);
	rclcpp::spin_some(node);
	loop_rate.sleep();

	rclcpp::shutdown();
	return 0;
}
