/**
 * Author: 		Iosif Haidu
 * Description: GUI engine implementation based on OpenGL 
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "igui.h"
#include "thread.h"

namespace GUI
{

/**
 * GUI engine implementing IGui
 */
class OpenGL : public IGui
{
public:
    OpenGL();
    /** see IGui::start() */
    bool start() override;
    /** see IGui::stop() */
    bool stop() override;

private:
    /**
     * Code to run before returning back to caller after thread starts
     * @param  {void*} pParamP : pass 'this' to have access to internal data
     */
    static void* initGuiEngine(void* pParamP);
    /**
     * Code to run for GUI engine 
     * @param  {void*} pParamP : pass 'this' to have access to internal data
     */
    static void* guiEngine(void*pParamP);

    /** Separate thread to run GUI engine */
    Os::Thread threadM;
};

} // namespace GUI