#pragma once


template <typename T> class Matrix {
private:
	typedef void (*func)(T&);
	T** mat;
	unsigned column, line;
	func lambda;

public:
	unsigned get_ncol() {
		return column;
	}
	unsigned get_nline() {
		return line;
	}
	func get_lambda() {
		return lambda;
	}
	void setLambda(func lam) {
		lambda = lam;
	} 

	T* getPtrEl(int x, int y) {
		return &mat[y][x];
	}
	Matrix& operator +(Matrix& m1) {
		if (m1.get_nline() == line && m1.get_ncol() == column) {
			for (unsigned i = 0; i < column; i++)
				for (unsigned j = 0; j < line; j++)
					mat[i][j] += m1[i][j];
		}
		else {
			throw 0;
		}

		return *this;
	}
	Matrix& operator *(int num) {
		for (unsigned i = 0; i < column; i++)
			for (unsigned j = 0; j < line; j++)
				mat[i][j] *= num;

		return *this;
	}
	T* operator [](int index) {
		return mat[index];
	}
	void transposition() {

		T** mat;
		unsigned bafnc = line, bafnl = column;

		mat = new T * [bafnc];
		for (unsigned i = 0; i < bafnc; i++)
			mat[i] = new T[bafnl];

		for (unsigned i = 0; i < bafnc; i++) {
			for (int last = bafnl - 1, first = 0; last >= 0; last--, first++) {
				mat[i][first] = this->mat[last][i];
			}
		}

		delete[] this->mat;
		this->mat = new T * [bafnc];
		for (unsigned i = 0; i < bafnc; i++)
			this->mat[i] = new T[bafnl];
		for (unsigned i = 0; i < bafnc; i++)
			for (unsigned j = 0; j < bafnl; j++)
				this->mat[i][j] = mat[i][j];

		mat = mat;
		column = bafnc;
		line = bafnl;

		delete[] mat;
	}
	Matrix<bool> findBigAlessB(T* zero) {
		Matrix<bool> nozero(column, line);

		for (unsigned i{ 0 }; i < column; i++)
			for (unsigned j{ 0 }; j < line; j++)
				if (mat[i][j] >= zero[0] && mat[i][j] <= zero[1])
					nozero[i][j] = true;
		return nozero;
	}
	/*
	стара версія findBigAlessB. раніше було так:
	int bigAlessB(T A, T B, Matrix<bool>& bigles = nullptr) {
		int bidAlessB = 0;
		for (unsigned i{ 0 }; i < column; i++)
			for (unsigned j{ 0 }; j < line; j++)
				if (mat[i][j] > A && mat[i][j] < B) {
					bidAlessB++;
					if (&bigles != nullptr) {
						bigles[i][j] = 1;
					}
				}
		return bidAlessB;
	}*/

	T** sortBycolsum() {
		/*
			!!!тут складно!!!
			схема:
			1)транспонуем матрицю щоб колонки стали лініями, так легше розуміти
			2)створюемо масив matcolsum де зберігаемо номер лінії та суму усіх ел
			3)створюемо буфер де тимчасово будемо зберігати лінію
			4)сортуемо matcolsum, у той самий час сортуемо сам масив
			5)транспонуемо матрицю 3 рази ще раз, щоб повернути її у початковий стан

			matcolsum зберігае:
			номер у 0 комірці
			суму у 1 комірці
		*/

		//1
		transposition();

		//2
		T** matcolsum = new T * [column];
		for (unsigned i = 0; i < column; i++) {
			matcolsum[i] = new T[2];
			matcolsum[i][1] = 0;
		}

		for (unsigned i = 0; i < column; i++) {
			matcolsum[i][0] = (T)i;
			for (unsigned j{ 0 }; j < line; j++)
				matcolsum[i][1] += mat[i][j];
		}

		//3
		T* baf = new T[column];
		for (unsigned i = 0; i < column; i++)
			baf[i] = mat[(unsigned int)matcolsum[0][0]][i];
		int bafidx = 0;

		//4
		T ch[2];// буфер, структура така сама як у matcolsum
		for (int i = 1, j; (unsigned)i < column; i++) {// це сортування вставками
			// буферезуемо данні
			ch[1] = matcolsum[i][1];
			ch[0] = (unsigned int)matcolsum[i][0];
			for (unsigned g = 0; g < line; g++)
				baf[g] = mat[(int)matcolsum[i][0]][g];
			// цикл сортування
			for (j = i - 1; j >= 0 && matcolsum[j][1] > ch[1]; j--) {
				matcolsum[j + 1][1] = matcolsum[j][1];
				matcolsum[j + 1][0] = matcolsum[j][0];
				for (unsigned g{ 0 }; g < line; g++)
					mat[j + 1][g] = mat[j][g];
			}
			// виписуемо данні з буферів
			matcolsum[j + 1][1] = ch[1];
			matcolsum[j + 1][0] = ch[0];
			for (unsigned g{ 0 }; g < column; g++)
				mat[j + 1][g] = baf[g];
		}

		//5
		transposition();
		transposition();
		transposition();
		return matcolsum;
	}

	Matrix(unsigned int column, unsigned int line) : column(column), line(line), lambda([](T& i) {i = 0;}) {
		mat = new T * [column];
		for (unsigned i = 0; i < column; i++)
			mat[i] = new T[line];
		for (unsigned i = 0; i < column; i++) {
			for (unsigned j = 0; j < line; j++) {
				mat[i][j] = 0;
			}
		}
	}
	Matrix(unsigned int column, unsigned int line, T el[]) : column(column), line(line), lambda([](T& i) {i = 0; }) {
		mat = new T * [column];
		for (unsigned i = 0; i < column; i++)
			mat[i] = new T[line];
		for (unsigned i = 0; i < column; i++)
			for (unsigned j = 0; j < line; j++)
				mat[i][j] = el[i * line + j];
	}
	Matrix(unsigned int column, unsigned int line, func lam) : column(column), line(line), lambda(lam) {
		mat = new T * [column];
		for (unsigned i = 0; i < column; i++)
			mat[i] = new T[line];
		for (unsigned i = 0; i < column; i++)
			for (unsigned j = 0; j < line; j++)
				lambda(mat[i][j]);
	}

};