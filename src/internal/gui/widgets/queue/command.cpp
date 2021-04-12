/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/widgets/queue/command.h"

namespace GUI {
namespace Widget {

void Command::set(WidgetCommand commandP, Id parentIdP, IWindow* pWindowP)
{
    CommandElem elem{commandP, parentIdP, pWindowP};
    mutexM.lock();
    commandsM.push_back(elem);
    mutexM.unlock();
}

void Command::set(WidgetCommand commandP, Id parentIdP, IWidget* pWidgetP)
{
    CommandElem elem{commandP, parentIdP, pWidgetP};
    mutexM.lock();
    commandsM.push_back(elem);
    mutexM.unlock();
}

CommandElem Command::get()
{
    CommandElem result{WidgetCommand::None};
    mutexM.lock();
    if (!commandsM.empty())
    {
        result = commandsM.front();
        commandsM.pop_front();
    }
    mutexM.unlock();
    return result;
}

} // namespace Widget
} // namespace GUI
