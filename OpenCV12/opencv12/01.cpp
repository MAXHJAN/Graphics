#include <opencv2/opencv.hpp>  
using namespace std;  
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")  
const char *pstrWindowsMouseDrawTitle = "鼠标绘图";  

IplImage *pSrcImage;
// 鼠标消息的回调函数  
void on_mouse(int event, int x, int y, int flags, void* param)  
{  

    static bool s_bMouseLButtonDown = false;  
    static CvPoint s_cvPrePoint = cvPoint(0, 0);  
	static CvPoint sx;
    switch (event)  
    {  
    case CV_EVENT_LBUTTONDOWN:  
        s_bMouseLButtonDown = true;  
        s_cvPrePoint = cvPoint(x, y);
		sx=s_cvPrePoint;
        break;  
  
    case  CV_EVENT_LBUTTONUP:  
        s_bMouseLButtonDown = false;  
        break;  
  
    case CV_EVENT_MOUSEMOVE: 
        if (s_bMouseLButtonDown)					
        {  
            CvPoint cvCurrPoint = cvPoint(x, y);  
            cvLine((IplImage*)param, s_cvPrePoint, cvCurrPoint, CV_RGB(0, 0, 20), 1);  
            s_cvPrePoint = cvCurrPoint; 
			//printf("%d,%d\n",cvCurrPoint.x,cvCurrPoint.y);		
			//printf("%d",cvCurrPoint.y);
			//printf("%d,%d\n",sx.x,sx.y);
			//printf("%d,%d\n",s_cvPrePoint.x,s_cvPrePoint.y);
			//if(s_cvPrePoint.x==cvCurrPoint.x&&s_cvPrePoint.x==cvCurrPoint.y)
			//{
			//	cvFloodFill(pSrcImage,cvCurrPoint,cvScalarAll(0),cvScalarAll(0),cvScalarAll(0),NULL,8,NULL);
			//}
			//cvNamedWindow("asd", CV_WINDOW_AUTOSIZE);  
            cvShowImage(pstrWindowsMouseDrawTitle, (IplImage*)param);  
			
        }  
        break;  
    }
	
    
}  
int main()  
{     
    const int MAX_WIDTH = 500, MAX_HEIGHT = 400;  
    const char *pstrSaveImageName = "01.jpg";  
    pSrcImage =  cvCreateImage(cvSize(MAX_WIDTH, MAX_HEIGHT), IPL_DEPTH_8U, 3);  
    cvSet(pSrcImage, CV_RGB(255, 255, 255)); //可以用cvSet()将图像填充成白色  
    cvNamedWindow(pstrWindowsMouseDrawTitle, CV_WINDOW_AUTOSIZE);  
    cvShowImage(pstrWindowsMouseDrawTitle, pSrcImage);  
    cvSetMouseCallback(pstrWindowsMouseDrawTitle, on_mouse, (void*)pSrcImage); 
    int c;  
    do{  
        c = cvWaitKey(0);  
        switch ((char)c)  
        {  
        case 'c':  
            cvSet(pSrcImage, CV_RGB(255, 255, 255));  
            cvShowImage(pstrWindowsMouseDrawTitle, pSrcImage);  
            break;  
  
        case 's':  
            cvSaveImage(pstrSaveImageName, pSrcImage);  
            break;  
        }  
    }while (c > 0 && c != 27);  
  
    cvDestroyWindow(pstrWindowsMouseDrawTitle);  
    cvReleaseImage(&pSrcImage);  
    return 0;  
}   