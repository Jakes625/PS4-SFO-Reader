/*
	Program Written By: Jakes625
	Feel free to use this source.. just don't rip credits!

	Special Thanks to Flat_z for his file reading functions

	Version: 1.0

	Update the hash file and help fellow developers! :D
*/

#include <iostream>
#include "SFO.h"
#include <Windows.h> //needed to change the stupid header of the console window! >:(

int main(int argc, char* args[])
{
	if(!args[1])
		return -1;

	SetConsoleTitle(TEXT("PS4: System File Object Viewer"));
	printf("Written by Jakes625.\nVersion: 1.0\nEnjoy!\n\n\n");

	SystemFileObject SFO(args[1]);
	SFO.DumpData();

	getchar();

	return 0;
}
