#include <vector>
#include <numeric>
#include "values.h"
#include <cmath>
#include <highgui.h>

using namespace std;
#pragma once
namespace mycode
{

	double getstd(const vector<int>& vec)			//�������еı�׼��;
	{
		double std;
		double addall = accumulate(vec.begin(),vec.end(),0);

		double avg = addall/vec.size();
		double total = 0.0f;
		for(int i=0;i<vec.size();i++)
		{
			total += (vec[i]-avg)*(vec[i]-avg);		//���в�ƽ��֮��;
		}

		std = sqrt(total/vec.size());
		return std;

	}

	void normalizeimage(IplImage* image)		//��׼��ͼ�������ֵ��ʹ�䴦��0-255֮�䣻
	{
		for(int i = 0;i<image->height;i++)
		{

			uchar* ptr = (uchar*)(image->imageData + i*image->widthStep);
			for(int j = 0 ;j<image->width;j++)
			{
				for(int channel = 0;channel<3;channel++)
				{
					if(ptr[3*j+channel]>255)
					{
						ptr[3*j+channel] = 255;
					}
					if(ptr[3*j+channel]<0)
					{
						ptr[3*j+channel] = 0;
					}
				}
			}
		}
	}

}