/**
 * Author: 		Iosif Haidu
 * Description: API to interface with Rebol2
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "api/export.h"

/**
 * Initialize GUI
 * @param  {int} guiTypeP : type of GUI
 * @return {int}          : 0 if succeeded
 */
EXPORT int rebInitGUI (int guiTypeP);
