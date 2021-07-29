#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <conio.h>

using namespace std;

ifstream in_file("input.txt");

class Map {
public:
	
	int length;
	int height;
	vector<vector<char>> Read_file(ifstream& in_file);                   //reading file and return DRP[][]
	void Out_map(vector<vector<char>> DRP);
} map;

class Player {
public:
	int x_pos = 0;
	int y_pos = 0;
	void movement(vector<vector<char>>& DRP, int key, int trash);

} player;



class Artifact {
public:
	int number = 0;
	int x_pos = 0;
	int y_pos = 0;
	bool check_for_take = false;
	void create(vector<vector<char>>& DRP);
public:
	Artifact(int number);
	
};
Artifact::Artifact(int number) : number(number) {}
vector<Artifact*> artifacts;

vector<vector<char>> Map::Read_file(ifstream& in_file) {                  //reading input file and create gameng map
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
	
	return DRP;
}

void Player::movement(vector<vector<char>>& DRP, int key, int trash) {
	int temp_x = player.x_pos;
	int temp_y = player.y_pos;
	switch (key) {
	case 72:
		if (player.x_pos > 0 && DRP[player.x_pos-1][player.y_pos]!='#') {
			player.x_pos -= 1;
		}
		break;
	case 80:
		if (player.x_pos < map.height - 1 && DRP[player.x_pos + 1][player.y_pos] != '#') {
			player.x_pos += 1;
		}
		break;
	case 75:
		if (player.y_pos > 0 && DRP[player.x_pos][player.y_pos-1] != '#') {
			player.y_pos -= 1;
		}
		break;
	case 77:
		if (player.y_pos < map.length - 1 && DRP[player.x_pos][player.y_pos + 1] != '#') {
			player.y_pos += 1;
		}
		break;
	}
	DRP[temp_x][temp_y] = '.';
	DRP[player.x_pos][player.y_pos] = 'P';
}

void Artifact::create(vector<vector<char>>& DRP) {
	
	int temp_x, temp_y, counter = 0;
	srand(time(NULL));

	while (counter < 1) {
		temp_x = rand() % map.height;
		temp_y = rand() % map.length;
		if (DRP[temp_x][temp_y] == '.') {
			x_pos = temp_x;
			y_pos = temp_y;
			DRP[x_pos][y_pos] = '+';
			counter++;
		}
	}

} 

void Map::Out_map(vector<vector<char>> DRP) {							
	for (int j = 0; j < map.height; j++) {
		for (int i = 0; i < map.length; i++) {
			cout << setw(3) << DRP[j][i];
		}
		cout << endl;
	}
	cout << endl;
}

int main() {
	vector<vector<char>> DRP_symbol = map.Read_file(in_file);
	vector<vector<int>> DRP;

	DRP_symbol[player.x_pos][player.y_pos] = 'P';												
	map.Out_map(DRP_symbol);

	for (int i = 0; i < 3; i++) {
		Artifact* art = new Artifact(i);
		artifacts.push_back(art);

		art->create(DRP_symbol);
	}
	map.Out_map(DRP_symbol);

	while (true) {
		
		player.movement(DRP_symbol, _getch(), _getch());                             //second _getch for for the special feature of arrow processing
		map.Out_map(DRP_symbol);
	}
	
	
	

	
}

