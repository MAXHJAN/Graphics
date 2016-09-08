#include <cv.h>
#include <highgui.h>
int g_threshold = 255;
IplImage* src = cvLoadImage("E:\\321.jpg", 0);
 void on_trackbar(int pos)
{
	IplImage *dst = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
	cvCopy(src,dst,NULL);
	cvCmpS(src, pos,dst, CV_CMP_LT);
	cvCopy(src, dst, dst);
	cvShowImage("binary image", dst);
	cvReleaseImage(&dst);
}
int main()
{
	cvNamedWindow("source image", 1);
	cvShowImage("source image", src);
	cvNamedWindow("binary image", 1);
	cvCreateTrackbar("slider", "binary image", &g_threshold, 255, on_trackbar);
	on_trackbar(g_threshold);
	cvWaitKey(0);
	cvReleaseImage(&src);
	cvDestroyAllWindows();
	return 0;
}