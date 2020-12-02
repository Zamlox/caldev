/**
 * Author: 		Iosif Haidu
 * Description: Macro for exported symbols
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */


#ifdef _WIN32
#define EXPORT  __declspec( dllexport )
#else
#define EXPORT __attribute__ ((visibility ("default")))
#endif