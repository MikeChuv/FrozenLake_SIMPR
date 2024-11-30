#ifndef INTERPRETER_H__
#define INTERPRETER_H__

#include "framework.h"
#include "point.h"
#include "hero.h"

/* identifier string for "Condition" message */
#define WIN_SIMPR_CONDITION_MSG_NAME L"WIN_SIMPR_CONDITION_MSG"
/* identifier string for "Action" message */
#define WIN_SIMPR_ACTION_MSG_NAME    L"WIN_SIMPR_ACTION_MSG"

/*
    Interpreter condion/action return value
*/
typedef enum tagResult {
    INTERP_NO      = 0,
    INTERP_YES     = 1,
    INTERP_UNKNOWN = 2
} tResult;


/*
    Interpreter instance struct
*/
struct tagInterpreter {
    UINT  conditionMessage; /* handle for the "Condition" massage */
    UINT  actionMessage;    /* handle for the "Action" message    */
    hHero hero;             /* handle for the Hero object         */
};
typedef struct tagInterpreter tInterpreter, *hInterpreter;

/*
    Interpreter initialisation method.
    Registers messages using defined identifiers:
         - `WIN_SIMPR_CONDITION_MSG_NAME`
         - `WIN_SIMPR_ACTION_MSG_NAME`
    Sets a reference to a hero (controllable agent)
    Params:
        - `pIpr`: interpreter handle (pointer)
        - `hero`: hero handle 
*/
int InterpreterInit(hInterpreter pIpr, hHero hero);


/*
    Processes "Condition" message
    Params:
        - `pIpr`:   interpreter handle (pointer)
        - `wParam`: condition message wParam
        - `lParam`: condition message lParam
*/
tResult InterpreterProcessConditionsMessage(hInterpreter pIpr, WPARAM wParam, LPARAM lParam);



/*
    Processes "Action" message
    Params:
        - `pIpr`:   interpreter handle (pointer)
        - `wParam`: action message wParam
        - `lParam`: action message lParam
*/
tResult InterpreterProcessActionsMessage(hInterpreter pIpr, WPARAM wParam, LPARAM lParam);



#endif // INTERPRETER_H__
