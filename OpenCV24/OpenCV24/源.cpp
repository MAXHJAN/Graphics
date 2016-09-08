#include <iostream>
#include <highgui.h>
#include <cv.h>
#include <stack>
#include <algorithm>
#include "util.h"
#include "myalgorithm.h"

using namespace std;
using namespace cv;
using namespace mycode;

void My_GRAY2RGB(IplImage* first, IplImage* second, char* str) {
	IplImage* firstLab = cvCreateImage(cvGetSize(first), first->depth, first->nChannels);
	IplImage* secondLab = cvCreateImage(cvGetSize(second), second->depth, second->nChannels);
	IplImage* secondLabClone = cvCreateImage(cvGetSize(second), second->depth, second->nChannels);

	cvCvtColor(first, firstLab, CV_BGR2Lab);
	cvCvtColor(second, secondLab, CV_BGR2Lab);


	/*colormap(secondLab,firstLab);	*///亮度映射;
	colorchange(firstLab);
	colorchange(secondLab);
	cout << "Colormap Done!" << endl;


	secondLabClone = cvCloneImage(secondLab);

	vector<Reference> references;
	references = getreference(firstLab);	//得到参考点;
	cout << "Reference selecting Done!" << endl;


	sort(references.begin(), references.end(), comparepix);	//按照weight排序；
	cout << "Sorting Done" << endl;


	for (int i = 0, information = 1, coutinf = 0; i<secondLabClone->height; i++, coutinf++)
	{
		uchar* ptr = (uchar*)(secondLab->imageData + i*secondLab->widthStep);

		if (coutinf == secondLabClone->height / 10)
		{
			coutinf = 0;
			cout << information << "/10"  << endl;
			information++;
		}

		for (int j = 0; j<secondLabClone->width; j++)
		{
			float weight = getstatis(i, j, secondLabClone);
			int index = getindex(references, weight);
			ptr[3 * j + 1] = references[index].a;
			ptr[3 * j + 2] = references[index].b;
		}
	}

	normalizeimage(secondLab);
	cvCvtColor(secondLab, secondLabClone, CV_Lab2BGR);
	cout << "Done" << endl;
	cvShowImage(str, secondLabClone);

	cvReleaseImage(&firstLab);
	cvReleaseImage(&secondLab);
	cvReleaseImage(&secondLabClone);
}
int main()
{
	IplImage* Original0 = cvLoadImage("E:\\Image\\test2.jpg", CV_LOAD_IMAGE_COLOR);			//参考图像;
	IplImage* Original1 = cvLoadImage("E:\\Image\\a.jpg", CV_LOAD_IMAGE_COLOR);			//参考图像;
	IplImage* Original2 = cvLoadImage("E:\\Image\\grass.jpg", CV_LOAD_IMAGE_COLOR);			//参考图像;
	IplImage* Result = cvLoadImage("E:\\Image\\test1.jpg", CV_LOAD_IMAGE_COLOR);		//目标图像;
																				//cvShowImage("参考图像", first);
	cvShowImage("目标图像", Result);

	if (Result->nChannels == 1)
	{
		cvCvtColor(Result, Result, CV_GRAY2RGB);
	}


	My_GRAY2RGB(Original0, Result, "结果图1");
	My_GRAY2RGB(Original1, Result, "结果图2");
	My_GRAY2RGB(Original2, Result, "结果图3");



	cvWaitKey(0);
	cvReleaseImage(&Original0);
	cvReleaseImage(&Original1);
	cvReleaseImage(&Original2);
	cvReleaseImage(&Result);

}