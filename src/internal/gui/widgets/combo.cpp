/**
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/widgets/combo.h"
#include "extern/imgui/imgui.h"

namespace GUI {
namespace Widget {

Combo::Combo(const char** pItemsP, int countP, int selectedP, ImFont* pFontP)
    : Base{pFontP}
    , pItemsM{pItemsP}
    , countM{countP}
    , selectedM{selectedP}
{
}

Combo::~Combo()
{
    destroyData(&pItemsM);
}

void Combo::beginRender()
{
    ImGuiID id;
    if (visibleM)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        window->DC.CursorPos.x = window->DC.CursorStartPos.x + xM;
        window->DC.CursorPos.y = window->DC.CursorStartPos.y + yM;
        
        if (pFontM) ImGui::PushFont(pFontM);
        ImGui::SetNextItemWidth(widthM);
        ImGui::Combo("", &selectedM, pItemsM, countM);
    }
}

void Combo::endRender()
{
    if (visibleM)
    {
        if (pFontM) ImGui::PopFont();
    }
}

void Combo::update(GlueFace const& rFaceP, bool partOfCreationP)
{
    Base<IWidget>::update(rFaceP);
    if (!partOfCreationP)
    {
        destroyData(&pItemsM);
        if (!rFaceP.data.none)
        {
            pItemsM = rFaceP.data.value.value.textItems.elems;
            countM  = rFaceP.data.value.value.textItems.size;
        }
    }
}

} // namespace Widget
} // namespace Gui