/*
 * main.cpp
 *
 *  Created on: 05.08.2013
 *      Author: Drag-On
 */

#include <Main/Log.h>
#include <Window/BaseGameWindow.h>
#include "GameHandler.h"

using namespace DBGL;

/**
 * Main application entry point
 * @param argc Amount of arguments passed to the application
 * @param argv Array of argument values
 * @return 0 in case everything went right, otherwise 1
 */
int main(int argc, char* argv[])
{
	// Show all log entries
	LOG->setLogLevel(DBG);

	// Create game handler object
	GameHandler* pGame = new GameHandler(argc, argv);

	// Run main loop
	pGame->run();

	delete(pGame);
	pGame = NULL;

	// Clean log
	LOG->del();

	return 0;
}
