#include <iostream>
#include <opencv2/opencv.hpp>
#include "Erode.h"

int main() {
	cv::Mat imageIntensive = cv::imread("C:/Users/giang/source/repos/implemetationInHome/flower.jpg", 0);
	cv::imshow("intensive", imageIntensive);
	cv::Mat binaryImage;
	cv::threshold(	imageIntensive,
					binaryImage,
					100, 
					255, 
					cv::THRESH_BINARY);
	cv::imshow("binary", binaryImage);
	cv::Mat erosionResult;
	Erode::Erode1C(binaryImage, 
		erosionResult, 
		cv::Mat(3,3,CV_8UC1, 1),
		cv::Point(-1, -1)
	);
	cv::imshow("test", erosionResult);
	std::cout << "Hello world" << std::endl;
	cv::waitKey(0);
}