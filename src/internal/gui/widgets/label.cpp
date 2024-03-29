/**
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/widgets/label.h"
#include "internal/gui/widgetfactory.h"
#include "extern/imgui/imgui.h"

namespace GUI {
namespace Widget {

Label::Label(const char* textP, ImFont* pFontP)
    : Base{pFontP}
    , textM{textP}
{
    // TODO: replacement must be done on rebol side
    replace(textM, "^/", "\n");
}

IWidget* Label::clone()
{
    IWidget* pWidget = WidgetFactory::instance().createLabel("", nullptr, true);
    Label* pLabel = static_cast<Label*>(pWidget);
    *pLabel = *this;
    return pLabel;
}

Label& Label::operator=(const Label& rOpP)
{
    if (&rOpP != this)
    {
        Base<IWidget>::operator=(rOpP);
        textM = rOpP.textM;
    }
    return *this;
}

void Label::beginRender()
{
    ImGuiID id;
    if (visibleM)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        window->DC.CursorPos.x = window->DC.CursorStartPos.x + xM;
        window->DC.CursorPos.y = window->DC.CursorStartPos.y + yM;
        // store extra attributes
        WidgetAttribs attrib(
            ImGui::ColorConvertFloat4ToU32(bgColorM)
            , ImGui::ColorConvertFloat4ToU32(frColorM)
            , alignM
            , ImRect(xM, yM, xM + widthM, yM + heightM)
            , (isWrapM) ? widthM : 0.0
            , ImRect{0, 0, 0, 0}
        );
        
        if (pFontM) ImGui::PushFont(pFontM);
        ImGui::TextBox(textM.c_str(), &attrib);
        //ImGui::LabelText(textM.c_str(), "");
    }
}

void Label::endRender()
{
    if (visibleM)
    {
        if (pFontM) ImGui::PopFont();
    }
}

void Label::update(GlueFace const& rFaceP, bool partOfCreationP)
{
    Base<IWidget>::update(rFaceP);
    if (!rFaceP.text.none)
    {
        textM = rFaceP.text.value;
    }
}

} // namespace Widget
} // namespace Gui