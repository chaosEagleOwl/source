// (C) Copyright 2002-2007 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------



#include "StdAfx.h"
#include "resource.h"

//-----------------------------------------------------------------------------


#define szRDS _RXST("")


//using namespace utf8util;
#pragma once

//char ch25, ch48, ch57;

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CArxProject1App : public AcRxArxApp {

public:


	CArxProject1App () : AcRxArxApp () { 
		//инициализация
		
	}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		// TODO: Add your initialization code here
		
		

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		// TODO: Unload dependencies here

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}


	// - ArxProject1._MyTest command (do not rename)	
	static void ArxProject1_MYHELLO(void)
	{
		// Add your code for command ArxProject1._AddProf here
		AfxMessageBox(L"Привет, мир.");
	
		/*
		ads_name ename;
		ads_point pt;
		AcDbObjectIdArray arIdKontur;

		ACHAR ach[3024];
		AcDbObjectId idBlock, idObj;
		CString tNameBlock;
		Adesk::Int32 i, max;
		AcDbObject* pObject;
		AcDbPolyline* mPLine;

		ads_name sset, entres;

		long n, kolZnak;
		ACHAR ach1[1024];
		CString kolZnak1;
		double hag = 0;
		AcDbLine* mLine;
		Acad::ErrorStatus es;
		TMDocument tDoc;
		ads_point pt1;
		CString csFult, cs1;
		TMDocument tDocRes;
		CString errorString;
		

		acutPrintf(_T("\nВыберите отрезки и полилинии, описывающие контур продавливания: "));
		acedSSGet(NULL, NULL, NULL, NULL, sset);
		arIdKontur.removeAll();
		//arIdPloshadka.removeAll();
		tDocRes.clear();

		if (acedSSLength(sset, &max) != RTNORM) {
			return;
		}

		double val;
		CString valNumer;
		long startNumer = -1;
		valNumer = "";
		CString fullValue, tVal, csHag, csDim;
		kolZnak = PM_param.KolZnak;
		long kolshag;
		str1(hag, csHag, 0);

		double leng;
		CString lay;
		double totLeng = 0;
		bool est = false;
		double Sx, Sy, A, xc, yc;
		AcGePoint3d p1, p2;
		CString csRb, csH0;
		double Rbt, H0, tRbt;
		long tNomer;
		double tSx, tA, tSy;
		AcDbPolyline::SegType Tseg1;

		Rbt = 0;
		tRbt = 0;

		Sx = 0;
		Sy = 0;
		A = 0;
		for (i = 0; i < max; i++) {
			if (acedSSName(sset, i, entres) == RTNORM) {
				idObj = idObj.setFromOldId(entres[0]);
				arIdKontur.append(idObj);
				est = false;
				
				if (acdbOpenObject(pObject, idObj, AcDb::kForRead) != Acad::eOk) {
					acedSSFree(sset);
					return;
				}

				if (pObject->isA() == AcDbLine::desc()) {
					mLine = ((AcDbLine*)pObject);
					p1 = mLine->startPoint();
					p2 = mLine->endPoint();
					leng = p1.distanceTo(p2);
					xc = (p1.x + p2.x) / 2;
					yc = (p1.y + p2.y) / 2;
					lay = mLine->layer();
					//extract_param_to_array(
					//Sx=Sx+
					tDoc.clear();
					extractStringNameValueToDoc(lay, tDoc);
					if (!tDoc.GetValue_by_Name(L"[Rbt]", csRb, tNomer)) {
						AfxMessageBox(L"В имени слоя отрезков и полилиний контура продавливания должен быть определено расчетное сопротивление бетона растяжению (в МПа) формате [Rbt]1.15");
						acedSSFree(sset);
						pObject->close();
						return;
					}
					val1(csRb, tRbt);
					if (ravno(tRbt, 0)) {
						AfxMessageBox(L"В имени слоя отрезков и полилиний контура продавливания должен быть определено расчетное сопротивление бетона растяжению НЕ РАВНОЕ НУЛЮ (в МПа) формате [Rbt]1.15");
						acedSSFree(sset);
						pObject->close();
						return;
					}
					if (ravno(Rbt, 0)) {
						Rbt = tRbt;
					}
					else {
						if (!ravno(tRbt, Rbt)) {
							AfxMessageBox(L"Обнаружено разное расчетное сопротивление бетона растяжению. В имени слоя отрезков и полилиний контура продавливания должен быть определено ТОЛЬКО ОДНО расчетное сопротивление бетона растяжению ОДИНАКОВОЕ ДЛЯ ВСЕХ ОТРЕЗКОВ КОНТУРА");
							acedSSFree(sset);
							pObject->close();
							return;
						}
					}

					if (!tDoc.GetValue_by_Name(L"[H0]", csH0, tNomer)) {
						AfxMessageBox(L"В имени слоя отрезков и полилиний контура продавливания должен быть определена приведенная рабочая высота сечения (в метрах) по п.8.1.47 СП 63.13330.2018 в формате [H0]0.22");
						acedSSFree(sset);
						pObject->close();
						return;
					}
					val1(csH0, H0);
					if (ravno(H0, 0)) {
						AfxMessageBox(L"В имени слоя отрезков и полилиний контура продавливания должен быть определена приведенная рабочая высота сечения (в метрах) по п.8.1.47 СП 63.13330.2018 в формате [H0]0.22");
						acedSSFree(sset);
						pObject->close();
						return;
					}
					tA = leng * H0;
					tSx = tA * xc;
					tSy = tA * yc;
					Sx = Sx + tSx;
					Sy = Sy + tSy;

					A = A + tA;

					est = true;
				}
				//AcDbArc



				if (pObject->isA() == AcDbPolyline::desc()) {
					mPLine = ((AcDbPolyline*)pObject);
					lay = mPLine->layer();
					tDoc.clear();
					extractStringNameValueToDoc(lay, tDoc);
					if (!tDoc.GetValue_by_Name(L"[Rbt]", csRb, tNomer)) {
						AfxMessageBox(L"В имени слоя отрезков и полилиний контура продавливания должен быть определено расчетное сопротивление бетона растяжению (в МПа) формате [Rbt]1.15");
						acedSSFree(sset);
						pObject->close();
						return;
					}
					val1(csRb, tRbt);
					if (ravno(tRbt, 0)) {
						AfxMessageBox(L"В имени слоя отрезков и полилиний контура продавливания должен быть определено расчетное сопротивление бетона растяжению НЕ РАВНОЕ НУЛЮ (в МПа) формате [Rbt]1.15");
						acedSSFree(sset);
						pObject->close();
						return;
					}
					if (ravno(Rbt, 0)) {
						Rbt = tRbt;
					}
					else {
						if (!ravno(tRbt, Rbt)) {
							AfxMessageBox(L"Обнаружено разное расчетное сопротивление бетона растяжению. В имени слоя отрезков и полилиний контура продавливания должен быть определено ТОЛЬКО ОДНО расчетное сопротивление бетона растяжению ОДИНАКОВОЕ ДЛЯ ВСЕХ ОТРЕЗКОВ КОНТУРА");
							acedSSFree(sset);
							pObject->close();
							return;
						}
					}

					if (!tDoc.GetValue_by_Name(L"[H0]", csH0, tNomer)) {
						AfxMessageBox(L"В имени слоя отрезков и полилиний контура продавливания должен быть определена приведенная рабочая высота сечения (в метрах) по п.8.1.47 СП 63.13330.2018 в формате [H0]0.22");
						acedSSFree(sset);
						pObject->close();
						return;
					}
					val1(csH0, H0);
					if (ravno(H0, 0)) {
						AfxMessageBox(L"В имени слоя отрезков и полилиний контура продавливания должен быть определена приведенная рабочая высота сечения (в метрах) по п.8.1.47 СП 63.13330.2018 в формате [H0]0.22");
						acedSSFree(sset);
						pObject->close();
						return;
					}


					n = mPLine->numVerts();
					double d, mlength;
					n = mPLine->numVerts() + 1;
					for (i = 0; i < n; i++) {
						es = mPLine->getBulgeAt(i, d);
						if (es != Acad::eOk)
							break;//Сегмента нет
						Tseg1 = mPLine->segType(i);
						//switch(mPLine->segType(i)){ 
						switch (Tseg1) {
						case AcDbPolyline::kLine: {
							AcGeLineSeg3d line;
							mPLine->getLineSegAt(i, line);
							mlength = line.length();
							p1 = line.startPoint();
							p2 = line.endPoint();
							xc = (p1.x + p2.x) / 2;
							yc = (p1.y + p2.y) / 2;
							tA = mlength * H0;

							tSx = tA * xc;
							tSy = tA * yc;
							Sx = Sx + tSx;
							Sy = Sy + tSy;

							A = A + tA;

							est = true;
						} break;
						case AcDbPolyline::kArc: {
							est = false;
							AfxMessageBox(L"Обнаружен дуговой сегмент полилинии контура продавливания. При расчете на продавливание контур продавливания должен состоять только из ЛИНЕЙНЫХ сегментов полилинии.");
							acedSSFree(sset);
							pObject->close();
							return;
							
						} break;
							
							break;
						}

					}
					//}					

				}
				pObject->close();
				if (!est) {
					AfxMessageBox(L"Обнаружен нелинейный сегмент полилинии контура продавливания. При расчете на продавливание контур продавливания должен состоять только из ЛИНЕЙНЫХ сегментов полилинии.");
					acedSSFree(sset);

				}
			}

		}
		acedSSFree(sset);

		if (ravno(A, 0)) {
			AfxMessageBox(L"Общая площадь контура продавливания оказалась равна нулю. Для расчета следует выбирать корректный контур продавливания из отрезков и полилиний.");
			return;
		}

		xc = Sx / A;
		yc = Sy / A;
		double tRadius;
		tRadius = PM_param.mHeightText * PM_param.ScaleFactor * 0.1;
		pt1[0] = xc;
		pt1[1] = yc;
		pt1[2] = 0;

		myaddCircleModel(pt1, tRadius);

		ads_point pt0;
		if (!acedGetPoint(NULL, _T("Укажите точку центра тяжести площадки приложения нагруки (центр колонны и т.п.)"), pt0)) {
			return;
		}

		

		double F, Mx, My;
		double Fbult, Ab;
		double Ix, Iy, Xmax, Xmin, Ymax, Ymin;
		double Hx, Hy;


		if (acedGetString(1, _T("Введите продольную вертикальную нагрузку на продавливание Rz, тонн :"), ach1) != RTNORM) {
			return;
		}
		val1(ach1, F);
		F = abs(F);

		str1(Rbt, cs1, PM_param.KolZnak);
		tDocRes.Param.add_name_value(L"[Rbt]", cs1);

		str1(F, cs1, PM_param.KolZnak);
		tDocRes.Param.add_name_value(L"[F]", cs1);

		str1(A / 1000 / H0, cs1, PM_param.KolZnak);
		tDocRes.Param.add_name_value(L"[u]", cs1);

		str1(A / 1000, cs1, PM_param.KolZnak);
		tDocRes.Param.add_name_value(L"[Ab]", cs1);

		str1(H0, cs1, PM_param.KolZnak);
		tDocRes.Param.add_name_value(L"[H0]", cs1);


		Ab = A / 1000;//м2
		Fbult = Ab * Rbt * 1000000 / 10000;//т. формула (8.88) СП 63.13330.2018
		double ontF = F / Fbult;

		str1(Fbult, cs1, PM_param.KolZnak);
		tDocRes.Param.add_name_value(L"[Fbult]", cs1);


		if (bolshe(ontF, 1) | ravno(ontF, 1)) {
			str1(Fbult, csFult, PM_param.KolZnak);
			//CString csFult,cs1;
			cs1 = L"Действующая нагрузка на продавливание превышает предельную нагрузку на продавливание согласно по формуле (8.88) СП 63.13330.2018 Fbult=Rbt·Ab=" + csFult;
			AfxMessageBox(cs1);
			return;
		}

		str1(ontF, cs1, PM_param.KolZnak);
		tDocRes.Param.add_name_value(L"[otnF]", cs1);

		if (acedGetString(1, _T("Введите изгибающий момент на продавливание Mx=Mloc,x/2, тонн :"), ach1) != RTNORM) {
			return;
		}
		val1(ach1, Mx);

		str1(Mx, cs1, PM_param.KolZnak);
		tDocRes.Param.add_name_value(L"[Mx1]", cs1);


		if (acedGetString(1, _T("Введите изгибающий момент на продавливание My=Mloc,y/2, тонн :"), ach1) != RTNORM) {
			return;
		}
		val1(ach1, My);

		str1(My, cs1, PM_param.KolZnak);
		tDocRes.Param.add_name_value(L"[My1]", cs1);

		Ix = 0;
		Iy = 0;
		Xmax = 0;
		Xmin = 0;
		Ymax = 0;
		Ymin = 0;
		double tx, ty, Ix1, Iy1, tt;

		max = arIdKontur.length();
		for (i = 0; i < max; i++) {
			idObj = arIdKontur[i];
			
			est = false;
			
			if (acdbOpenObject(pObject, idObj, AcDb::kForRead) != Acad::eOk) {
				return;
			}

			if (pObject->isA() == AcDbLine::desc()) {
				mLine = ((AcDbLine*)pObject);
				p1 = mLine->startPoint();
				p2 = mLine->endPoint();
				leng = p1.distanceTo(p2);
				tx = (p1.x + p2.x) / 2 - xc;
				ty = (p1.y + p2.y) / 2 - yc;
				lay = mLine->layer();

				tDoc.clear();
				extractStringNameValueToDoc(lay, tDoc);
				if (!tDoc.GetValue_by_Name(L"[Rbt]", csRb, tNomer)) {
					AfxMessageBox(L"В имени слоя отрезков и полилиний контура продавливания должен быть определено расчетное сопротивление бетона растяжению (в МПа) формате [Rbt]1.15");

					pObject->close();
					return;
				}
				val1(csRb, tRbt);
				if (ravno(tRbt, 0)) {
					AfxMessageBox(L"В имени слоя отрезков и полилиний контура продавливания должен быть определено расчетное сопротивление бетона растяжению НЕ РАВНОЕ НУЛЮ (в МПа) формате [Rbt]1.15");

					pObject->close();
					return;
				}
				if (ravno(Rbt, 0)) {
					Rbt = tRbt;
				}
				else {
					if (!ravno(tRbt, Rbt)) {
						AfxMessageBox(L"Обнаружено разное расчетное сопротивление бетона растяжению. В имени слоя отрезков и полилиний контура продавливания должен быть определено ТОЛЬКО ОДНО расчетное сопротивление бетона растяжению ОДИНАКОВОЕ ДЛЯ ВСЕХ ОТРЕЗКОВ КОНТУРА");

						pObject->close();
						return;
					}
				}

				if (!tDoc.GetValue_by_Name(L"[H0]", csH0, tNomer)) {
					AfxMessageBox(L"В имени слоя отрезков и полилиний контура продавливания должен быть определена приведенная рабочая высота сечения (в метрах) по п.8.1.47 СП 63.13330.2018 в формате [H0]0.22");

					pObject->close();
					return;
				}
				val1(csH0, H0);
				if (ravno(H0, 0)) {
					AfxMessageBox(L"В имени слоя отрезков и полилиний контура продавливания должен быть определена приведенная рабочая высота сечения (в метрах) по п.8.1.47 СП 63.13330.2018 в формате [H0]0.22");

					pObject->close();
					return;
				}
				tA = leng * H0 * 1000;
				//double Ix,Iy,Xmax,Xmin,Ymax,Ymin;
				//double Hx,Hy;
				Hx = abs(p2.x - p1.x);
				Hy = abs(p2.y - p1.y);

				if ((!ravno(Hx, 0)) & (!ravno(Hy, 0))) {
					AfxMessageBox(L"На данный момент обрабатываются только горизонтальные и вертикальные отрезки контура");
					pObject->close();
					return;

				}

				Ix1 = H0 * 1000 * Hy * Hy * Hy / 12 + tA * ty * ty;
				Iy1 = H0 * 1000 * Hx * Hx * Hx / 12 + tA * tx * tx;

				Ix = Ix + Ix1;
				Iy = Iy + Iy1;

				//Ищем максимальные и минимальные координаты
				tt = xc - p1.x;
				if (bolshe(tt, Xmax)) {
					Xmax = tt;
				}
				if (menshe(tt, Xmin)) {
					Xmin = tt;
				}
				tt = xc - p2.x;
				if (bolshe(tt, Xmax)) {
					Xmax = tt;
				}
				if (menshe(tt, Xmin)) {
					Xmin = tt;
				}

				tt = yc - p1.y;
				if (bolshe(tt, Ymax)) {
					Ymax = tt;
				}
				if (menshe(tt, Ymin)) {
					Ymin = tt;
				}
				tt = yc - p2.y;
				if (bolshe(tt, Ymax)) {
					Ymax = tt;
				}
				if (menshe(tt, Ymin)) {
					Ymin = tt;
				}
				
				est = true;
			}
			//AcDbArc



			if (pObject->isA() == AcDbPolyline::desc()) {
				mPLine = ((AcDbPolyline*)pObject);
				lay = mPLine->layer();
				tDoc.clear();
				extractStringNameValueToDoc(lay, tDoc);
				if (!tDoc.GetValue_by_Name(L"[Rbt]", csRb, tNomer)) {
					AfxMessageBox(L"В имени слоя отрезков и полилиний контура продавливания должен быть определено расчетное сопротивление бетона растяжению (в МПа) формате [Rbt]1.15");
					acedSSFree(sset);
					pObject->close();
					return;
				}
				val1(csRb, tRbt);
				if (ravno(tRbt, 0)) {
					AfxMessageBox(L"В имени слоя отрезков и полилиний контура продавливания должен быть определено расчетное сопротивление бетона растяжению НЕ РАВНОЕ НУЛЮ (в МПа) формате [Rbt]1.15");
					acedSSFree(sset);
					pObject->close();
					return;
				}
				if (ravno(Rbt, 0)) {
					Rbt = tRbt;
				}
				else {
					if (!ravno(tRbt, Rbt)) {
						AfxMessageBox(L"Обнаружено разное расчетное сопротивление бетона растяжению. В имени слоя отрезков и полилиний контура продавливания должен быть определено ТОЛЬКО ОДНО расчетное сопротивление бетона растяжению ОДИНАКОВОЕ ДЛЯ ВСЕХ ОТРЕЗКОВ КОНТУРА");
						acedSSFree(sset);
						pObject->close();
						return;
					}
				}

				if (!tDoc.GetValue_by_Name(L"[H0]", csH0, tNomer)) {
					AfxMessageBox(L"В имени слоя отрезков и полилиний контура продавливания должен быть определена приведенная рабочая высота сечения (в метрах) по п.8.1.47 СП 63.13330.2018 в формате [H0]0.22");
					acedSSFree(sset);
					pObject->close();
					return;
				}
				val1(csH0, H0);
				if (ravno(H0, 0)) {
					AfxMessageBox(L"В имени слоя отрезков и полилиний контура продавливания должен быть определена приведенная рабочая высота сечения (в метрах) по п.8.1.47 СП 63.13330.2018 в формате [H0]0.22");
					acedSSFree(sset);
					pObject->close();
					return;
				}


				n = mPLine->numVerts();
				double d, mlength;
				n = mPLine->numVerts() + 1;
				for (i = 0; i < n; i++) {
					es = mPLine->getBulgeAt(i, d);
					if (es != Acad::eOk)
						break;//Сегмента нет
					Tseg1 = mPLine->segType(i);
					//switch(mPLine->segType(i)){ 
					switch (Tseg1) {
					case AcDbPolyline::kLine: {
						AcGeLineSeg3d line;
						mPLine->getLineSegAt(i, line);
						mlength = line.length();
						p1 = line.startPoint();
						p2 = line.endPoint();
						tx = (p1.x + p2.x) / 2 - xc;
						ty = (p1.y + p2.y) / 2 - yc;
						tA = mlength * H0;

						//tA=leng*H0*1000;

						//double Ix,Iy,Xmax,Xmin,Ymax,Ymin;
						//double Hx,Hy;
						Hx = abs(p2.x - p1.x);
						Hy = abs(p2.y - p1.y);

						if ((!ravno(Hx, 0)) & (!ravno(Hy, 0))) {
							AfxMessageBox(L"На данный момент обрабатываются только горизонтальные и вертикальные отрезки контура");
							pObject->close();
							return;

						}

						//tA=leng*H0*1000;
						tA = mlength * H0 * 1000;

						//double Ix,Iy,Xmax,Xmin,Ymax,Ymin;
						//double Hx,Hy;
						Hx = abs(p2.x - p1.x);
						Hy = abs(p2.y - p1.y);

						if ((!ravno(Hx, 0)) & (!ravno(Hy, 0))) {
							AfxMessageBox(L"На данный момент обрабатываются только горизонтальные и вертикальные отрезки контура");
							pObject->close();
							return;

						}

						Ix1 = H0 * 1000 * Hy * Hy * Hy / 12 + tA * ty * ty;
						Iy1 = H0 * 1000 * Hx * Hx * Hx / 12 + tA * tx * tx;

						Ix = Ix + Ix1;
						Iy = Iy + Iy1;

						//Ищем максимальные и минимальные координаты
						tt = p1.x - xc;
						if (bolshe(tt, Xmax)) {
							Xmax = tt;
						}
						if (menshe(tt, Xmin)) {
							Xmin = tt;
						}
						tt = p2.x - xc;
						if (bolshe(tt, Xmax)) {
							Xmax = tt;
						}
						if (menshe(tt, Xmin)) {
							Xmin = tt;
						}

						tt = p1.y - yc;
						if (bolshe(tt, Ymax)) {
							Ymax = tt;
						}
						if (menshe(tt, Ymin)) {
							Ymin = tt;
						}
						tt = p2.y - yc;
						if (bolshe(tt, Ymax)) {
							Ymax = tt;
						}
						if (menshe(tt, Ymin)) {
							Ymin = tt;
						}



						est = true;
					} break;
					case AcDbPolyline::kArc: {
						est = false;
						AfxMessageBox(L"Обнаружен дуговой сегмент полилинии контура продавливания. При расчете на продавливание контур продавливания должен состоять только из ЛИНЕЙНЫХ сегментов полилинии.");
						acedSSFree(sset);
						pObject->close();
						return;
						
					} break;
						
						break;
					}

				}
				//}					

			}
			pObject->close();
			if (!est) {
				AfxMessageBox(L"Обнаружен нелинейный сегмент полилинии контура продавливания. При расчете на продавливание контур продавливания должен состоять только из ЛИНЕЙНЫХ сегментов полилинии.");
				acedSSFree(sset);

			}

		}

		
		double Mbxult, Mbyult;
		double txMax, tyMax;
		if (bolshe(Mx, 0)) {
			txMax = abs(Xmax);
		}
		else {
			txMax = abs(Xmin);
		}

		if (bolshe(My, 0)) {
			//ПРИНЯТО НАОБОРОТ
			tyMax = abs(Ymin);
		}
		else {
			tyMax = abs(Ymax);
		}

		double Wbx, Wby, kd;
		kd = 0.001 * 0.001 * 0.001 * 0.001;//Перевод в м4
		txMax = txMax / 1000;
		tyMax = tyMax / 1000;

		Ix = Ix * kd;
		Iy = Iy * kd;

		str1(Ix / H0, cs1, PM_param.KolZnak);
		tDocRes.Param.add_name_value(L"[Ix]", cs1);

		str1(Iy / H0, cs1, PM_param.KolZnak);
		tDocRes.Param.add_name_value(L"[Iy]", cs1);

		Wbx = Ix / tyMax / H0;//(8.98) СП 63.13330.2018		
		str1(tyMax, cs1, PM_param.KolZnak);
		tDocRes.Param.add_name_value(L"[Ymax]", cs1);
		str1(Wbx, cs1, PM_param.KolZnak);
		tDocRes.Param.add_name_value(L"[Wbx]", cs1);

		Wby = Iy / txMax / H0;
		str1(txMax, cs1, PM_param.KolZnak);
		tDocRes.Param.add_name_value(L"[Xmax]", cs1);
		str1(Wby, cs1, PM_param.KolZnak);
		tDocRes.Param.add_name_value(L"[Wby]", cs1);


		Mbxult = Rbt * 1000000 * Wbx * H0 / 10000;//тм
		str1(Mbxult, cs1, PM_param.KolZnak);
		tDocRes.Param.add_name_value(L"[Mbxult]", cs1);

		Mbyult = Rbt * 1000000 * Wby * H0 / 10000;//тм
		str1(Mbyult, cs1, PM_param.KolZnak);
		tDocRes.Param.add_name_value(L"[Mbyult]", cs1);

		if (ravno(Mbxult, 0) | ravno(Mbyult, 0)) {
			AfxMessageBox(L"Один из контуров продавливания оказался с нулевым сопротивлением.");
			return;
		}

		double otnMpred, koefNagr;

		double ddX, ddY;//Эксцентриститеты расчетного контура относительно центра тяжести колонны
		
		ddX = (xc - pt0[0]) / 1000;//Переводим в метры
		ddY = (yc - pt0[1]) / 1000;

		str1(ddX, cs1, PM_param.KolZnak);
		tDocRes.Param.add_name_value(L"[dx]", cs1);

		str1(ddY, cs1, PM_param.KolZnak);
		tDocRes.Param.add_name_value(L"[dy]", cs1);

		double dMx, dMy;
		

		double My2 = My + ddX * F;
		str1(My2, cs1, PM_param.KolZnak);
		tDocRes.Param.add_name_value(L"[My]", cs1);

		double Mx2 = Mx - ddY * F;
		str1(Mx2, cs1, PM_param.KolZnak);
		tDocRes.Param.add_name_value(L"[Mx]", cs1);



		otnMpred = abs(Mx2 / Mbxult) + abs(My2 / Mbyult);

		str1(otnMpred, cs1, PM_param.KolZnak);
		tDocRes.Param.add_name_value(L"[otnM]", cs1);

		str1(0.5 * ontF, cs1, PM_param.KolZnak);
		tDocRes.Param.add_name_value(L"[otnF05]", cs1);

	


			//double ontF=F/Fbult;
		if (bolshe(otnMpred, 0.5 * ontF)) {
			otnMpred = 0.5 * ontF;
			tDocRes.Param.add_name_value(L"[зн]", L">");
		}
		else {
			tDocRes.Param.add_name_value(L"[зн]", L"<");
		}

		str1(otnMpred, cs1, PM_param.KolZnak);
		tDocRes.Param.add_name_value(L"[otnMfin]", cs1);

		koefNagr = otnMpred + ontF;

		str1(koefNagr, cs1, PM_param.KolZnak);
		tDocRes.Param.add_name_value(L"[res]", cs1);

		if (bolshe(koefNagr, 1)) {
			str1(koefNagr, csFult, PM_param.KolZnak);
			//CString csFult,cs1;
			cs1 = L"Коэффициент прочности на продавливание по формуле (8.95) СП 63.13330.2018 превышает единицу K=" + csFult;
			cs1 = cs1 + L", что говорит о недостоточной несущей способности на продавливание.";
			AfxMessageBox(cs1);
			return;
		}

		tDocRes.Param.add_name_value(L"[вывод]", L"несущая способность обеспечена");

		//Mbyult;
		//Mbxult=;

		//Оформляем расчет
		acutPrintf(_T("\nВыберите текст для формирования оформленного расчета: "));
		acedSSGet(NULL, NULL, NULL, NULL, sset);
		if (acedSSLength(sset, &max) != RTNORM) {
			return;
		}
		for (i = 0; i < max; i++) {
			if (acedSSName(sset, i, entres) == RTNORM) {
				idObj = idObj.setFromOldId(entres[0]);
				if (GetCStringValue(idObj, cs1)) {
					if (!replaceValueByDocDataSkipUnitialized(cs1, tDocRes, errorString)) {//Заменяем значения
						AfxMessageBox(errorString);
						acedSSFree(sset);
						//setColorCopyObject(idCommand,arPair,colorError);
						return;
					}
					setText(idObj, cs1);
				}
			}
		}
		acedSSFree(sset);
		return;
		*/

	}

	



} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CArxProject1App)
ACED_ARXCOMMAND_ENTRY_AUTO(CArxProject1App, ArxProject1, _MYHELLO, MYHELLO, ACRX_CMD_TRANSPARENT, NULL)

