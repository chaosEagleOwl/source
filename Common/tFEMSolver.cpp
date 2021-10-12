#include "stdafx.h"
#include "tFEMSolver.h"
#pragma once

using namespace std;
//using namespace indexNameFEMsolver;

tIndexNameFEMSolver indexName;//Глобальная переменная, которая хранит все индексы имен переменных

void tFEMSolver::registerStandartSystemVariableName()
{
	long i;
	//регистрируем имена системных переменных, которые создаются при инициализации программы

	
	//имена переменных, связанные с кодировкой усилий и перемещений
	if (!registerSystemVariableName(L"Vx", L"перемещение по оси X", L"м", indexName.iVx)) {
		acutPrintf(L"Переменная с именем Vx была зарегистрирована ранее");
	}

	if (!registerSystemVariableName(L"Vy", L"перемещение по оси Y", L"м", indexName.iVy)) {
		acutPrintf(L"Переменная с именем Vy была зарегистрирована ранее");
	}

	if (!registerSystemVariableName(L"Vz", L"перемещение по оси Z", L"м", indexName.iVz)) {
		acutPrintf(L"Переменная с именем Vz была зарегистрирована ранее");
	}

	if (!registerSystemVariableName(L"Ux", L"угол поворота вокруг оси X", L"радиан", indexName.iUx)) {
		acutPrintf(L"Переменная с именем Ux была зарегистрирована ранее");
	}

	if (!registerSystemVariableName(L"Uy", L"угол поворота вокруг оси Y", L"радиан", indexName.iUy)) {
		acutPrintf(L"Переменная с именем Uy была зарегистрирована ранее");
	}

	if (!registerSystemVariableName(L"Uz", L"угол поворота вокруг оси Z", L"радиан", indexName.iUz)) {
		acutPrintf(L"Переменная с именем Uz была зарегистрирована ранее");
	}

	if (!registerSystemVariableName(L"Rx", L"сила вдоль оси X", L"Н", indexName.iRx)) {
		acutPrintf(L"Переменная с именем Rx была зарегистрирована ранее");
	}

	if (!registerSystemVariableName(L"Ry", L"сила вдоль оси Y", L"Н", indexName.iRy)) {
		acutPrintf(L"Переменная с именем Ry была зарегистрирована ранее");
	}

	if (!registerSystemVariableName(L"Rz", L"сила вдоль оси Z", L"Н", indexName.iRz)) {
		acutPrintf(L"Переменная с именем Rz была зарегистрирована ранее");
	}

	if (!registerSystemVariableName(L"Mx", L"момент относительно оси X", L"радиан", indexName.iMx)) {
		acutPrintf(L"Переменная с именем Mx была зарегистрирована ранее");
	}

	if (!registerSystemVariableName(L"My", L"момент относительно оси Y", L"радиан", indexName.iMy)) {
		acutPrintf(L"Переменная с именем My была зарегистрирована ранее");
	}

	if (!registerSystemVariableName(L"Mz", L"момент относительно оси Z", L"радиан", indexName.iMz)) {
		acutPrintf(L"Переменная с именем Mz была зарегистрирована ранее");
	}
	
	//имена переменных, связанные с кодировкой характеристик материалов
	if (!registerSystemVariableName(L"E", L"модуль упругости", L"МПа", indexName.iE)) {
		acutPrintf(L"Переменная с именем E была зарегистрирована ранее");
	}

	if (!registerSystemVariableName(L"mu", L"коэффициент пуассона", L"д.е.", indexName.imu)) {
		acutPrintf(L"Переменная с именем mu была зарегистрирована ранее");
	}

	//имена переменных, связанные с кодировкой геометрических харакетристик плит и стержней
	if (!registerSystemVariableName(L"t", L"толщина плиты", L"м", indexName.it)) {
		acutPrintf(L"Переменная с именем t была зарегистрирована ранее");
	}
	
	
}
tFEMSolver::tFEMSolver()
{

}


tFEMSolver::~tFEMSolver()
{
	long i,n;
	
	systemVariableNameIndexMap.clear();//очищаем массив при выходе
	systemVariableNameDescriptionArray.clear();//очищаем массив при выходе
		
	//Очищаем массив материалов
	n=materialArray.size();
	for (i = 0; i < n; i++) {
		materialArray[i].indexValueMap.clear();
	}
	materialArray.clear();

	//Очищаем массив сечений
	n = sectionArray.size();
	for (i = 0; i < n; i++) {
		sectionArray[i].indexValueMap.clear();
	}
	sectionArray.clear();

	
	
}

long tFEMSolver::getSystemVariableIndex(CString systemVariableName)
{//Функция для получения индекса глобального имени переменной в глобавльном массиве имен переменных 
	// вслучае, если глобальная переменная с таким индексом не зарегистрирована, возращается -1
	long i;
	CString ts = systemVariableName;//переменная, которая будет хранить имя в нижнем регистре
	ts.MakeLower();

	tNameValueLongintMap::iterator it1;//итератор

	it1 = systemVariableNameIndexMap.find(ts);//ищем элемент с именем systemVariableName в нижнем регистре

	if (it1 == systemVariableNameIndexMap.end()) {
		i = -1;//элемент не найден, возвращать буем -1
	}
	else {
		i = it1->second;//элемент найден, возвращаем индекс имени в вектор systemVariableNameArray
	}
	return i;

}
bool tFEMSolver::registerSystemVariableName(CString newSystemVariableName, CString newSystemVariableDescription, CString newSystemVariableDimension, long& indexSystemVariableName)
{//Процедура для регистрации глобального имени переменной с получением индекса
	//возвращает indexSystemVariableName - индекс, который используется вместо имени переменной при получении значений из различных хранилищ
	//возвращает true - если имя переменной было глобально зарегистрировано
	//возвращает false - если имя переменной уже было глобально зарегистрировано ранее
	long i;
	bool retValBool=false;//условие устанавливаем false, так как по умолчанию предполагаем, что переменную не получиться зарегистрировать
	i=getSystemVariableIndex(newSystemVariableName);
	if (i < 0) {
		//Существующее имя 
		tNameValueDescriptionValue newVariable;
		
		newVariable.nameValue = newSystemVariableName;
		newVariable.nameValue.MakeLower();//имя переменных сохраняется только в нижнем регистре для исключения конфликтов имен

		newVariable.descriptionValue = newSystemVariableDescription;
		newVariable.descriptionValue.MakeLower();//имя переменных сохраняется только в нижнем регистре для исключения конфликтов имен

		newVariable.dimensionValue = newSystemVariableDimension;
		newVariable.dimensionValue.MakeLower();//имя переменных сохраняется только в нижнем регистре для исключения конфликтов имен
		
		i = systemVariableNameDescriptionArray.size();//Получаем индекс, который будет присвоен новому элементу
		systemVariableNameDescriptionArray.push_back(newVariable);//Добавляем описание новой переменной в вектор с описанием переменных

		systemVariableNameIndexMap.insert(make_pair(newVariable.nameValue, i));

		retValBool = true;//Возращаем true, так как переменная была зарегистрирована
	}
	return retValBool;
}