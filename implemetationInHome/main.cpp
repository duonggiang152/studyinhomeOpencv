#include <iostream>
#include <opencv2/opencv.hpp>
#include "Erode.h"
#include "GaussianBlur.h"
int main() {
	cv::Mat imageIntensive = cv::imread("C:/Users/giang/source/repos/implemetationInHome/train.jpg", 0);
	cv::imshow("intensive", imageIntensive);
	cv::Mat gaussianResult;
	GaussianBlur::blur(imageIntensive, gaussianResult, 5, 2,4);
	cv::imshow("gaussianMy", gaussianResult);
	cv::Mat gaOpencv;
	cv::GaussianBlur(imageIntensive, gaOpencv, cv::Size(5,5), 2, 2,4);
	cv::imshow("gaussianCV", gaOpencv);
	long long count = 0;
	for (int i = 0; i < gaussianResult.rows; i++) {
		for (int j = 0; j < gaussianResult.cols; j++) {
			if (gaussianResult.at<uchar>(i, j) == gaOpencv.at<uchar>(i, j)) count++;
		}
	}
	std::cout << (double)count / (gaussianResult.rows * gaussianResult.cols) << std::endl;
	/*cv::Mat binaryImage;
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
	std::cout << "Hello world" << std::endl;*/
	cv::waitKey(0);
}