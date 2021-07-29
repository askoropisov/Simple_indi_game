#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

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
	int x_pos;
	int y_pos; 

};

class Artifact {
public:
	int x_pos;
	int y_pos;
	
};

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

void Map::Out_map(vector<vector<char>> DRP) {							
	for (int j = 0; j < map.height; j++) {
		for (int i = 0; i < map.length; i++) {
			cout << setw(3) << DRP[j][i];
		}
		cout << endl;
	}
}

int main() {
	vector<vector<char>> DRP_symbol = map.Read_file(in_file);
	vector<vector<int>> DRP;

	DRP_symbol[0][0] = 'P';												
	map.Out_map(DRP_symbol);




	
}

