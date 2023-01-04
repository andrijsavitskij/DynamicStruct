#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <ctime>
#include <windows.h>
#include <string>
#include "Dynamic_Struct.h"

HANDLE HSTDOUT = GetStdHandle(STD_OUTPUT_HANDLE);// for beauty
#define STD SetConsoleTextAttribute(HSTDOUT, 7);
#define RED SetConsoleTextAttribute(HSTDOUT, 4);
#define PUR SetConsoleTextAttribute(HSTDOUT, 13);
#define GOL SetConsoleTextAttribute(HSTDOUT, 6);
#define GRE SetConsoleTextAttribute(HSTDOUT, 2);
#define BLU SetConsoleTextAttribute(HSTDOUT, 3);
#define BEK SetConsoleTextAttribute(HSTDOUT, 32);// for beauty
constexpr auto STIMESMOL = 50LU;// smol pause (5 sec)					// можна зм≥нювати 
constexpr auto STIMEBIG = 10LU;	// big pause	(10 sec)
constexpr unsigned int LINE_COUNT{ 13 };	// standart					// можна зм≥нювати 
constexpr unsigned int COLUMN_COUNT{ 13 };	// standart
constexpr unsigned int ELEMENT_COUNT{ COLUMN_COUNT * LINE_COUNT};// standart

using std::cout;
using std::cin;
using std::endl;

template<typename T> void nonZero(Matrix<T>, T, T);
template<typename T> void bigLes(Matrix<T>, T, T);
template<typename T> void sortCol(Matrix<T>);

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Ukrainian");
	srand((unsigned)time(0));
	cout << std::fixed << std::setprecision(3); // for beauty

	GOL cout << "√енеруетсь три квадратнi матрицi розмiром: "<< LINE_COUNT <<"*"<<COLUMN_COUNT
		 << ", кiлтькiсть Їлементiтiв: "<< ELEMENT_COUNT <<" \n\n";
	Sleep(STIMESMOL);
	STD; //<<-- €кщо р€док зак≥нчюЇтьс€ зм≥ною кольору то треба ставити ; бо студ≥€(у €к≥й € це написав) сходить з розуму ≥ починаЇ л≥пити tab (напевно думаЇ що ; немаЇ) 

	//////////////////////////Matrix gen///////////////////////////////////
	// трошки заморочивс€ ≥ зробив л€мбду, бо € так вм≥ю))

	Matrix<int> matInt(LINE_COUNT, COLUMN_COUNT, 
		[](int& i) {
			i = rand() % 10;
		}); 
	Matrix<char> matChar(LINE_COUNT, COLUMN_COUNT, 
		[](char& i) {
			i = char(rand() % 94 + 32);
		});
	Matrix<double> matDouble(LINE_COUNT, COLUMN_COUNT, 
		[](double& i) {
			i = (double)rand() / RAND_MAX;
		});

	//////////////////////////non zer///////////////////////////////////

	GOL;
	cout << "” першому завданнi перевiр€емо чи э у матрицi колонки з нул€ми.\n ( ƒл€ кожного типу матриц≥ були обран≥ р≥зн≥ значенн€ \"Ќул€\" за дл€ нагл€дност≥)";
	RED cout << " олонки з нул€ми змiнюють колiр\n";
	Sleep(STIMESMOL);
	STD;

	PUR cout << "\n\t\t\t÷IЋќ„»—≈Ћ№Ќј ћј“–»÷я\n";
	STD nonZero<int>(matInt, 0,0);

	PUR cout << "\n\t\t\t—»ћ¬ќЋ№Ќј ћј“–»÷я\n";
	STD nonZero<char>(matChar, ' ',' ');

	PUR cout << "\n\t\t\tƒ–ќЅќ¬ј ћј“–»÷я\n";
	STD nonZero<double>(matDouble, 0.0, 0.09999);

	//////////////////////////big les///////////////////////////////////

	GOL;
	cout << "\n” другому завданнi дл€ кожноњ матрицi окремо задаютс€ радомнi ј та ¬.\n";
	cout << "ѕiдраховуетьс€ њх кiлькiсть та пiдкреслюетс€ њх позицi€ у матрицi.\n";
	Sleep(STIMEBIG + STIMEBIG);
	STD;

	int Ai, Bi;
	char Ac, Bc;
	double Ad, Bd;


	PUR cout << "\n\t\t\t÷IЋќ„»—≈Ћ№Ќј ћј“–»÷я\n";
	/* 
		так тут goto, але це зручний ≥нструмент €кщо використовувати його на малих маштабах.
		«ам≥сть goto тут маожно було написати while(true), але це ж тесаме goto виходть)   
	*/
second1:
	matInt.get_lambda()(Ai); 
	matInt.get_lambda()(Bi);
	if (Ai >= Bi) goto second1;
	STD bigLes<int>(matInt, Ai, Bi);

	PUR cout << "\n\t\t\t—»ћ¬ќЋ№Ќј ћј“–»÷я\n";// в≥д ' ' до 128 символу 
second2:
	matChar.get_lambda()(Ac);
	matChar.get_lambda()(Bc);
	if (Ac >= Bc) goto second2;
	STD bigLes<char>(matChar, Ac, Bc);

	PUR cout << "\n\t\t\tƒ–ќЅќ¬ј ћј“–»÷я\n";// в≥д 0.0 до 0.999 
second3:
	matDouble.get_lambda()(Ad);
	matDouble.get_lambda()(Bd);
	if (Ad >= Bd) goto second3;
	STD bigLes<double>(matDouble, Ad, Bd);

	//////////////////////////sortcol///////////////////////////////////

	GOL;
	cout << "\n” третьому завданнi матриц€ сортуетьс€ за сумою элементiв у колонках.\n";
	cout << " олонки мають свiй колiр,\n";
	cout << "пiсл€ сортуванн€ можливо побачити €к був вiдсортований масив.\n";
	Sleep(STIMEBIG + STIMEBIG);
	STD;

	PUR cout << "\n\t\t\t÷IЋќ„»—≈Ћ№Ќј ћј“–»÷я\n";
	STD sortCol<int>(matInt);

	PUR cout << "\n\t\t\t—»ћ¬ќЋ№Ќј ћј“–»÷я\n";
	STD sortCol<char>(matChar);


	PUR cout << "\n\t\t\tƒ–ќЅќ¬ј ћј“–»÷я\n";
	STD sortCol<double>(matDouble);

}

template<typename T> void nonZero(Matrix<T> matrix, T zeromin,T zeromax) {
	auto nonzerocol = matrix.findBigAlessB(new T[2]{zeromin,zeromax});
	int out = 0; bool* lines = new bool[COLUMN_COUNT]{};
	for (unsigned i = 0; i < LINE_COUNT; i++){
		for (unsigned j = 0; j < COLUMN_COUNT; j++){
			if (nonzerocol[i][j]) {
				out++;
				lines[j] = true;
			}
		}
	}
	for (unsigned i = 0; i < LINE_COUNT; i++){
		STD; cout << endl;
		for (unsigned j = 0; j < COLUMN_COUNT; j++){
			if (lines[j]) RED;
			if (nonzerocol[i][j]) BEK;
			cout << matrix[i][j]; STD; cout << " "; STD;
		}
	}
	BLU;
	if(zeromin == zeromax)  cout << "\nFor this matrix zero is: "<< zeromin<<", zero col count : " << out << endl; 
	else cout << "\nFor this matrix zero is: " << zeromin << " -- " << zeromax << ", zero col count: "<< out << endl;
	STD;
}

template<typename T> void bigLes(Matrix<T> matrix, T A, T B) {
	auto bl = matrix.findBigAlessB(new T[2]{A, B});
	int out = 0;
	for (unsigned i = 0; i < LINE_COUNT; i++){
		std::cout << std::endl;
		for (unsigned j = 0; j < COLUMN_COUNT; j++){
			if (bl[i][j]) { PUR; out++; }
			else STD;
			std::cout << matrix[i][j] << " ";
		}
	}
	BLU cout << "\nCount big then " << A << " and less then " << B << " : " << out << endl; STD;
}

template<typename T> void sortCol(Matrix<T> matrix) {
	for (unsigned i = 0; i < LINE_COUNT; i++) {
		std::cout << std::endl;
		for (unsigned j = 0; j < COLUMN_COUNT; j++) {
			SetConsoleTextAttribute(HSTDOUT, (j%15) + 1);// (j % 15) -- тому що у консол≥ всього 4 б≥ти кольору (16 кольор≥в)
			std::cout << matrix[i][j] << " ";
		}
		STD;
	} std::cout << "\n";

	T** colsumch = matrix.sortBycolsum();

	for (unsigned i = 0; i < LINE_COUNT; i++) {
		std::cout << std::endl;
		for (unsigned j = 0; j < COLUMN_COUNT; j++) {
			SetConsoleTextAttribute(HSTDOUT, ((int)colsumch[j][0]%15) + 1);
			std::cout << matrix[i][j] << " ";
		}
		STD;
	} std::cout << "\n";
}
