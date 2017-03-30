#ifndef BINARY_TREES
#define BINARY_TREES
#include"games.h"
#include"retrieve_class.h"

/*
This binary search tree data structure is used to handle the table ADT of games for Program 4

ALL FUNCTIONS WERE DONE RECURSIVELY!  I thought it would help prepare me for 202

INPUT: The names of games (to add, remove, or give to retrieve)
INPUT: The platform name (for specific remove)
INPUT: The beginning and ending characters for the range display
INPUT: The total items in the list passed by reference, so it may be printed in main

OUTPUT: The total list and a range of values in the list.

*/

struct node
{
	game_info game;
	node * left;
	node * right;
};

class bst
{
	public:
		bst();
		~bst();

		//Accessor functions
		int display_all(void);	
		int display_range(char begin, char end);
		int count_5_stars(void);
		int retrieve(char * to_retrieve, retrieve_class & gotcha); 
		int display_height(int &items);

		//Mutator functions	
		int insert(char * new_name, game_info & to_add);
		int remove(char * old_name, char * old_platform);
		int remove_all(char * old_name);


	private:
		//Recursive destructor
		int destroy_all(node * current);
		
		//Recursive accessor
		int display_all(node * current);
		int display_range(char begin, char end, node * current);
		int count_5_stars(node * current);
		int retrieve(char * to_retrieve, node * current, retrieve_class & gotcha);
		int display_height(node * current, int &items);

		//Recursive Mutator
		int insert(char * new_name, game_info & to_add, node * &current);
		int remove(char * old_name, char * old_platform, node * &current);
		int delete_successor(game_info & to_fill, node * &current);
		int remove_all(char * old_name, node * &current);

		node * root;
};

#endif
