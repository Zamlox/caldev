/**
 * Author: 		Iosif Haidu
 * Description: Face data structure to interface with API 
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __API_FACEAPI_H__
#define __API_FACEAPI_H__

namespace Api
{

struct pair
{
    int x;
    int y;
};

struct tuple
{
    int a;
    int b;
    int c;
};

struct binary 
{
    char* data;
    int length;
};

struct edgeT
{
    tuple   color;
    binary  image;
    // effect
    pair    size;
};

struct fontT
{
    char*   name;
    int     style;
    int     size;
    tuple   color;
    pair    offset;
    pair    space;
    int     align;
    int     valign;
    pair    shadow;
};

struct paraT
{
    pair    origin;
    pair    margin;
    pair    indent;
    int     tabs;
    int     wrap;
    pair    scroll;
};

struct Face
{
    int     type;
    pair    offset;
    pair    size;
    // span
    // pane
    char*   text;
    tuple   color;
    binary  image;
    // effect
    // data
    edgeT   edge;
    fontT   font;
    paraT   para;
    int     rate;
    int     show;
    int     parentId;
    char*   fonrPath;
};

} // namespace Api

#endif // __API_FACEAPI_H__