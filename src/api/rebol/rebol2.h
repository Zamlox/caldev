/**
 * Author: 		Iosif Haidu
 * Description: API to interface with Rebol2
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "export.h"

/**
 * Initialize GUI
 * @param  {int} guiTypeP : type of GUI
 * @return {int}          : 0 if succeeded
 */
extern "C" EXPORT 
int rebInitGUI (int guiTypeP);