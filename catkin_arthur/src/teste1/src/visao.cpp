#include<opencv2/highgui/highgui.hpp>
#include<ros/ros.h>
#include<image_transport/image_transport.h>
#include<cv_bridge/cv_bridge.h>

int main(int argc, char ** argv){

	ros::init(argc,argv,"noCamera");
	ros::NodeHandle nh;
	image_transport::ImageTransport it(nh);
	image_transport::Publisher pb = it.advertise("camera",1);
	ros::Rate loop(1);
	cv::Mat imagem (10,10,CV_8UC1);
	sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(),"bgr8",imagem).toImageMsg();
	
	while(nh.ok()){
		pb.publish(msg);
		ros::spinOnce();
		loop.sleep();
	}
	return 0;
}
