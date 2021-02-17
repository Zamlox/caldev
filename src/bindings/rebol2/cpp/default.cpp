/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "bindings/rebol2/cpp/default.h"

namespace Bind
{
namespace Rebol2
{

Default* Default::pInstanceM{nullptr};

Default::Default()
{}

Default& Default::instance()
{
    if (pInstanceM == nullptr)
    {
        pInstanceM = new Default();
    }
    assert(pInstanceM);
    return *pInstanceM;
}

void Default::setEdge(
    Color const& rColorP,
    Pair const& rSizeP,
    Effect const& rEffectP,
    Image const& rImageP
)
{
    edgeM.colorM    = rColorP;
    edgeM.sizeM     = rSizeP;
    edgeM.effectM   = effectM;
    edgeM.imageM    = rImageP;
}

void Default::setEffectWord(
    Word const& rWordP
)
{
    effectM = rWordP;
}

void Default::setEffectBlock(
    EffectBlock const& rBlockP
)
{
    effectM = rBlockP;
}

void Default::setFaceFont(
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
)
{
    faceFontM.nameM     = rNameP;
    faceFontM.sizeM     = sizeP;
    faceFontM.styleM    = rStyleP;
    faceFontM.colorM    = rColorP;
    faceFontM.alignM    = rAlignP;
    faceFontM.valignM   = rValignP;
    faceFontM.offsetM   = rOffsetP;
    faceFontM.spaceM    = rSpaceP;
    faceFontM.shadowM   = rShadowP;
    faceFontM.fontPathM = rPathP;
}

void Default::setPara(
    Pair const& rOriginP,
    Pair const& rMarginP,
    Pair const& rIndentP,
    Pair const& rScrollP,
    ParaTabs const& rTabsP,
    bool wrapP
)
{
    paraM.originM   = rOriginP;
    paraM.marginM   = rMarginP;
    paraM.indentM   = rIndentP;
    paraM.scrollM   = rScrollP;
    paraM.scrollM   = rScrollP;
    paraM.tabsM     = rTabsP;
    paraM.wrapM     = wrapP;
}

void Default::setFace(
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
)
{
    faceM.typeM     = rTypeP;
    faceM.offsetM   = rOffsetP;
    faceM.sizeM     = rSizeP;
    faceM.spanM     = rSpanP;
    faceM.paneM     = rPanesP;
    faceM.textM     = rTextP;
    faceM.colorM    = rColorP;
    faceM.imageM    = rImageP;
    faceM.rateM     = rRateP;
    faceM.showM     = showP;
    faceM.optionsM  = rOptionsP;
    faceM.changesM  = rChangesP;
    faceM.edgeM     = edgeM;
    faceM.effectM   = effectM;
    faceM.fontM     = faceFontM;
    faceM.paraM     = paraM;
}

Edge const& Default::getEdge()
{
    return edgeM;
}

Effect const& Default::getEffect()
{
    return effectM;
}

FaceFont const& Default::getFont()
{
    return faceFontM;
}

Para const& Default::getPara()
{
    return paraM;
}

Face const& Default::getFace()
{
    return faceM;
}

Text const& getDefaultFontName()
{
    assert(Default::instance().getFont().nameM.getValue1());
    return *Default::instance().getFont().nameM.getValue1();
}

int getDefaultFontSize()
{
    assert(Default::instance().getFont().sizeM.getValue1());
    return *Default::instance().getFont().sizeM.getValue1();
}


} // namespace Rebol2
} // namespace Bind