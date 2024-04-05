#include <ros/ros.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <iostream>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>
int main(int argc, char** argv)
{
	ros::init(argc, argv, "image_send");
	ros::NodeHandle nh;
 	image_transport::ImageTransport it(nh);
	image_transport::Publisher pub = it.advertise("camera/image", 1);
	cv_bridge::CvImagePtr cv_ptr (new cv_bridge::CvImage);

	cv::Mat img(1024,1024,CV_8UC3,cv::Scalar(0,0,255));

	cv::waitKey(30);
	sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", img).toImageMsg();
	ros::Rate loop(10);
	ROS_INFO("antes do while");
	while(ros::ok()){
	pub.publish(msg);
	ros::spinOnce();
	loop.sleep();
	}
	return 0;
}
