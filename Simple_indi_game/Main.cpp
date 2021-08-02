#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <conio.h>
#include <thread>
#include <Windows.h>
#include <stdio.h>

using namespace std;

class Player {
public:
	int x_pos = 0;
	int y_pos = 0;

	void movement(vector<vector<char>>& DRP, int key, int trash);
};

class Artifact {
public:
	int number = 0;
	int x_pos = 0;
	int y_pos = 0;

	void create(vector<vector<char>>& DRP);
	Artifact(int number);
	~Artifact() {};
};
Artifact::Artifact(int number) : number(number) {}

class Map {
public:
	enum symbol {
		barier = '#',
		void_cell = '.',
		player = 'P',
		artifact = '@',
		exit = 'E',
	};
	enum color {
		black,
		blue,
		green,
		white_blue,
		red,
		purple,
		yelow,
		white,
		gray,
		light_blue,
		light_green,
		light_white_blue,
		light_red,
		pink,
		light_yelow,
		light_white
	};
	HANDLE h_console;
	int length;
	int height;
	int exit_x_pos = -10;
	int exit_y_pos = -10;
	vector<vector<char>> DRP;

	bool create(ifstream& in_file, Player player, vector<Artifact*>& artifacts);
	void read_file(ifstream& in_file);                       //reading file and return DRP[][]
	void print(vector<vector<char>> DRP);
	void create_exit(vector<vector<char>>& DRP);
	void color_symbol(vector<vector<char>>& DRP, int color, int i, int j);
} map;


void Player::movement(vector<vector<char>>& DRP, int key, int trash) {
	int temp_x = this->x_pos;
	int temp_y = this->y_pos;
	switch (key) {
	case 72:
		if (this->x_pos > 0 && DRP[this->x_pos - 1][this->y_pos] != map.barier) {
			this->x_pos -= 1;
		}
		break;
	case 80:
		if (this->x_pos < map.height - 1 && DRP[this->x_pos + 1][this->y_pos] != map.barier) {
			this->x_pos += 1;
		}
		break;
	case 75:
		if (this->y_pos > 0 && DRP[this->x_pos][this->y_pos - 1] != map.barier) {
			this->y_pos -= 1;
		}
		break;
	case 77:
		if (this->y_pos < map.length - 1 && DRP[this->x_pos][this->y_pos + 1] != map.barier) {
			this->y_pos += 1;
		}
		break;
	default:
		break;
	}
	DRP[temp_x][temp_y] = map.void_cell;
	DRP[this->x_pos][this->y_pos] = map.player;
}

void Artifact::create(vector<vector<char>>& DRP) {
	int temp_x, temp_y, counter = 0;
	srand(time(NULL));

	while (counter < 1) {
		temp_x = rand() % map.height;
		temp_y = rand() % map.length;
		if (DRP[temp_x][temp_y] == map.void_cell && DRP[temp_x][temp_y] != DRP[0][0]) {
			x_pos = temp_x;
			y_pos = temp_y;
			DRP[x_pos][y_pos] = map.artifact;
			counter++;
		}
	}
}

void Map::read_file(ifstream& in_file) {                      //reading input file and create gaming map

	char symbol;
	in_file >> this->length;
	in_file >> this->height;
	vector<char> string;

	symbol = in_file.get();                                               //skip '\n'
	for (int j = 0; j < this->height; j++) {
		for (int i = 0; i < this->length; i++) {
			symbol = in_file.get();
			string.push_back(symbol);
		}
		symbol = in_file.get();                                           //skip '\n' in end string
		this->DRP.push_back(string);
		string.clear();
	}
	in_file.close();
}

void Map::color_symbol(vector<vector<char>>& DRP, int color, int i, int j) {
	h_console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h_console, color);
	cout << setw(2) << DRP[j][i];
	SetConsoleTextAttribute(h_console, color::white);
}

void Map::print(vector<vector<char>> DRP) {

	for (int j = 0; j < this->height; j++) {
		cout << "                                      ";
		for (int i = 0; i < this->length; i++) {
			switch (DRP[j][i])
			{
			case symbol::artifact: {
				this->color_symbol(DRP, color::red, i, j);
				break;
			}
			case symbol::player: {
				this->color_symbol(DRP, color::green, i, j);
				break;
			}
			case symbol::exit: {
				this->color_symbol(DRP, color::purple, i, j);
				break;
			}
			case symbol::barier: {
				this->color_symbol(DRP, color::yelow, i, j);
				break;
			}
			case symbol::void_cell: {
				this->color_symbol(DRP, color::light_blue, i, j);
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
		temp_x = rand() % this->height;
		temp_y = rand() % this->length;
		if (DRP[temp_x][temp_y] == this->barier) {
			this->exit_x_pos = temp_x;
			this->exit_y_pos = temp_y;
			DRP[exit_x_pos][exit_y_pos] = symbol::exit;
			counter++;
		}
	}
}

bool Map::create(ifstream& in_file, Player player, vector<Artifact*>& artifacts) {

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
		map.read_file(in_file);
	}

	this->DRP[player.x_pos][player.y_pos] = this->player;                                      //set Player
	this->print(this->DRP);

	for (int i = 0; i < 3; i++) {                                                             //create 3 object artifact
		Artifact* art = new Artifact(i);
		artifacts.push_back(art);

		art->create(this->DRP);
	}
	this->print(this->DRP);
}

void simple_music_back() {
	while (true) {
		Beep(784, 150);
		Sleep(300);
		Beep(784, 150);
		Sleep(300);
		Beep(932, 150);
		Sleep(150);
		Beep(1047, 150);
		Sleep(150);
		Beep(784, 150);
		Sleep(300);
		Beep(784, 150);
		Sleep(300);
		Beep(699, 150);
		Sleep(150);
		Beep(740, 150);
		Sleep(150);
		Beep(784, 150);
		Sleep(300);
		Beep(784, 150);
		Sleep(300);
		Beep(932, 150);
		Sleep(150);
		Beep(1047, 150);
		Sleep(150);
		Beep(784, 150);
		Sleep(300);
		Beep(784, 150);
		Sleep(300);
		Beep(699, 150);
		Sleep(150);
		Beep(740, 150);
		Sleep(150);
		Beep(932, 150);
		Beep(784, 150);
		Beep(587, 1200);
		Sleep(75);
		Beep(932, 150);
		Beep(784, 150);
		Beep(554, 1200);
		Sleep(75);
		Beep(932, 150);
		Beep(784, 150);
		Beep(523, 1200);
		Sleep(150);
		Beep(466, 150);
		Beep(523, 150);
	}
}
void simple_music_win() {
	Beep(659.26, 200);
	Beep(659.26, 200);
	Sleep(200);
	Beep(659.26, 200);
	Sleep(100);
	Beep(523.26, 200);
	Beep(659.26, 200);
	Sleep(200);
	Beep(783.98, 200);
	Sleep(400);
	Beep(391.99, 200);
}

void victory() {
	simple_music_win();

	SetConsoleTextAttribute(map.h_console, map.purple);
	cout << endl << endl << endl << endl << endl << endl << setw(62) << "YOU WIN!"
		<< endl << endl << endl << endl << endl << endl << endl << endl << endl;
	SetConsoleTextAttribute(map.h_console, map.white);
}


int main() {

	//Map map;
	Player player;
	thread music(simple_music_back);

	ifstream in_file("input_medium.txt");
	vector<Artifact*> artifacts;

	map.create(in_file, player, artifacts);
	int counter_artifacts = 0;


	while (true) {
		player.movement(map.DRP, _getch(), _getch());                                          //second _getch for for the special feature of arrow processing
		for (int i = 0; i < artifacts.size(); i++) {
			if (player.x_pos == artifacts[i]->x_pos && player.y_pos == artifacts[i]->y_pos) {
				counter_artifacts++;
				delete artifacts[i];
			}
		}

		map.print(map.DRP);

		if (counter_artifacts == 3) {
			map.create_exit(map.DRP);
			map.print(map.DRP);
			counter_artifacts = 0;
		}

		if (player.x_pos == map.exit_x_pos && player.y_pos == map.exit_y_pos) {
			music.detach();
			victory();
			break;
		}
	}
	return 0;
}

