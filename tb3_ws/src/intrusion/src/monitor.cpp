#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "example_interfaces/msg/bool.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/transform_broadcaster.h"
#include "nav_msgs/msg/odometry.hpp"

using namespace std::chrono_literals;

bool north = false, northeast = false, northwest = false, west = false, east = false, southwest = false, southeast = false, south = false;

double current_angle = 0.0;

enum State {
    stay,
    turn_to_southwest,
    turn_to_south,
    turn_to_southeast,
    turn_to_east,
    turn_to_northeast,
    turn_to_northwest,
    turn_to_north,
    turn_to_west
};

State state = stay;

void callback_north(const example_interfaces::msg::Bool::SharedPtr msg)
{
	north = msg->data;
}

void callback_northwest(const example_interfaces::msg::Bool::SharedPtr msg)
{
	northwest = msg->data;
}

void callback_northeast(const example_interfaces::msg::Bool::SharedPtr msg)
{
	northeast = msg->data;
}

void callback_west(const example_interfaces::msg::Bool::SharedPtr msg)
{
	west = msg->data;
}

void callback_east(const example_interfaces::msg::Bool::SharedPtr msg)
{
	east = msg->data;
}

void callback_southwest(const example_interfaces::msg::Bool::SharedPtr msg)
{
	southwest = msg->data;
}

void callback_southeast(const example_interfaces::msg::Bool::SharedPtr msg)
{
	southeast = msg->data;
}

void callback_south(const example_interfaces::msg::Bool::SharedPtr msg)
{
	south = msg->data;
}

void odomCallback(const nav_msgs::msg::Odometry::SharedPtr msg)
{
    double roll, pitch, yaw;
    tf2::Quaternion q(
        msg->pose.pose.orientation.x,
        msg->pose.pose.orientation.y,
        msg->pose.pose.orientation.z,
        msg->pose.pose.orientation.w);

    q.setRPY(roll, pitch, yaw);
    current_angle = yaw;
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("follower");
    auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
    auto subs_north = node->create_subscription<example_interfaces::msg::Bool>("/north", 10, callback_north);
    auto subs_northeast = node->create_subscription<example_interfaces::msg::Bool>("/northeast", 10, callback_northeast);
    auto subs_northwest = node->create_subscription<example_interfaces::msg::Bool>("/northwest", 10, callback_northwest);
    auto subs_west = node->create_subscription<example_interfaces::msg::Bool>("/west", 10, callback_west);
    auto subs_east = node->create_subscription<example_interfaces::msg::Bool>("/east", 10, callback_east);
    auto subs_south = node->create_subscription<example_interfaces::msg::Bool>("/south", 10, callback_south);
    auto subs_southwest = node->create_subscription<example_interfaces::msg::Bool>("/southwest", 10, callback_southwest);
    auto subs_southeast = node->create_subscription<example_interfaces::msg::Bool>("/southeast", 10, callback_southeast);
    auto subscription = node->create_subscription<nav_msgs::msg::Odometry>("odom", 10, odomCallback);

    geometry_msgs::msg::Twist message;
    rclcpp::WallRate loop_rate(50ms);
   
    while (rclcpp::ok()) 
    {
        switch (state) 
        {
            case stay:
                message.linear.x = 0.0;
                message.angular.z = 0.0;
                if (north) {state = turn_to_north;}
                if (south) {state = turn_to_south;}
                if (west) {state = turn_to_west;}
                if (east) {state = turn_to_east;}
                if (northeast) {state = turn_to_northeast;}
                if (northwest) {state = turn_to_northwest;}
                if (southeast) {state = turn_to_southeast;}
                if (southwest) {state = turn_to_southwest;}
                break;

            case turn_to_north:				
                message.linear.x = 0.0;
                message.angular.z = current_angle;    // Quiero que el ángulo de giro sea controlado por odom
                if (!north) {
                    state = stay;
                }
                break;
                
            case turn_to_west:		
                message.linear.x = 0.0;
                message.angular.z = current_angle;
                if (!west) {
                    state = stay;
                }
                break;
                
            case turn_to_east:			
                message.linear.x = 0.0;
                message.angular.z = current_angle;
                if (!east) {
                    state = stay;
                }
                break;
            
            case turn_to_south:
                message.linear.x = 0.0;
                message.angular.z = current_angle;
                if (!south) {
                    state = stay;
                }
                break;

            case turn_to_southeast:
                message.linear.x = 0.0;
                message.angular.z = current_angle;
                if (!southeast) {
                    state = stay;
                }
                break;
            
            case turn_to_southwest:
                message.linear.x = 0.0;
                message.angular.z = current_angle;
                if (!southwest) {
                    state = stay;
                }
                break;

            case turn_to_northeast:
                message.linear.x = 0.0;
                message.angular.z = current_angle;
                if (!northeast) {
                    state = stay;
                }
                break;

            case turn_to_northwest:
                message.linear.x = 0.0;
                message.angular.z = current_angle;
                if (!northwest) {
                    state = stay;
                }
                break;
        }
        
        publisher->publish(message);
        rclcpp::spin_some(node);
        loop_rate.sleep();
    }

    rclcpp::shutdown();
    return 0;
}
