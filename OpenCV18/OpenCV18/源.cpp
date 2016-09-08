#include<cv.h>
#include<highgui.h>
#include<iostream>
using namespace std;
#define cvQueryHistValue_1D( hist, idx0 ) \
    ((float)cvGetReal1D( (hist)->bins, (idx0)))
void main()
{
	IplImage* pSrcImage, *pGrayImage, *pGrayImageEqualizeHist;
	pSrcImage = cvLoadImage("E:\\Image\\ol.jpg");
	pGrayImage = cvCreateImage(cvGetSize(pSrcImage), pSrcImage->depth, 1);
	pGrayImageEqualizeHist = cvCreateImage(cvGetSize(pSrcImage), pSrcImage->depth, 1);

	cvCvtColor(pSrcImage, pGrayImage, CV_BGR2GRAY);
	cvEqualizeHist(pGrayImage, pGrayImageEqualizeHist);

	int size = 256;
	float ranges[] = { 0, 256 };
	float *pfRanges[] = { ranges };
	float max_value = 0;

	CvHistogram* originalPictureHist = cvCreateHist(1, &size, CV_HIST_ARRAY, pfRanges);
	cvCalcHist(&pGrayImage, originalPictureHist);

	IplImage* originalPictureHistImage = cvCreateImage(cvSize(510, 150), 8, 1);
	cvRectangle(originalPictureHistImage, cvPoint(0, 0), cvPoint(originalPictureHistImage->width, originalPictureHistImage->height), CV_RGB(255, 255, 255));
	cvGetMinMaxHistValue(originalPictureHist, NULL, &max_value, 0, 0);
	/*for (int i = 0; i < 255; i++)
	{
	float fHistValue = cvQueryHistValue_1D(originalPictureHist, i);
	int realHeight = cvRound(fHistValue * 150 / max_value);
	cvRectangle(originalPictureHistImage, cvPoint(i * 2, 150 - 1), cvPoint((i + 1) * 2 - 1, 150 - realHeight), cvScalar(i, 0, 0, 0), CV_FILLED);
	}*/

	CvHistogram* pGrayImageHist = cvCreateHist(1, &size, CV_HIST_ARRAY, pfRanges);
	cvCalcHist(&pGrayImageEqualizeHist, pGrayImageHist);

	IplImage* equalizeHistImage = cvCreateImage(cvSize(500, 150), pGrayImageEqualizeHist->depth, 1);
	float hist_max_value = 0;
	cvGetMinMaxHistValue(pGrayImageHist, NULL, &hist_max_value, 0, 0);
	for (int i = 0; i < 255; i++)
	{
		float value = cvQueryHistValue_1D(pGrayImageHist, i);
		int realHeight = cvRound(value * 150 / hist_max_value);
		cvRectangle(equalizeHistImage, cvPoint(i * 2, 150 - 1), cvPoint((i + 1) * 2 - 1, 150 - realHeight), cvScalar(i, 0, 0, 0), CV_FILLED);
	}

	//cvSaveImage("E:\\f\\图像处理图片\\originalHist.jpg", originalPictureHistImage);
	//cvSaveImage("E:\\f\\图像处理图片\\afterEqualizeHist.jpg", equalizeHistImage);
	cvShowImage("originalPicture", pSrcImage);
	cvShowImage("histImage", equalizeHistImage);
	//cvShowImage("originalHist", originalPictureHistImage);
	//cvShowImage("equalizeHistPicture", pGrayImageEqualizeHist);
	cvWaitKey(0);
	//自己释放图像空间的函数；
}