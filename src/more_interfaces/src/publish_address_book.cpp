#include <chrono>
#include <memory>
#include "userdefined_modbus_library.hpp"
#include "std_msgs/msg/string.hpp"
#include "rclcpp/rclcpp.hpp"                                                      // including necessary libraries
// #include "more_interfaces/msg/address_book.hpp"                                   // including custom made message library
#include "more_interfaces/msg/nested_book.hpp"

using namespace std::chrono_literals;

vector<int>x={245,254,265};
// modbus_implementation_class m("127.0.0.1", x,"TCP", 502);

modbus_implementation_class m("/dev/pts/3", x,"RTU", 9600, 'N', 8,1);
class AddressBookPublisher : public rclcpp::Node                                  // message publisher class inherited from node class of rclcpp library
{
  public:
    AddressBookPublisher(): Node("address_book_publisher")
    {
      address_book_publisher_ =                                                   // creating message publisher of custom message type that will publish to the topic "address_book" 
      this->create_publisher<more_interfaces::msg::NestedBook>("address_book", 10);
      timer_ = this->create_wall_timer(500ms, std::bind(&AddressBookPublisher::timer_callback, this));                        // Repeater
    }

  private:
    void timer_callback()
      {
        m.read_modbus_fun();
        auto message = more_interfaces::msg::NestedBook();                     // definfing message type
        message.addr.name = "Itachi Uchiha"; 
        message.addr.clan = "Uchiha";                                                // definging message variables
        message.addr.age = 21;
        message.addr.address = "Village Hidden in the Leaves";
        message.addr.designation = "Hokage";
        message.addr.reading1= m.reading1;
        // std::cout << "\n \n"<<m.reading1<<"\n \n";
        std::cout << "I Lord Fifth Kakashi Hatake here by announce " << message.addr.name <<" of clan "<<message.addr.clan<<
        " as the youngest "<<message.addr.designation<<" of Village Hidden in the Leaves to be made "<<message.addr.designation<<" at the age of "<<message.addr.age<<"\n";
        address_book_publisher_ -> publish(message);
      }
    rclcpp::Publisher<more_interfaces::msg::NestedBook>::SharedPtr address_book_publisher_; 
    rclcpp::TimerBase::SharedPtr timer_;
};


int main(int argc, char * argv[])
{
  // vector<int>x={245,254,265};
  // modbus_implementation_class m("127.0.0.1", x,"TCP", 504);
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<AddressBookPublisher>());                         // to keep publishing
  rclcpp::shutdown();   
  return 0;
}