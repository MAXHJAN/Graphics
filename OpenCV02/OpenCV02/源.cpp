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
	cvNamedWindow("ԴͼƬ", 1);
	copy = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
	cvCopy(src,copy,NULL);
	cvSetMouseCallback("ԴͼƬ", onMouse, NULL);//��׽���
	cvShowImage("ԴͼƬ", src);
	cvWaitKey(0);
	cvDestroyAllWindows();
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvReleaseImage(&copy);
	return 0;
}
//����¼�������
void onMouse(int event, int x, int y, int flags, void* param)
{
	if (event == CV_EVENT_LBUTTONDOWN && !CV_EVENT_MOUSEMOVE)
	{
		
		if (count==0) {
			origin = cvPoint(x, y);
			rect = cvRect(x, y, 0, 0);
			count++;
			cvCircle(src, CvPoint(x,y), 3, cvScalar(0, 0, 255), -1);
			cvShowImage("ԴͼƬ", src);
		}
		else {
			cvCircle(src, CvPoint(x, y), 3, cvScalar(0, 0, 255), -1);
			cvShowImage("ԴͼƬ", src);
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
			//cvShowImage("ԴͼƬ", copy);
			cvCopy(copy, src, NULL);
			rect.x = MIN(origin.x, x);
			rect.y = MIN(origin.y, y);
			rect.height = abs(origin.y - y);
			rect.width = abs(origin.x - x);

			if (rect.height == 0 || rect.width == 0)
			{
				cvDestroyWindow("��ͼ");
				return;
			}
			dst = cvCreateImage(cvSize(rect.width, rect.height), copy->depth, copy->nChannels);
			cvSetImageROI(copy, rect);
			cvCopy(copy, dst);
			cvResetImageROI(copy);

			cvNamedWindow("��ͼ", 1);
			cvShowImage("��ͼ", dst);
			//cvSaveImage("��ͼ.jpg", dst);		
			cvWaitKey(0);			
			cvDestroyWindow("��ͼ");
		}
		
	}
}