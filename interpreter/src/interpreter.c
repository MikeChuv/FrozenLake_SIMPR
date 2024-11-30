

#include "interpreter.h"
#include "hero.h"

typedef enum tagInterpTblNumber {
    TBL_MAIN = 1,
    TBL_RU   = 2,
    TBL_DU   = 3,
    TBL_DR   = 4,
    TBL_DRU  = 5,
    TBL_LU   = 6,
    TBL_LR   = 7,
    TBL_LRU  = 8,
    TBL_LD   = 9,
    TBL_LDU  = 10,
    TBL_LDR  = 11,
    TBL_LDRU = 12,
    TBL_STOP = 13,
}tInterpTblNumber;


typedef enum tagTableMainCondition {
    TBL_MAIN_ICE_LEFT = 1,
    TBL_MAIN_ICE_DOWN,
    TBL_MAIN_ICE_RIGHT,
    TBL_MAIN_ICE_UP,
} tTableMainCondition;

typedef enum tagTableStopCondition {
    TBL_STOP_HOLE_REACHED = 1,
    TBL_STOP_GOAL_REACHED,
} tTableStopCondition;



typedef enum tagTableMainAction {
    ACTION_L = 1,
    ACTION_D,
    ACTION_R,
    ACTION_U,
} tTableMainAction;



static int     _RegisterMessages(hInterpreter pIpr);
static tResult _ProcessConditionsTable(hInterpreter pIpr, tInterpTblNumber tableNumber, LPARAM lParam);
static tResult _ProcessActionsTable   (hInterpreter pIpr, tInterpTblNumber tableNumber, LPARAM lParam);

static inline int _GetRandomAction(int range);

int InterpreterInit(hInterpreter pIpr, hHero hero) {
    assert(pIpr != NULL && hero != NULL);
    if (!_RegisterMessages(pIpr)) {
        return 0;
    }
    pIpr->hero = hero;
    return 1;
}


static int _RegisterMessages(hInterpreter pIpr) {
    assert(pIpr != NULL);
    pIpr->conditionMessage = RegisterWindowMessage(WIN_SIMPR_CONDITION_MSG_NAME);
    pIpr->actionMessage    = RegisterWindowMessage(WIN_SIMPR_ACTION_MSG_NAME   );
    if (!(pIpr->conditionMessage && pIpr->actionMessage)) {
        return 0;
    }
    return 1;
}

static inline int _GetRandomAction(int range) {
    return (rand() % range) + 1;
}

static inline tResult _GetRandomResult() {
    return (tResult)(rand() % 2);
}


// =========================================================================================
//  
//                                   CONDITIONS
//  
// =========================================================================================

static tResult _ProcessConditionsMainTable(hInterpreter pIpr, tTableMainCondition condition) { 
    assert(pIpr != NULL);
    switch (condition)
    {
    case TBL_MAIN_ICE_LEFT:  { return (tResult)(TileTypeIsSteppable(HeroLook(pIpr->hero, DIRECTION_L))); }
    case TBL_MAIN_ICE_DOWN:  { return (tResult)(TileTypeIsSteppable(HeroLook(pIpr->hero, DIRECTION_D))); }
    case TBL_MAIN_ICE_RIGHT: { return (tResult)(TileTypeIsSteppable(HeroLook(pIpr->hero, DIRECTION_R))); }
    case TBL_MAIN_ICE_UP:    { return (tResult)(TileTypeIsSteppable(HeroLook(pIpr->hero, DIRECTION_U))); }
    default:
        return INTERP_UNKNOWN;
    }
}


static tResult _ProcessConditionsStopTable(hInterpreter pIpr, tTableStopCondition condition) { 
    assert(pIpr != NULL);
    switch (condition)
    {
    case TBL_STOP_HOLE_REACHED: { return (tResult)(HeroHoleReached(pIpr->hero)); }
    case TBL_STOP_GOAL_REACHED: { return (tResult)(HeroGoalReached(pIpr->hero)); }
    default:
        return INTERP_UNKNOWN;
    }
}


static tResult _ProcessConditionsTable(hInterpreter pIpr, tInterpTblNumber tableNumber, LPARAM condno) {
    assert(pIpr != NULL);

    switch (tableNumber)
    {
    case TBL_MAIN: { return _ProcessConditionsMainTable(pIpr, (tTableMainCondition)condno); }
    case TBL_RU:
    case TBL_DU:
    case TBL_DR:
    case TBL_DRU:
    case TBL_LU:
    case TBL_LR:
    case TBL_LRU:
    case TBL_LD:
    case TBL_LDU:
    case TBL_LDR:
    case TBL_LDRU: { return _GetRandomResult(); }
    case TBL_STOP: { return _ProcessConditionsStopTable(pIpr, (tTableStopCondition)condno); }
    default:
        return INTERP_UNKNOWN;
    }
}

// =========================================================================================
//  
//                                     ACTIONS
//  
// =========================================================================================


static tResult _ProcessActionsTable_Main(hInterpreter pIpr, tTableMainAction action) {
    assert(pIpr != NULL);
    switch (action)
    {
    case ACTION_L: { HeroMove(pIpr->hero, DIRECTION_L); break; }
    case ACTION_D: { HeroMove(pIpr->hero, DIRECTION_D); break; }
    case ACTION_R: { HeroMove(pIpr->hero, DIRECTION_R); break; }
    case ACTION_U: { HeroMove(pIpr->hero, DIRECTION_U); break; }
    default:
        break;
    }
    return INTERP_YES;
}

static tResult _ProcessActionsTable_RU(hInterpreter pIpr, LPARAM action) {
    assert(pIpr != NULL);
    //int raction = _GetRandomAction(2);
    switch (action) {
    case 1: { HeroMove(pIpr->hero, DIRECTION_R); break; }
    case 2: { HeroMove(pIpr->hero, DIRECTION_U); break; }
    default: break;
    }
    return INTERP_YES;
}
static tResult _ProcessActionsTable_DU(hInterpreter pIpr, LPARAM action) {
    assert(pIpr != NULL);
    //int raction = _GetRandomAction(2);
    switch (action) {
    case 1: { HeroMove(pIpr->hero, DIRECTION_D); break; }
    case 2: { HeroMove(pIpr->hero, DIRECTION_U); break; }
    default: break;
    }
    return INTERP_YES;
}
static tResult _ProcessActionsTable_DR(hInterpreter pIpr, LPARAM action) {
    assert(pIpr != NULL);
    //int raction = _GetRandomAction(2);
    switch (action) {
    case 1: { HeroMove(pIpr->hero, DIRECTION_D); break; }
    case 2: { HeroMove(pIpr->hero, DIRECTION_R); break; }
    default: break;
    }
    return INTERP_YES;
}
static tResult _ProcessActionsTable_DRU(hInterpreter pIpr, LPARAM action) {
    assert(pIpr != NULL);
    //int raction = _GetRandomAction(2);
    switch (action) {
    case 1: { HeroMove(pIpr->hero, DIRECTION_D); break; }
    case 2: { HeroMove(pIpr->hero, DIRECTION_R); break; }
    default: break;
    }
    return INTERP_YES;
}
static tResult _ProcessActionsTable_LU(hInterpreter pIpr, LPARAM action) {
    assert(pIpr != NULL);
    //int raction = _GetRandomAction(2);
    switch (action) {
    case 1: { HeroMove(pIpr->hero, DIRECTION_L); break; }
    case 2: { HeroMove(pIpr->hero, DIRECTION_U); break; }
    default: break;
    }
    return INTERP_YES;
}
static tResult _ProcessActionsTable_LR(hInterpreter pIpr, LPARAM action) {
    assert(pIpr != NULL);
    //int raction = _GetRandomAction(2);
    switch (action) {
    case 1: { HeroMove(pIpr->hero, DIRECTION_L); break; }
    case 2: { HeroMove(pIpr->hero, DIRECTION_R); break; }
    default: break;
    }
    return INTERP_YES;
}
static tResult _ProcessActionsTable_LRU(hInterpreter pIpr, LPARAM action) {
    assert(pIpr != NULL);
    //int raction = _GetRandomAction(3);
    switch (action) {
    case 1: { HeroMove(pIpr->hero, DIRECTION_L); break; }
    case 2: { HeroMove(pIpr->hero, DIRECTION_R); break; }
    case 3: { HeroMove(pIpr->hero, DIRECTION_U); break; }
    default: break;
    }
    return INTERP_YES;
}
static tResult _ProcessActionsTable_LD(hInterpreter pIpr, LPARAM action) {
    assert(pIpr != NULL);
    //int raction = _GetRandomAction(2);
    switch (action) {
    case 1: { HeroMove(pIpr->hero, DIRECTION_L); break; }
    case 2: { HeroMove(pIpr->hero, DIRECTION_D); break; }
    default: break;
    }
    return INTERP_YES;
}
static tResult _ProcessActionsTable_LDU(hInterpreter pIpr, LPARAM action) {
    assert(pIpr != NULL);
    //int raction = _GetRandomAction(3);
    switch (action) {
    case 1: { HeroMove(pIpr->hero, DIRECTION_L); break; }
    case 2: { HeroMove(pIpr->hero, DIRECTION_D); break; }
    case 3: { HeroMove(pIpr->hero, DIRECTION_U); break; }
    default: break;
    }
    return INTERP_YES;
}
static tResult _ProcessActionsTable_LDR(hInterpreter pIpr, LPARAM action) {
    assert(pIpr != NULL);
    //int raction = _GetRandomAction(3);
    switch (action) {
    case 1: { HeroMove(pIpr->hero, DIRECTION_L); break; }
    case 2: { HeroMove(pIpr->hero, DIRECTION_D); break; }
    case 3: { HeroMove(pIpr->hero, DIRECTION_R); break; }
    default: break;
    }
    return INTERP_YES;
}
static tResult _ProcessActionsTable_LDRU(hInterpreter pIpr, LPARAM action) {
    assert(pIpr != NULL);
    //int raction = _GetRandomAction(4);
    switch (action) {
    case 1: { HeroMove(pIpr->hero, DIRECTION_L); break; }
    case 2: { HeroMove(pIpr->hero, DIRECTION_D); break; }
    case 3: { HeroMove(pIpr->hero, DIRECTION_R); break; }
    case 4: { HeroMove(pIpr->hero, DIRECTION_U); break; }
    default: break;
    }
    return INTERP_YES;
}



static tResult _ProcessActionsTable_Stop(hInterpreter pIpr, LPARAM action) {
    return INTERP_YES;
}


static tResult _ProcessActionsTable(hInterpreter pIpr, tInterpTblNumber tableNumber, LPARAM action) {
    assert(pIpr != NULL);

    switch (tableNumber)
    {
    case TBL_MAIN: { _ProcessActionsTable_Main(pIpr, (tTableMainAction)action); break; }
    case TBL_RU:   { _ProcessActionsTable_RU(  pIpr,                   action); break; }
    case TBL_DU:   { _ProcessActionsTable_DU(  pIpr,                   action); break; }
    case TBL_DR:   { _ProcessActionsTable_DR(  pIpr,                   action); break; }
    case TBL_DRU:  { _ProcessActionsTable_DRU( pIpr,                   action); break; }
    case TBL_LU:   { _ProcessActionsTable_LU(  pIpr,                   action); break; }
    case TBL_LR:   { _ProcessActionsTable_LR(  pIpr,                   action); break; }
    case TBL_LRU:  { _ProcessActionsTable_LRU( pIpr,                   action); break; }
    case TBL_LD:   { _ProcessActionsTable_LD(  pIpr,                   action); break; }
    case TBL_LDU:  { _ProcessActionsTable_LDU( pIpr,                   action); break; }
    case TBL_LDR:  { _ProcessActionsTable_LDR( pIpr,                   action); break; }
    case TBL_LDRU: { _ProcessActionsTable_LDRU(pIpr,                   action); break; }
    case TBL_STOP: { _ProcessActionsTable_Stop(pIpr,                   action); break; }
    default:
        break;
    }
    return INTERP_YES; // actions processor always returns YES (3)
}



// =========================================================================================
//  
//                                   Messages Processors
//  
// =========================================================================================

const char* tResultStr[] = {"NO", "YES", "UNKNOWN"};

tResult InterpreterProcessConditionsMessage(hInterpreter pIpr, WPARAM wParam, LPARAM lParam) {
    assert(pIpr != NULL);
    tInterpTblNumber tableNumber = (tInterpTblNumber)LOWORD(wParam);
    tResult res = _ProcessConditionsTable(pIpr, tableNumber, lParam);
    printf("CONDITION: Table=%d, No=%llu, res=%s\n", tableNumber, lParam, tResultStr[res]);
    return res;
}

tResult InterpreterProcessActionsMessage(hInterpreter pIpr, WPARAM wParam, LPARAM lParam) {
    assert(pIpr != NULL);
    tInterpTblNumber tableNumber = (tInterpTblNumber)LOWORD(wParam);
    printf("ACTION: Table=%d, No=%llu\n", tableNumber, lParam);
    return _ProcessActionsTable(pIpr, tableNumber, lParam);
}
