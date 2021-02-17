/**
 * Author: 		Iosif Haidu
 * Description: Default instances for rebol2 objects
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __BIND_REBOL2_DEFAULTS_H__
#define __BIND_REBOL2_DEFAULTS_H__

#include "bindings/rebol2/cpp/edge.h"
#include "bindings/rebol2/cpp/effect.h"
#include "bindings/rebol2/cpp/face.h"
#include "bindings/rebol2/cpp/font.h"
#include "bindings/rebol2/cpp/para.h"


namespace Bind
{
namespace Rebol2
{

/**
 * Class used to set default values for face object
 */
class Default
{
public:
    static Default& instance();

    void setEdge(
        Color const& rColorP,
        Pair const& rSizeP,
        Effect const& rEffectP,
        Image const& rImageP
    );
    void setEffectWord(
        Word const& rWordP
    );
    void setEffectBlock(
        EffectBlock const& rBlockP
    );
    void setFaceFont(
        Text const& rNameP,
        int         sizeP,
        FontStyle const& rStyleP,
        Color const& rColorP,
        Word const& rAlignP,
        Word const& rValignP,
        Pair const& rOffsetP,
        Pair const& rSpaceP,
        Pair const& rShadowP,
        Text const& rPathP
    );
    void setPara(
        Pair const& rOriginP,
        Pair const& rMarginP,
        Pair const& rIndentP,
        Pair const& rScrollP,
        ParaTabs const& rTabsP,
        bool wrapP
    );
    void setFace(
        Word const& rTypeP,
        Pair const& rOffsetP,
        Pair const& rSizeP,
        Pair const& rSpanP,
        Panes const& rPanesP,
        Text const& rTextP,
        Color const& rColorP,
        Image const& rImageP,
        Rate const& rRateP,
        bool showP,
        Options const& rOptionsP,
        Changes const& rChangesP
    );

    Edge const& getEdge();
    Effect const& getEffect();
    FaceFont const& getFont();
    Para const& getPara();
    Face const& getFace();

private:
    Default();

    Edge        edgeM;
    Effect      effectM;
    FaceFont    faceFontM;
    Para        paraM;
    Face        faceM;

    static Default* pInstanceM;
};

/**
 * Short form of getting default font name
 * @return {Text}  : name of default font
 */
Text const& getDefaultFontName();
/**
 * Short form of getting default font size
 * @return {int}  : size of default font
 */
int         getDefaultFontSize();

} // namespace Rebol2
} // namespace Bind

#endif // __BIND_REBOL2_DEFAULTS_H__