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


int main()
{
	IplImage* first = cvLoadImage("E:\\a.jpg",CV_LOAD_IMAGE_COLOR);			//参考图像;
	IplImage* second = cvLoadImage("E:\\test1.jpg",CV_LOAD_IMAGE_COLOR);		//目标图像;

	if(second->nChannels == 1)
	{
		cvCvtColor(second,second,CV_GRAY2RGB);
	}

	IplImage* firstLab = cvCreateImage(cvGetSize(first),first->depth,first->nChannels);
	IplImage* secondLab = cvCreateImage(cvGetSize(second),second->depth,second->nChannels);
	IplImage* secondLabClone = cvCreateImage(cvGetSize(second),second->depth,second->nChannels);

	cvCvtColor(first,firstLab,CV_BGR2Lab);
	cvCvtColor(second,secondLab,CV_BGR2Lab);
	

	/*colormap(secondLab,firstLab);	*///亮度映射;
	colorchange(firstLab);
	colorchange(secondLab);
	cout<<"Colormap Done!"<<endl;
	
	
	secondLabClone = cvCloneImage(secondLab);

	vector<Reference> references;
	references = getreference(firstLab);	//得到参考点;
	cout<<"Reference selecting Done!"<<endl;


	sort(references.begin(),references.end(),comparepix);	//按照weight排序；
	cout<<"Sorting Done"<<endl;

	
	for(int i = 0,information = 1,coutinf = 0;i<secondLabClone->height;i++,coutinf++)
	{
		uchar* ptr = (uchar*)(secondLab->imageData+i*secondLab->widthStep);

		if(coutinf == secondLabClone->height/10)
		{
			coutinf = 0;
			cout<<"proceeding----"<<information<<"/10"<<"---"<<endl;
			information++;
		}

		for(int j=0;j<secondLabClone->width;j++)
		{
			float weight = getstatis(i,j,secondLabClone);
			int index = getindex(references,weight);
			ptr[3*j+1] = references[index].a;
			ptr[3*j+2] = references[index].b;
		}
	}

	normalizeimage(secondLab);
	cvCvtColor(secondLab,secondLabClone,CV_Lab2BGR);
	cout<<"Done"<<endl;

	cvShowImage("output",secondLabClone);
	


	cvWaitKey(0);
	cvReleaseImage(&first);
	cvReleaseImage(&second);
	cvReleaseImage(&firstLab);
	cvReleaseImage(&secondLab);
	cvReleaseImage(&secondLabClone);

}