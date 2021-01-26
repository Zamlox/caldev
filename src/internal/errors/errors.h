/**
 * Author: 		Iosif Haidu
 * Description: Error codes and messages
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __ERRORS_ERRORS_H__
#define __ERRORS_ERRORS_H__

#define MAKE_ERR(ERR_CODE_NAME, CODE, MESSAGE)                  \
    constexpr int ERR_CODE_NAME = CODE;                         \
    constexpr const char* MSG_##ERR_CODE_NAME = MESSAGE;

MAKE_ERR(SUCCESS, 0, "Success !")
/** GUI */
MAKE_ERR(ERR_GUI_INVALID_THREAD_TYPE,       -1, "ERR ! Invalid thread type !")
MAKE_ERR(ERR_GUI_CANNOT_INITIALIZE,         -2, "ERR ! Cannot initialize GUI engine !")
MAKE_ERR(ERR_GUI_INVALID_GUI_ENGINE_TYPE,   -3, "ERR ! Invalid GUI engine type !")
MAKE_ERR(ERR_GUI_EXEC_ENGINE_BKG_THREAD,    -4, "ERR ! Error executing GUI engine in background thread !")
MAKE_ERR(ERR_GUI_EXEC_ENGINE_MAIN_THREAD,   -5, "ERR ! Error executing GUI engine in main thread !")
MAKE_ERR(ERR_GUI_ENGINE_NOT_INIT,           -6, "ERR ! GUI engine instance not inititalized. Call guiEngineInit() before calling guiEngineStart() !")
MAKE_ERR(ERR_GUI_INVALID_WIDGET,            -7, "ERR ! Invalid widget !\n")
MAKE_ERR(ERR_GUI_MAIN_WINDOW_FAILED,        -8, "ERR ! Main window not creatd !\n")

#endif // __ERRORS_ERRORS_H__