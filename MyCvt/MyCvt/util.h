#pragma once
#include "values.h"

namespace mycode
{
	

	class Reference		//�ο�����
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

	bool comparepix(const Reference &first,const Reference &second)	//�Զ���������
	{
		return first.weight<second.weight;
	}

}