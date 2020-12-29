/**
 * Author: 		Iosif Haidu
 * Description: API to interface with Rebol2
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __API_REBOL2_H__
#define __API_REBOL2_H__

#include "api/export.h"

/**
 * Initialize GUI
 * @param  {int} guiTypeP : type of GUI
 * @return {int}          : 0 if succeeded
 */
EXPORT int rebInitGUI(int guiTypeP);
/**
 * Stop GUI engine
 * @return {int}  : 0 if succeeded
 */
EXPORT int rebStopGUI();

#endif // __API_REBOL2_H__