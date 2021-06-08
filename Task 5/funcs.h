#include "stdafx.h"

struct countT
{
	float re;
	float im;
};

int task1();

void ptFunc(double distance, double xP, double* arrC, double* arrS, int maxlen, double step);

void refFunc(double distance, double xP, double* arrC, double* arrS, int maxlen, double step);

int task2();

int task3();

int Save_FLT_TO_BMP(float* flt, char* cc, int nx, int ny, int type, CString name, float kf);

void oporFunc();

void saveToTxt (int x1, int y1, int x2, int y2, int intStrCount, int NN, countT* report);

void saveToTxt2(countT* report, int NN, CString name);