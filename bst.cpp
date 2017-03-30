#include"BST.h"
#include<cstring>
#include<iostream>

using namespace std;



//Constructor
bst::bst()
{
	root = NULL;
}



//Destructor
bst::~bst()
{
	if (root)
		destroy_all(root);
}	



//Recursive call of the destructor
//Desctructor of game class will be called in addition
int bst::destroy_all(node * current)
{
	if (!current)
		return 0;

	destroy_all(current->left);
	destroy_all(current->right);			

	delete current;
	
	return 0;
}



//Wraper function for the display, returns 0 if bst empty
int bst::display_all(void)
{
	if (!root)
		return 0;

	return display_all(root) + 1;	
}



//Inorder recursive call for the display
int bst::display_all(node * current)
{
	if (!current)
		return 0;

	display_all(current->left);
	current->game.display_game();

	display_all(current->right);

	return 1;
} 




//Wrapper function checks to make sure the BST isn't empty
int bst::display_range(char begin, char end)
{
	if (!root)
		return 0;

	return display_range(begin, end, root);
}




//Recursive call traverses the BST inorder and prints
int bst::display_range(char begin, char end, node * current)
{
	if (!current)
		return 0;
	
	if (begin <= current->game.return_1st_letter() ) //If lower range is below the current node
	{
		display_range(begin, end, current->left); //Move to the next left node first
		if (end >= current->game.return_1st_letter() ) //Then, if the current node is not outside the upper range, print and go right
		{
			current->game.display_game();
			return display_range(begin, end, current->right);
		}
		return 0; //Otherwise, no need to go right since anything to the right will be outside the range anyway
	}		

	return display_range(begin, end, current->right); //If the current node is lower than the lower range, no need to go left because it only gets smaller
	
}



//Wrapper function for counting the number of 5 star games.  Since 0 will indicate 0 games with 5 stars,
//-1 indicates that the list is empty
int bst::count_5_stars(void)
{
	if (!root)
		return -1;

	return count_5_stars(root);
}



//Recursive call visits all nodes in the bst to check for 5 scores, adds 1 to return value if one is found 
int bst::count_5_stars(node * current)
{
	if (!current)
		return 0;

	if (current->game.return_rating() == 5)
	{
		return count_5_stars(current->left) + count_5_stars(current->right) + 1;
	}

	return count_5_stars(current->left) + count_5_stars(current->right);
}



//Wrapper function checks to see if the bst is empty or not
int bst::retrieve(char * to_retrieve, retrieve_class & gotcha)
{
	if (!root)
		return 0;

	return retrieve(to_retrieve, root, gotcha);	
}



//Recursive call logarithmically searches bst for any matching games
//and uses the retrieve function to populate the retrieve LLL with any matches
int bst::retrieve(char * to_retrieve, node * current, retrieve_class & gotcha)
{
	if (!current)
	{
		return 0;
	}

	if (strcmp(to_retrieve, current->game.return_name() ) < 0)
	{
		return retrieve(to_retrieve, current->left, gotcha);
	}

	if (strcmp(to_retrieve, current->game.return_name() ) == 0)
	{
		gotcha.insert(&(current->game));
		return retrieve(to_retrieve, current->right, gotcha) + 1;
	}



	return retrieve(to_retrieve, current->right, gotcha);
}	



//Wrapper function access private function
int bst::insert(char * new_name, game_info & to_add)
{
	return insert(new_name, to_add, root);
}



//Recursive call checks to see if leaf has been reached (base case) and inserts if so.
//If not, it traverses the bst based on value (right = greater, left = lesser)
int bst::insert(char * new_name, game_info & to_add, node * &current)
{
	if (!current)
	{
		current = new node;
		current->game.copy_game(to_add);
		current->left = NULL;
		current->right = NULL;
		return 1;
	}

	if (strcmp(new_name, current->game.return_name() ) >= 0)
		return insert(new_name, to_add, current->right);

	return insert(new_name, to_add, current->left);
}	



//Wrapper function checks to see if bst is empty
int bst::display_height(int &items)
{

	if (!root)
		return 0;

	return display_height(root, items);	
}



//Recursive fucntion tallies both the total number of times and the height of the tree
int bst::display_height(node * current, int &items)
{
	if (!current)
		return 0;

	++items;	
	return 1 + max (display_height(current->left, items), display_height(current->right, items));
}



//Wrapper checks to see if bst is empty
int bst::remove(char * old_name, char * old_platform)
{
	if (!root)
		return 0;
	
	return remove(old_name, old_platform, root);
}



//Recursive call traverses a simple path down the bst until a match is found
//Once found, it evalutes the number of children for the node
//There are 4 cases: no children, 1 left child, 1 right child, and 2 children
//If 2 children are discovered, the IOS is copied into the node to be deleted,
//and the IOS node is then deleted
int bst::remove(char * old_name, char * old_platform, node * &current)
{
	if (!current)
	{
		return 0;
	}

	if (strcmp(old_name, current->game.return_name() ) < 0)
	{
		return remove(old_name, old_platform, current->left);
	}

	if (strcmp(old_name, current->game.return_name() ) == 0)
	{
		if (strcmp(old_platform, current->game.return_platform() ) == 0)
		{
			if ( (current->left == NULL) && (current->right == NULL) )
			{
				delete current;
				current = NULL;
			}

			else if ( (current->left != NULL) && (current->right == NULL) )
			{
				node * temp = current->left;
				delete current;
				current = temp;
			}

			else if ( (current->left == NULL) && (current->right != NULL) )
			{
				node * temp = current->right;
				delete current;
				current = temp;
			}

			else
			{
				delete_successor(current->game, current->right); //Current->game is passed by reference and "deleted" by being replaced with the new value
			}
		}

		return 1;
	}



	return remove(old_name, old_platform, current->right);
}	

 


//This recursive function finds the IOS, copies the IOS's data into the game to be deleted
//and then delets the IOS node (since its data is now safe in the new spot)
int bst::delete_successor(game_info & to_fill, node * &current)
{
	if (current->left == NULL)
	{
		if ( current->right != NULL)
		{
			to_fill.copy_game(current->game); //Prevent 2 traversals, use the copy function from the object that needs to be removed to replace it with the IOS
			node * temp = current->right;
			delete current;
			current = temp;
			return 1;
		}
		to_fill.copy_game(current->game); //Performs same function described above
		delete current;
		current = NULL;
		return 1;
	}

	return delete_successor(to_fill, current->left);
}




//Wrapper function checks to see if the table is empty
int bst::remove_all(char * old_name)
{
	if (!root)
		return 0;
	
	return remove_all(old_name, root);
}



//Recursive call is almost identical to the remove single game function
//However, it does not stop once a game has been removed, it continues its recursion
//until it reaches the end of a path, or a leaf's NULL child
int bst::remove_all(char * old_name, node * &current)
{
	if (!current)
	{
		return 0;
	}

	if (strcmp(old_name, current->game.return_name() ) < 0)
	{
		return remove_all(old_name, current->left);
	}

	if (strcmp(old_name, current->game.return_name() ) == 0)
	{
		if ( (current->left == NULL) && (current->right == NULL) )
		{
			delete current;
			current = NULL;
		}

		else if ( (current->left != NULL) && (current->right == NULL) )
		{
			node * temp = current->left;
			delete current;
			current = temp;
		}

		else if ( (current->left == NULL) && (current->right != NULL) )
		{
			node * temp = current->right;
			delete current;
			current = temp;
		}

		else
		{
			delete_successor(current->game, current->right);
		}

		return remove_all(old_name, current) + 1;
	}



	return remove_all(old_name, current->right);
}	

 


