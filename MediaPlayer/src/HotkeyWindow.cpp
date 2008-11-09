/******************************************************************************
 * Copyright (C) 2008 Tim Boundy <gigaplex@gmail.com>                         *
 *                                                                            *
 * This program is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU General Public License as             *
 * published by the Free Software Foundation; either version 2 of             *
 * the License, or (at your option) any later version.                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.      *
 ******************************************************************************/

#include "stdafx.h"

#include <qsmp/HotkeyWindow.h>
#include <qsmp/HotkeyWindow.moc>

#include <qsmp/Log.h>
#include <MMShellHook.h>

QSMP_BEGIN

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

HotkeyWindow::HotkeyWindow()
: registered_hotkeys_(false)
{
}

//-----------------------------------------------------------------------------

HotkeyWindow::~HotkeyWindow()
{
  DeregisterHotkeys();
}

//-----------------------------------------------------------------------------

bool HotkeyWindow::RegisterHotkeys()
{
  if (registered_hotkeys_)
    DeregisterHotkeys();

  registered_hotkeys_ = SetMMShellHook(internalWinId());

  if (registered_hotkeys_)
    QSMP_LOG("Hotkey") << "Hotkey registration succeeded";
  else
    QSMP_LOG("Hotkey") << "Hotkey registration failed";

  return registered_hotkeys_;
}

//-----------------------------------------------------------------------------

bool HotkeyWindow::DeregisterHotkeys()
{
  if (registered_hotkeys_)
  {
    registered_hotkeys_ = !UnSetMMShellHook(internalWinId());

    if (registered_hotkeys_)
      QSMP_LOG("Hotkey") << "Hotkey unregistration failed";
    else
      QSMP_LOG("Hotkey") << "Hotkey deregistration succeeded";

    return !registered_hotkeys_;
  }

  return false;
}

//-----------------------------------------------------------------------------

bool HotkeyWindow::winEvent(MSG* message, long* /*result*/)
{
  if(message->message == WM_APPCOMMAND)
  {
    switch(GET_APPCOMMAND_LPARAM(message->lParam))
    {
    case APPCOMMAND_MEDIA_NEXTTRACK:
      QSMP_LOG("Hotkey") << "Next hotkey detected: " << GetTickCount();
      OnNext();
      return true;

    case APPCOMMAND_MEDIA_PREVIOUSTRACK:
      QSMP_LOG("Hotkey") << "Previous hotkey detected: " << GetTickCount();
      OnPrevious();
      return true;

    case APPCOMMAND_MEDIA_STOP:
      QSMP_LOG("Hotkey") << "Stop hotkey detected: " << GetTickCount();
      OnStop();
      return true;

    case APPCOMMAND_MEDIA_PLAY_PAUSE:
      QSMP_LOG("Hotkey") << "Play/Pause hotkey detected: " << GetTickCount();
      OnPlayPause();
      return true;
    }
  }
  return false;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

QSMP_END
