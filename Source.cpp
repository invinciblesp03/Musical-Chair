/**************************************************************
* Programmer Name:Shree Prakash Shah
* File Name: Musicalchair
* Date of Last Modification: 11/22/2022 A.D.
* Description: This is a complete c++ program which is a version of musical chairs, 
implemented using a circular linked list.  The program asks the user for the number of
players (2 to 7) and then for their names.  The program then selects a random number of
players to loop through (from a single player to three times the initial number of players).
It then displays a list of the players, with arrows pointing to the current player, 
and moves through the current players the chosen number of times. The player who is chosen
at this point will be eliminated.  This continues until there is one player remaining. 
At the end of each round, the program prints the name of the eliminated player.  
At the end of the game, the program prints the name of the winner.
*
**************************************************************/
#include <iostream>
#include <string>
#include <cstdlib>
#include <Windows.h>
#include <iomanip>

using namespace std;


struct ListNode
{
	string data;
	ListNode* next;
	ListNode* previous;
};

void addPlayer(ListNode*&, ListNode*&, string);
void printPlayers(ListNode*, ListNode*, string);
void playRound(ListNode*&, ListNode*&, long);
void removePlayer(ListNode*&, ListNode*&, string);
void removePlayerAfter(ListNode*&, ListNode*&, ListNode*);
ListNode* listSearch(ListNode*, ListNode*, string);


int main() {
	ListNode* head = nullptr;
	ListNode* tail = nullptr;
	ListNode* temp = nullptr;
	ListNode* newNode = nullptr;
	string playerName;
	int numPlayers, tempplayer;
	int randnum;
	srand(100);

	
	do {
	cout << "PLEASE ENTER THE NUMBER OF PLAYERS FROM 2 TO 7." << endl;
	cin >> numPlayers;
	} while (numPlayers > 7 || numPlayers < 2);

	for (int i = 0; i < numPlayers; i++) {
		//Beep(600, 600);
		cout << "Enter the name of Player " << i + 1 << endl;
		cin >> playerName; 		
		addPlayer(head,tail, playerName);
	}



	system("cls");
	system("pause");

	

	for (int i = numPlayers-1; i > 0; i--) {
		randnum = rand() % 3*numPlayers + 1;
		playRound(head, tail,randnum );
		system("pause");
		system("cls");
		cout << "The winner is " << head->data <<"!" << endl;
	}
	



	return 0;
}

// This function is used to add a player to the end of the list when passed the head, tail, and that player’s name(It is similar to listAppend).
void addPlayer(ListNode*& head, ListNode*& tail, string playerName)  {
	ListNode* newNode;
	newNode = new ListNode;
	newNode->data = playerName;
	newNode->next = nullptr;
	newNode->previous = nullptr;
		if (head == nullptr) {
			head = newNode;
			tail = newNode;
			head->next = head;
			head->previous=head;
		}
		else {
			newNode->previous = tail;
			tail->next = newNode;
			tail = newNode;
			tail->next = head;
			head->previous = newNode;
		}
	}
/*
This function prints all the players in the list, given the head, tail, and the name of the player to draw arrows under. 
It has two list traversals in it.
*/
void printPlayers(ListNode* head, ListNode* tail, string playername) {
	ListNode* currentnode;

	int count=0;
	string arrow = "";
	if (head != nullptr) {
		currentnode = head;

		do {
			cout <<setw(18)<<  currentnode->data;
			currentnode = currentnode->next;
		} while (currentnode != head);

		cout << endl;
		
		for (int i = 0; i < size(playername); i++) {
			arrow = arrow + "^";
		}
		currentnode = head;

		while (currentnode->data != playername) {
			count++;
			currentnode = currentnode->next;
		}

		for (int i = 0; i < count; i++) {
			cout << setw(18) << " ";
		}
		
		cout << setw(18) << arrow;
		cout << endl;

	}
	
	
	}

//This function deletes a player from the list, given the head, tail, and the name of the player.

void removePlayer(ListNode*& head, ListNode*& tail, string playername) {
	ListNode* temp;

	if (head != nullptr)
	{
		if (head->data == playername)
		{
			removePlayerAfter(head, tail, nullptr);
		}
		else
		{
			temp = head;

			while (temp->next != head && temp->next->data != playername)
			{
				temp = temp->next;
			}
			if (temp->next != head)
			{
				removePlayerAfter(head, tail, temp);

			}
			
		}
	}
}
// This deletes a player from the list, given the head, tail, and a pointer to node before the player to delete. (similar to listRemoveAfter)
void removePlayerAfter(ListNode*& head , ListNode*& tail, ListNode* curNode) {
	
		ListNode* sucNode;
		ListNode* toDelete;
		if ((curNode == nullptr) && (head != nullptr))
		{
			sucNode = head->next;
			sucNode->previous = tail;
			toDelete = head;
			head = sucNode;

			if (sucNode == toDelete) {
				head = nullptr;
				tail = nullptr;
			}
			else
			{
				tail->next = head;
			}

		}

		else if (curNode->next != head)
		{
			sucNode = curNode->next->next;
			toDelete = curNode->next;
		 sucNode->previous = curNode ;
			curNode->next = sucNode;
			
			if (sucNode == head) {

				tail = curNode;
				tail->next = head;

			}
			delete toDelete;
		}


	}

/*This function plays a single round of the game.
*It is passed the head, tail, and the total number of players to loop through before stopping,
*and will delete the player that is chosen once the looping is complete.
*/
void playRound(ListNode*& head, ListNode*& tail, long numloop) {
	ListNode* currentnode = head;
	int random;
	//cout << numloop;
	for (int i = numloop+1; i > 0; i--) {
		system("cls");
		printPlayers(head, tail, currentnode->data);
		

		random = (rand() % 500 + 100);
		Sleep(random);
		currentnode = currentnode->next;
		
		Beep(523, 500);
		system("cls");

}
	
	printPlayers(head, tail, currentnode->data);
	cout << currentnode->data << " has been eliminated. " << endl;
	removePlayer(head, tail, currentnode->data);	

}