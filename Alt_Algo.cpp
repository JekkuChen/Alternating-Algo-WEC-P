#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void ActionDownRight(int max_c, int dimx, int dimy, int &x, int &y, int botnum, int** board);
void ActionDown(int max_c, int dimx, int dimy, int &x, int &y, int botnum, int** board);
void ActionUpLeft(int max_c, int dimx, int dimy, int &x, int &y, int botnum, int** board); 
void ActionUp(int max_c, int dimx, int dimy, int &x, int &y, int botnum, int** board);
void ActionUpDown(int max_c, int dimx, int dimy, int &x, int &y, int botnum, int**board);
int** createBoard(int dimx, int dimy);
void FileRead(int& max_c, int& max_f, int& dimx, int& dimy, int**& board);
void FileWriteR(int botnum, vector<int> botposx, vector<int> botposy);


ofstream solu_file("solution5.txt");
string name[15] = { "Peter","Alex","Jekku","Jessie","Rob","Bob","Billy","Cleany","Chad", "Ian", "Ryan", "Stephen", "Joey", "Jason", "Annie" }; 

void FileWriteR(int botnum, vector<int> botposx,vector<int> botposy) { 
	
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
	prob_file.open("case5.txt");
	if (prob_file.is_open()) {           
		prob_file >> max_c >> max_f >> dimx >> dimy;
		board = createBoard(dimx, dimy); 
		for (int i = 0; i < dimx ; ++i) {
			for (int j = 0; j < dimy; ++j) {
				prob_file >> board[i][j];
			}
		}
	}
	prob_file.close();
	return;

}

//All Action Functions for the robots

void ActionUpDown(int max_c, int dimx, int dimy, int &x, int &y, int botnum, int**board) { 
	for (int i = dimx-1; i >= 0; --i) {
		solu_file << "\t\t[\"" << name[botnum] << "\", \"move\", [" << i << ", " << y << "]]," <<endl;
		solu_file << "\t\t[\"" << name[botnum] << "\", \"clean\"," << board[i][y] <<"]," << endl;
	}
	for (int i = 1; i <= dimx; ++i) {
		solu_file << "\t\t[\"" << name[botnum] << "\", \"move\", [" << i << ", " << y << "]]," << endl;
	}
	
}

void ActionUp(int max_c, int dimx, int dimy, int &x, int &y, int botnum, int** board) {
	for (int i = dimx - 1; i >= 0; --i) {
		solu_file << "\t\t[\"" << name[botnum] << "\", \"move\", [" << i << ", " << y << "]]," << endl;
		solu_file << "\t\t[\"" << name[botnum] << "\", \"clean\"," << board[i][y] << "]," << endl;
	}
	x = 0;
}

void ActionUpLeft(int max_c, int dimx, int dimy, int &x, int &y, int botnum, int** board) {
	solu_file << "\t\t[\"" << name[botnum] << "\", \"move\", [" << x << ", " << y+1 << "]]," << endl;
	solu_file << "\t\t[\"" << name[botnum] << "\", \"move\", [" << x-1 << ", " << y + 1 << "]]," << endl;

}


void ActionDown(int max_c, int dimx, int dimy, int &x, int &y, int botnum, int** board) {
	for (int i = 0; i < dimx; ++i) {
		solu_file << "\t\t[\"" << name[botnum] << "\", \"move\", [" << i << ", " << y << "]]," << endl;
		solu_file << "\t\t[\"" << name[botnum] << "\", \"clean\"," << board[i][y] << "]," << endl;
	}
	x = dimx-1;
}

void ActionDownRight(int max_c, int dimx, int dimy, int &x, int &y, int botnum, int** board) {
	
	solu_file << "\t\t[\"" << name[botnum] << "\", \"move\", [" << x << ", " << y-1 << "]]," << endl;
	solu_file << "\t\t[\"" << name[botnum] << "\", \"move\", [" << x + 1 << ", " << y - 1 << "]]," << endl;


}



int main() {
	int max_c{}, max_f{}, dimx{}, dimy{}, ** board{}, botnum{};
	vector<int>startx, starty;


	FileRead(max_c, max_f, dimx, dimy, board); //Read File and Input Variables
	int* locx = new int[dimy] {};
	int* locy = new int[dimy] {};


	for (int i = 0; i < dimy; i++) { //Starting position, even columns start left side, odd start right;
		if (i % 2 == 0) {
			startx.push_back(dimx);
			starty.push_back(i);
			locx[i] = dimx;
			locy[i] = i;
		}
		else {
			startx.push_back(-1);
			starty.push_back(i);
			locx[i] = -1;
			locy[i] = i;
		}
		botnum++;
	}
	FileWriteR(botnum, startx, starty);

	


	for (int i = 0; i < dimy; i++) {  //If Unpaired, robot goes up then down
		if ((i == dimy - 1) && (i % 2 == 0)) {
			ActionUpDown(max_c, dimx, dimy, locx[i], locy[i], dimy - i - 1, board);
		}
		else if ((i % 2 == 0)){ //If one even column (0,2,4,etc.), robot goes up
			ActionUp(max_c, dimx, dimy, locx[i], locy[i], dimy - i - 1, board);
		}
		else { //If one odd column (0,2,4,etc.), robot goes down
			ActionDown(max_c, dimx, dimy, locx[i], locy[i], dimy - i - 1, board);
		}
		
	}
	for (int i = 0; i < dimy; i++) {
		if ((i != dimy - 1) && (i % 2 == 0)) {
			ActionUpLeft(max_c, dimx, dimy, locx[i], locy[i], dimy - i - 1, board);
		}
		else if ((i % 2 == 1)) {
			ActionDownRight(max_c, dimx, dimy, locx[i], locy[i], dimy - i - 1, board);
		}

	}


	solu_file << "\t\t[\"" << name[0] << "\", \"clean\"," << 0 << "]" << endl << "\t]" << endl << "}";
	solu_file.close();
	cout << "Done" << endl;

	
	return 0;
}
