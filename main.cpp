#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

vector<vector<string>> cells;
int rows = 40; // note to future me: make sure row and cols are min 3
int cols = 175;

int num_alive = 0;

void print_grid() {
	system("clear");
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			
			if(i == 0 || i == (rows-1) || j == 0 || j == (cols-1)) {
				cout << "\033[0;31m" << cells[i][j] << "\033[0m";
				continue;
			}
			
			if(cells[i][j] == "0") {
				cout << "\033[0;30m" << cells[i][j] << "\033[0m";
			} else if (cells[i][j] == "2") {
				cout << "\033[1;33m" << cells[i][j] << "\033[0m";
			}
			else {
				cout << "\033[1;32m" << cells[i][j] << "\033[0m";
			}
			//cout << cells[i][j]; // print each element of cells 2D vec
		
		}
		cout << endl;
	}
	cout << "\033[1;33m" << num_alive << "\033[0m";
	cout << endl;
}

bool is_alive(int row, int col) {
	if(stoi(cells[row][col]) >= 1) {
		return true;
	} else {
		return false;
	}
}

void set_alive(int row, int col) {
	cells[row][col] = "1";
}

void set_dead(int row, int col) {
	cells[row][col] = "0";
}

void set_semi_dead(int row, int col) {
	cells[row][col] = "-1";
}

void set_semi_alive(int row, int col) {
	cells[row][col] = "-2";
}

void set_random_alive(int row, int col) {
	cells[row][col] = "2";
}

int count_neighbors(int row, int col) {
	int neighbors = 0;
	for(int i = (row - 1); i < (row + 2); i++) {
		for(int j = (col - 1); j < (col + 2); j++) {
			
			if( (stoi(cells[i][j]) == 1 || stoi(cells[i][j]) == -1) ) { // alive neighbors
				if(i == row && j == col) {
					continue;
				}
				//cout << "i: " << i << "j: " << j << endl;
				neighbors++;
			}	
			
		}
	}
	return neighbors;
}

void update_state() {
	for(int i = 1; i < (rows - 1); i++) {
		for(int j = 1; j < (cols - 1); j++) {
			int num_neighbors = count_neighbors(i,j);
			// 1. Living cells die if they have less than 2 neighbors (loneliness)
			if(is_alive(i,j)) {
				
				if(num_neighbors < 2 || num_neighbors > 3) {
					set_semi_dead(i,j); // loneliness and overpop
				} else {
					set_alive(i,j);
				}
				
			} else { // dead cells w/ 3 neighbors become alive (reproduction)
				
				if(num_neighbors == 3) {
					set_semi_alive(i,j);
				}
				
				
			}
		}
	}
	
	for(int i = 1; i < (rows - 1); i++) { // update zombies
		for(int j = 1; j < (cols - 1); j++) {
			if( stoi(cells[i][j]) == -1 ) {
				set_dead(i,j);
				num_alive--;
			}
			
			if( stoi(cells[i][j]) == -2) {
				set_alive(i,j);
				num_alive++;
			}
		}
	}
	
	
}

void generate_random(int n) {
	
	srand(time(0));
	
	while(n > 0) {
		
		int x = ( rand() % (cols-2) ) + 1; // 0 to max
		int y = ( rand() % (rows-2) ) + 1; // 0 to max
		
		if(cells[y][x] != "1" && cells[y][x] != "2") { // not alive or already been picked
			set_random_alive(y,x);
			n--;
			num_alive++;
		}
		
	}
	
}

void create_board() {
	for(int i = 0; i < rows; i++) {
		vector<string> temp; // 1D vec
		for(int j = 0; j < cols; j++) {
			temp.push_back("0"); // add white square unicode character
		}
		cells.push_back(temp); // add the 1D array creating a 2D vec
	}
}

int main() {


	// initialize cell grid
	
	create_board();
	
	
	int x_shift = 16;
	int y_shift = 32;
	
	set_alive(2+y_shift,1+x_shift);
	set_alive(2+y_shift,2+x_shift);
	set_alive(2+y_shift,3+x_shift);
	set_alive(3+y_shift,1+x_shift);
	set_alive(4+y_shift,2+x_shift);
	
	//set_alive(3,2);
	//set_alive(3,3);
	
	string loop = "y";
	int cycle = 10;
	int counter = 1;
	bool log_random = false;
	
	int random = 120;
	print_grid();
	while(loop == "y") {
		//print_grid();
		//cout << endl;
		
		update_state();
		
		if(log_random) {
			random -= 5;
		}
		
		//if(random == 0) {
		//	generate_random(2);
		//}
		
		//if(num_alive == 0) {
		//	random = 10;
		//}
		
		generate_random(random);
		
		
		print_grid();
		
		
		//sleep(0.1);
		//cin >> loop;
		
		/*if(counter < cycle) {
			counter++;
		} else {
			cin >> loop;
			counter = 1;
		}*/
	}
	
	//cout << endl << count_neighbors(2,2) << endl;
	
	//cout << "\033[1;31m" << count_neighbors(3,3) << "\033[0m\n";
	//cout << endl << count_neighbors(3,3) << endl;
	
	return 0;
}
