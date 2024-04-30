#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "example_interfaces/msg/bool.hpp"


using namespace std::chrono_literals;

bool person_front = false;
bool person_left = false;
bool person_right = false;

enum State {
    forward,
    turn_left,
    turn_right,
    stop
};

State state = forward;

void callback_front(const example_interfaces::msg::Bool::SharedPtr msg)
{
	person_front = msg->data;
}

void callback_left(const example_interfaces::msg::Bool::SharedPtr msg)
{
	person_left = msg->data;
}

void callback_right(const example_interfaces::msg::Bool::SharedPtr msg)
{
	person_right = msg->data;
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("follower");
    auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
    auto subs_front = node->create_subscription<example_interfaces::msg::Bool>("/front/person", 10, callback_front);
    auto subs_left = node->create_subscription<example_interfaces::msg::Bool>("/left/person", 10, callback_left);
    auto subs_right = node->create_subscription<example_interfaces::msg::Bool>("/right/person", 10, callback_right);

    geometry_msgs::msg::Twist message;
    rclcpp::WallRate loop_rate(50ms);
   
		while (rclcpp::ok()) 
		{
		    switch (state) 
			{
				case forward:				
					message.linear.x = 0.3;
					message.angular.z = 0.0;
					if (!person_front) {
						state = stop;
					}
					break;
					
				case turn_left:		
					message.linear.x = 0.0;
					message.angular.z = 0.3;
					if (person_front) {
						state = forward;
					}
                    else if (!person_left) {
                        state = stop;
                    }
					break;
					
				case turn_right:			
					message.linear.x = 0.0;
					message.angular.z = -0.3;
					if (person_front) {
						state = forward;
					}
                    else if (!person_right) {
                        state = stop;
                    }
					break;
                
                case stop:
                    message.linear.x = 0.0;
					message.angular.z = 0.0;
                    if (person_left) {
						turn_left;
					} else if (person_right) {
						turn_right;
					} else if (person_front) {
						forward;
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
