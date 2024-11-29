#include "display.h"

using namespace std;

int get_num_floors(){
	int n;
	do{
		cout << "How many floors?\n";
		cin >> n;
		if(n > 0){
			return n;
		}else{
			cout << "Please enter a positive number. \n";
		}
	}while(true);
}

int get_width(){
	cout << "Welcome to Hunt the Wumpus. \n\n";
	int n;
	do{
		cout << "How many rooms wide?" << endl;
		cin >> n;
		if(n >= 4 && n <= 50){
			return n;
		}else{
			cout << "Invalid choice. Please choose from the range 4 - 50. ";
		}
	}while(true);
}

int get_length(){
	int n;
	do{
		
		cout << "How many rooms long?\n";
		cin >> n;
		if(n >= 4 && n <= 50){
			return n;
		}else{
			cout << "Invalid choice. Please choose from the range 4 - 50. ";
		}
	}while(true);
}

bool get_debug(){
	char n;
	do{
		cout << "Enter debug mode? (y/n)\n";
		cin >> n;
		if(n == 'y'){
			return true;
		}else if(n == 'n'){
			return false;
		}else{
			cout << "Invalid choice. ";
		}
	}while(true);
}

bool get_restart(){
	char n;
	do{
		printw("Play again? (y/n)");
		refresh();
		n = getch();
		if(n == 'y'){
			wclear(stdscr);
			return true;
		}else if(n == 'n'){
			wclear(stdscr);
			return false;
		}else{
			printw("\nInvalid choice. ");
		}
	}while(true);
}

bool get_keep_settings(){
	char n;
	do{
		printw("1: Keep same cave settings\n2. Restart with a new cave\n");
		refresh();
		n = getch();
		if(n == '1'){
			wclear(stdscr);
			return true;
		}else if(n == '2'){
			wclear(stdscr);
			return false;
		}else{
			printw("\nInvalid choice. \n");
		}
	}while(true);
}