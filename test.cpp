#include "boxExtractor.hpp"

#ifdef _DEBUG
#pragma comment(lib, "opencv_world310d")
#else
#pragma comment(lib, "opencv_world310")
#endif // _DEBUG

using namespace cv;

int main()
{
    VideoCapture cap("test.avi");

    CV_Assert(cap.isOpened());

    VideoCapture ss;

    BoxExtractor box;

    Rect roi = box.extract(cap);

    // do something about the ROI, e.g. tracking...

    return 0;
}