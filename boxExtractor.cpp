#include "boxExtractor.hpp"

using namespace cv;

void BoxExtractor::mouseCallback(int event, int x, int y, int, void *param)
{
	handlerT * data = (handlerT*)param;
	switch (event)
	{
	// start to select the bounding box
	case EVENT_LBUTTONDOWN:
		data->isDrawing = true;
		data->box = cvRect(x, y, 0, 0);
		break;

	// update the selected bounding box
	case EVENT_MOUSEMOVE:
		if (data->isDrawing)
		{
			data->box.width = x - data->box.x;
			data->box.height = y - data->box.y;
		}
		break;

	// cleaning up the selected bounding box
	case EVENT_LBUTTONUP:
		data->isDrawing = false;
		if (data->box.width < 0)
		{
			data->box.x += data->box.width;
			data->box.width *= -1;
		}
		if (data->box.height < 0)
		{
			data->box.y += data->box.height;
			data->box.height *= -1;
		}
		break;
	}
}

Rect BoxExtractor::extract(const Mat& img)
{
	CV_Assert(!img.empty());

	return extract("Bounding Box Extractor", img);
}

Rect BoxExtractor::extract(const std::string& windowName, const Mat& img, bool showCrosshair)
{
	CV_Assert(!img.empty());
	CV_Assert(!windowName.empty());

	int key = 0;

	// show the image and give feedback to user
	imshow(windowName, img);
	printf("Select an object and then press SPACE/BACKSPACE/ENTER button!\n");

	// copy the data, rectangle should be drawn in the fresh image
	params.image = img.clone();

	// select the object
	setMouseCallback(windowName, mouseCallback, (void *)&params);

	// end selection process on SPACE (32) BACKSPACE (27) or ENTER (13)
	while (!(key == 32 || key == 27 || key == 13))
	{
		// draw the selected object
		rectangle(params.image, params.box, Scalar(255, 0, 0), 2, 1);

		// draw cross air in the middle of bounding box
		if (showCrosshair)
		{
			// horizontal line
			line(params.image,
			     Point((int)params.box.x, (int)(params.box.y + params.box.height / 2)),
			     Point((int)(params.box.x + params.box.width), (int)(params.box.y + params.box.height / 2)),
			     Scalar(255, 0, 0), 2, 1
			    );

			// vertical line
			line(params.image,
			     Point((int)(params.box.x + params.box.width / 2), (int)params.box.y),
			     Point((int)(params.box.x + params.box.width / 2), (int)(params.box.y + params.box.height)),
			     Scalar(255, 0, 0), 2, 1
			    );
		}

		// show the image bouding box
		imshow(windowName, params.image);

		// reset the image
		params.image = img.clone();

		//get keyboard event
		key = waitKey(1);
	}

	return params.box;
}

Rect BoxExtractor::extract(VideoCapture& cap)
{
	CV_Assert(cap.isOpened());

	return extract("Bounding Box Extractor", cap);
}


Rect BoxExtractor::extract(const std::string& windowName, VideoCapture& cap, bool showCrosshair)
{
	CV_Assert(!windowName.empty());
	CV_Assert(cap.isOpened());

	Mat frame;

	while (cap.read(frame))
	{
		CV_Assert(!frame.empty());

		imshow(windowName, frame);

		int key = waitKey(30);
		if (key == 'p')
		{
			return extract(windowName, frame, showCrosshair);
		}
	}

	return params.box;
}