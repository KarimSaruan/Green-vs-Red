#include "GreenRed.h"
#include <iostream>


// Initializing class data members
GreenRed::GreenRed(int x, int y, char** grid, int x1, int y1, int N): x(x), y(y), x1(x1), y1(y1), N(N) {
	generationZero = new char*[y];
	for (int i = 0; i < y; i++) {
		generationZero[i] = new char[x];
		for (int j = 0; j < x; j++){
			generationZero[i][j] = grid[i][j];
		}
	}
}


// Freeing memory
GreenRed::~GreenRed() {
	for (int i = 0; i < y; i++)
		delete[] generationZero[i];

	delete[] generationZero;
}


// Start function 
void GreenRed::startGame() {
	greenCountResult = 0; 

	// Two copies of gen zero, so it is never changed.
	char** nextGeneration = new char*[y];
	for (int i = 0; i < x; i++) nextGeneration[i] = new char[x];

	char** currentGeneration = new char*[y];
	for (int i = 0; i < x; i++) currentGeneration[i] = new char[x];

	gridCopyFunction(nextGeneration, generationZero);
	gridCopyFunction(currentGeneration, generationZero);

	// If N is 0 the function will stop.
	if (N == 0 && generationZero[y1][x1] == '0') return;
	if (N == 0 && generationZero[y1][x1] == '1') { greenCountResult = 1; return; }

	// Changing every cell at a time and saving it in nextGen array.
	// CurrentGen array is used for comparison.
	// When nextGen array is fully finished, currentGen array becomes nextGen array for the next iteration.
	// This cycle repeats N times. Every iteration cell [x1 y1] is checked is it's green, thus the
	// green cell counter is incremented.
	// After the end of the FOR loop there is one last check for a green cell.
	for (int i = 0; i < N; i++) {
		if (currentGeneration[y1][x1] == '1') greenCountResult++;
		for (int j = 0; j < y; j++) {
			for (int k = 0; k < x; k++) {
				// NextGenCell function returns green or red cell.
				// This function counts every green cell surrounding this exact cell(index k, index j).
				// CurrentGen array argument is used for comparison, because it is untouched yet and because
				// nextGen array changes every iteration.
				nextGeneration[j][k] = nextGenCell(currentGeneration, k, j);
			}
		}
		gridCopyFunction(currentGeneration, nextGeneration);
	}

	// Last check for green cell in the final generation grid.
	if (currentGeneration[y1][x1] == '1') greenCountResult++;

	freeMemory(nextGeneration);
	freeMemory(currentGeneration);
}


// NextGenCell function returns green or red cell.
// This function counts every green cell surrounding this exact cell(index xIdx, index yIdx).
char GreenRed::nextGenCell(char** grid, int xIdx, int yIdx) {
	int greenCount = 0;
	for (int i = yIdx - 1; i <= yIdx + 1; i++) {
		for (int j = xIdx - 1; j <= xIdx + 1; j++) {
			// This IF is preventing the program to check for green cells outside the array.
			// This occures on the sides of the array. For example arr[0][0] is surrounded by
			// 3 cells, arr[0][1] is surrounded by 5 cells etc.
			if (i < 0 || j < 0 || i == y || j == x) continue;
			// This IF skips the center cell.
			if ((i == yIdx) && (j == xIdx)) continue;
			// This IF checks for green cell and increments counter if so.
			if (grid[i][j] == '1') greenCount++;
		}
	}

	// Here the count variable is cheked with the rules of the task and
	// returns either green or red cell ('1' or '0').
	if (grid[yIdx][xIdx] == '0') {
		if (greenCount == 3 || greenCount == 6)
			return '1';
		else return '0';
	}
	else {
		if (greenCount == 2 || greenCount == 3 || greenCount == 6)
			return '1';
		else return '0';
	}
}


void GreenRed::gridCopyFunction(char** dest, char** src) {
	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++)
			dest[i][j] = src[i][j];
}


void GreenRed::freeMemory(char** grid) {
	for (int i = 0; i < y; i++)
		delete[] grid[i];

	delete[] grid;
}


void GreenRed::printGenerationZero() {
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			std::cout << generationZero[i][j];
		}
		std::cout << std::endl;
	}
}

int GreenRed::getResult() {
	return greenCountResult;
}