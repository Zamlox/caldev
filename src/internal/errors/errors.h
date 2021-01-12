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
MAKE_ERR(ERR_GUI_INVALID_THREAD_TYPE,       -1, "ERR ! Invalid thread type !\n")
MAKE_ERR(ERR_GUI_CANNOT_INITIALIZE,         -2, "ERR ! Cannot initialize GUI engine !\n")
MAKE_ERR(ERR_GUI_INVALID_GUI_ENGINE_TYPE,   -3, "ERR ! Invalid GUI engine type !\n")
MAKE_ERR(ERR_GUI_EXEC_ENGINE,               -4, "ERR ! Error executing GUI engine thread !\n")
MAKE_ERR(ERR_GUI_ENGINE_NOT_INIT,           -5, "ERR ! GUI engine instance not inititalized. Call guiEngineInit() before calling guiEngineStart() !\n")
MAKE_ERR(ERR_GUI_INVALID_WIDGET,            -6, "ERR ! Invalid widget !\n")
MAKE_ERR(ERR_GUI_MAIN_WINDOW_FAILED,        -7, "ERR ! Main window not creatd !\n")

#endif // __ERRORS_ERRORS_H__