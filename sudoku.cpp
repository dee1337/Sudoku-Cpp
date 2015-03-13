//=================================================================
// Author       : Daniel Geers
// Mail         : geers-(at)-cs.uni-frankfurt.de
// Created      : 28.11.2014
// Description  : Sudoku and random stuff
//=================================================================

#include <iostream>
using namespace std;

typedef double Matrix33[3][3];

// computes the sum of two 3x3 matrices, returns a 3x3 matrix
void MatAdd(Matrix33 matOut, Matrix33 A, Matrix33 B){
	for (int zeile = 0; zeile < 3; zeile++){
		for (int spalte = 0; spalte < 3; spalte++){
			matOut[zeile][spalte] = A[zeile][spalte] + B[zeile][spalte];
		}
	}
}


// prints a 3x3 matrix, takes a 3x3 matrix as input
void MatPrint(Matrix33 A){
	cout << "-------- Ausgabe der Matrix C: --------------" << endl;
	for (int zeile = 0; zeile < 3; zeile++){
		for (int spalte = 0; spalte < 3; spalte++){
			cout << A[zeile][spalte] << "\t";
		}
		cout << endl;
	}
	cout << "---------------------------------------------" << endl;
}


// computes the product of matrix a and matrix b
void MatMul(Matrix33 matOut, Matrix33 A, Matrix33 B){
	int n = 3; // dimension of the n x n matrix
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			matOut[i][j] = 0;
			for (int k = 0; k < n; k++){
				matOut[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

typedef int Sudoku[9][9];

// checks a sudoku row of length 9, if valid:
bool SudokuRowIsValid(Sudoku s, int rowIndex){
	int tempArray[9] = { 0 };
	for (int i = 0; i < 9; i++){
		if (s[rowIndex][i] > 9 || s[rowIndex][i] < 1){ return false; }
		else { tempArray[s[rowIndex][i] - 1] = 1; }
	}
	for (int i = 0; i < 9; i++){
		if (tempArray[i] == 0){ return false; }
	}
	return true;
}


// checks a sudoku column of length 9, if valid:
bool SudokuColumnIsValid(Sudoku s, int colIndex){
	int tempArray[9] = { 0 };
	for (int i = 0; i<9; i++){
		if (s[i][colIndex] > 9 || s[i][colIndex] < 1){ return false; }
		else { tempArray[s[colIndex][i] - 1] = 1; }
	}
	for (int i = 0; i<9; i++){
		if (tempArray[i] == 0){ return false; }
	}
	return true;
}

// checks a sudoku block (3x3), if valid:
bool SudokuBlockIsValid(Sudoku s, int blockIndX, int blockIndY){
	int tempArray[9] = { 0 };
	for (int rows = blockIndX * 3; rows < ((blockIndX * 3) + 3); rows++){
		for (int cols = blockIndY * 3; cols < ((blockIndY * 3) + 3); rows++){
			if (s[rows][cols] < 1 || s[rows][cols] >9){ return false; }
			else { tempArray[s[rows][cols] - 1] = 1; }
		}
	}
	for (int i = 0; i<9; i++){
		if (tempArray[i] == 0){ return false; }
	}
	return true;
}

// checks a 9x9 Sudoku with 3x3 Blocks on all rules; returns true if valid
bool SudokuIsValid(Sudoku s) {
	// check columns / rows:
	for (int i = 0; i < 9; i++) {
		// check rows
		if (!SudokuRowIsValid(s, i)) {
			// cout << "Zeile / Spalte " << i << " ist fehlerhaft." << endl;
			return false;
		}
		// check columns
		if (!SudokuColumnIsValid(s, i)) {
			// cout << "Spalte " << i << " ist fehlerhaft." << endl;
			return false;
		}
	}
	// check blocks:
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (!SudokuBlockIsValid(s, i, j)) {
				// cout << "3x3 Block " << "ist fehlerhaft" << endl;
				return false;
			}
		}
	}
	return true;
}



// return true, if a given string starts with a given substring; false otherwise
bool StringBeginsWithSubstring(const char* str, const char* subStr){
	int i = 0;
	while (subStr[i] != 0){
		if (subStr[i] != str[i]){
			//cout << subStr << " enthalten!" << endl;
			return false;
		}
		i++;
	}
	return true;
}


// returns a string starting from a given substring if found in a given string
const char* FindSubstringInString(const char* str, const char* subStr){
	while (*str != 0){
		if (StringBeginsWithSubstring(str, subStr)){
			return str;
		}
		++str;
	}
	return 0;
}


int main() {
	cout << "-----------------[ Task 01 ]-----------------" << endl;
	Matrix33 A = {
	{ 2.1, 8.3, -1.3 },
	{ -1.1, 2.3, 4 },
	{ 1, -7.3, 8 } };

	Matrix33 B = {
	{ 0.9, -3, 4 },
	{ -1.1, -1.3, 19 },
	{ 6, -3.3, 4 } };


	Matrix33 C;
	MatAdd(C, A, B);
	cout << "A + B:" << endl;
	MatPrint(C);
	MatMul(C, A, B);
	cout << endl << "A * B:" << endl;
	MatPrint(C);

	cout << "-----------------[ Task 02 ]-----------------" << endl;
	Sudoku s = {
			{ 1, 2, 3, 4, 5, 6, 7, 8, 9 },
			{ 4, 5, 6, 7, 8, 9, 1, 2, 3 },
			{ 7, 8, 9, 1, 2, 3, 4, 5, 6 },
			{ 2, 3, 4, 5, 6, 7, 8, 9, 1 },
			{ 5, 6, 7, 8, 9, 1, 2, 3, 4 },
			{ 3, 4, 5, 6, 7, 8, 9, 1, 2 },
			{ 8, 9, 1, 2, 3, 4, 5, 6, 7 },
			{ 6, 7, 8, 9, 1, 2, 3, 4, 5 },
			{ 9, 1, 2, 3, 4, 5, 6, 7, 8 } };


	if (SudokuIsValid(s)){
		cout << " Sudoku is correct" << endl;
	}
	else {
		cout << "Sudoku is incorrect" << endl;
	};

	cout << "-----------------[ Task 03 ]-----------------" << endl;


	const char* text = "Dieser Text besteht aus mehreren Worten";
	const char* word = "meh";

	const char* subText = FindSubstringInString(text, word);
	if (subText != 0){
		cout << "Der Teil des Textes ’" << text << "’, der mit ’"
			<< word << "’ beginnt, lautet: ’"
			<< subText << "’ " << endl;
	}
	else{
		cout << "Das Wort ’" << word << "’ ist nicht in dem Text ’"
			<< text << "’ enthalten." << endl;
	}

	return 0;
}

