#pragma once
#ifndef In_getCalculateArgs_H_
#define In_getCalculateArgs_H_
#include <string>
#include "In_getCalculateArgs.h"
using namespace std;
namespace Model
{
	// ��ȡԶ���㷨���
	class In_getCalculateArgs :public In_DataBaseArgs
	{
	public:
		//��¼����(����)
		string token;
		// �㷨ID(��̨->���ƹ���->Զ���㷨�б�->�㷨ID)
		string calculateid;
		//����ת����ַ�ύ�Ĳ���(������ʽʾ����args1=value1&args2=value2)
		string requestargs;
	};
}
#endif