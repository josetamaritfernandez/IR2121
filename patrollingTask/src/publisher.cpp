#include <chrono>
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/odometry.hpp"


using namespace std::chrono_literals;
double x,y,z,or_x,or_y,or_z,or_w, v_x,v_y,v_z,w_x,w_y,w_z;
int t=0;
void odom_callback(nav_msgs::msg::Odometry::SharedPtr msg){
    v_x = msg->twist.twist.linear.x;
    w_z = msg->twist.twist.angular.z;
}
int main(int argc, char * argv[])
{
rclcpp::init(argc, argv);
auto node = rclcpp::Node::make_shared("publisher");
auto publisher =
node->create_publisher<geometry_msgs::msg::PoseStamped>("/goal_pose", 10);
auto subscription =
node->create_subscription<nav_msgs::msg::Odometry>("odom", 10,odom_callback);
geometry_msgs::msg::PoseStamped message;
nav_msgs::msg::Odometry odometry;
rclcpp::WallRate loop_rate(500ms);
rclcpp::WallRate poses(4);
message.pose.position.x=-1;
message.pose.position.y=3;
message.pose.position.z=0;
message.pose.orientation.x=0;
message.pose.orientation.y=0;
message.pose.orientation.z=0;
message.pose.orientation.w=1;


while (v_x > 0.001 || w_z > 0.001 || t<=100) {
    publisher->publish(message);
    rclcpp::spin_some(node);
    loop_rate.sleep();
    t++;
    if(v_x<0.005 && v_y<0.005 && t==100){
        poses.sleep();
        break;
    }
}
rclcpp::shutdown();
return 0;
}