#include<opencv2/highgui/highgui.hpp>
#include<ros/ros.h>
#include<image_transport/image_transport.h>
#include<cv_bridge/cv_bridge.h>

int main(int argc, char ** argv){

	ros::init(argc,argv,"noCameraAoVivo");
	ros::NodeHandle nh;
	image_transport::ImageTransport it(nh);
	image_transport::Publisher pb = it.advertise("cameraAoVivo",1);
	ros::Rate loop(1);
	int videoSource = 0;
	cv::VideoCapture cap(videoSource,cv::CAP_V4L);
	
	if(!cap.isOpened()) return 1;	
	

	cv::Mat frame;
	//cv::Mat imagem (1050,1050,CV_8UC3,cv::Scalar(0,255,0));

	//sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(),"bgr8",imagem).toImageMsg();
	sensor_msgs::ImagePtr msg;
	cv::Mat frame2;
	while(nh.ok()){
		cap>>frame;
		cv::resize(frame,frame2, cv::Size(150,150), 0, 0, CV_INTER_LINEAR);
		if(!frame2.empty()){
			msg = cv_bridge::CvImage(std_msgs::Header(),"bgr8",frame2).toImageMsg();
			pb.publish(msg);
	       		//cv::waitKey(0);
		}
//		pb.publish(msg);
		ros::spinOnce();
		loop.sleep();
	}
	return 0;
}