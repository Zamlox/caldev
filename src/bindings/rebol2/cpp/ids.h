/**
 * Author: 		Iosif Haidu
 * Description: Id's for face fields and values 
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __BIND_REBOL2_IDS_H__
#define __BIND_REBOL2_IDS_H__

namespace Bind
{
namespace Rebol2
{

typedef enum
{
    // Face type values
    FACE_FACE           = 200,
    FACE_WINDOW         = 201,
    FACE_BUTTON         = 202,
    FACE_LABEL          = 203,
    FACE_FIELD          = 204,
    // Face fields
    FACE_TYPE           = 100,
    FACE_OFFSET         = 101,
    FACE_SIZE           = 102,
    FACE_SPAN           = 103,
    FACE_PANE           = 104,
    FACE_TEXT           = 105,
    FACE_COLOR          = 106,
    FACE_IMAGE          = 107,
    FACE_EFFECT         = 108,
    FACE_DATA           = 109,
    FACE_EDGE           = 110,
    FACE_FONT           = 111,
    FACE_PARA           = 112,
    FACE_FEEL           = 113,
    FACE_SAVED_AREA     = 114,
    FACE_RATE           = 115,
    FACE_SHOW           = 116,
    FACE_OPTIONS        = 117,
    FACE_PARENT_FACE    = 118,
    FACE_OLD_OFFSET     = 119,
    FACE_OLD_SIZE       = 120,
    FACE_LINE_LIST      = 121,
    FACE_CHANGES        = 122,
    FACE_FLAGS          = 123,
    FACE_ACTION         = 124,
    // Effect words
    EFFECT_MERGE        = 1,
    EFFECT_FIT          = 2,
    EFFECT_ASPECT       = 3,
    EFFECT_EXTEND       = 4,
    EFFECT_TILE         = 5,
    EFFECT_TILE_VIEW    = 6,
    EFFECT_CLIP         = 7,
    EFFECT_CROP         = 8,
    EFFECT_FLIP         = 9,
    EFFECT_ROTATE       = 10,
    EFFECT_REFLECT      = 11,
    EFFECT_INVERT       = 12,
    EFFECT_LUMA         = 13,
    EFFECT_CONTRAST     = 15,
    EFFECT_TINT         = 16,
    EFFECT_GRAYSCALE    = 17,
    EFFECT_COLORIZE     = 18,
    EFFECT_MULTIPLY     = 19,
    EFFECT_DIFFERENCE   = 20,
    EFFECT_BLUR         = 21,
    EFFECT_SHARPEN      = 22,
    EFFECT_EMBOSS       = 23,
    EFFECT_GRADIENT     = 24,
    EFFECT_GRADCOL      = 25,
    EFFECT_GRADMUL      = 26,
    EFFECT_KEY          = 27,
    EFFECT_SHADOW       = 28,
    EFFECT_DRAW         = 29,
    EFFECT_ARROW        = 30,
    EFFECT_CROSS        = 31,
    EFFECT_OVAL         = 32,
    EFFECT_ROUND        = 33,
    EFFECT_GRID         = 34,
    // Edge
    EDGE_COLOR          = 35,
    EDGE_SIZE           = 36,
    EDGE_EFFECT         = 37,
    EDGE_IMAGE          = 38,
    // Font
    FONT_NAME           = 39,
    FONT_SIZE           = 40,
    FONT_STYLE          = 41,
    FONT_COLOR          = 42,
    FONT_ALIGN          = 43,
    FONT_VALIGN         = 44,
    FONT_OFFSET         = 45,
    FONT_SPACE          = 46,
    FONT_SHADOW         = 47,
    // Style
    STYLE_BOLD          = 48,
    STYLE_ITALIC        = 49,
    STYLE_UNDERLINE     = 50,
    STYLE_NORMAL        = 500,
    // Align
    ALIGN_LEFT          = 51,
    ALIGN_RIGHT         = 52,
    ALIGN_CENTER        = 53,
    // VAlign
    VALIGN_TOP          = 54,
    VALIGN_BOTTOM       = 55,
    VALIGN_MIDDLE       = 56,
    // Para
    PARA_ORIGIN         = 57,
    PARA_MARGIN         = 58,
    PARA_INDENT         = 59,
    PARA_SCROLL         = 60,
    PARA_TABS           = 61,
    PARA_WRAP           = 62,
    // Options
    OPTIONS_NOTITLE     = 63,
    OPTIONS_NOBORDER    = 64,
    OPTIONS_NORESIZE    = 65,
    OPTIONS_ALLOVER     = 66,
    OPTIONS_ACTIVATE_ON_SHOW    = 67,
    OPTIONS_MIN_SIZE    = 68,
    // Changes
    CHANGES_OFFSET      = 69,
    CHANGES_TEXT        = 70,
    CHANGES_ACTIVATE    = 71,
    CHANGES_MAXIMIZE    = 72,
    CHANGES_MINIMIZE    = 73,
    CHANGES_RESTORE     = 74
} FaceId;


} // namespace Rebol2
} // namespace Bind

#endif // __BIND_REBOL2_IDS_H__