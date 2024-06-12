#include <chrono>
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_with_covariance_stamped.hpp"

using namespace std::chrono_literals;

constexpr double x_start = -1;
constexpr double y_start = 3;
constexpr double z_start = 0;
constexpr double w_start = 1;
double p_x, p_y;
int count = 0;

void odom_callback(const geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr msg) {
    p_x = msg->pose.pose.position.x;
    p_y = msg->pose.pose.position.y;
}

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("publisher");
    auto publisher = node->create_publisher<geometry_msgs::msg::PoseStamped>("/goal_pose", 10);
    auto subscription = node->create_subscription<geometry_msgs::msg::PoseWithCovarianceStamped>("/amcl_pose", 10, odom_callback);

    size_t goal_index = 0;

    std::vector<geometry_msgs::msg::PoseStamped> goals;
    
    geometry_msgs::msg::PoseStamped goal1;
    goal1.pose.position.x = x_start;
    goal1.pose.position.y = y_start;
    goal1.pose.position.z = z_start;
    goal1.pose.orientation.w = w_start;
    goals.push_back(goal1);

    geometry_msgs::msg::PoseStamped goal2;
    goal2.pose.position.x = 3;
    goal2.pose.position.y = 4.5;
    goal2.pose.position.z = 0;
    goal2.pose.orientation.w = 1;
    goals.push_back(goal2);

    geometry_msgs::msg::PoseStamped goal3;
    goal3.pose.position.x = 8;
    goal3.pose.position.y = -1.5;
    goal3.pose.position.z = 0;
    goal3.pose.orientation.w = 1;
    goals.push_back(goal3);

    geometry_msgs::msg::PoseStamped goal4;
    goal4.pose.position.x = -5;
    goal4.pose.position.y = -1.5;
    goal4.pose.position.z = 0;
    goal4.pose.orientation.w = 1;
    goals.push_back(goal4);

    geometry_msgs::msg::PoseStamped goal5;
    goal5.pose.position.x = 1;
    goal5.pose.position.y = 0;
    goal5.pose.position.z = 0;
    goal5.pose.orientation.w = 1;
    goals.push_back(goal5);

    rclcpp::WallRate loop_rate(500ms);

    while (rclcpp::ok() && goal_index < goals.size()) {
        publisher->publish(goals[goal_index]);
        loop_rate.sleep(); 
        count+=1;
        if (std::abs(p_x-goals[goal_index].pose.position.x)<0.5 && std::abs(p_y-goals[goal_index].pose.position.y)<0.5 && count>100){
            loop_rate.sleep(); 
            goal_index+=1;
            std::cout << "Pose reached"<< std::endl; 
            count=0;
        }

        rclcpp::spin_some(node);
    }

    rclcpp::shutdown();
    return 0;
}
