/**
 * Author: 		Iosif Haidu
 * Description: Face data structure 
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __BIND_REBOL2_FACE_H__
#define __BIND_REBOL2_FACE_H__

#include "api/imp/apiface.h"
#include "bindings/common.h"
#include "bindings/rebol2/cpp/base.h"
#include "bindings/rebol2/cpp/effect.h"
#include "bindings/rebol2/cpp/edge.h"
#include "bindings/rebol2/cpp/font.h"
#include "bindings/rebol2/cpp/para.h"
#include "bindings/rebol2/cpp/none.h"

namespace Bind
{
namespace Rebol2
{

struct Face;

using Panes     = std::vector<Face>;
using Rate      = std::variant<int, Time>;
using Options   = std::variant<
    Word,
    std::vector<Word>
>;
using Changes   = std::variant<
    Word,
    std::vector<Word>
>;

/**
 * Data structure for corresponding face object in Rebol2
 */
struct Face
{
    Face() = default;
    Face(Api::Face const& rApiFaceP)
        : idM{0}
    {
        typeM.setValue1(rApiFaceP.type);
        offsetM.setValue1(Pair(rApiFaceP.offset.x, rApiFaceP.offset.y));
        sizeM.setValue1(Pair(rApiFaceP.size.x, rApiFaceP.size.y));
        //spanM.setValue1(Pair(rApiFaceP.spanM.x, rApiFaceP.spanM.y));
        // paneM.setValue1(...)
        textM.setValue1(rApiFaceP.text);
        colorM.setValue1(Color(rApiFaceP.color.a, rApiFaceP.color.b, rApiFaceP.color.c));
        // image.setValue1(...)
        // effectM.setValue1(...)
        // edgeM.setValue1(...)
        //fontM.setValue1
    }

    int                 idM;
    CanBeNone<Word>     typeM;
    CanBeNone<Pair>     offsetM;
    CanBeNone<Pair>     sizeM;
    CanBeNone<Pair>     spanM;
    CanBeNone<Panes>    paneM;
    CanBeNone<Text>     textM;
    CanBeNone<Color>    colorM;
    CanBeNone<Image>    imageM;
    CanBeNone<Effect>   effectM;
    CanBeNone<Edge>     edgeM;
    CanBeNone<FaceFont> fontM;
    CanBeNone<Para>     paraM;
    CanBeNone<Rate>     rateM;
    CanBeNone<bool>     showM;
    CanBeNone<Options>  optionsM;
    CanBeNone<Changes>  changesM;
};

} // namespace Rebol2
} // namespace Bind

#endif // __BIND_REBOL2_FACE_H__