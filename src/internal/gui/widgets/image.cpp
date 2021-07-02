/**
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/widgets/image.h"
#include "internal/gui/widgetfactory.h"
#include "extern/imgui/imgui.h"
#include "extern/stb/stb_image.h"

namespace GUI {
namespace Widget {

Image::Image(Api::GuiType guiTypeP, const char* pFileNameP, int desiredChannelsP)
    : guiTypeM{guiTypeP}
    , desiredChannelsM{desiredChannelsP}
    , textureIdM{0}
    , canBeDeletedM{true}
{
    pDataM = stbi_load(pFileNameP, &imgWidthM, &imgHeightM, &nChannelsM, desiredChannelsM);
}

Image::Image(Api::GuiType guiTypeP, unsigned char* pDataP, int widthP, int heightP, int nChannelsP)
    : guiTypeM{guiTypeP}
    , pDataM{pDataP}
    , nChannelsM{nChannelsP}
    , desiredChannelsM{nChannelsP}
    , textureIdM{0}
    , imgWidthM{widthP}
    , imgHeightM{heightP}
    , canBeDeletedM{true}
{
}

Image::~Image()
{
    if (canBeDeletedM)
        stbi_image_free(pDataM);
    pDataM = nullptr;
    if (textureIdM)
        glDeleteTextures(1, &textureIdM);
}

IWidget* Image::clone()
{
    IWidget* pWidget = WidgetFactory::instance().createImage(Api::GuiType::INVALID_TYPE, nullptr, 0, 0, 0, true);
    Image* pImage = static_cast<Image*>(pWidget);
    *pImage = *this;
    return pImage;
}

Image& Image::operator=(const Image& rOpP)
{
    if (&rOpP != this)
    {
        int length = rOpP.imgWidthM * rOpP.imgHeightM * rOpP.nChannelsM;
        Base<IWidget>::operator=(rOpP);
        guiTypeM    = rOpP.guiTypeM;
        desiredChannelsM = rOpP.desiredChannelsM;
        nChannelsM  = rOpP.nChannelsM;
        textureIdM  = rOpP.textureIdM;
        imgWidthM   = rOpP.imgWidthM;
        imgHeightM  = rOpP.imgHeightM;
        if (rOpP.pDataM)
        {
            pDataM      = (unsigned char*)malloc(length);
            memcpy(pDataM, rOpP.pDataM, length);
        }
    }
    return *this;
}

void Image::beginRender()
{
    if (visibleM)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        window->DC.CursorPos.x = window->DC.CursorStartPos.x + xM;
        window->DC.CursorPos.y = window->DC.CursorStartPos.y + yM;
        // store extra attributes
        WidgetAttribs attrib;
        attrib.clipRect = ImRect{window->DC.CursorPos, ImVec2{window->DC.CursorPos.x + widthM, window->DC.CursorPos.y + heightM}};

        //int renderWidth = (widthM < imgWidthM) ? widthM : imgWidthM;
        //int renderHeight = (heightM < imgHeightM) ? heightM : imgHeightM;
        if (guiTypeM == Api::GuiType::GUI_OPENGL2)
        {
            renderForOpenGl2();
        }
        ImGui::Face(ImVec2(widthM, heightM), bgColorM);
        ImGui::Image((ImTextureID)textureIdM, ImVec2(imgWidthM, imgHeightM), &attrib);
    }
}

void Image::endRender()
{
}

void Image::update(GlueFace const& rFaceP, bool partOfCreationP)
{
    Base<IWidget>::update(rFaceP);
    if (!rFaceP.image.none)
    {
        if (pDataM != rFaceP.image.value.data)
        {
            canBeDeletedM = rFaceP.image.value.canBeDeleted;
            if (rFaceP.image.value.canBeDeleted)
                stbi_image_free(pDataM);
            pDataM = rFaceP.image.value.data;
            glDeleteTextures(1, &textureIdM);
        }

        imgWidthM = rFaceP.image.value.width;
        imgHeightM = rFaceP.image.value.height;
        if (rFaceP.size.none)
        {
            widthM = imgWidthM;
            heightM = imgHeightM;
        }
        nChannelsM = rFaceP.image.value.channels;

        renderForOpenGl2(true);
    }
}

void Image::renderForOpenGl2(bool forceP)
{
    int rgbType = (nChannelsM == 4) ? GL_RGBA : GL_RGB;
    if (textureIdM == 0 || forceP)
    {
        glGenTextures(1, &textureIdM);
        glBindTexture(GL_TEXTURE_2D, textureIdM);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load and generate the texture
        if (pDataM)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, rgbType, imgWidthM, imgHeightM, 0, rgbType, GL_UNSIGNED_BYTE, pDataM);
        }
    }
}

} // namespace Widget
} // namespace Gui