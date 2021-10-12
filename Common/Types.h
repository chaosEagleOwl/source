//#include "StdAfx.h"
#include "resource.h"
#include <vector>
#include <map>
#include <C:\ArxLib\eigen\Eigen\Dense>
#include <C:\ArxLib\eigen\Eigen\Sparse>


//нужно описать типы функций, формирующих матрицы жесткости

using namespace std;
using namespace Eigen;//Подключаем пространство имен Eigen для возможности описания массивов
#pragma once

typedef struct tIndexNameFEMSolver//индексы всех имен переменных
{
	//в программе будет большое количество моментов, когда к базе данных следует получать доступ по имени ключа, которое является строкой
	//но доступ по строке обычно тормозит, поэтому имена строковых переменные хранятся в глобальном массиве, а в программе имя переменной заменяется ее индексом
	//данный тип хранит индексы имен всех важных переменных (модуль упругости, коэффициент пуассона и т.д.)
	//это нужно, чтобы можно было получать необходимовые значения из некоторых хранилищ по индексу имени переменной
	//глобальная переменная данного типа в программе одна и объявлена в модуле "tFEMSolver.cpp" - tIndexNameFEMSolver indexName;
	//соспоставление имен переменных и индексов на данный момент производится в процедуре 
	//void tFEMSolver::registerStandartSystemVariableName(), которая пока вызывается в arxEntryPoint в процедуре CArxProject1App () : AcRxArxApp ()

	long iVx, iVy, iVz, iUx, iUy, iUz;//индексы имен узловых перемещений
	long iRx, iRy, iRz, iMx, iMy, iMz;//индексы имен узловых реакций
	long iE, imu, it;//индексы модуля упругости, коэффициента Пуассона, толщины плиты
};


typedef map <CString, double> tNameValueDoubletMap;//Тип массив ключ-значение, который позволяет хранить пару строка(имя) и соотвествующее ей значение double и быстро получять доступ к значению по имени 
typedef map <CString, long> tNameValueLongintMap;//Тип массив ключ-значение, который позволяет хранить пару строка(имя) и соотвествующее ей значение long и быстро получять доступ к значению по имени
typedef map <CString, CString> tNameValueCStringMap;//Тип массив ключ-значение, который позволяет хранить пару строка(имя) и соотвествующее ей значение CString и быстро получять доступ к значению по имени
typedef vector <long> tLongintArray;//Тип - массив целых чисел
typedef vector <CString> tCStringArray;//Тип - массив целых чисел
typedef map <long, double> tIndexValueDoubletMap;//Тип массив ключ-значение, который позволяет хранить пару индекс(номер) и соотвествующее ему значение double и быстро получять доступ к значению по индексу 

typedef struct tNameValueDescriptionValue//тип для описания мени глобавльной переменной, включая размерность и тестовое описание
{
	CString nameValue;//имя переменной, например - "E"
	CString descriptionValue;//описание переменной, например "Модуль упругости"
	CString dimensionValue;//размерность переменной, например "МПа", также см2, т, кН и т.д.
};
typedef vector <tNameValueDescriptionValue> tNameValueDescriptionValueArray;//Тип - массив целых чисел

typedef struct tMaterial//тип, описывающий физические характеристики материала (включая точки диаграмм деформирования и т.д.) 
{
	CString nameMaterial;//имя материала - опционально, задавать не обязательно. есть вариант не задавать числовые значения, а задавать имя материала - программа сама нужные значения должна взять.
	tIndexValueDoubletMap indexValueMap;//массив ключ-значение: индекс - это номер глобальной переменной в массиве tNameValueDescriptionValueArray, значение Double - значение переменной
};
typedef vector <tMaterial> tMaterialArray;//Тип - массив целых чисел

typedef struct tSection//тип, описывающий геометрические характеристики элементов (сечений стержней, толщин пластин и т.д.)
{
	CString nameSection;//имя сечения - опционально, задавать не обязательно. есть вариант не задавать числовые значения, а задавать имя сечения - программа сама нужные значения должна взять.
	tIndexValueDoubletMap indexValueMap;//массив ключ-значение: индекс - это номер глобальной переменной в массиве tNameValueDescriptionValueArray, значение Double - значение переменной
};
typedef vector <tSection> tSectionArray;//Тип - массив целых чисел


typedef struct tPoint3d//тип трехмерной точки
{
	double x;
	double y;
	double z;
};
typedef vector <tPoint3d> tPoint3dArray;//Тип, который хранит массив трехмерных точек

typedef struct tFiniteElement//конечный элемент
{
	long indexFEType; //номер типа конечного элемента в массиве типов конечных элементов
	long indexMaterial; //номер материала конечного элемента в глобальном массиве материалов
	long indexSection; //номер материала конечного элемента в глобальном массиве сечений
	tLongintArray indexPoint3d;//Индексы узлов конечного элемента в глобальном массиве точек
	
};
typedef vector <tFiniteElement> tFiniteElementArray;//Тип - массив конечных элементов


//Описываем процедурный тип, переменные которого будут хранить адреса процедур вычисления матриц жесткостей для разных конечных элементов
typedef bool (*tLocalStiffnessMatrixProcedure)(const tFiniteElement & finiteElement, const tPoint3dArray& point3dArray, const tMaterialArray & materialArray, const tSectionArray &sectionArray, MatrixXd & localStiffnessMatrix);
//finiteElement - ссылка на конечный элемент, матрица жесткости которого вычисляется см. тип tFiniteElement 
// point3dArray - ссылка на глобальный массив всех узлов системы, см. тип tPoint3dArray
//materialArray - ссылка на глобальный массив материалов, см. тип tMaterialArray 
//sectionArray - ссылка на глобальный массив геометрических характеристик элементов, см. тип tSectionArray
//localStiffnessMatrix - вычисленная локальная матрица жесткости конечного элемента, занесенная в стандартный тип Eigen::MatrixXd 



//Доделывай !
typedef struct tFiniteElementType//описание типа конечного элемента
{
	CString nameElementType;//имя типа конечного элемента, например - "треугольный КЭ оболочки"
	tLocalStiffnessMatrixProcedure localStiffnessMatrixProcedure;//Переменная, которая хранит адрес процедуры для вычисления локальной матрицы жесткости
	//... здесь должны быть другие переменные-процедуры - вычисления внутренних усилий, реакций от заданных перемещений и т.д.	
};
