#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "more_interfaces/msg/nested_book.hpp"                                  // CHANGE
using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("minimal_subscriber")
  {
    subscription_ = this->create_subscription<more_interfaces::msg::NestedBook>(          // CHANGE
      "address_book", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const more_interfaces::msg::NestedBook::SharedPtr msg) const       // CHANGE
  {

    std::cout<<(msg->addr.name)<<"\n";                                                                  // CHANGE
  }
  rclcpp::Subscription<more_interfaces::msg::NestedBook>::SharedPtr subscription_;       // CHANGE
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
