/**
 * Author: 		Iosif Haidu
 * Description: API to interface with Rebol2
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __API_H__
#define __API_H__

#include "api/export.h"

/**
 * Initialize GUI
 * @param  {int} guiTypeP : type of GUI
 * @return {int}          : 0 if succeeded
 */
EXPORT int initGUI(int guiTypeP);
/**
 * Stop GUI engine
 * @return {int}  : 0 if succeeded
 */
EXPORT int stopGUI();

#endif // __API_H__