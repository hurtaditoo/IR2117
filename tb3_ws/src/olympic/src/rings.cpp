#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <cmath> 

double radius;
double angular_speed;
double linear_speed;

using namespace std::chrono_literals;

int main(int argc, char * argv[])
{
 rclcpp::init(argc, argv);
 auto node = rclcpp::Node::make_shared("rings");
 auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);

 node->declare_parameter("radius", 1.0);
 node->declare_parameter("linear_speed", 1.0);
 node->declare_parameter("angular_speed", 1.0);
 radius = node->get_parameter("radius").get_parameter_value().get<double>();
 linear_speed = node->get_parameter("linear_speed").get_parameter_value().get<double>();
 angular_speed = node->get_parameter("angular_speed").get_parameter_value().get<double>();

 geometry_msgs::msg::Twist message;
 rclcpp::WallRate loop_rate(10ms);

 int k=0;
 double m = (2 * M_PI * radius) / 0.01;
 while (rclcpp::ok() && k<m) {
   k++;
   message.linear.x = 1.0;
   message.angular.z = linear_speed / radius;
   publisher->publish(message);
   rclcpp::spin_some(node);
   loop_rate.sleep();
 }
 
 // Send zero velocity to topic 
 message.linear.x = 0;
 message.angular.z = 0;
 publisher->publish(message);
    
 rclcpp::shutdown();
 return 0;
}

