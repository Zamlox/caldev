/**
 * Author: 		Iosif Haidu
 * Description: Constants for API implementation
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#pragma once

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

   