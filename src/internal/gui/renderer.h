/**
 * Author: 		Iosif Haidu
 * Description: Renders widgets
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "bindings/rebol2/cpp/font.h"
#include "internal/gui/widgets/queue/storage.h"
#include "internal/gui/widgets/queue/command.h"
#include "internal/gui/imgui/common.h"
#include "internal/os/mutex.h"

namespace GUI {

/**
 * Handles collection of widgets.
 */
class Renderer
{
public:
    Renderer(Os::Mutex& rFrameSynchronizerP);

    /** Command related */
    /**
     * Create widget.
     * 
     * @param  {char*} pFaceDescriptionP : text description of widget
     * @return {Id}                      : widget id
     */
    Id createWidget(const char* pFaceDescriptionP);
    /**
     * Update widget.
     * 
     * @param  {char*} pFaceDescriptionP : text description of widget
     */
    void updateWidget(const char* pFaceDescriptionP);
    /**
     * Remove wiwdget.
     * 
     * @param  {char*} pFaceDescriptionP : text description of widget
     */
    void removeWidget(const char* pFaceDescriptionP);

    /** Storage related */
    /**
     * Renders widgets from storage.
     */
    void render();

    /**
     * Set flag when new font is added.
     * 
     * @param  {bool} valueP : value for flag to be set
     */
    void setNewFontAdded(bool valueP);
    
    /**
     * Get flag of new font added.
     * 
     * @return {bool}  : value of flag
     */
    bool getNewFontAdded() const;

private:
    /**
     * Parse face description and generates face object
     * 
     * @param  {char*} faceDescriptionP : description of face
     * @param  {GlueFace} rFaceP        : face object
     * @return {bool}                   : true if succedd, false otherwise
     */
    bool parseFaceDescription(const char* faceDescriptionP, GlueFace& rFaceP, FaceCounters& rCountersP);
    /**
     * Create widget
     * @param  {GlueFace} const : face object
     * @return {Id}             : id of widget
     */
    Id createWidget(GlueFace const& rFaceP, FaceCounters const& rCountersP);
    /**
     * Parse face description and calls widget creation function.
     * 
     * @param  {const char*}                                 : face description
     * @param  {std::function<Id(GlueFace)>} widgetCreatorP  : widget creation function
     * @return {Id}                                          : widget id
     */
    Id widgetStub(char const* pFaceDescriptionP, std::function<Id(GlueFace const&, FaceCounters const&)> widgetCreatorP);
    /**
     * Calls widget creation function. 
     * 
     * @param  {GlueFace} const                             : face object
     * @param  {std::function<Id(GlueFace)>} widgetCreatorP : widget creation function
     * @return {Id}                                         : widget id
     */
    Id widgetStub(GlueFace const& rFaceP, std::function<Id(GlueFace const&, FaceCounters const&)> widgetCreatorP, FaceCounters& rCountersP);
    /**
     * Create different widgets based on T.
     * 
     * @param  {GlueFace} const                          : face object
     * @param  {std::function<T*} (GlueFace const&)      : creation sfunction
     * @param  {std::function<void(void)>} beforeUpdateP : function to execute before creation
     * @return {Id}                                      : id of widget
     */
    template <typename T>
    Id createStub(
        GlueFace const& rFaceP, 
        std::function<T*(GlueFace const&)> createP, 
        std::function<void(void)> beforeUpdateP = nullptr);

    /**
     * Create font based on a rebol font object
     * @param  {Bind::Rebol2::Font} const : rebol2 font object
     * @return {Font*}                    : font created if successful or nullptr otherwise
     */
    Font* createFont(FaceFont const& rFontP);

    /**
     * Create label.
     * 
     * @param  {GlueFace} const : label face
     */
    Id  createLabel(GlueFace const& rFaceP);


    /** Storage for widgets */
    Widget::Storage widgetsM;
    /** Commands queue */
    Widget::Command commandsM;
    /** Mutex used to synchrnize operations with frames */
    Os::Mutex& rFrameSynchronizerM;
    /** Collection of created fonts */
    Bind::Rebol2::FontsMap fontsM;
    /** Flag indicating new font has been added */
    bool newFontAddedM;
};

} // namespace GUI