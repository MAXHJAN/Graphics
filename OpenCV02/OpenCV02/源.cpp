#include <cv.h>
#include <highgui.h>

bool drawing = false;
int count = 0;
CvRect rect;
CvPoint origin;
IplImage* src;
IplImage* dst;
IplImage* copy;

void onMouse(int event, int x, int y, int flags, void* param = NULL);

int main(int argc, char* argv[])
{
	src = cvLoadImage("E:\\s2.jpg", -1);
	cvNamedWindow("源图片", 1);
	copy = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
	cvCopy(src,copy,NULL);
	cvSetMouseCallback("源图片", onMouse, NULL);//捕捉鼠标
	cvShowImage("源图片", src);
	cvWaitKey(0);
	cvDestroyAllWindows();
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvReleaseImage(&copy);
	return 0;
}
//鼠标事件处理函数
void onMouse(int event, int x, int y, int flags, void* param)
{
	if (event == CV_EVENT_LBUTTONDOWN && !CV_EVENT_MOUSEMOVE)
	{
		
		if (count==0) {
			origin = cvPoint(x, y);
			rect = cvRect(x, y, 0, 0);
			count++;
			cvCircle(src, CvPoint(x,y), 3, cvScalar(0, 0, 255), -1);
			cvShowImage("源图片", src);
		}
		else {
			cvCircle(src, CvPoint(x, y), 3, cvScalar(0, 0, 255), -1);
			cvShowImage("源图片", src);
			count++;
		}
			
	}
	/*else if (event == CV_EVENT_MOUSEMOVE)
	{
		if (drawing)
		{
			rect.x = MIN(origin.x, x);
			rect.y = MIN(origin.y, y);
			rect.height = abs(origin.y - y);
			rect.width = abs(origin.x - x);
		}
	}*/
	else if (event == CV_EVENT_LBUTTONUP)
	{
		if (count==2)
		{
			count = 0;
			//cvShowImage("源图片", copy);
			cvCopy(copy, src, NULL);
			rect.x = MIN(origin.x, x);
			rect.y = MIN(origin.y, y);
			rect.height = abs(origin.y - y);
			rect.width = abs(origin.x - x);

			if (rect.height == 0 || rect.width == 0)
			{
				cvDestroyWindow("截图");
				return;
			}
			dst = cvCreateImage(cvSize(rect.width, rect.height), copy->depth, copy->nChannels);
			cvSetImageROI(copy, rect);
			cvCopy(copy, dst);
			cvResetImageROI(copy);

			cvNamedWindow("截图", 1);
			cvShowImage("截图", dst);
			//cvSaveImage("截图.jpg", dst);		
			cvWaitKey(0);			
			cvDestroyWindow("截图");
		}
		
	}
}