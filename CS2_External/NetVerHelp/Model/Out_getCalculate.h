#pragma once
#ifndef Out_getCalculate_H_
#define Out_getCalculate_H_
#include <string>
#include "Out_DataBaseArgs.h"
using namespace std;
namespace Model
{
	//Զ���㷨����
	class Out_getCalculate :public Out_DataBaseArgs
	{
	public:
		// Զ���㷨ת����ַ���ص�����
		string calculateresult;
	};
}
#endif