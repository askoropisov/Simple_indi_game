#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
#include <stdio.h>

using namespace std;

HANDLE hConsole;

ifstream in_file("input_medium.txt");

class Map {
public:
	int length;
	int height;
	int exit_x_pos = -10;
	int exit_y_pos = -10;
	char barier_target = '#';
	char void_target = '.';
	vector<vector<char>> DRP;

	vector<vector<char>> Read_file(ifstream& in_file);                       //reading file and return DRP[][]
	void out_map(vector<vector<char>> DRP);
	void create_exit(vector<vector<char>>& DRP);
} map;

class Player {
public:
	int x_pos = 0;
	int y_pos = 0;
	char target = 'P';

	void movement(vector<vector<char>>& DRP, int key, int trash);
} player;


class Artifact {
public:
	int number = 0;
	int x_pos = 0;
	int y_pos = 0;

	void create(vector<vector<char>>& DRP);
	Artifact(int number);	
};
Artifact::Artifact(int number) : number(number) {}
vector<Artifact*> artifacts;

vector<vector<char>> Map::Read_file(ifstream& in_file) {                      //reading input file and create gaming map

	char symbol;
	vector<vector<char>> DRP;
		in_file >> map.length;
		in_file >> map.height;
		vector<char> string;

		symbol = in_file.get();                                               //skip '\n'
		for (int j = 0; j < map.height; j++) {
			for (int i = 0; i < map.length; i++) {
				symbol = in_file.get();
				string.push_back(symbol);
			}
			symbol = in_file.get();                                           //skip '\n' in end string
			DRP.push_back(string);
			string.clear();
		}
	in_file.close();
	return DRP;
}

void Player::movement(vector<vector<char>>& DRP, int key, int trash) {
	int temp_x = player.x_pos;
	int temp_y = player.y_pos;
	switch (key) {
	case 72:
		if (player.x_pos > 0 && DRP[player.x_pos-1][player.y_pos] != map.barier_target) {
			player.x_pos -= 1;
		}
		break;
	case 80:
		if (player.x_pos < map.height - 1 && DRP[player.x_pos + 1][player.y_pos] != map.barier_target) {
			player.x_pos += 1;
		}
		break;
	case 75:
		if (player.y_pos > 0 && DRP[player.x_pos][player.y_pos-1] != map.barier_target) {
			player.y_pos -= 1;
		}
		break;
	case 77:
		if (player.y_pos < map.length - 1 && DRP[player.x_pos][player.y_pos + 1] != map.barier_target) {
			player.y_pos += 1;
		}
		break;
	default:
		break;
	}
	DRP[temp_x][temp_y] = map.void_target;
	DRP[player.x_pos][player.y_pos] = player.target;
}

void Artifact::create(vector<vector<char>>& DRP) {	
	int temp_x, temp_y, counter = 0;
	srand(time(NULL));

	while (counter < 1) {
		temp_x = rand() % map.height;
		temp_y = rand() % map.length;
		if (DRP[temp_x][temp_y] == map.void_target && DRP[temp_x][temp_y] != DRP[0][0]) {
			x_pos = temp_x;
			y_pos = temp_y;
			DRP[x_pos][y_pos] = '@';
			counter++;
		}
	}
} 

void Map::out_map(vector<vector<char>> DRP) {							
	for (int j = 0; j < map.height; j++) {
		for (int i = 0; i < map.length; i++) {
			switch (DRP[j][i])
			{
			case '@': {
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 4);
				cout << setw(2) << DRP[j][i];
				SetConsoleTextAttribute(hConsole, 7);
				break;
			}
			case 'P': {
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 2);
				cout << setw(2) << DRP[j][i];
				SetConsoleTextAttribute(hConsole, 7);
				break;
			}
			case 'E': {
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 5);
				cout << setw(2) << DRP[j][i];
				SetConsoleTextAttribute(hConsole, 7);
				break;
			}
			case '#': {
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 6);
				cout << setw(2) << DRP[j][i];
				SetConsoleTextAttribute(hConsole, 7);
				break;
			}
			case '.': {
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 9);
				cout << setw(2) << DRP[j][i];
				SetConsoleTextAttribute(hConsole, 7);
				break;
			}
			default:
				cout << setw(2) << DRP[j][i];
				break;
			}
		}
		cout << endl;
	}
	cout << endl;
}

void Map::create_exit(vector<vector<char>>& DRP) {
	int temp_x, temp_y, counter = 0;
	srand(time(NULL));

	while (counter < 1) {
		temp_x = rand() % map.height;
		temp_y = rand() % map.length;
		if (DRP[temp_x][temp_y] == map.barier_target) {
			map.exit_x_pos = temp_x;
			map.exit_y_pos = temp_y;
			DRP[exit_x_pos][exit_y_pos] = 'E';
			counter++;
		}
	}
}


int main() {
	int counter_artifacts = 0;
	if (!in_file.is_open()) {
		cout << "The file cannot be opened" << endl;
		return EXIT_FAILURE;
	}
	else if (in_file.peek() == EOF) {
		cout << "File empty" << endl;
		return EXIT_FAILURE;
	}
	else {
			map.DRP = map.Read_file(in_file);
	}

	map.DRP[player.x_pos][player.y_pos] = player.target;                                      //set Player 												
	map.out_map(map.DRP);

	for (int i = 0; i < 3; i++) {                                                             //create 3 object artifact
		Artifact* art = new Artifact(i);
		artifacts.push_back(art);

		art->create(map.DRP);
	}
	map.out_map(map.DRP);

	while (true) {

		player.movement(map.DRP, _getch(), _getch());                                          //second _getch for for the special feature of arrow processing
		for (int i = 0; i < artifacts.size(); i++) {
			if (player.x_pos == artifacts[i]->x_pos && player.y_pos == artifacts[i]->y_pos) {
				counter_artifacts++;
				artifacts[i]->x_pos = -10;
				artifacts[i]->y_pos = -10;
			}
		}

		map.out_map(map.DRP);

		if (counter_artifacts == 3) {
			map.create_exit(map.DRP);
			map.out_map(map.DRP);
			counter_artifacts = 0;
		}

		if (player.x_pos == map.exit_x_pos && player.y_pos == map.exit_y_pos) {
			cout << endl << endl << endl << endl << endl << endl << setw(59) << "YOU WIN!"
				 << endl << endl << endl << endl << endl << endl << endl << endl << endl;
			break;
		}
	}
	return 0;
}

