#include<cv.h>  
#include<highgui.h>  

int main()
{
	IplImage* src = NULL;
	IplImage* img = NULL;

	CvMemStorage* storage = cvCreateMemStorage(0);;
	CvSeq* contour = 0;
	int contours = 0;
	CvScalar external_color;
	CvScalar hole_color;

	src = cvLoadImage("E:\\321.jpg", 1);


	img = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);


	cvCvtColor(src, img, CV_BGR2GRAY);
	cvThreshold(img, img, 100, 200, CV_THRESH_BINARY);
	contours = cvFindContours(img, storage, &contour, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

	for (; contour != 0; contour = contour->h_next)
	{
		external_color = CV_RGB(rand() & 255, rand() & 255, rand() & 255);
		hole_color = CV_RGB(rand() & 255, rand() & 255, rand() & 255);
		cvDrawContours(src, contour, external_color, hole_color, 1, 2, 8);
	}

	cvNamedWindow("Contour", 1);
	cvShowImage("Contour", src);

	cvWaitKey(0);

	cvReleaseMemStorage(&storage);
	cvReleaseImage(&src);
	cvReleaseImage(&img);

	return 0;
}