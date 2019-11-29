#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>
#include <chrono>

using namespace cv;
using namespace std;


int thresh = 50, N = 11;

static double angle(Point pt1, Point pt2, Point pt0)
{
	double dx1 = pt1.x - pt0.x;
	double dy1 = pt1.y - pt0.y;
	double dx2 = pt2.x - pt0.x;
	double dy2 = pt2.y - pt0.y;
	return (dx1 * dx2 + dy1 * dy2) / sqrt((dx1 * dx1 + dy1 * dy1) * (dx2 * dx2 + dy2 * dy2) + 1e-10);
}

static void findSquares(const Mat& image, vector<vector<Point> >& squares)
{
	squares.clear();

	Mat pyr, timg, gray0(image.size(), CV_8U), gray;

	pyrDown(image, pyr, Size(image.cols / 2, image.rows / 2));
	pyrUp(pyr, timg, image.size());
	vector<vector<Point> > contours;

	for (int c = 0; c < 3; c++)
	{
		int ch[] = { c, 0 };
		mixChannels(&timg, 1, &gray0, 1, ch, 1);

		for (int l = 0; l < N; l++)
		{

			if (l == 0)
			{
				Canny(gray0, gray, 0, thresh, 5);
				dilate(gray, gray, Mat(), Point(-1, -1));
			}
			else
			{
				gray = gray0 >= (l + 1) * 255 / N;
			}

			findContours(gray, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

			vector<Point> approx;

			for (size_t i = 0; i < contours.size(); i++)
			{
				approxPolyDP(contours[i], approx, arcLength(contours[i], true) * 0.02, true);

				if (approx.size() == 4 &&
					fabs(contourArea(approx)) > 1000 &&
					isContourConvex(approx))
				{
					double maxCosine = 0;

					for (int j = 2; j < 5; j++)
					{
						double cosine = fabs(angle(approx[j % 4], approx[j - 2], approx[j - 1]));
						maxCosine = MAX(maxCosine, cosine);
					}
					if (maxCosine < 0.3)
						squares.push_back(approx);
				}
			}
		}
	}
}

static void drawSquares(Mat& image, const vector<vector<Point> >& squares)
{
	for (size_t i = 0; i < squares.size(); i++)
	{
		const Point* p = &squares[i][0];
		int n = (int)squares[i].size();
		polylines(image, &p, &n, 1, true, Scalar(0, 255, 0), 3, LINE_AA);
	}

}


int main(int argc, char** argv)
{

	vector<vector<Point> > squares;

	VideoCapture cap(0);
	if (!cap.isOpened()) {
		cout << "Video stream input error" << endl;
		return -1;
	}

	long int tperiod = 1;
	chrono::steady_clock::duration time_step = chrono::duration<chrono::steady_clock::rep, std::ratio<1, 1>>{ tperiod };
	chrono::steady_clock::time_point next = chrono::steady_clock::now() + time_step;

	while (1) {


		Mat frame;
		cap >> frame;

		if (frame.empty())
			break;

		findSquares(frame, squares);
		drawSquares(frame, squares);

		imshow("OUFOVision", frame);

		char c = (char)waitKey(25);
		if (c == 27)
			break;

		std::this_thread::sleep_until(next);
		next += time_step;

	}

	cap.release();
	destroyAllWindows();

	return 0;

}
