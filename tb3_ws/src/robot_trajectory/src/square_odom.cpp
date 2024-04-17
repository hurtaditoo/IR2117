#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "nav_msgs/msg/odometry.hpp"

#include <iostream>
#include <cmath>

using namespace std::chrono_literals;

double global_x = 0.0, global_y = 0.0;
double angle_x = 0.0, angle_y = 0.0, angle_z = 0.0, angle_w = 0.0, yaw = 0.0;
double initial_x = 0.0, initial_y = 0.0, initial_yaw = 0.0;
double distance_x = 0.0, distance_y = 0.0, angle_difference = 0.0;
double distance = 0.0;

void odomCallback(const nav_msgs::msg::Odometry::SharedPtr msg)
{
    global_x = msg->pose.pose.position.x;
    global_y = msg->pose.pose.position.y;
    angle_x = msg->pose.pose.orientation.x;
    angle_y = msg->pose.pose.orientation.y;     
    angle_z = msg->pose.pose.orientation.z;
    angle_w = msg->pose.pose.orientation.w;
    yaw = std::atan2(2 * (angle_z * angle_w + angle_x * angle_y), 1 -2 * (angle_y * angle_y + angle_z * angle_z));
    
    if (initial_x == 0.0 && initial_y == 0.0 && initial_yaw == 0.0) {
        initial_x = global_x;
        initial_y = global_y;
        initial_yaw = yaw;
        std::cout << "Initial Position (x, y): (" << initial_x << ", " << initial_y << "), Initial Angle: " << initial_yaw << std::endl;
    }
    
    distance_x = global_x - initial_x;
    distance_y = global_y - initial_y;
    distance = sqrt(std::pow(distance_x, 2) + std::pow(distance_y, 2));
    angle_difference = yaw - initial_yaw;
    if (angle_difference > M_PI) {
        angle_difference -= 2 * M_PI;
    } else if (angle_difference < -M_PI) {
        angle_difference += 2 * M_PI;
    }
    
    std::cout << "Position (x, y): (" << global_x << ", " << global_y << "), Angle: " << yaw << ", Distance from initial position: (" << distance_x << ", " << distance_y << "), Angle difference from initial: " << angle_difference << std::endl;
}

int main(int argc, char *argv[])
{
	rclcpp::init(argc, argv);
	auto node = rclcpp::Node::make_shared("square");
	auto subscription = node->create_subscription<nav_msgs::msg::Odometry>("odom", 10, odomCallback);
	auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
	
	node->declare_parameter("linear_speed", 0.1);
	node->declare_parameter("angular_speed", M_PI / 20);
	node->declare_parameter("square_length", 1.00);
	geometry_msgs::msg::Twist message;
	rclcpp::WallRate loop_rate(10ms);
	
	double linear_speed = node->get_parameter("linear_speed").get_parameter_value().get<double>();
	double angular_speed = node->get_parameter("angular_speed").get_parameter_value().get<double>();
	double square_length = node->get_parameter("square_length").get_parameter_value().get<double>();

	for(int j=0; j<4; j++)
	{
		initial_x = global_x;
    initial_y = global_y;
    initial_yaw = yaw;
    distance = 0.0;
    
		while (rclcpp::ok() && distance < square_length) 
		{
			message.linear.x = linear_speed;
			publisher->publish(message);
			rclcpp::spin_some(node);
			loop_rate.sleep();
		}
		
		initial_x = global_x;
    initial_y = global_y;
    initial_yaw = yaw;
    distance = 0.0;

		while (rclcpp::ok() && angle_difference < M_PI/2)
		{
			message.linear.x = 0;
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
