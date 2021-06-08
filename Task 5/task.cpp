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


#define pi 3.1415926535
#define DEBUG 0

using namespace std;



int task1() {

	setlocale(LC_ALL, "Russian");

	ofstream sinFile, cosFile, amplFile, phaseFile, sincos;
	sinFile.open("sin.txt");//синусойда
	cosFile.open("cos.txt");//косинусойда
	amplFile.open("ampl.txt");//амплитуда квадратур
	phaseFile.open("phase.txt");//фаза
	sincos.open("sincos.txt");

	//Исходные данные:
	int min = -200;
	int max = -min;
	double distance = 5000;
	double waveLen = 0.03;
	double xP = -25.0;

	double rt = 0;
	double step = 1;//шаг измерения 
	double valueSin = 0, valueCos = 0, valuePhase = 0, valueAmpl = 0.0;
	double arrC[4096];
	double arrS[4096];
	double refS[4096];
	double refC[4096];
	double ZS[4096];
	double ZC[4096];
	for (int i = 0; i < 4096; i++)		ZS[i] = ZC[i] = refS[i] = refC[i] = arrS[i] = arrC[i] = 0;
	//cout << "Введите шаг для измерения: ";
	//cin >> step;

	sincos << "#" << max - min + 1 << " 0" << endl;
	ptFunc(distance, 0, arrC, arrS, max - min + 0, step);
	ptFunc(distance, -25, arrC, arrS, max - min + 0, step);
	refFunc(distance, 0, refC, refS, 40, step);

	for (int i = 0; i < max - min + 1; i += 1)
	{
		double zc = 0, zs = 0;
		for (int j = 0; j < 40; j++) {
			zc += arrC[i + j] * refC[j] - arrS[i + j] * refS[j];
			zs += arrC[i + j] * refS[j] + arrS[i + j] * refC[j];
		}
		ZC[i] = zc;
		ZS[i] = zs;
	}
	for (int i = 0; i < max - min + 1; i += 1) {// цикл по точкам на земле
		sinFile << setw(4) << i << "\t " << setw(2) << valueSin << "\n  ";
		cosFile << setw(4) << i << "\t " << setw(2) << valueCos << "\n  ";
		phaseFile << setw(4) << i << "\t " << setw(2) << valuePhase << "\n  ";
		amplFile << setw(4) << i << "\t " << setw(2) << valueAmpl << "\n  ";
		//sincos<<i<<" "<<arrC[i]<<" "<<arrS[i]<<endl;
		sincos << i << " " << ZC[i] << " " << ZS[i] << endl;
	}
	sinFile.close();
	cosFile.close();
	phaseFile.close();
	amplFile.close();

	return 0;
}

void ptFunc(double distance, double xP, double* arrC, double* arrS, int maxlen, double step)
{
	double rt, waveLen = 0.03, id;
	double valueSin = 0, valueCos = 0, valuePhase = 0, valueAmpl = 0.0;
	for (int i = 0; i <= maxlen; i += 1) {// цикл по точкам на земле
		id = (i - maxlen / 2) * step;
		valueSin = 0; valueCos = 0; valuePhase = 0; valueAmpl = 0.0;
		for (double j = -0.5; j <= 0.5; j += 0.25) { //сигналы из отражающей точки до земли
			rt = (sqrt(pow(xP - j + id, 2) + pow(-distance, 2)));
			valueSin += sin((2 * rt / waveLen) * (2 * pi));
			valueCos += cos((2 * rt / waveLen) * (2 * pi));
			valueAmpl = sqrt(pow(valueCos, 2) + pow(valueSin, 2));
			valuePhase = atan(valueSin / valueCos);
		}
		arrC[i] += valueCos;
		arrS[i] += valueSin;
	}
}

void oldRefFunc(double distance, double xP, double* arrC, double* arrS, int maxlen, double step)
{
	double rt, waveLen = 0.03, id, alf = waveLen / 1, sled, n_im = 0;
	double valueSin = 0, valueCos = 0; /* valuePhase = 0, valueAmpl = 0.0;*/
	for (int i = 0; i <= maxlen; i += 1) {// цикл по точкам на земле
		id = i * step;
		valueSin = 0; valueCos = 0; /*valuePhase = 0; valueAmpl = 0.0;*/
		for (double j = -0.5; j <= 0.5; j += 0.25) { //сигналы из отражающей точки до земли
			rt = (sqrtf(pow(xP - j + id, 2) + pow(-distance, 2)));
			valueSin += sin((-2 * rt / waveLen) * (2 * pi));
			valueCos += cos((-2 * rt / waveLen) * (2 * pi));
			/*valueAmpl = sqrt(pow(valueCos, 2) + pow(valueSin, 2));
			valuePhase = atan(valueSin / valueCos);*/
		}
		arrC[i] = valueCos;
		arrS[i] = valueSin;
	}
}
void refFunc(double distance, double xP, double* arrC, double* arrS, int maxlen, double step)
{
	double rt, waveLen = 0.03, id, alf = waveLen / 1, sled, n_im = 0;
	double valueSin = 0, valueCos = 0; /* valuePhase = 0, valueAmpl = 0.0;*/
	/*for(int i=0;i<maxlen;++i){
		arrC[i]=0;
		arrS[i]=0;
	}*/
	for (int i = 0; i <= maxlen; i += 1) {// цикл по точкам на земле
		id = (i- maxlen / 2) * step;
		valueSin = 0.; valueCos = 0.; /*valuePhase = 0; valueAmpl = 0.0;*/
		for (double j = -0.5; j <= 0.5; j += 0.25) { //сигналы из отражающей точки до земли
			//rt = (sqrtf(pow(xP - j + id, 2) + pow(-distance, 2)));
			rt = (sqrtf(pow(xP + id, 2) + pow(-distance, 2)));
			valueSin += sin((-2 * rt / waveLen) * (2 * pi));
			valueCos += cos((-2 * rt / waveLen) * (2 * pi));	
			/*valueAmpl = sqrt(pow(valueCos, 2) + pow(valueSin, 2));
			valuePhase = atan(valueSin / valueCos);*/
		}
		arrC[i] = valueCos;
		arrS[i] = valueSin;
	}
	for (int i = 0; i < maxlen * 0.7; ++i) {
		//for(int i=maxlen*0.3; i<maxlen;++i){
		for (int i = 0; i < maxlen; ++i) {
			//if (i > 0 * maxlen && i < maxlen * 0.5) {
			//if(i>0.5*maxlen && i<maxlen*0.999){
			if(i>0 * maxlen && i< maxlen * 0.4 ){
				
				arrC[i] = 0;
				arrS[i] = 0;
			}
			continue;
			/*arrC[i] = 0;
			arrS[i] = 0;*/
		}
	}
}

int index = 0;
double _sqrt = 0;
float re = 0, im = 0;

/*Задание №2*/
int task2()
{
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

	vector<countT> report;
	int size = intStrCount * NN;
	report.reserve(size);
	countT tmp;
	for (int i = 0; i < intStrCount; ++i)
	{
		for (int j = 0; j < NN; ++j)
		{
			fin.read(bufStr, 8);
			memcpy(&tmp, bufStr, 8);
			report.push_back(tmp);
		}
	}

	float* amplArr = new float[size];
	char* charArr = new char[size];
	for (int i = 0; i < report.size() - 1; ++i)
	{
		index = i;
		//outPut << fixed << setw(14) << setprecision(pres) << report[i].re << " " << setw(14) << setprecision(pres) << report[i].im << " \n";
		_sqrt = amplArr[i] = (float)sqrt(pow(re = report[i].re, 2) + pow(im = report[i].im, 2));
	}
	CString name = "out.bmp";
	Save_FLT_TO_BMP(amplArr, charArr, intStrCount, NN, 10, name, 100.);
	//cout << "Файл закончился" << endl;
	fin.close();
	outPut.close();
	delete[] charArr;
	return 0;
}

//========== SAVE_FLT_TO_BMP ===========
int Save_FLT_TO_BMP(float* flt, char* cc, int nx, int ny, int type, CString name, float kf)
{
	CImage BM;
	unsigned char* ptr;//, *ptt;
	int     i, j, k; float vv; double mea = 0;
	for (i = 2; i < nx * ny - 1; i++)
		mea += flt[i];
	mea /= (nx * ny - 2); if (mea != 0) kf = kf / mea; /*kf=10;*/
	for (i = 0; i < nx * ny; i++) { vv = flt[i] * kf; if (vv < 0) vv = 0; if (vv > 255)vv = 255; cc[i] = (char)vv; }
	int nxbm = nx, nybm = ny;

	if (type < 10) {
		nxbm = ((nxbm + 3) / 4) * 4; BM.Create(nxbm, -ny, 24, 0);//prt("TYPE RDP"); 
	}
	else {
		nybm = ((nybm + 3) / 4) * 4; BM.Create(nybm, -nx, 24, 0); //prt("TYPE10");
	}
	ptr = (unsigned char*)BM.GetBits();
	if (type < 10)
	{
		for (i = 0; i < ny; i++)
			for (j = 0; j < nx; j++) for (k = 0; k < 3; k++) ptr[(i * nxbm + j) * 3 + k] = cc[i * nx + j];
	}
	else {
		for (j = 0; j < nx; j++)
			for (i = 0; i < ny; i++)
				for (k = 0; k < 3; k++) ptr[(j * nybm + i) * 3 + k] = cc[j * ny + i];
	}
	BM.Save(name);
	CString T = "explorer.exe " + name;
	WinExec((LPCSTR)T, SW_SHOWNORMAL);
	return 1;
}

int task3() {
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
	saveToTxt2(&reverceReport[889 * intStrCount], intStrCount, "mem.txt");
	//for (int i = 0; i < 1819; i++) {
		for (int i = 889; i < 900; i++) {
		alf = wavelen / 1;
		rt = R0 + i* step_r;
		sled = rt * alf;
		n_im = sled / step;
		refFunc(rt, 0, refC, refS, n_im, step);
		for(int i=0;i<intStrCount; ++i){
			Arr[i].re=refC[i];
			Arr[i].im=refS[i];
		}
		saveToTxt2(Arr,intStrCount,"ref.txt");
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

	CString totxt2 = "totxt4.1.txt";;
	saveToTxt2(&report[889*intStrCount],intStrCount, totxt2);

	Save_FLT_TO_BMP(amplArr, charArr, NN, intStrCount, 10, "one.bmp", 100.);
	saveToTxt2(reverceReport, 4096, "temp.txt");
	saveToTxt(0, 889, 2538, 889, intStrCount, NN, report);
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


