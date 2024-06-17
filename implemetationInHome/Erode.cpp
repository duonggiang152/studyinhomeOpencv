#include "Erode.h"
#include <iostream>	
cv::Mat Erode::sourceImg = cv::Mat();
cv::Point Erode::topLeftKernelMappingSourceImg = cv::Point(-1, -1);
cv::Point Erode::rightDownKernelMappingSourceImg = cv::Point(-1, -1);
cv::Point Erode::anchorPoint = cv::Point(-1, -1);
cv::Mat Erode::kernel = cv::Mat();
void Erode::Erode1C(cv::Mat sourceImg, cv::Mat& targetImage, cv::Mat kernel, cv::Point anchorPoint)
{
	Erode::sourceImg = sourceImg;
	Erode::anchorPoint = anchorPoint;
	Erode::kernel = kernel;
	if (targetImage.empty())
		targetImage = cv::Mat(sourceImg.rows, sourceImg.cols, CV_8UC1, cv::Scalar(0));
	if (targetImage.rows != sourceImg.rows ||
		targetImage.cols != sourceImg.cols) 
		targetImage = cv::Mat(sourceImg.rows, sourceImg.cols, CV_8UC1, cv::Scalar(0));
	
	Erode::anchorPoint = getAnchorPoint();

	for (int i = 0; i < sourceImg.rows; i++) {
		for (int j = 0; j < sourceImg.cols; j++) {
			targetImage.at<uchar>(i, j)= findMinInKernel(i, j);
		}
	}
	return;
}

cv::Point Erode::getAnchorPoint()
{
	if (anchorPoint.x == -1 && anchorPoint.y == -1) {
		int row = (int)(Erode::kernel.rows / 2);
		int col = (int)(Erode::kernel.cols / 2);
		return cv::Point(row, col);
	}
	if (anchorPoint.x > kernel.rows ||  anchorPoint.y > kernel.cols ||
		anchorPoint.x < 0 || anchorPoint.y < 0 ) {
		std::cout << "Anchor not exist" << std::endl;
		return cv::Point(-1, -1);
	}
	return anchorPoint;
}

uchar Erode::findMinInKernel(int row, int col)
{	
	uchar min = 255;

	Erode::topLeftKernelMappingSourceImg.x = row - anchorPoint.x;
	Erode::topLeftKernelMappingSourceImg.y = col - anchorPoint.y;

	Erode::rightDownKernelMappingSourceImg.x = Erode::topLeftKernelMappingSourceImg.x + Erode::kernel.rows - 1;
	Erode::rightDownKernelMappingSourceImg.y = Erode::topLeftKernelMappingSourceImg.y + Erode::kernel.cols - 1;

	for (int r = Erode::topLeftKernelMappingSourceImg.x; r <= Erode::rightDownKernelMappingSourceImg.x; r++) {
		for (int c = Erode::topLeftKernelMappingSourceImg.y; c <= Erode::rightDownKernelMappingSourceImg.y; c++) {
			if (r < 0 || c < 0 ||
				r >= Erode::sourceImg.rows || c >= Erode::sourceImg.cols) continue;
			if (Erode::kernel.at<uchar>(r - Erode::topLeftKernelMappingSourceImg.x, c - Erode::topLeftKernelMappingSourceImg.y) == (uchar)1) {
				min = (min <= Erode::sourceImg.at<uchar>(r, c) ? min : Erode::sourceImg.at<uchar>(r, c));
			}
		}
	}

	return min;
}


