#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/srv/set_pen.hpp"
#include "turtlesim/srv/teleport_absolute.hpp"
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
 
 // Call service Setpen 
 
 auto client_setpen = node->create_client<turtlesim::srv::SetPen>("/turtle1/set_pen");
 auto request_setpen = std::make_shared<turtlesim::srv::SetPen::Request>();
 
 request_setpen->r = 0;
 request_setpen->g = 0;
 request_setpen->b = 255;
 request_setpen->width = 4;
 request_setpen->off = true; // Si está en true no dibuja, en false dibuja
 
 while (!client_setpen->wait_for_service(1s)) {
  if (!rclcpp::ok()) {
   RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
   return 0;
  }
   RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Waiting for the setpen service to be available...");
 } 

 auto result_setpen = client_setpen->async_send_request(request_setpen);
 
 // Wait for the result of SetPen.
 if (rclcpp::spin_until_future_complete(node, result_setpen) == rclcpp::FutureReturnCode::SUCCESS)
 {
   RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Works well");
 } else {
   RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service SetPen");
 }
 
 // Call service teleport_absolute 
 
 auto client_teleport = node->create_client<turtlesim::srv::TeleportAbsolute>("/turtle1/teleport_absolute");
 auto request_teleport = std::make_shared<turtlesim::srv::TeleportAbsolute::Request>();
    
 request_teleport->x = 3;
 request_teleport->y = 7;
 request_teleport->theta = 0;
 
 while (!client_teleport->wait_for_service(1s)) {
  if (!rclcpp::ok()) {
   RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
   return 0;
  }
   RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Waiting for the teleport service to be available...");
 }  

 auto result_teleport = client_teleport->async_send_request(request_teleport); 
 
 // Wait for the result of Teleport.
 if (rclcpp::spin_until_future_complete(node, result_teleport) == rclcpp::FutureReturnCode::SUCCESS)
 {
   RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Works well");
 } else {
   RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service Teleport Absolute");
 }
 
 // Change off to false after teleportation
 request_setpen->off = false;
 result_setpen = client_setpen->async_send_request(request_setpen);
    
 
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
