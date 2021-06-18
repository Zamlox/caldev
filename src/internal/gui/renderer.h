/**
 * Author: 		Iosif Haidu
 * Description: Renders widgets
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "api/imp/apiconst.h"
#include "bindings/rebol2/cpp/font.h"
#include "internal/gui/widgets/queue/storage.h"
#include "internal/gui/widgets/queue/command.h"
#include "internal/gui/imgui/common.h"
#include "internal/os/mutex.h"
#include "modules/gui/igui.h"
#include <functional>

namespace GUI {

/**
 * Handles collection of widgets.
 */
class Renderer
{
public:
    Renderer(Os::Mutex& rFrameSynchronizerP);
    /**
     * Add main window to stirage.
     * 
     * @param  {IWindow*} pMainWindowP : instance of main window
     */
    void addMainWindow(IWindow* pMainWindowP);
    /** Command related */
    /**
     * Create widget.
     * 
     * @param  {char*} pFaceDescriptionP : text description of widget
     * @return {Id}                      : widget id
     */
    Id createWidget(const char* pFaceDescriptionP, Api::GuiType guiTypeP);
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
    /**
     * Start stashing rendering. 
     */
    void stash();
    /**
     * Stop stashing and render stashed content.
     */
    void unstash();
    /**
     * Check if initial unstash was called.
     * 
     * @return {bool}  : true if initial unstash was called, false otherwise
     */
    bool isInitialUnstash() const;

    Os::Mutex& getWidgetsSync();
    IWidget* getWidget(Id idP);
    IWindow* getWindow(Id idP);

private:
    /**
     * Renders recursively children of a widget.
     * 
     * @param  {StorageElem} const : storage element for a widget
     */
    void renderino(Widget::StorageElem const& rElemP);
    /**
     * Parse face description and generates face object
     * 
     * @param  {char*} faceDescriptionP : description of face
     * @param  {GlueFace} rFaceP        : face object
     * @return {bool}                   : true if succedd, false otherwise
     */
    bool parseFaceDescription(const char* faceDescriptionP, GlueFace& rFaceP, FaceCounters& rCountersP);
    /**
     * Get an option value from options block
     * 
     * @param  {int} optionTypeP            : type of option
     * @param  {ElemsManager*} pElemsP      : options values
     * @param  {OptionsValue} rOptionValueP : identified value
     * @return {bool}                       : true if found, false otherwise
     */
    bool getOptionValue(int optionTypeP, ElemsManager* pElemsP, OptionsValue& rOptionValueP);

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
     * Create window.
     * 
     * @param  {GlueFace} const : window face
     * @return {Id}             : id of window
     */
    Id  createWindow(GlueFace const& rFaceP);
    /**
     * Create label.
     * 
     * @param  {GlueFace} const : label face
     * @return {Id}             : id of label
     */
    Id  createLabel(GlueFace const& rFaceP);
    /**
     * Create area.
     * 
     * @param  {GlueFace} const : area face
     * @return {Id}             : id of area
     */
    Id  createArea(GlueFace const& rFaceP);
    /**
     * Create field.
     * 
     * @param  {GlueFace} const : field face
     * @return {Id}             : id of field
     */
    Id  createField(GlueFace const& rFaceP);
    /**
     * Create button.
     * 
     * @param  {GlueFace} const : button face
     * @return {Id}             : id of field
     */
    Id  createButton(GlueFace const& rFaceP);
    /**
     * Create checkbox.
     * 
     * @param  {GlueFace} const : checkbox face
     * @return {Id}             : id of field
     */
    Id  createCheckbox(GlueFace const& rFaceP);
    /**
     * Create radio button.
     * 
     * @param  {GlueFace} const : radio button face
     * @return {Id}             : id of radio button
     */
    Id  createRadioButton(GlueFace const& rFaceP);
    /**
     * Create image.
     * 
     * @param  {GlueFace} const : image face
     * @return {Id}             : id of image
     */
    Id  createImage(GlueFace const& rFaceP);
    /**
     * Create combo.
     * 
     * @param  {GlueFace} const : combo face
     * @return {Id}             : id of combo
     */
    Id  createCombo(GlueFace const& rFaceP);

    /** Storage for widgets */
    Widget::Storage widgetsM;
    /** Root widgets, without parents */
    std::list<Widget::Storage::Index> rootWidgetsM;
    /** Commands queue */
    Widget::Command commandsM;
    /** Mutex used to synchrnize operations with frames */
    Os::Mutex& rFrameSynchronizerM;
    /** Collection of created fonts */
    Bind::Rebol2::FontsMap fontsM;
    /** Flag indicating new font has been added */
    bool newFontAddedM;
    /** Gui type. Some widgets may need this info (ex.: image) */
    Api::GuiType guiTypeM;
    /** Flag indicating stash/unstash status */
    bool stashedM;
    /** Flag indicating when first time unstash is done. */
    bool isInitialUnstashM;
};

inline Os::Mutex& Renderer::getWidgetsSync()
{
    return syncWidgetsM;
}

inline IWidget* Renderer::getWidget(Id idP)
{
    return widgetsM.getElement(idP);
}

inline IWindow* Renderer::getWindow(Id idP)
{
    return static_cast<IWindow*>(widgetsM.getElement(idP));
}

} // namespace GUI