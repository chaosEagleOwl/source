//#include "StdAfx.h"
#include "Types.h"

#pragma once


class tFEMSolver
{
public:
	//tNameValueLongintMap ;
	long getSystemVariableIndex(CString systemVariableName);
	bool registerSystemVariableName(CString newSystemVariableName, CString newSystemVariableDescription, CString newSystemVariableDimension, long &indexSystemVariableName);
	void registerStandartSystemVariableName();
	//long register  
	
	tFEMSolver();
	~tFEMSolver();
private:
	tNameValueLongintMap systemVariableNameIndexMap;//��������� ��� �������� ��������� ������� ����� ���������� (� ������� ���� ����������) �� ����� ����������
	tNameValueDescriptionValueArray systemVariableNameDescriptionArray;//������ ��� �������� ���������� ���� ����������
	tMaterialArray materialArray;//������ ������������ ����������, ������� ��������� �������� ���������
	tSectionArray sectionArray;//������ ������������ ����� �������, ����������� �������� ���������
	//tPoint3dArray point3dArray;//������ 3� �����, ������� �������� ������ �� - ���������
};

