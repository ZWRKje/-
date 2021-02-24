#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;



int main()
{
	setlocale(LC_ALL, "Russian");

	ofstream out("..\\output1.txt");

	//Исходные данные:
	int min = -300;
	int max = -min;
	int distance = 5000;
	double waveLen = 0.03;

	double Rt = 0;
	int step = 0;//шаг измерения 
	double value = 0.0;

	cout << "Введите шаг для измерения: ";
	cin >> step;

	for (int i = min; i <= max; i += step)// цикл по точкам на земле
	{
		for (double j = -5.0; j <= 5.0; j += 2.5)//цикл по точкам на антенне
		{
			Rt = (sqrt(pow(i - j, 2) + pow(-distance, 2)));
			value += sin(Rt / waveLen);
		}
		out << "x = " << setw(4) << i << "\tS = " << setw(2) << value << "\n";
		value = 0;
	}

	cout << "\n" << "Результаты измерений записанны в файл output1.txt" << " \n ";
	return 0;
}