#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <conio.h>
#include <thread>
#include <Windows.h>
#include <stdio.h>
#pragma once

using namespace std;


class Map;
class Artifact;

class Player {
public:
    int x_pos = 0;
    int y_pos = 0;
    enum user_key {
        key_up = 75,
        key_left = 72,
        key_right = 80,
        key_down = 77,
        key_escape = 27,
    };

    void movement(vector<vector<char>>& DRP, int key, int trash, Map map);

    ~Player() {};
};

class Artifact {
public:
    int number = 0;
    int x_pos = 0;
    int y_pos = 0;

    void create(vector<vector<char>>& DRP, Map map);

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
    bool exit_open = false;
    int exit_x_pos = 0;
    int exit_y_pos = 0;
    vector<vector<char>> DRP;

    bool create(Player player, vector<Artifact*>& artifacts);
    void victory();
    void rendering(int x, int y);
    void processing_key_user(Player player, vector<Artifact*> artifacts);
    void read_file(ifstream& in_file);
    void print(vector<vector<char>> DRP);
    void create_exit(vector<vector<char>>& DRP);
    void color_symbol(vector<vector<char>>& DRP, int color, int i, int j);

    ~Map() {};
};