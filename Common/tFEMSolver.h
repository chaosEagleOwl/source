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
	tNameValueLongintMap systemVariableNameIndexMap;//Структура для быстрого получения индекса ИМЕНИ переменной (в массиве имен переменных) по имени переменной
	tNameValueDescriptionValueArray systemVariableNameDescriptionArray;//массив для хранения глобальных имен переменных
	tMaterialArray materialArray;//массив используемых материалов, которые назначены конечным элементам
	tSectionArray sectionArray;//массив используемых типов сечений, назначенных конечным элементам
	//tPoint3dArray point3dArray;//массив 3д точек, которые являются узлами КЭ - элементов
};

