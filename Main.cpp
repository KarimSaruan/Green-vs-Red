#include <iostream>
#include <string>
#include "GreenRed.h"
using namespace std;

int main() {
	// INTERFACE ==============================================
	int x, y;
	cin >> x >> y;

	char** grid = new char*[y];
	for (int i = 0; i < y; i++)
		grid[i] = new char[x];

	string s;
	for (int i = 0; i < y; i++) {
		cin >> s;
		for (int j = 0; j < x; j++) {
			grid[i][j] = s[j];
		}
	}
	
	int x1, y1, N;
	cin >> x1 >> y1 >> N;
	// INTERFACE END ==========================================


	// GAME EXECUTE ===========================================
	GreenRed game(x, y, grid, x1, y1, N);
	game.startGame();
	cout << "Result: " << game.getResult << endl;


	// FREE MEMORY ============================================
	for (int i = 0; i < y; i++)
		delete[] grid[i];
	delete[] grid;


	/* 
	Example 1:
	3 3
	000
	111
	000
	1 0 10

	Example 2:
	4 4
	1001
	1111
	0100
	1010
	2 2 15
	*/
}