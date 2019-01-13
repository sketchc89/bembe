#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class PosePublisher : public rclcpp::Node
{
public:
	PosePublisher() : Node("pose_publisher"), count_(0)
	{
		publisher_ this->create_publisher<std_msgs::msg::String>("pose");
		timer_ = this->create_wall_timer(500ms, 
			std::bind(&PosePublisher::timer_callback, this));
	}
private:
	void timer_callback()
	{
		auto message = std_msgs::msg::String();
		message.data = "X: " + std::to_string(x_) + 
			     "\nY: " + std::to_string(y_) + 
			     "\nZ: " + std::to_string(z_) + "\n";
		RCLCPP_INFO(this->get_logger(), "Publishing '%s'", message.data.c_str());
		publisher_->publish(message);
	}
	rclcpp::TimerBase::SharedPtr timer_;
	rclcpp::Publisher<std_msgs:msg::String>::SharedPtr publisher_;
	int x_ = 0;
	int y_ = 0;
	int z_ = 0;
};

int main(int argc, char* argv[])
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<MinimalPublisher>());
	rclcpp::shutdown();
	return 0;
}
