#include <chrono>
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/odometry.hpp"

using namespace std::chrono_literals;

constexpr double x_start = -1;
constexpr double y_start = 3;
constexpr double z_start = 0;
constexpr double w_start = 1;
double v_x, w_z;
int t = 0;

void odom_callback(const nav_msgs::msg::Odometry::SharedPtr msg) {
    v_x = msg->twist.twist.linear.x;
    w_z = msg->twist.twist.angular.z;
}

int main(int argc, char * argv[]) {
rclcpp::init(argc, argv);
auto node = rclcpp::Node::make_shared("publisher");
auto publisher =
node->create_publisher<geometry_msgs::msg::PoseStamped>("/goal_pose", 10);
auto subscription =
node->create_subscription<nav_msgs::msg::Odometry>("odom", 10,
odom_callback);

geometry_msgs::msg::PoseStamped message;

message.pose.position.x = x_start;
message.pose.position.y = y_start;
message.pose.position.z = z_start;
message.pose.orientation.x = 0;
message.pose.orientation.y = 0;
message.pose.orientation.z = 0;
message.pose.orientation.w = w_start;

rclcpp::WallRate loop_rate(500ms);
rclcpp::WallRate poses(3);

std::vector<geometry_msgs::msg::PoseStamped> goals;
goals.push_back(message); 

geometry_msgs::msg::PoseStamped goal2;

goal2.pose.position.x = 3 ;
goal2.pose.position.y =4.5;
goal2.pose.position.z = 0;
goal2.pose.orientation.x = 0;
goal2.pose.orientation.y = 0;
goal2.pose.orientation.z = 0;
goal2.pose.orientation.w = 1;
goals.push_back(goal2); // 2

geometry_msgs::msg::PoseStamped goal3;

goal3.pose.position.x =8;
goal3.pose.position.y = -1.5;
goal3.pose.position.z = 0;
goal3.pose.orientation.x = 0;
goal3.pose.orientation.y = 0;
goal3.pose.orientation.z = 0;
goal3.pose.orientation.w = 1;
goals.push_back(goal3); // 3

geometry_msgs::msg::PoseStamped goal4;

goal4.pose.position.x = -5 ;
goal4.pose.position.y = -1.5 ;
goal4.pose.position.z = 0;
goal4.pose.orientation.x = 0;
goal4.pose.orientation.y = 0;
goal4.pose.orientation.z = 0;
goal4.pose.orientation.w = 1;
goals.push_back(goal4); //4

geometry_msgs::msg::PoseStamped goal5;

goal5.pose.position.x = 1;
goal5.pose.position.y = 0;
goal5.pose.position.z = 0;
goal5.pose.orientation.x = 0;
goal5.pose.orientation.y = 0;
goal5.pose.orientation.z = 0;
goal5.pose.orientation.w = 1;

goals.push_back(goal5); //5
size_t goal_index = 0;
while (true) {
    publisher->publish(goals[goal_index]);
    rclcpp::spin_some(node);
    loop_rate.sleep();
    t++;
    if (v_x < 0.005 && t >= 100)
    {
        poses.sleep();
        goal_index++;
        t = 0;
        if (goal_index >= goals.size()) {
            break;
        }
    }
}
rclcpp::shutdown();
return 0;
}
