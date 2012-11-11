// TalismanConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ConsoleGameUI.h"
#include "Game.h"
#include <string>
#include <iostream>

using namespace std;

void print_usage()
{
  cout << "Usage: TalismanConsole.exe -m /path/to/mapfile.txt -c /path/to/characters.txt -d /path/to/deckfile.txt\n";
}

int main(int argc, char* argv[])
{
  Game* game = NULL;
  string map_file;
  string character_file;
  string deck_file;

  // Parse command-line arguments
  for (int i = 1; i < argc-1; i += 2) {
    string arg(argv[i]);
    if (arg == "-m") {
      map_file = argv[i+1];
    }
    else if (arg == "-d") {
      deck_file = argv[i+1];
    }
    if (arg == "-c") {
      character_file = argv[i+1];
    }
  }
  if (map_file.size() <= 0) {
    print_usage();
    return 1;
  }

  if (character_file.size() <= 0) {
    print_usage();
    return 1;
  }

  if (deck_file.size() <= 0) {
    print_usage();
    return 1;
  }

  // Construct main Game object by invoking factory method with file paths
  try {
    game = Game::init(map_file, character_file, deck_file);
  }
  catch (TException* e) {
    cout << "An error occured during initialization: " << e->message() << endl;
    return 1;
  }
  catch (...) {
    cout << "An error occured during initialization!\n";
  }

  // Construct GameUI object (console) and attach it to Game object
  GameUI* ui = new ConsoleGameUI(*game);
  game->setUI(*ui);

  // Start the game
  game->start();

  // Clean up
  delete ui;
  Game::destroy(game);

	return 0;
}
