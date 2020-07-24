#pragma once
class GreenRed {
public:
	GreenRed(int x, int y, char** grid, int x1, int y1, int N);
	~GreenRed();

	void startGame();
	char nextGenCell(char** grid, int xIdx, int yIdx);
	void gridCopyFunction(char** dest, char** src);
	void freeMemory(char** grid);
	void printGenerationZero();

	int getResult();
private:
	int x, y, x1, y1, N;
	char** generationZero;
	int greenCountResult;
};

