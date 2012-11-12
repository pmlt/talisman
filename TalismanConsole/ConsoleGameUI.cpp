#include "stdafx.h"
#include "ConsoleGameUI.h"
#include <iostream>
#include <string>
#include <iomanip>

ConsoleGameUI::ConsoleGameUI(Game &game) :
  GameUI(game)
{
}


ConsoleGameUI::~ConsoleGameUI(void)
{
}

void ConsoleGameUI::announce(string msg)
{
  cout << msg << endl << endl;
  getchar();
}

unsigned int ConsoleGameUI::prompt(string msg, string options[], unsigned int options_size)
{
  //asks user for the index position of their choice plus 1, in
  //order to allow for the choice of 1, 2, 3, instead of 0, 1, 2
  
  unsigned int choice;

  cout << msg << endl;
  for (unsigned int i = 0; i < options_size; ++i)
  {
    cout << "  " << i+1 << ") " << options[i] << endl;
  }
  cout << "Enter your choice: ";
  cin >> choice;

  while (choice < 1 || choice > options_size)
  {
    cout << "Invalid choice selected. Please enter a number between 1 and " << options_size << "." << endl;
    cout << msg << endl;
    for (unsigned int i = 0; i < options_size; ++i)
    {
      cout << " " << i+1 << ") " << options[i] << endl;
    }
    cout << "Enter your choice: ";
    cin >> choice;
  }

  return (choice - 1);
}

void ConsoleGameUI::notify()
{
  //Redraw screen here! You have access to the whole game information from this->game

  string str;
  system("cls");

  //Set top bar
  cout << " ";
  for (int i = 0; i < 6; ++i)
    cout << "_____________________";
  cout << "____________________" << endl;
  
  //Rows = i. Columns = j.
  for (int i = 0; i < 7; ++i)
  {
    //First
    for (int j = 0; j < 7; ++j)
    {
      cout << "|" << setw(20);
      if (this->game->getBoard()->getTile(i, j) != NULL)
      {
        
        str = this->game->getBoard()->getTile(i, j)->getTitle();
        cout << str + string((20 - str.length()) / 2, ' ');
      }
      else 
        cout << " ";

    }
    cout << "|" << endl;

    //Second
    for (int j = 0; j < 7; ++j)
    {
      cout << "|" << setw(21);
    }
    cout << "|" << endl;

    //Third
    for (int j = 0; j < 7; ++j)
    {
      cout << "|" << setw(21);
      if (this->game->getBoard()->getTile(i, j) != NULL && this->game->getBoard()->getTile(i, j)->getPlayer() != NULL)
      {
        cout << this->game->getBoard()->getTile(i, j)->getPlayer()->craft();
      }
    }
    cout << "|" << endl;

    //Fourth
    for (int j = 0; j < 7; ++j)
    {
      cout << "|" << setw(21);
    }
    cout << "|" << endl;

    //Fifth
    for (int j = 0; j < 7; ++j)
    {
      cout << "|____________________";
    }
    cout << "|" << endl;

  }
}
