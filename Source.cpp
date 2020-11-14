#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int** createBoard(int dimx, int dimy);
void FileRead(int& max_c, int& max_f, int& dimx, int& dimy, int**& board);
int main();


int** createBoard(int dimx, int dimy) { //Board has dim(rows + 1 by col + 1)
	int** board = new int* [dimx + 2]{};
	for (int i = 0; i < dimx + 2; ++i) { //Outside Border is only for base stations
		board[i] = new int[dimy + 2]{};
	}
	return board;
}


void FileRead(int& max_c, int& max_f, int& dimx, int& dimy, int**& board) {
	ifstream prob_file;;
	prob_file.open("case2.txt");
	if (prob_file.is_open()) {           
		prob_file >> max_c >> max_f >> dimx >> dimy;
		board = createBoard(dimx, dimy); //Create Board
		for (int i = 1; i < dimx + 1; ++i) {
			for (int j = 1; j < dimy + 1; ++j) {
				prob_file >> board[i][j];
			}
		}
	}
	prob_file.close();
	return;

}

int main() {
	int max_c{}, max_f{}, dimx{}, dimy{},** board{};
	FileRead(max_c, max_f, dimx, dimy, board); //Read File and Input Variables







	for (int i = 0; i < dimx + 2; ++i) { 
		for (int j = 0; j < dimy + 2; ++j) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}