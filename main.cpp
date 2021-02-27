#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;



int main()
{
	setlocale(LC_ALL, "Russian");

    ofstream sinFile,cosFile,amplFile,phaseFile;
    sinFile.open("sin.txt");//синусоида
    cosFile.open("cos.txt");//косинусоида
    amplFile.open("ampl.txt");//амплитуда квадратур
    phaseFile.open("phase.txt");//фаза

	//Исходные данные:
	int min = -300;
	int max = -min;
	int distance = 5000;
	double waveLen = 0.03;

	double rt = 0;
	int step = 0;//шаг измерения 
	double valueSin,valueCos,valuePhase,valueAmpl = 0.0;

	cout << "Введите шаг для измерения: ";
	cin >> step;
 
	for (int i = min; i <= max; i += step)// цикл по точкам на земле
	{
		for (double j = -5.0; j <= 5.0; j += 2.5)//цикл по точкам на антенне
		{
			rt = (sqrt(pow(i - j, 2) + pow(-distance, 2)));
			valueSin += sin(rt / waveLen);
            valueCos += cos(rt / waveLen);
            valueAmpl = sqrt( pow(valueCos,2) + pow(valueSin,2));
            valuePhase = atan(valueSin/valueCos);
        }
        sinFile << "\n  " << setw(4) << i << "\t " << setw(2) << valueSin;
	cosFile << "\n  " << setw(4) << i << "\t " << setw(2) << valueCos;
        phaseFile << "\n  " << setw(4) << i << "\t " << setw(2) << valuePhase;
        amplFile << "\n  " << setw(4) << i << "\t " << setw(2) << valueAmpl;
        valuePhase = valueAmpl = valueCos = valueSin = 0;
	}
  
    sinFile.close();
    cosFile.close();
    phaseFile.close();
    amplFile.close();
    cout << "\n" << "Результаты измерений записанны в файлы sin.txt cos.txt phaze.txt ampl.txt" << " \n ";
	
	return 0;
}