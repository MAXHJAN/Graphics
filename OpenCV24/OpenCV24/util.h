#pragma once
#include "values.h"

namespace mycode
{
	

	class Reference		//参考点类
	{
	public:
		float weight;
		int a;
		int b;
		Reference(float weight,int a,int b)
		{
			this->weight = weight;
			this->a = a;
			this->b = b;
		}
	};

	bool comparepix(const Reference &first,const Reference &second)	//自定义排序函数
	{
		return first.weight<second.weight;
	}

}