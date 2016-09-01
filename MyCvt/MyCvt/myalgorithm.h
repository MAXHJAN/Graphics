#include<vector>
#include"util.h"
#include"values.h"
#include <highgui.h>
#include <algorithm>
#include<cmath>
#include"otheralgorithm.h"

using namespace std;

#pragma once

namespace mycode
{
	double getstatis(int x,int y,IplImage* image)			//得到领域像素的均值方差;其中方差为标准差的平方；
	{
		int number = 0;
		vector<int> vec;
		for(int i=x - Domain/2;i<=x + Domain/2;i++)
		{
			uchar *ptr = (uchar*)(image->imageData+i*image->widthStep);
			for(int j=y-Domain/2;j<=y+Domain/2;j++)
			{
				if(i<0||i>=image->height||j<0||j>=image->width)
				{
					continue;
				}
				int light = ptr[3*j];
				vec.push_back(light);
			}
		}

		uchar *ptr = (uchar*)(image->imageData+x*image->widthStep);
		int light = ptr[3*y];
		return (light*Alpha+(1-Alpha)*(getstd(vec)));
		
	}
	
	vector<Reference> getreference(IplImage* image)					//得到参考点
	{
		vector<Reference> reference;
		int stepx,stepy;
		if(Number == -1)
		{
			stepx = 1;
			stepy = 1;
			
		}else{
			stepx = image->height/(Number+1);
			stepy = image->width/(Number+1);
		}
		stepx = stepx == 0?1:stepx;
		stepy = stepy == 0?1:stepy;
		for(int i=stepx;i<image->height;i+=stepx)
		{
			uchar *ptr = (uchar*)(image->imageData+i*image->widthStep);
			for(int j=stepy;j<image->width;j+=stepy)
			{
				double weight = getstatis(i,j,image);
				Reference re = Reference(weight,ptr[3*j+1],ptr[3*j+2]);
				reference.push_back(re);
			}
		}
		return reference;
	}

	void colormap(IplImage* first,IplImage* second)			//调整first图像的L分量的值；
	{
		CvScalar avg_first,std_first,avg_second, std_second;
		cvAvgSdv(first,&avg_first,&std_first);
		cvAvgSdv(second,&avg_second,&std_second);

		for(int i=0;i<first->height;i++)
		{
			uchar* ptr = (uchar*)(first->imageData+i*first->widthStep);
			for(int j=0;j<first->width;j++)
			{
				ptr[3*j] = (std_second.val[0]/std_first.val[0])*(ptr[3*j]-avg_first.val[0])+avg_second.val[0];
			}
		}
	}

	void colorchange(IplImage* image)
	{
		vector<int> pix;
		for(int i=0;i<image->height;i++)
		{
			uchar* ptr = (uchar*)(image->imageData+i*image->widthStep);
			for(int j=0;j<image->width;j++)
			{
				int lightpix = ptr[3*j];
				pix.push_back(lightpix);
			}
		}
		int maxlight = *max_element(pix.begin(),pix.end());
		int minlight = *min_element(pix.begin(),pix.end());
		int distance = maxlight - minlight;
		for(int i=0;i<image->height;i++)
		{
			uchar* ptr = (uchar*)(image->imageData+i*image->widthStep);
			for(int j=0;j<image->width;j++)
			{
				int lightpix = ptr[3*j];
				ptr[3*j] = (int)(lightpix/(256-distance));
			}
		}

	}
	

	int getindex(const vector<Reference> &reference,double weight)			//找出权值最近的点；
	{
		int i = 0;
		int j = reference.size()-1;
		while(i != j)
		{
			int k = (i+j)/2;
			if(k == i)
			{
				break;
			}
			if(reference[k].weight>weight)
			{
				j = k;
			}else if(reference[k].weight<=weight)
			{
				i = k;
			}
		}
		float first = reference[i+1].weight - weight;
		float second = weight - reference[i].weight;
		return (first>second?i:(i+1));

	}

}