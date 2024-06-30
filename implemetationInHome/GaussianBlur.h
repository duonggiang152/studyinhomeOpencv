#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
class GaussianBlur
{
public:
	static void blur (cv::Mat source, cv::Mat& dest, uint size,double sigma ,uint borderType = cv::BORDER_DEFAULT);
private: 
	static uint radiusKernel;
	static void createKernel(cv::Mat& kernel, double sigma, uint size);
	static uchar convolution(const cv::Mat& source, const cv::Mat& kernel, uint row, uint col);
};

