#ifndef CONSOLE_H__
#define CONSOLE_H__

#include "framework.h"
#include <stdio.h>


/*
	Console interface and info structure
*/
struct tagConsole {
	FILE*  fstdin;
	FILE*  fstdout;
	FILE*  fstderr;
	int    allocated;
};
typedef struct tagConsole tConsole, *hConsole;



/*
	Create a console for Windows Application, which does not have a console by default
*/
hConsole ConsoleCreate(int alloc);


/*
	Close opened files (stdin, stdout, stdout).
*/
void ConsoleDestroy(hConsole console);


#endif // !CONSOLE_H__