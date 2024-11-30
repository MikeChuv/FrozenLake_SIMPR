

#include "console.h"

#include <io.h>


static void ConsoleSetup(hConsole console, int alloc);


static int bAttachToConsole()
{
    if (!AttachConsole(ATTACH_PARENT_PROCESS)) {
        if (GetLastError() != ERROR_ACCESS_DENIED) {
            //already has a console
            if (!AttachConsole(GetCurrentProcessId())) {
                DWORD dwLastError = GetLastError();
                if (dwLastError != ERROR_ACCESS_DENIED) {
                    //already has a console
                    return 0;
                }
            }
        }
    }
    return 1;
}


hConsole ConsoleCreate(int alloc) {

    hConsole con = malloc(sizeof(tConsole));
    if (!con) {
        return NULL;
    }

    memset(con, 0, sizeof(tConsole));

    ConsoleSetup(con, alloc);

    return con;

}


static void ConsoleSetup(hConsole console, int alloc)
{
    if (!bAttachToConsole()) {
        if (alloc) {
            console->allocated = AllocConsole();
            if (!console->allocated)
                return; // We already have a console.
            bAttachToConsole();
        }
    }
    freopen_s(&console->fstdin, "CON", "r", stdin);
    freopen_s(&console->fstdout, "CON", "w", stdout);
    freopen_s(&console->fstderr, "CON", "w", stderr);
}


void ConsoleDestroy(hConsole console) {
    if (console == NULL) {
        return;
    }
    if (console->fstdin) {
        fclose(console->fstdin);
        console->fstdin = NULL;
    }
    if (console->fstdout) {
        fclose(console->fstdout);
        console->fstdout = NULL;
    }
    if (console->fstderr) {
        fclose(console->fstderr);
        console->fstderr = NULL;
    }
    if (console->allocated) {
        FreeConsole();
    }
}
