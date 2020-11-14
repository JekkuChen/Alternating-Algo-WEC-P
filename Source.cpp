#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


int** createBoard(int dimx, int dimy);
void FileRead(int& max_c, int& max_f, int& dimx, int& dimy, int**& board);
int main();
void FileWriteR(int botnum, vector<int> botposx, vector<int> botposy);
ofstream solu_file("sol.txt");
string name[12] = { "peter","alex","jekku","jessie","rob","bob","billy","cleany","chad", "ian", "ryan", "stephen" }; //Add more if you want

void FileWriteR(int botnum, vector<int> botposx,vector<int> botposy) { //Keep in mind, coordinate system in code is (N+1)X(M+1). JSON output needs to be in 0,0;
	
	solu_file << "{\n\t\"robots\": [\n";
	for (int i = 0; i < botnum-1 ; ++i) {
		solu_file << "\t\t[\"" << name[i] << "\", [" << botposx.back() << ", " << botposy.back() << "]]," << endl;
		botposx.pop_back();
		botposy.pop_back();
	}

	solu_file << "\t\t[\"" << name[botnum-1] << "\", [" << botposx.back() << ", " << botposy.back() << "]]" << endl << "\t]," << endl;
	solu_file << "\t\"actions\": [" << endl;
	return;
}


int** createBoard(int dimx, int dimy) { 
	int** board = new int* [dimx]{};
	for (int i = 0; i < dimx; ++i) { 
		board[i] = new int[dimy]{};
	}
	return board;
}


void FileRead(int& max_c, int& max_f, int& dimx, int& dimy, int**& board) {

	ifstream prob_file;
	prob_file.open("case2.txt");
	if (prob_file.is_open()) {           
		prob_file >> max_c >> max_f >> dimx >> dimy;
		board = createBoard(dimx, dimy); //Create Board
		for (int i = 0; i < dimx ; ++i) {
			for (int j = 0; j < dimy; ++j) {
				prob_file >> board[i][j];
			}
		}
	}
	prob_file.close();
	return;

}

void ActionR(int max_c, int dimx, int dimy, int x, int y, int botnum, int**board) { // 1 is Move, 2 is Clean; 
	for (int i = dimx-1; i >= 0; --i) {
		solu_file << "\t\t[\"" << name[botnum] << "\", \"move\", [" << i << ", " << y << "]]," <<endl;
		solu_file << "\t\t[\"" << name[botnum] << "\", \"clean\"," << board[i][y] <<"]," << endl;
	}
	for (int i = 1; i <= dimx; ++i) {
		solu_file << "\t\t[\"" << name[botnum] << "\", \"move\", [" << i << ", " << y << "]]," << endl;
	}
	
}


int main() {
	int max_c{}, max_f{}, dimx{}, dimy{}, ** board{}, botnum{};
	vector<int>startx, starty;

	FileRead(max_c, max_f, dimx, dimy, board); //Read File and Input Variables
	int* locx = new int[dimy] {};
	int* locy = new int[dimy] {};


	for (int i = 0; i < dimy; i++) {
		startx.push_back(dimx);
		starty.push_back(i);
		locx[i] = dimx;
		locy[i] = i;
		botnum++;
	}

	FileWriteR(botnum, startx, starty);

	for (int i = 0; i < dimy; i++) {
		ActionR(max_c, dimx, dimy, locx[i], locy[i], dimy-i-1,board);
	}
	solu_file << "\t\t[\"" << name[0] << "\", \"clean\"," << 0 << "]" << endl << "\t]" << endl << "}";


		
	return 0;
}