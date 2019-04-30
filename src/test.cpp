#include "test.hpp"

Test::Test()
{
	cv::Mat mat_input = cv::imread( "/home/dekwan/Projek/Dataset/Cummins/CityCentre/Images/1156.jpg", cv::IMREAD_UNCHANGED );

	std::vector<cv::KeyPoint> fpKp = FixedPartition( mat_input, 100 );
	std::vector<cv::KeyPoint> surfKp = Surf( mat_input, 100 );
	std::vector<cv::KeyPoint> sirfKp = Sift( mat_input, 100 );
}

Test::~Test()
{

}

std::vector<cv::KeyPoint> Test::FixedPartition( cv::Mat mat, long totalPartition )
{
	long totalPixel = mat.cols * mat.rows;
	double volume = double( totalPixel ) / double( totalPartition );
	double radius = std::sqrt( volume / M_PI );
	cv::Point2f center = cv::Point2f( mat.cols / 2.0, mat.rows / 2.0 );
	double longestDist = std::sqrt( std::pow( mat.cols - center.x, 2 ) + std::pow( mat.rows - center.y, 2 ) );

	cv::KeyPoint keyPoint;
	std::vector<cv::KeyPoint> vecKeyPoint;
	keyPoint.class_id = -1;

	for( double y = radius; y < mat.rows; y += ( radius * 2.0 ) )
	{
		for( double x = radius; x < mat.cols; x += ( radius * 2.0 ) )
		{
			keyPoint.pt.x = x;
			keyPoint.pt.y = y;
			keyPoint.size = radius * 2;
			keyPoint.angle = 0.0;
			keyPoint.class_id++;
			keyPoint.octave = 0;
			keyPoint.response = longestDist - std::sqrt( std::pow( double( x ) - center.x, 2 ) + std::pow( double( y ) - center.y, 2 ) );

			vecKeyPoint.push_back( keyPoint );
		}
	}

	vecKeyPoint = MaxPartition( vecKeyPoint, totalPartition );

	cv::Mat mat_output;
	cv::drawKeypoints( mat, vecKeyPoint, mat_output, cv::Scalar( 0, 0, 255 ), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

	cv::imshow( "FixedPartition", mat_output );
	cv::imwrite( "FixedPartition.jpg", mat_output );
	cv::waitKey( true );

	return vecKeyPoint;
}

std::vector<cv::KeyPoint> Test::Surf( cv::Mat mat, long totalPartition )
{
	cv::Ptr<cv::xfeatures2d::SURF> detector = cv::xfeatures2d::SURF::create();
	std::vector<cv::KeyPoint> vecKeyPoint;
	detector->detect( mat, vecKeyPoint );

	vecKeyPoint = MaxPartition( vecKeyPoint, totalPartition );

	cv::Mat mat_output;
	cv::drawKeypoints( mat, vecKeyPoint, mat_output, cv::Scalar( 0, 0, 255 ), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

	cv::imshow( "Surf", mat_output );
	cv::imwrite( "Surf.jpg", mat_output );
	cv::waitKey( true );

	return vecKeyPoint;
}

std::vector<cv::KeyPoint> Test::MaxPartition( std::vector<cv::KeyPoint> keyPoint, long totalPartition )
{
	if( totalPartition > 0 && keyPoint.size() > totalPartition )
	{
		std::multimap<float, int> hessianMap;

		for( unsigned int i = 0; i < keyPoint.size(); i++ )
		{
			hessianMap.insert( std::pair<float, int>( fabs( keyPoint[i].response ), i ) );
		}

		std::vector<cv::KeyPoint> tempKeyPoint( totalPartition );
		std::multimap<float, int>::reverse_iterator j = hessianMap.rbegin();

		for( unsigned int i = 0; i < tempKeyPoint.size() && j != hessianMap.rend(); i++, j++ )
		{
			tempKeyPoint[i] = keyPoint[j->second];
		}

		keyPoint = tempKeyPoint;
	}

	return keyPoint;
}

std::vector<cv::KeyPoint> Test::Sift( cv::Mat mat, long totalPartition )
{
	cv::Ptr<cv::xfeatures2d::SIFT> detector = cv::xfeatures2d::SIFT::create();
	std::vector<cv::KeyPoint> vecKeyPoint;
	detector->detect( mat, vecKeyPoint );

	vecKeyPoint = MaxPartition( vecKeyPoint, totalPartition );

	cv::Mat mat_output;
	cv::drawKeypoints( mat, vecKeyPoint, mat_output, cv::Scalar( 0, 0, 255 ), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

	cv::imshow( "Sift", mat_output );
	cv::imwrite( "Sift.jpg", mat_output );
	cv::waitKey( true );

	return vecKeyPoint;
}
