#include "stdafx.h"
#include "funcs.h"

#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <locale>
#include <vector>
#include <iomanip>
#include <stdio.h>

int newTask() {
	setlocale(LC_ALL, "rus");
	string fileName1 = "_0123.cpx";
	string fileName = "_01_RAW.CPX";
	int fileSize;
	char bufStr[8];
	float NN;
	int intStrCount;
	int pres = 8;
	bufStr[4] = '\0';
	//Открытие файли как бинарного
	ifstream fin;
	ofstream outPut;

	outPut.open("output.txt");
	fin.open(fileName, ios::binary);
	if (!fin.is_open())
	{
		cout << "Файл не может быть открыт!\n";
		return 1;
	}

	//Чтение длинны файла в байтах
	fin.seekg(0, ios_base::end);
	fileSize = fin.tellg();
	fin.seekg(0, ios_base::beg);
#if DEBUG
	cout << "\n File size =" << fileSize << "\n"
		<< endl;
#endif

	//чтение первых 4-ёх байтов
	fin.read(bufStr, 4);
	string dataStr(bufStr);
#if DEBUG
	cout << "\n CPLX =" << dataStr << "\n"
		<< endl;
#endif
	// Проверка формата файла
	if (dataStr != "CPLX")
	{
		cout << "\n Файл не .cpl \n";
		return 2;
	}

	//Счситывание NN
	fin.read(bufStr, 4);
	memcpy(&NN, bufStr, 4);
#if DEBUG
	cout << "\n NN =" << NN << "\n"
		<< endl;
#endif
	//Определение числа строк отчетов
	intStrCount = fileSize / 8 / NN;
#if DEBUG
	cout << "\n Count string =" << intStrCount << "\n"
		<< endl;
#endif
	int size = intStrCount * NN;
	countT* report = new countT[size];
	ofstream output("testOutput.txt");
	double ZS[4096];
	double ZC[4096];
	int k = 0, k1 = 0;
	float temp;
	countT tmp;
	for (int i = 0; i < intStrCount; ++i)
	{
		for (int j = 0; j < NN; ++j)
		{
			fin.read(bufStr, 8);
			memcpy(&tmp, bufStr, 8);
			report[k] = tmp;
			k++;
		}
	}
	k = 0;
	float* amplArr = new float[size];
	countT* amplStrArr = new countT[2538 - 1498 + 1];
	countT Arr[4096*2];
	for(int i=0; i<4096*2;++i){
		Arr[i].im=0;
		Arr[i].re=0;
	}
	countT* reverceReport = new countT[size];
	char* charArr = new char[size];
	double* refS = new double[4096];
	double* refC = new double[4096];
	for(int i=0;i<4096;++i){
		refC[i]=0;
		refS[i]=0;
	}
	for (int i = 0; i < size - 1; ++i)
	{
		amplArr[i] = sqrtf(pow(report[i].re, 2) + pow(report[i].im, 2));
	}
	CString name = "out.bmp";
	
	Save_FLT_TO_BMP(amplArr, charArr, intStrCount, NN, 10, name, 100.);
	for (int i = 0; i < NN; i++) {
		for (int j = 0; j < intStrCount; j++) {
			k = i * intStrCount + j;
			k1 = ((intStrCount - 1) - j) * NN + i;
			//amplArr[k] = sqrtf(pow(report[k1].re, 2) + pow(report[k1].im, 2));
			reverceReport[k] = report[k1];
			amplArr[k] = sqrtf(pow(reverceReport[k].re, 2) + pow(reverceReport[k].im, 2));

		}
	}
	Save_FLT_TO_BMP(amplArr, charArr, NN, intStrCount, 10, "out1.bmp", 100.);
	double wavelen = 0.03;
	double alf = wavelen/1;
	double step_r = 1;
	double step=0.15;
	double sled = 0.;
	double rt = 0.;
	double n_im = 0.;
	double R0 = 1000;

	for (int i = 0; i < 1819; i++) {
		//for (int i = 889; i < 900; i++) {
		alf = wavelen / 1;
		rt = R0 + i* step_r;
		sled = rt * alf;
		n_im = sled / step;
		refFunc(rt, 0, refC, refS, n_im, step);
		for(int i=0;i<intStrCount; ++i){
			Arr[i].re=refC[i];
			Arr[i].im=refS[i];
		}
		//saveToTxt2(Arr,intStrCount,"ref.txt");
		countT* pp = &report[i * intStrCount];
		for (int i1 = 0; i1 < intStrCount - n_im; i1++)
		{
		  double zc = 0, zs = 0; 
		  for (int j = 0; j < n_im; j++) {
			int kk = i * intStrCount;
			zc += reverceReport[kk + i1 + j].re * refC[j] - reverceReport[kk + i1 + j].im * refS[j];
		    zs += reverceReport[kk + i1 + j].re * refS[j] + reverceReport[kk + i1 + j].im * refC[j];
		  }
		  pp[i1].re = zc; pp[i1].im = zs;
		}
	}
	
	for (int i = 0; i < size - 1; ++i)
	{
		amplArr[i] = sqrtf(pow(report[i].re, 2) + pow(report[i].im, 2));
	}

	CString totxt2 = "totxt2.txt";;
	saveToTxt2(&reverceReport[889*intStrCount],intStrCount, totxt2);

	Save_FLT_TO_BMP(amplArr, charArr, NN, intStrCount, 10, "out3-3.bmp", 100.);
	//saveToTxt2(reverceReport, 4096, "temp.txt");
	//saveToTxt(0, 889, 2538, 889, intStrCount, NN, report);
	fin.close();
	outPut.close();
	delete[] charArr;
	delete[] amplArr;
	delete[] report;
	delete[] reverceReport;
	delete[] refC;
	delete[] refS;
	return 0;
}

void saveToTxt(int x1, int y1, int x2, int y2, int intStrCount, int NN, countT* report) {
	ofstream output("testOutput.txt");
	output << "#" << 2538 - 1498 + 1 << " 0\n";
	//output << "a";
	int i = y1;
	for (int j = x1; j <= x2; j++) {
		int k = ((intStrCount - 1) - j) * NN + i;
		int p = pow(report[k].re, 2);
		output << j - x1 << " " << report[k].re
			<< " " << report[k].im << endl;
		output << j - 1499 << " " << (pow(report[k].re, 2) + pow(report[k].im, 2))
			<< " " << sqrtf(pow(report[k].re, 2) + pow(report[k].im, 2)) << endl;
	}
	output.close();
}

void saveToTxt2(countT* report, int NN, CString name) {
	ofstream output(name);
	const char* nName=(LPCTSTR) name;
	remove(nName);
	output << "#" << NN  << " 0\n";
	int x1 = 0, x2 = NN - 1;
	for (int j = x1; j <= x2; j++) {
		output << j << " " << report[j].re
			<< " " << report[j].im << endl;
	}
	output.close();
}
