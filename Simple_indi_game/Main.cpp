#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <conio.h>
#include <thread>
#include <Windows.h>
#include <stdio.h>
#include "Class.h"

using namespace std;

void Player::movement(vector<vector<char>>& DRP, int key, int trash, Map map) {

    int temp_x = this->x_pos;
    int temp_y = this->y_pos;
 
    switch (key) {
    case key_left:
        if (this->x_pos > 0 && DRP[this->x_pos - 1][this->y_pos] != map.barier) {
            this->x_pos -= 1;
        }
        break;
    case key_right:
        if (this->x_pos < map.height - 1 && DRP[this->x_pos + 1][this->y_pos] != map.barier) {
            this->x_pos += 1;
        }
        break;
    case key_up:
        if (this->y_pos > 0 && DRP[this->x_pos][this->y_pos - 1] != map.barier) {
            this->y_pos -= 1;
        }
        break;
    case key_down:
        if (this->y_pos < map.length - 1 && DRP[this->x_pos][this->y_pos + 1] != map.barier) {
            this->y_pos += 1;
        }
        break;
    case key_escape:
        exit(0);
    default:
        break;
    }
    DRP[temp_x][temp_y] = map.void_cell;
    DRP[this->x_pos][this->y_pos] = map.player;
}

void Artifact::create(vector<vector<char>>& DRP, Map map) {
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

void Map::read_file(ifstream& in_file) {                                  //reading input file and create gaming map

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

void Map::rendering(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

void Map::print(vector<vector<char>> DRP) {
    this->rendering(0, 0);

    cout << endl << endl << endl << endl << endl << endl;
    for (int j = 0; j < this->height; j++) {
        cout << "                                      ";
        for (int i = 0; i < this->length; i++) {
            switch (DRP[j][i])
            {
            case artifact: {
                this->color_symbol(DRP, color::red, i, j);
                break;
            }
            case player: {
                this->color_symbol(DRP, color::green, i, j);
                break;
            }
            case exit: {
                this->color_symbol(DRP, color::purple, i, j);
                break;
            }
            case barier: {
                this->color_symbol(DRP, color::yelow, i, j);
                break;
            }
            case void_cell: {
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
            this->exit_open=true;
            this->exit_x_pos = temp_x;
            this->exit_y_pos = temp_y;
            DRP[exit_x_pos][exit_y_pos] = symbol::exit;
            counter++;
        }
    }
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
    Sleep(300);
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



void Map::victory() {
    simple_music_win();
    SetConsoleTextAttribute(this->h_console, this->purple);
    cout << endl << endl << endl << endl << endl << endl << setw(62) << "YOU WIN!"
        << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    SetConsoleTextAttribute(this->h_console, this->white);
}

bool Map::create(Player player, vector<Artifact*>& artifacts) {
    ifstream in_file("input_medium.txt");

    if (!in_file.is_open()) {
        cout << "The file cannot be opened" << endl;
        return EXIT_FAILURE;
    }
    else if (in_file.peek() == EOF) {
        cout << "File empty" << endl;
        return EXIT_FAILURE;
    }
    else {
        this->read_file(in_file);
    }

    this->DRP[player.x_pos][player.y_pos] = this->player;                                      //set Player
    this->print(this->DRP);

    for (int i = 0; i < 3; i++) {                                                             //create 3 object artifact
        Artifact* art = new Artifact(i);
        artifacts.push_back(art);

        art->create(this->DRP, *this);
    }
    this->print(this->DRP);
}


void Map::processing_key_user(Player player, vector<Artifact*> artifacts) {
    thread music(simple_music_back);
    int counter_artifacts = 0;

    while (true) {
        player.movement(this->DRP, _getch(), _getch(), *this);                                 //second _getch for for the special feature of arrow processing
        for (int i = 0; i < artifacts.size(); i++) {
            if (player.x_pos == artifacts[i]->x_pos && player.y_pos == artifacts[i]->y_pos) {
                counter_artifacts++;
                delete artifacts[i];
            }
        }

        this->print(this->DRP);

        if (counter_artifacts == 3) {
            this->create_exit(this->DRP);
            this->print(this->DRP);
            counter_artifacts = 0;
        }

        if (player.x_pos == this->exit_x_pos && player.y_pos == this->exit_y_pos && this->exit_open == true) {
            player.~Player();
            music.detach();
            this->victory();
            this->~Map();
            break;
        }
    }
}


int main() {

    Player player;
    vector<Artifact*> artifacts;
    Map map;

    if (!map.create(player, artifacts)) {
        return EXIT_FAILURE;
    }

    map.processing_key_user(player, artifacts);

    return 0;
}