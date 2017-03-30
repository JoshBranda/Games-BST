#include"retrieve_class.h"
#include<iostream>
#include<cstring>

using namespace std;



//Default constructor
retrieve_class::retrieve_class()
{
	head = NULL;
}



//Destructor
retrieve_class::~retrieve_class()
{
	p_node * temp;
	
	while (head)
	{
		temp = head->next;
		delete head;
		head = temp;
	}	
	
}



//This displays the games stored in retrieve that match the search critera of the user
int retrieve_class::display_games(void)
{
	p_node * current = head;
	
	if (!head)
		return 0;

	while (current)
	{
		current->p_game->display_game();
		current = current->next;
	}
	
	return 1;
}



//This traverses the retrieve object to only display games that also match the platform criteria of the user 
int retrieve_class::display_platform(char * p_name)
{
	p_node * current = head;

	if (!head)
		return 0;
	
	while (current)
	{
		if ( strstr(current->p_game->return_platform(), p_name) )
		{
			current->p_game->display_game();
		}
		current = current->next;
	}

	return 1;
}



//This adds games to the retrieve object
int retrieve_class::insert(game_info * to_add)
{
	if (!head)
	{
		head = new p_node;
		head->p_game = to_add;
		head->next = NULL;
		return 1;
	}

	p_node * temp = new p_node;
	temp->p_game = to_add;
	temp->next = head;
	head = temp;
	

	return 1;

}



//I created this extra function for interacting with my bst in main.  Since different objects can be retrieved in succession,
//this is essentially a destructor function that can be called to clear the list for the next set of objects
int retrieve_class::destroy_list(void)
{
	p_node * temp;
	
	while (head)
	{
		temp = head->next;
		delete head;
		head = temp;
	}	

	return 1;	
}
