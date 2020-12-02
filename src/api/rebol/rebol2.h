/**
 * Author: 		Iosif Haidu
 * Description: API to interface with Rebol2
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

/**
 * Initialize GUI
 * @param  {int} guiTypeP : type of GUI
 * @return {int}          : 0 if succeeded
 */
extern "C" __attribute__ ((visibility ("default"))) 
int rebInitGUI (int guiTypeP);
