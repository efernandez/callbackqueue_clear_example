
#include <ros/callback_queue.h>
#include <ros/ros.h>
#include <std_msgs/Int8.h>

void subscriberCallback(const std_msgs::Int8::ConstPtr& msg)
{
  std::cout << "Callback " << static_cast<int>(msg->data) << std::endl;

  // clear callback queue
  ros::getGlobalCallbackQueue()->clear();
}

void publish(ros::Publisher& publisher, const size_t n = 10)
{
  for (size_t i = 0; i < n; ++i)
  {
    std_msgs::Int8 msg;
    msg.data = i;

    publisher.publish(msg);
  }
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "callbackqueue_clear_example");

  ros::NodeHandle nh;

  const std::string topic = "test_topic";

  auto subscriber = nh.subscribe(topic, 1, subscriberCallback);
  auto publisher = nh.advertise<std_msgs::Int8>(topic, 1);

  // subscriber is working => "Callback" will be printed
  std::cout << "will call callback" << std::endl;
  publish(publisher);
  ros::spinOnce();

  // publish message => subscriber queue is full
  publish(publisher);

  // subscriber is broken => no "Callback" will be printed any more
  std::cout << "will not call callback" << std::endl;
  publish(publisher);
  ros::spinOnce();

  // resubscribe
  subscriber = nh.subscribe(topic, 1, subscriberCallback);

  // working again => "Callback" will be printed
  std::cout << "will call callback" << std::endl;
  publish(publisher);
  ros::spinOnce();

  return EXIT_SUCCESS;
}
