/**
 * Author: 		Iosif Haidu
 * Description: Macro for exported symbols
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */


#ifdef _WIN32
#define EXPORT extern "C" __declspec( dllexport )
#else
#define EXPORT extern "C" __attribute__ ((visibility ("default")))
#endif