#include "stdafx.h"
#include "tFEMSolver.h"
#pragma once

using namespace std;
//using namespace indexNameFEMsolver;

tIndexNameFEMSolver indexName;//���������� ����������, ������� ������ ��� ������� ���� ����������

void tFEMSolver::registerStandartSystemVariableName()
{
	long i;
	//������������ ����� ��������� ����������, ������� ��������� ��� ������������� ���������

	
	//����� ����������, ��������� � ���������� ������ � �����������
	if (!registerSystemVariableName(L"Vx", L"����������� �� ��� X", L"�", indexName.iVx)) {
		acutPrintf(L"���������� � ������ Vx ���� ���������������� �����");
	}

	if (!registerSystemVariableName(L"Vy", L"����������� �� ��� Y", L"�", indexName.iVy)) {
		acutPrintf(L"���������� � ������ Vy ���� ���������������� �����");
	}

	if (!registerSystemVariableName(L"Vz", L"����������� �� ��� Z", L"�", indexName.iVz)) {
		acutPrintf(L"���������� � ������ Vz ���� ���������������� �����");
	}

	if (!registerSystemVariableName(L"Ux", L"���� �������� ������ ��� X", L"������", indexName.iUx)) {
		acutPrintf(L"���������� � ������ Ux ���� ���������������� �����");
	}

	if (!registerSystemVariableName(L"Uy", L"���� �������� ������ ��� Y", L"������", indexName.iUy)) {
		acutPrintf(L"���������� � ������ Uy ���� ���������������� �����");
	}

	if (!registerSystemVariableName(L"Uz", L"���� �������� ������ ��� Z", L"������", indexName.iUz)) {
		acutPrintf(L"���������� � ������ Uz ���� ���������������� �����");
	}

	if (!registerSystemVariableName(L"Rx", L"���� ����� ��� X", L"�", indexName.iRx)) {
		acutPrintf(L"���������� � ������ Rx ���� ���������������� �����");
	}

	if (!registerSystemVariableName(L"Ry", L"���� ����� ��� Y", L"�", indexName.iRy)) {
		acutPrintf(L"���������� � ������ Ry ���� ���������������� �����");
	}

	if (!registerSystemVariableName(L"Rz", L"���� ����� ��� Z", L"�", indexName.iRz)) {
		acutPrintf(L"���������� � ������ Rz ���� ���������������� �����");
	}

	if (!registerSystemVariableName(L"Mx", L"������ ������������ ��� X", L"������", indexName.iMx)) {
		acutPrintf(L"���������� � ������ Mx ���� ���������������� �����");
	}

	if (!registerSystemVariableName(L"My", L"������ ������������ ��� Y", L"������", indexName.iMy)) {
		acutPrintf(L"���������� � ������ My ���� ���������������� �����");
	}

	if (!registerSystemVariableName(L"Mz", L"������ ������������ ��� Z", L"������", indexName.iMz)) {
		acutPrintf(L"���������� � ������ Mz ���� ���������������� �����");
	}
	
	//����� ����������, ��������� � ���������� ������������� ����������
	if (!registerSystemVariableName(L"E", L"������ ���������", L"���", indexName.iE)) {
		acutPrintf(L"���������� � ������ E ���� ���������������� �����");
	}

	if (!registerSystemVariableName(L"mu", L"����������� ��������", L"�.�.", indexName.imu)) {
		acutPrintf(L"���������� � ������ mu ���� ���������������� �����");
	}

	//����� ����������, ��������� � ���������� �������������� ������������� ���� � ��������
	if (!registerSystemVariableName(L"t", L"������� �����", L"�", indexName.it)) {
		acutPrintf(L"���������� � ������ t ���� ���������������� �����");
	}
	
	
}
tFEMSolver::tFEMSolver()
{

}


tFEMSolver::~tFEMSolver()
{
	long i,n;
	
	systemVariableNameIndexMap.clear();//������� ������ ��� ������
	systemVariableNameDescriptionArray.clear();//������� ������ ��� ������
		
	//������� ������ ����������
	n=materialArray.size();
	for (i = 0; i < n; i++) {
		materialArray[i].indexValueMap.clear();
	}
	materialArray.clear();

	//������� ������ �������
	n = sectionArray.size();
	for (i = 0; i < n; i++) {
		sectionArray[i].indexValueMap.clear();
	}
	sectionArray.clear();

	
	
}

long tFEMSolver::getSystemVariableIndex(CString systemVariableName)
{//������� ��� ��������� ������� ����������� ����� ���������� � ����������� ������� ���� ���������� 
	// �������, ���� ���������� ���������� � ����� �������� �� ����������������, ����������� -1
	long i;
	CString ts = systemVariableName;//����������, ������� ����� ������� ��� � ������ ��������
	ts.MakeLower();

	tNameValueLongintMap::iterator it1;//��������

	it1 = systemVariableNameIndexMap.find(ts);//���� ������� � ������ systemVariableName � ������ ��������

	if (it1 == systemVariableNameIndexMap.end()) {
		i = -1;//������� �� ������, ���������� ���� -1
	}
	else {
		i = it1->second;//������� ������, ���������� ������ ����� � ������ systemVariableNameArray
	}
	return i;

}
bool tFEMSolver::registerSystemVariableName(CString newSystemVariableName, CString newSystemVariableDescription, CString newSystemVariableDimension, long& indexSystemVariableName)
{//��������� ��� ����������� ����������� ����� ���������� � ���������� �������
	//���������� indexSystemVariableName - ������, ������� ������������ ������ ����� ���������� ��� ��������� �������� �� ��������� ��������
	//���������� true - ���� ��� ���������� ���� ��������� ����������������
	//���������� false - ���� ��� ���������� ��� ���� ��������� ���������������� �����
	long i;
	bool retValBool=false;//������� ������������� false, ��� ��� �� ��������� ������������, ��� ���������� �� ���������� ����������������
	i=getSystemVariableIndex(newSystemVariableName);
	if (i < 0) {
		//������������ ��� 
		tNameValueDescriptionValue newVariable;
		
		newVariable.nameValue = newSystemVariableName;
		newVariable.nameValue.MakeLower();//��� ���������� ����������� ������ � ������ �������� ��� ���������� ���������� ����

		newVariable.descriptionValue = newSystemVariableDescription;
		newVariable.descriptionValue.MakeLower();//��� ���������� ����������� ������ � ������ �������� ��� ���������� ���������� ����

		newVariable.dimensionValue = newSystemVariableDimension;
		newVariable.dimensionValue.MakeLower();//��� ���������� ����������� ������ � ������ �������� ��� ���������� ���������� ����
		
		i = systemVariableNameDescriptionArray.size();//�������� ������, ������� ����� �������� ������ ��������
		systemVariableNameDescriptionArray.push_back(newVariable);//��������� �������� ����� ���������� � ������ � ��������� ����������

		systemVariableNameIndexMap.insert(make_pair(newVariable.nameValue, i));

		retValBool = true;//��������� true, ��� ��� ���������� ���� ����������������
	}
	return retValBool;
}