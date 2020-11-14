#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


int** createBoard(int dimx, int dimy);
void FileRead(int& max_c, int& max_f, int& dimx, int& dimy, int**& board);
int main();


void FileWrite(int botnum, vector<int> botposx,vector<int> botposy) { //Keep in mind, coordinate system in code is (N+1)X(M+1). JSON output needs to be in 0,0;
	string name[12] = {"peter","alex","jekku","jessie","rob","bob","billy","cleany","chad", "ian", "ryan", "stephen"}; //Add more if you want
	ofstream solu_file("sol.txt");
	solu_file << "{\n\t\"robots\": [\n";
	for (int i = 0; i < botnum-1 ; ++i) {
		solu_file << "\t\t[\"" << name[i] << "\", [" << botposx.back() << ", " << botposy.back() << "]]," << endl;
		botposx.pop_back();
		botposy.pop_back();
	}

	solu_file << "\t\t[\"" << name[botnum-1] << "\", [" << botposx.back() << ", " << botposy.back() << "]]" << endl << "]," << endl;

	return;
}


int** createBoard(int dimx, int dimy) { //Board has dim(rows + 1 by col + 1)
	int** board = new int* [dimx + 2]{};
	for (int i = 0; i < dimx + 2; ++i) { //Outside Border is only for base stations
		board[i] = new int[dimy + 2]{};
	}
	return board;
}


void FileRead(int& max_c, int& max_f, int& dimx, int& dimy, int**& board) {

	ifstream prob_file;
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
	int max_c{}, max_f{}, dimx{}, dimy{}, ** board{}, botnum{};
	vector<int>startx, starty;
	startx.push_back(1);
	starty.push_back(1);
	startx.push_back(1);
	starty.push_back(2);
	botnum = 2;

	FileRead(max_c, max_f, dimx, dimy, board); //Read File and Input Variables

















	FileWrite(botnum, startx, starty);










	/*for (int i = 0; i < dimx + 2; ++i) { 
		for (int j = 0; j < dimy + 2; ++j) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
	*/
	return 0;
}