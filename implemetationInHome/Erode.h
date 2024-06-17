#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
class Erode
{

	public:
		// currenly support Erode1C 
		void static Erode1C(cv::Mat sourceImg, cv::Mat& targetImage, cv::Mat kernel, cv::Point anchorPoint  = cv::Point(-1,-1));
	private:
		Erode();
		static cv::Point getAnchorPoint();
		static uchar findMinInKernel(int row, int col);
	private:
		static cv::Mat sourceImg;
		static cv::Point topLeftKernelMappingSourceImg;
		static cv::Point rightDownKernelMappingSourceImg;
		static cv::Point anchorPoint;
		static cv::Mat kernel;

};

