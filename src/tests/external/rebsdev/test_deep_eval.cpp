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
    result = get_block_int(pBlock, 1, &iValue);
    EXPECT_EQ(result, SUCCESS);
    EXPECT_EQ(iValue, 10);
    result = get_block_int(pBlock, 2, &iValue);
    EXPECT_EQ(result, SUCCESS);
    EXPECT_EQ(iValue, 11);
    result = get_block_subblock(pBlock, 3, &pSubBlock);
    EXPECT_EQ(result, SUCCESS);
    result = get_block_int(pSubBlock, 0, &iValue);
    EXPECT_EQ(result, SUCCESS);
    EXPECT_EQ(iValue, 12);
    result = get_block_tuple(pBlock, 4, &a, &b, &c);
    EXPECT_EQ(result, SUCCESS);
    EXPECT_EQ(a, 10);
    EXPECT_EQ(b, 20);
    EXPECT_EQ(c, 30);
}

TEST(DoDeepEvaluation, Face)
{
    void* pBlock = parse_block("make face [      \
        pane: [                                     \
            make object! [                          \
                id: 12                              \
            ]                                       \
        ]                                           \
        id: 11                                      \
        type: 'face                                 \
        offset: 2x3                                 \
        size: 12x13                                 \
        span: 1x4                                   \
        text: \"Window_1\"                          \
        color: 1.2.3                                \
        image: make image! 2x2                      \
        effect: [                                   \
            merge                                   \
            extend 2x3 4x5                          \
            draw [                                  \
                box 100x100 200x200 3               \
                circle 150x150 100 120              \
                line 10x20 30x20 5x6                \
                shape [                             \
                    arc 10x11 3 4 30 1 1            \
                    move 200x300                    \
                    line-by 10x10 25x15             \
                ]                                   \
            ]                                       \
        ]                                           \
        data: none                                  \
        edge: make face/edge [                      \
            color: 100.101.102                      \
            size: 5x6                               \
            image: none                             \
            effect: [                               \
                bevel bezel nurbs                   \
            ]                                       \
        ]                                           \
        font: make face/font [                      \
            name: \"Arial\"                         \
            style: 'bold                            \
            size: 16                                \
            color: 200.201.202                      \
            offset: 10x20                           \
            space: 0x0                              \
            align: 'left                            \
            valign: 'top                            \
            shadow: 1x1                             \
            path: \"/usr/share/font/fun.ttf\"       \
        ]                                           \
        para: make face/para [                      \
            origin: 3x4                             \
            margin: 5x6                             \
            indent: 7x8                             \
            tabs: 10                                \
            wrap?: true                             \
            scroll: 2x5                             \
        ]                                           \
    ]");
    GlueFace glueFace;
    FaceCounters faceCounters;
    int colorChannels;
    Effect *pEffect{nullptr};
    Draw *pDraw{nullptr};
    Shape *pShape{nullptr};

    COLOR_FIELDS(colorChannels);
    get_face_by_index(pBlock, &glueFace, &faceCounters);
    EXPECT_EQ(glueFace.id.none, 0);
    EXPECT_EQ(glueFace.id.value, 11);
    EXPECT_EQ(glueFace.type.none, 0);
    EXPECT_EQ(glueFace.type.value, TYPE_FACE);
    EXPECT_EQ(glueFace.offset.none, 0);
    EXPECT_EQ(glueFace.offset.value.x, 2);
    EXPECT_EQ(glueFace.offset.value.y, 3);
    EXPECT_EQ(glueFace.size.none, 0);
    EXPECT_EQ(glueFace.size.value.x, 12);
    EXPECT_EQ(glueFace.size.value.y, 13);
    EXPECT_EQ(glueFace.span.none, 0);
    EXPECT_EQ(glueFace.span.value.x, 1);
    EXPECT_EQ(glueFace.span.value.y, 4);
    EXPECT_EQ(faceCounters.paneCount, 1);
    EXPECT_EQ(glueFace.text.none, 0);
    EXPECT_STREQ(glueFace.text.value, "Window_1");
    EXPECT_EQ(glueFace.color.none, 0);
    EXPECT_EQ(glueFace.color.value.a, 1);
    EXPECT_EQ(glueFace.color.value.b, 2);
    EXPECT_EQ(glueFace.color.value.c, 3);
    EXPECT_EQ(glueFace.image.none, 0);
    EXPECT_EQ(glueFace.image.value.width, 2);
    EXPECT_EQ(glueFace.image.value.height, 2);
    EXPECT_EQ(glueFace.image.value.length, glueFace.image.value.width * glueFace.image.value.height * colorChannels);
    EXPECT_EQ(faceCounters.effectCount, 3);
    // effect
    EXPECT_EQ(get_face_effect_elem(0, &pEffect), SUCCESS);
    ASSERT_NE(pEffect, nullptr);
    EXPECT_EQ(pEffect->type, EFFECT_MERGE);
    EXPECT_EQ(get_face_effect_elem(1, &pEffect), SUCCESS);
    ASSERT_NE(pEffect, nullptr);
    EXPECT_EQ(pEffect->type, EFFECT_EXTEND);
    EXPECT_EQ(pEffect->elem.extend.horiz.x, 2);
    EXPECT_EQ(pEffect->elem.extend.horiz.y, 3);
    EXPECT_EQ(pEffect->elem.extend.vert.x, 4);
    EXPECT_EQ(pEffect->elem.extend.vert.y, 5);
    EXPECT_EQ(get_face_effect_elem(2, &pEffect), SUCCESS);
    ASSERT_NE(pEffect, nullptr);
    EXPECT_EQ(pEffect->type, EFFECT_DRAW);
    // draw
    EXPECT_EQ(get_face_effect_draw_count(pEffect->elem.draw), 4);
    get_face_effect_draw_elem(0, &pDraw);
    EXPECT_EQ(pDraw->type, DRAW_BOX);
    EXPECT_EQ(pDraw->elem.box.upper_left.x, 100);
    EXPECT_EQ(pDraw->elem.box.upper_left.y, 100);
    EXPECT_EQ(pDraw->elem.box.bottom_right.x, 200);
    EXPECT_EQ(pDraw->elem.box.bottom_right.y, 200);
    EXPECT_EQ(*pDraw->elem.box.corner_radius.p_data, 3);
    get_face_effect_draw_elem(1, &pDraw);
    EXPECT_EQ(pDraw->type, DRAW_CIRCLE);
    EXPECT_EQ(pDraw->elem.circle.center.x, 150);
    EXPECT_EQ(pDraw->elem.circle.center.y, 150);
    EXPECT_EQ(pDraw->elem.circle.radius_x, 100);
    EXPECT_EQ(*pDraw->elem.circle.radius_y.p_data, 120);
    get_face_effect_draw_elem(2, &pDraw);
    EXPECT_EQ(pDraw->type, DRAW_LINE);
    EXPECT_EQ(pDraw->elem.line.size, 3);
    EXPECT_EQ(pDraw->elem.line.elems[0].x, 10);
    EXPECT_EQ(pDraw->elem.line.elems[0].y, 20);
    EXPECT_EQ(pDraw->elem.line.elems[1].x, 30);
    EXPECT_EQ(pDraw->elem.line.elems[1].y, 20);
    EXPECT_EQ(pDraw->elem.line.elems[2].x, 5);
    EXPECT_EQ(pDraw->elem.line.elems[2].y, 6);
    // shape
    get_face_effect_draw_elem(3, &pDraw);
    EXPECT_EQ(pDraw->type, DRAW_SHAPE);
    EXPECT_EQ(get_face_effect_draw_shape_count(pDraw->elem.shape_cmd_block), 3);
    EXPECT_EQ(get_face_effect_draw_shape_elem(0, &pShape), SUCCESS);
    EXPECT_EQ(pShape->type, SHAPE_ARC);
    EXPECT_EQ(pShape->elem.arc.point1.x, 10);
    EXPECT_EQ(pShape->elem.arc.point1.y, 11);
    EXPECT_EQ(pShape->elem.arc.radius_x, 3);
    EXPECT_EQ(pShape->elem.arc.radius_y, 4);
    EXPECT_EQ(pShape->elem.arc.angle, 30);
    EXPECT_EQ(pShape->elem.arc.large, 1);
    EXPECT_EQ(pShape->elem.arc.sweep, 1);
    EXPECT_EQ(get_face_effect_draw_shape_elem(1, &pShape), SUCCESS);
    EXPECT_EQ(pShape->type, SHAPE_MOVE);
    EXPECT_EQ(pShape->elem.move.x, 200);
    EXPECT_EQ(pShape->elem.move.y, 300);
    EXPECT_EQ(get_face_effect_draw_shape_elem(2, &pShape), SUCCESS);
    EXPECT_EQ(pShape->type, SHAPE_LINE_BY);
    EXPECT_EQ(pShape->elem.line.size, 2);
    EXPECT_EQ(pShape->elem.line.elems[0].x, 10);
    EXPECT_EQ(pShape->elem.line.elems[0].y, 10);
    EXPECT_EQ(pShape->elem.line.elems[1].x, 25);
    EXPECT_EQ(pShape->elem.line.elems[1].y, 15);
    // data - ignored
    // edge
    EXPECT_EQ(glueFace.edge.none, 0);
    EXPECT_EQ(glueFace.edge.value.color.none, 0);
    EXPECT_EQ(glueFace.edge.value.color.value.a, 100);
    EXPECT_EQ(glueFace.edge.value.color.value.b, 101);
    EXPECT_EQ(glueFace.edge.value.color.value.c, 102);
    EXPECT_EQ(glueFace.edge.value.size.none, 0);
    EXPECT_EQ(glueFace.edge.value.size.value.x, 5);
    EXPECT_EQ(glueFace.edge.value.size.value.y, 6);
    EXPECT_EQ(glueFace.edge.value.image.none, 1);
    EXPECT_EQ(glueFace.edge.value.effect.none, 0);
    EXPECT_EQ(glueFace.edge.value.effect.value.words_count, 3);
    EXPECT_EQ(glueFace.edge.value.effect.value.words[0], EDGE_BEVEL);
    EXPECT_EQ(glueFace.edge.value.effect.value.words[1], EDGE_BEZEL);
    EXPECT_EQ(glueFace.edge.value.effect.value.words[2], EDGE_NURBS);
    // font
    EXPECT_EQ(glueFace.font.none, 0);
    EXPECT_EQ(glueFace.font.value.name.none, 0);
    EXPECT_STREQ(glueFace.font.value.name.value, "Arial");
    EXPECT_EQ(glueFace.font.value.style.none, 0);
    EXPECT_EQ(glueFace.font.value.style.value, FONT_BOLD);
    EXPECT_EQ(glueFace.font.value.size.none, 0);
    EXPECT_EQ(glueFace.font.value.size.value, 16);
    EXPECT_EQ(glueFace.font.value.color.none, 0);
    EXPECT_EQ(glueFace.font.value.color.value.a, 200);
    EXPECT_EQ(glueFace.font.value.color.value.b, 201);
    EXPECT_EQ(glueFace.font.value.color.value.c, 202);
    EXPECT_EQ(glueFace.font.value.offset.none, 0);
    EXPECT_EQ(glueFace.font.value.offset.value.x, 10);
    EXPECT_EQ(glueFace.font.value.offset.value.y, 20);
    EXPECT_EQ(glueFace.font.value.space.none, 0);
    EXPECT_EQ(glueFace.font.value.space.value.x, 0);
    EXPECT_EQ(glueFace.font.value.space.value.y, 0);
    EXPECT_EQ(glueFace.font.value.align.none, 0);
    EXPECT_EQ(glueFace.font.value.align.value, FONT_LEFT);
    EXPECT_EQ(glueFace.font.value.valign.none, 0);
    EXPECT_EQ(glueFace.font.value.valign.value, FONT_TOP);
    EXPECT_EQ(glueFace.font.value.shadow.none, 0);
    EXPECT_EQ(glueFace.font.value.shadow.value.x, 1);
    EXPECT_EQ(glueFace.font.value.shadow.value.y, 1);
    EXPECT_EQ(glueFace.font.value.path.none, 0);
    EXPECT_STREQ(glueFace.font.value.path.value, "/usr/share/font/fun.ttf");
    // para
    EXPECT_EQ(glueFace.para.none, 0);
    EXPECT_EQ(glueFace.para.value.origin.none, 0);
    EXPECT_EQ(glueFace.para.value.origin.value.x, 3);
    EXPECT_EQ(glueFace.para.value.origin.value.y, 4);
    EXPECT_EQ(glueFace.para.value.margin.none, 0);
    EXPECT_EQ(glueFace.para.value.margin.value.x, 5);
    EXPECT_EQ(glueFace.para.value.margin.value.y, 6);
    EXPECT_EQ(glueFace.para.value.indent.none, 0);
    EXPECT_EQ(glueFace.para.value.indent.value.x, 7);
    EXPECT_EQ(glueFace.para.value.indent.value.y, 8);
    EXPECT_EQ(glueFace.para.value.tabs.none, 0);
    EXPECT_EQ(glueFace.para.value.tabs.value, 10);
    EXPECT_EQ(glueFace.para.value.wrap.none, 0);
    EXPECT_EQ(glueFace.para.value.wrap.value, 1);
    EXPECT_EQ(glueFace.para.value.scroll.none, 0);
    EXPECT_EQ(glueFace.para.value.scroll.value.x, 2);
    EXPECT_EQ(glueFace.para.value.scroll.value.y, 5);
}

} // anonymous namespace
