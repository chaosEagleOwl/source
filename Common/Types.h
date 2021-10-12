//#include "StdAfx.h"
#include "resource.h"
#include <vector>
#include <map>
#include <C:\ArxLib\eigen\Eigen\Dense>
#include <C:\ArxLib\eigen\Eigen\Sparse>


//����� ������� ���� �������, ����������� ������� ���������

using namespace std;
using namespace Eigen;//���������� ������������ ���� Eigen ��� ����������� �������� ��������
#pragma once

typedef struct tIndexNameFEMSolver//������� ���� ���� ����������
{
	//� ��������� ����� ������� ���������� ��������, ����� � ���� ������ ������� �������� ������ �� ����� �����, ������� �������� �������
	//�� ������ �� ������ ������ ��������, ������� ����� ��������� ���������� �������� � ���������� �������, � � ��������� ��� ���������� ���������� �� ��������
	//������ ��� ������ ������� ���� ���� ������ ���������� (������ ���������, ����������� �������� � �.�.)
	//��� �����, ����� ����� ���� �������� ������������� �������� �� ��������� �������� �� ������� ����� ����������
	//���������� ���������� ������� ���� � ��������� ���� � ��������� � ������ "tFEMSolver.cpp" - tIndexNameFEMSolver indexName;
	//�������������� ���� ���������� � �������� �� ������ ������ ������������ � ��������� 
	//void tFEMSolver::registerStandartSystemVariableName(), ������� ���� ���������� � arxEntryPoint � ��������� CArxProject1App () : AcRxArxApp ()

	long iVx, iVy, iVz, iUx, iUy, iUz;//������� ���� ������� �����������
	long iRx, iRy, iRz, iMx, iMy, iMz;//������� ���� ������� �������
	long iE, imu, it;//������� ������ ���������, ������������ ��������, ������� �����
};


typedef map <CString, double> tNameValueDoubletMap;//��� ������ ����-��������, ������� ��������� ������� ���� ������(���) � �������������� �� �������� double � ������ �������� ������ � �������� �� ����� 
typedef map <CString, long> tNameValueLongintMap;//��� ������ ����-��������, ������� ��������� ������� ���� ������(���) � �������������� �� �������� long � ������ �������� ������ � �������� �� �����
typedef map <CString, CString> tNameValueCStringMap;//��� ������ ����-��������, ������� ��������� ������� ���� ������(���) � �������������� �� �������� CString � ������ �������� ������ � �������� �� �����
typedef vector <long> tLongintArray;//��� - ������ ����� �����
typedef vector <CString> tCStringArray;//��� - ������ ����� �����
typedef map <long, double> tIndexValueDoubletMap;//��� ������ ����-��������, ������� ��������� ������� ���� ������(�����) � �������������� ��� �������� double � ������ �������� ������ � �������� �� ������� 

typedef struct tNameValueDescriptionValue//��� ��� �������� ���� ����������� ����������, ������� ����������� � �������� ��������
{
	CString nameValue;//��� ����������, �������� - "E"
	CString descriptionValue;//�������� ����������, �������� "������ ���������"
	CString dimensionValue;//����������� ����������, �������� "���", ����� ��2, �, �� � �.�.
};
typedef vector <tNameValueDescriptionValue> tNameValueDescriptionValueArray;//��� - ������ ����� �����

typedef struct tMaterial//���, ����������� ���������� �������������� ��������� (������� ����� �������� �������������� � �.�.) 
{
	CString nameMaterial;//��� ��������� - �����������, �������� �� �����������. ���� ������� �� �������� �������� ��������, � �������� ��� ��������� - ��������� ���� ������ �������� ������ �����.
	tIndexValueDoubletMap indexValueMap;//������ ����-��������: ������ - ��� ����� ���������� ���������� � ������� tNameValueDescriptionValueArray, �������� Double - �������� ����������
};
typedef vector <tMaterial> tMaterialArray;//��� - ������ ����� �����

typedef struct tSection//���, ����������� �������������� �������������� ��������� (������� ��������, ������ ������� � �.�.)
{
	CString nameSection;//��� ������� - �����������, �������� �� �����������. ���� ������� �� �������� �������� ��������, � �������� ��� ������� - ��������� ���� ������ �������� ������ �����.
	tIndexValueDoubletMap indexValueMap;//������ ����-��������: ������ - ��� ����� ���������� ���������� � ������� tNameValueDescriptionValueArray, �������� Double - �������� ����������
};
typedef vector <tSection> tSectionArray;//��� - ������ ����� �����


typedef struct tPoint3d//��� ���������� �����
{
	double x;
	double y;
	double z;
};
typedef vector <tPoint3d> tPoint3dArray;//���, ������� ������ ������ ���������� �����

typedef struct tFiniteElement//�������� �������
{
	long indexFEType; //����� ���� ��������� �������� � ������� ����� �������� ���������
	long indexMaterial; //����� ��������� ��������� �������� � ���������� ������� ����������
	long indexSection; //����� ��������� ��������� �������� � ���������� ������� �������
	tLongintArray indexPoint3d;//������� ����� ��������� �������� � ���������� ������� �����
	
};
typedef vector <tFiniteElement> tFiniteElementArray;//��� - ������ �������� ���������


//��������� ����������� ���, ���������� �������� ����� ������� ������ �������� ���������� ������ ���������� ��� ������ �������� ���������
typedef bool (*tLocalStiffnessMatrixProcedure)(const tFiniteElement & finiteElement, const tPoint3dArray& point3dArray, const tMaterialArray & materialArray, const tSectionArray &sectionArray, MatrixXd & localStiffnessMatrix);
//finiteElement - ������ �� �������� �������, ������� ��������� �������� ����������� ��. ��� tFiniteElement 
// point3dArray - ������ �� ���������� ������ ���� ����� �������, ��. ��� tPoint3dArray
//materialArray - ������ �� ���������� ������ ����������, ��. ��� tMaterialArray 
//sectionArray - ������ �� ���������� ������ �������������� ������������� ���������, ��. ��� tSectionArray
//localStiffnessMatrix - ����������� ��������� ������� ��������� ��������� ��������, ���������� � ����������� ��� Eigen::MatrixXd 



//��������� !
typedef struct tFiniteElementType//�������� ���� ��������� ��������
{
	CString nameElementType;//��� ���� ��������� ��������, �������� - "����������� �� ��������"
	tLocalStiffnessMatrixProcedure localStiffnessMatrixProcedure;//����������, ������� ������ ����� ��������� ��� ���������� ��������� ������� ���������
	//... ����� ������ ���� ������ ����������-��������� - ���������� ���������� ������, ������� �� �������� ����������� � �.�.	
};
