/*
Joshua Sander
CS163
Program 4
11/17/2016

This program allows a user to access and edit a list of games.

It is represented by an ADT table, sorting the data by value.

There are two menus in the program.  First, the main menu allows the user to print the entire,
unsorted list of games, as well as a range of games within two characters.  They can also add games and display the # of 5 star games.

The second menu is accessed through the first.  It combines the retrieve and remove functions for this ADT,
allowing the user to search for an item and remove any instance of that item or remove only the specified platform-item combo.

*/

#include"games.h"
#include"BST.h"
#include"retrieve_class.h"
#include<cstring>
#include<iostream>
#include<fstream>

using namespace std;

const int MAX = 100;
const int COMMENT_MAX = 300;

int load_file(bst & my_bst);
int show_range(bst & my_bst);
int search(bst & my_bst);
int add_game(bst & my_bst);



int main()
{
	int total_games = 0;
	int height = 0;
	int best_games;
	game_info game;
	bst my_bst;
	load_file(my_bst);

	char choice;
	
	cout << endl << "Welcome to the game archive!" << endl;

	do {

		cout << endl;
		cout << "Please choose from the following options:" << endl;
		cout << "A: Add an entry to the archive" << endl;
		cout << "B: View or remove a game" << endl;
		cout << "C: Display all games" << endl;
		cout << "D: Display games within a range" << endl;
		cout << "E: Display the number of 5 star games" << endl;
		cout << "F: Exit this program" << endl;
		cout << "G: Display the height of the tree (CODERS ONLY!!)" << endl;

		cin >> choice;
		cin.ignore();

		switch (choice)
		{
			case 'a':
			case 'A':
				add_game(my_bst);	
				break;
			case 'b':
			case 'B':
				search(my_bst);
				break;
			case 'c':
			case 'C':
				if (my_bst.display_all() == 0 )
					cout << endl << "Your list is empty!" << endl;
				break;
			case 'd':
			case 'D':
				show_range(my_bst);
				break;
			case 'e':
			case 'E':
				best_games = my_bst.count_5_stars();
				if (best_games < 0)
					cout << endl << "There are no games in your list!" << endl;
				else	
					cout << endl << "There are " << best_games << " five star games in your list" << endl;
				break;
			case 'f':
			case 'F':
				break;
			case 'g':
			case 'G':
				height = my_bst.display_height(total_games);
				cout << "There are " << total_games << " in your bst with a height of " << height << "." << endl; 		
				total_games = 0;
				break;
			default:
				cout << "This is not a valid choice!  Choose again!" << endl;
				break;	
		}

	}while (choice != 'f' && choice != 'F');

	return 0;

}



//Loads a pre-selected file and reads the data, line by line, from the file.
int load_file(bst & my_bst)
{
	char name[MAX];
	char desc[MAX];
	char type[MAX];
	char platform[MAX];
	int rating;
	char comments[COMMENT_MAX];
 
	game_info new_game;
	ifstream games_list;
	games_list.open("CS163_games.txt");
	

	games_list.ignore(MAX,'\n');
	games_list.getline(name,MAX,':');
	games_list.getline(desc,MAX,':');
	games_list.getline(type,MAX,':');
	games_list.getline(platform,MAX,':');
	games_list >> rating;
	games_list.ignore(MAX,':');
	games_list.getline(comments,COMMENT_MAX,':');
	games_list.ignore(MAX,'\n');

	while (!games_list.eof())
	{
		new_game.insert_game_info(name, desc, type, platform, rating, comments);
		my_bst.insert(name, new_game);
		games_list.getline(name,MAX,':');
		games_list.getline(desc,MAX,':');
		games_list.getline(type,MAX,':');
		games_list.getline(platform,MAX,':');
		games_list >> rating;
		games_list.ignore(MAX,':');
		games_list.getline(comments,COMMENT_MAX,':');
		games_list.ignore(MAX,'\n');
	}

	games_list.close();

	return 1;
}



//Function to call the display_function within the bst
int show_range(bst & my_bst)
{
	char begin;
	char end;

	cout << "Please enter IN UPPERCASE the lowest letter of games you would like to see: " << endl;
	cin >> begin;
	cin.ignore();
	cout << endl << "Please enter IN UPPERCASE the highest letter of games you would like to see: " << endl;
	cin >> end;
	cin.ignore();
	cout << endl;

	if (my_bst.display_range(begin,end) == 0)
	{
		cout << "There are no games to display in this range!" << endl;
		return 0;
	}

	return 1;

}



//Function to retrieve objects from the bst.  Users can remove and view from here.
int search(bst & my_bst)
{
	char choice = 'a';
	char name[MAX];
	char remove_platform[MAX];
	retrieve_class gotcha; //Object containing desired table info

	cout << endl << "Please enter the name of the game" << endl;
	cin.getline(name, MAX, '\n');

	if (my_bst.retrieve(name, gotcha) == 0)
	{
		cout << endl << "This item is not in the list!" << endl;
	}

	else
	{
		cout << endl << "This is what we found: " << endl;
		gotcha.display_games();	

	}	

	gotcha.destroy_list(); //Clears the list of objects for the next game the user chooses

	do {
		cout << endl;
		cout << "Please choose from the following options:" << endl;
		cout << "A: Remove all matching games" << endl;
		cout << "B: Remove only 1 platform version of this game" << endl;
		cout << "C: Display another game" << endl;
		cout << "F: Return to main menu" << endl;

		cin >> choice;
		cin.ignore();

		switch (choice)
		{
			case 'a':
			case 'A':
				if (my_bst.remove_all(name) == 0)
					cout << "This game is not in your list!" << endl;
				else
					cout << "Successfully removed!" << endl;
				break;
			case 'b':
			case 'B':
				cout << endl << "Enter the name of the platform you would like to remove: " << endl;
				cin.getline(remove_platform, MAX, '\n');

				if (my_bst.remove(name, remove_platform) == 0)
				{
					cout << "This game is not in your list!" << endl;
				}
				else
					cout << "Success!" << endl;
				break;
			case 'c':
			case 'C':
				cout << endl << "Please enter the name of the game" << endl;
				cin.getline(name, MAX, '\n');

				if (my_bst.retrieve(name, gotcha) == 0)
				{
					cout << endl << "This item is not in the list!" << endl;
				}

				else
				{
					cout << endl << "This is what we found: " << endl;
					gotcha.display_games();	

				}	
				gotcha.display_platform(name);
				break;
			case 'f':
			case 'F':
				break;
			default:
				cout << "This is not a valid choice!  Choose again!" << endl;
				break;	
		}

	}while (choice != 'f' && choice != 'F');
	
	return 1;

}




//Reads user input and places it into table as new entry
int add_game(bst & my_bst)
{
	char new_name[MAX];
	char new_desc[MAX];
	char new_type[MAX];
	char new_platform[MAX];
	int rating;
	char new_comments[MAX];
	game_info to_add;
	
	cout << endl << "Please enter the name of the game" << endl;
	cin.getline(new_name, MAX, '\n');
	cout << "Please enter the description for the game" << endl;
	cin.getline(new_desc, MAX, '\n');
	cout << "Please enter the type of game" << endl;
	cin.getline(new_type, MAX, '\n');
	cout << "Please enter the platform for the game" << endl;
	cin.getline(new_platform, MAX,'\n');
	cout << "Please enter its star rating" << endl;
	cin >> rating;
	cin.ignore();
	cout << "Please enter comments for the game" << endl;
	cin.getline(new_comments, MAX,'\n');

	to_add.insert_game_info(new_name, new_desc, new_type, new_platform, rating, new_comments);

	return my_bst.insert(new_name, to_add);

}	

