#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "example_interfaces/msg/bool.hpp"
#include <cstdlib>
#include <ctime>


using namespace std::chrono_literals;

bool obstacle_front = false;
bool obstacle_left = false;
bool obstacle_right = false;

enum State {
    forward,
    turn_left,
    turn_right
};

State state = forward;

void callback_front(const example_interfaces::msg::Bool::SharedPtr msg)
{
	obstacle_front = msg->data;
}

void callback_left(const example_interfaces::msg::Bool::SharedPtr msg)
{
	obstacle_left = msg->data;
}

void callback_right(const example_interfaces::msg::Bool::SharedPtr msg)
{
	obstacle_right = msg->data;
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("avoidance");
    auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
    auto subs_front = node->create_subscription<example_interfaces::msg::Bool>("/front/obstacle", 10, callback_front);
    auto subs_left = node->create_subscription<example_interfaces::msg::Bool>("/left/obstacle", 10, callback_left);
    auto subs_right = node->create_subscription<example_interfaces::msg::Bool>("/right/obstacle", 10, callback_right);
    
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    int random;

    geometry_msgs::msg::Twist message;
    rclcpp::WallRate loop_rate(50ms);
   
	while (rclcpp::ok()) 
	{
		random = std::rand() % 2;
		switch (state) 
		{
			case forward:				
				message.linear.x = 0.3;
				message.angular.z = 0.0;
				if (obstacle_front) {
					if (obstacle_left && !obstacle_right) {
						state = turn_right;
					} else if (obstacle_right && !obstacle_left) {
						state = turn_left;
					} else
					{
						if (random) state = turn_left;
						if (!random) state = turn_right;
					}
				}
				break;
				
			case turn_left:		
				message.linear.x = 0.0;
				message.angular.z = 0.3;
				if (!obstacle_front) {
					state = forward;
				}
				break;
				
			case turn_right:			
				message.linear.x = 0.0;
				message.angular.z = -0.3;
				if (!obstacle_front) {
						state = forward;
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
