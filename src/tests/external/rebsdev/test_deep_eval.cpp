/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "gtest/gtest.h"

extern "C" {
#include "extern/rebsdev/src/glue/glue.h"
#include "extern/rebsdev/src/glue/macros.h"
}

namespace 
{

TEST(DoDeepEvaluation, SubBlocks)
{
    int result;
    int iValue, a, b, c;
    void* pSubBlock;

    init_rebsdev();

    //void* pBlock = parse_block("make image! [1x1 #{000000}]");
    void* pBlock = parse_block("['z] a: 10 b: a + 1 [c: b + 1] d: 10.20.30");
    result = get_block_int(pBlock, 0, &iValue);
    EXPECT_EQ(result, SUCCESS);
    EXPECT_EQ(iValue, 10);
    result = get_block_int(pBlock, 1, &iValue);
    EXPECT_EQ(result, SUCCESS);
    EXPECT_EQ(iValue, 11);
    result = get_block_subblock(pBlock, 2, &pSubBlock);
    EXPECT_EQ(result, SUCCESS);
    result = get_block_int(pSubBlock, 0, &iValue);
    EXPECT_EQ(result, SUCCESS);
    EXPECT_EQ(iValue, 12);
    result = get_block_tuple(pBlock, 3, &a, &b, &c);
    EXPECT_EQ(result, SUCCESS);
    EXPECT_EQ(a, 10);
    EXPECT_EQ(b, 20);
    EXPECT_EQ(c, 30);
}

TEST(DoDeepEvaluation, Face)
{
    void* pBlock = parse_block("make object! [      \
        id: 11                                      \
        type: 'face                                 \
        offset: 2x3                                 \
        size: 12x13                                 \
        span: 1x4                                   \
        pane: [                                     \
            make object! [                          \
                id: 12                              \
            ]                                       \
        ]                                           \
        text: \"Window_1\"                          \
        color: 1.2.3                                \
        image: make image! 2x2                      \
        effect: [merge extend 2x3 4x5 ]             \
    ]");

    void* pFace = get_face(pBlock);
    int result;
    int iValue, x, y, len;
    int red, green, blue;
    const char* szValue;
    void* pElem;
    unsigned char* pImage;
    Effect effect;
    result = get_face_id(pFace, &iValue);
    EXPECT_EQ(result, SUCCESS);
    EXPECT_EQ(iValue, 11);
    result = get_face_type(pFace, &szValue);
    EXPECT_EQ(result, SUCCESS);
    EXPECT_STREQ(szValue, "face");
    result = get_face_offset(pFace, &x, &y);
    EXPECT_EQ(result, SUCCESS);
    EXPECT_EQ(x, 2);
    EXPECT_EQ(y, 3);
    result = get_face_size(pFace, &x, &y);
    EXPECT_EQ(result, SUCCESS);
    EXPECT_EQ(x, 12);
    EXPECT_EQ(y, 13);
    result = get_face_span(pFace, &x, &y);
    EXPECT_EQ(result, SUCCESS);
    EXPECT_EQ(x, 1);
    EXPECT_EQ(y, 4);
    result = get_face_pane_count(pFace);
    EXPECT_EQ(result, 1);
    result = get_face_pane_elem(pFace, 0, &pElem);
    EXPECT_EQ(result, SUCCESS);
    result = get_face_id(pElem, &iValue);
    EXPECT_EQ(result, SUCCESS);
    EXPECT_EQ(iValue, 12);
    result = get_face_text(pFace, &szValue);
    EXPECT_EQ(result, SUCCESS);
    EXPECT_STREQ(szValue, "Window_1");
    result = get_face_color(pFace, &red, &green, &blue);
    EXPECT_EQ(red, 1);
    EXPECT_EQ(green, 2);
    EXPECT_EQ(blue, 3);
    result = get_face_image(pFace, &pImage, &len);
    EXPECT_EQ(result, SUCCESS);
    EXPECT_EQ(len, 12);
    result = get_face_effect_count(pFace);
    EXPECT_EQ(result, 2);
    result = get_face_effect_elem(pFace, 0, &effect);
    EXPECT_EQ(result, SUCCESS);
    EXPECT_EQ(effect.type, EFFECT_MERGE);
    result = get_face_effect_elem(pFace, 1, &effect);
    EXPECT_EQ(result, SUCCESS);
    EXPECT_EQ(effect.type, EFFECT_EXTEND);
}

} // anonymous namespace
