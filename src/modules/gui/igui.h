/**
 * Author: 		Iosif Haidu
 * Description: GUI engines must derive from this interface 
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

namespace GUI
{
/**
 * Interface for GUI engines
 */
class IGui
{
public:
    virtual ~IGui() = default;
    /**
     * Starts GUI engine
     * @return {bool}  :  true if succeeded, false otherwise
     */
    virtual bool start() = 0;
    /**
     * Stops GUI engine
     * @return {bool}  : true if succeeded, false otherwise
     */
    virtual bool stop() = 0;
};

} // namespace GUI