
#include <ros/callback_queue.h>
#include <ros/ros.h>
#include <std_msgs/Int8.h>

void subscriberCallback(const std_msgs::Int8::ConstPtr& msg)
{
  std::cout << "Callback" << std::endl;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "callbackqueue_clear_example");

  ros::CallbackQueue cq;

  ros::NodeHandle nh;
  nh.setCallbackQueue(&cq);

  const std::string topic = "test_topic";

  auto subscriber = nh.subscribe(topic, 1, subscriberCallback);
  auto publisher = nh.advertise<std_msgs::Int8>(topic, 1);

  // subscriber is working => "Callback" will be printed
  std::cout << "will call callback" << std::endl;
  publisher.publish(std_msgs::Int8::Ptr(new std_msgs::Int8()));
  cq.callAvailable();

  // publish message => subscriber queue is full
  publisher.publish(std_msgs::Int8::Ptr(new std_msgs::Int8()));
  // clear callback queue
  cq.clear();

  // subscriber is broken => no "Callback" will be printed any more
  std::cout << "will not call callback" << std::endl;
  publisher.publish(std_msgs::Int8::Ptr(new std_msgs::Int8()));
  cq.callAvailable();

  // resubscribe
  subscriber = nh.subscribe(topic, 1, subscriberCallback);

  // working again => "Callback" will be printed
  std::cout << "will call callback" << std::endl;
  publisher.publish(std_msgs::Int8::Ptr(new std_msgs::Int8()));
  cq.callAvailable();

  return EXIT_SUCCESS;
}
