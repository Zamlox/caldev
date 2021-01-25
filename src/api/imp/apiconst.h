/**
 * Author: 		Iosif Haidu
 * Description: Constants for API implementation
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __API_APICONST_H__
#define __API_APICONST_H__

namespace Api
{

/**
 * GUI type
 */
enum class GuiType {
    INVALID_TYPE = -1,
    GUI_OPENGL2,
    GUI_DIRECTX
};

/**
 * Type of thread to execute gui engine
 */
enum class GuiEngineExecutionType {
    INVALID_THREAD = -1,
    MAIN_THREAD,
    BKG_THREAD
};

} // namespace Api

#endif // __API_APICONST_H__
   