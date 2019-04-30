#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <iostream>
#include <cmath>

class Test
{
	public: Test();
	public: virtual ~Test();

	private: std::vector<cv::KeyPoint> FixedPartition( cv::Mat mat, long totalPartition );
	private: std::vector<cv::KeyPoint> Surf( cv::Mat mat, long totalPartition );
	private: std::vector<cv::KeyPoint> MaxPartition( std::vector<cv::KeyPoint> keyPoint, long totalPartition );
	private: std::vector<cv::KeyPoint> Sift( cv::Mat mat, long totalPartition );
};
