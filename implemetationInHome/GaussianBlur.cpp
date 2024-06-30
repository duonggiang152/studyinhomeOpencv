#include "GaussianBlur.h"
#include <math.h>
#include <iostream>
uint GaussianBlur::radiusKernel = 1;
void GaussianBlur::blur(cv::Mat source, cv::Mat& dest, uint size, double sigma, uint borderType)
{
	cv::Mat temp;
	radiusKernel = size / 2;

	cv::copyMakeBorder(source, 
		temp, 
		radiusKernel, 
		radiusKernel,
		radiusKernel, 
		radiusKernel, 
		borderType);
	
	cv::Mat kernel;
	createKernel(kernel, sigma, size);

	dest = cv::Mat(source.rows, source.cols, CV_8U, cv::Scalar(0));

	for (uint i = radiusKernel; i < temp.rows - radiusKernel; i++) {
		for (uint j = radiusKernel; j < temp.cols - radiusKernel; j++) {
			dest.at<uchar>(i - radiusKernel, j - radiusKernel) = convolution(temp, kernel, i, j);
		}
	}



}

void GaussianBlur::createKernel(cv::Mat& kernel, double sigma, uint size)
{
	kernel = cv::Mat(size, size, CV_64F ,cv::Scalar(0.0f));

	double sum = 0.0f;


	for (int i = -((int)radiusKernel); i <= (int)radiusKernel; i++) {
		for (int j = -((int)radiusKernel); j <= (int)radiusKernel; j++) {
			double value = exp(-1 * (i * i + j * j) / (2 * sigma * sigma));
			sum += value;
			kernel.at<double>(i + radiusKernel, j + radiusKernel) = value;
		}
	}

	//normalize;
	kernel /= sum;

	
}

uchar GaussianBlur::convolution(const cv::Mat& source, const cv::Mat& kernel, uint row, uint col)
{	
	double result = 0.0;
	for (int i = -((int)radiusKernel); i <= (int)radiusKernel; i++) {
		for (int j = -((int)radiusKernel); j <= (int)radiusKernel; j++) {
			result += source.at<uchar>(row - i, col - j) * kernel.at<double>(i + radiusKernel, j + radiusKernel);
		}
	}
	return std::round(result);
	
}
