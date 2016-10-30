#pragma once

#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

class BoxExtractor
{
public:
	cv::Rect extract(const cv::Mat& img);
	cv::Rect extract(const std::string& windowName, const cv::Mat& img, bool showCrosshair = true);
	cv::Rect extract(cv::VideoCapture& cap);
	cv::Rect extract(const std::string& windowName, cv::VideoCapture& cap, bool showCrosshair = true);

	struct handlerT
	{
		bool isDrawing;
		cv::Rect box;
		cv::Mat image;

		// initializer list
		handlerT() : isDrawing(false) {};
	} params;

private:
	static void mouseHandler(int event, int x, int y, int flags, void *param);
	void opencv_mouse_callback(int event, int x, int y, int, void *param);
};