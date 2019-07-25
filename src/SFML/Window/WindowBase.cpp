////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2018 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Window/WindowBase.h>
#include <SFML/Window/WindowBaseStruct.h>
#include <SFML/Internal.h>
#include <SFML/Window/ContextSettingsInternal.h>
#include <SFML/Window/CursorStruct.h>
#include <SFML/ConvertEvent.h>


////////////////////////////////////////////////////////////
sfWindowBase* sfWindowBase_create(sfVideoMode mode, const char* title, sfUint32 style)
{
    // Convert video mode
    sf::VideoMode videoMode(mode.width, mode.height, mode.bitsPerPixel);

    // Create the window
    sfWindowBase* window = new sfWindowBase;
    window->This.create(videoMode, title, style);

    return window;
}

////////////////////////////////////////////////////////////
sfWindowBase* sfWindowBase_createUnicode(sfVideoMode mode, const sfUint32* title, sfUint32 style)
{
    // Convert video mode
    sf::VideoMode videoMode(mode.width, mode.height, mode.bitsPerPixel);

    // Create the window
    sfWindowBase* window = new sfWindowBase;
    window->This.create(videoMode, title, style);

    return window;
}

/*
////////////////////////////////////////////////////////////
sfWindowBase* sfWindowBase_createFromHandle(sfWindowHandle handle, const sfContextSettings* settings)
{
    // Convert context settings
    sf::ContextSettings params;
    if (settings)
    {
        priv::sfContextSettings_writeToCpp(*settings, params);
    }

    // Create the window
    sfWindowBase* window = new sfWindow;
    window->This.create(handle, params);

    return window;
}
*/

////////////////////////////////////////////////////////////
void sfWindowBase_destroy(sfWindowBase* window)
{
    delete window;
}

////////////////////////////////////////////////////////////
void sfWindowBase_close(sfWindowBase* window)
{
    CSFML_CALL(window, close());
}


////////////////////////////////////////////////////////////
sfBool sfWindowBase_isOpen(const sfWindowBase* window)
{
    CSFML_CALL_RETURN(window, isOpen(), sfFalse);
}

/*
////////////////////////////////////////////////////////////
sfContextSettings sfWindowBase_getSettings(const sfWindowBase* window)
{
    sfContextSettings settings = priv::sfContextSettings_null();
    CSFML_CHECK_RETURN(window, settings);

    const sf::ContextSettings& params = window->This.getSettings();
    priv::sfContextSettings_readFromCpp(params, settings);

    return settings;
}
*/


////////////////////////////////////////////////////////////
sfBool sfWindowBase_pollEvent(sfWindowBase* window, sfEvent* event)
{
    CSFML_CHECK_RETURN(window, sfFalse);
    CSFML_CHECK_RETURN(event, sfFalse);

    // Get the event
    sf::Event SFMLEvent;
    sfBool ret = window->This.pollEvent(SFMLEvent);

    // No event, return
    if (!ret)
        return sfFalse;

    // Convert the sf::Event event to a sfEvent
    convertEvent(SFMLEvent, event);

    return sfTrue;
}


////////////////////////////////////////////////////////////
sfBool sfWindowBase_waitEvent(sfWindowBase* window, sfEvent* event)
{
    CSFML_CHECK_RETURN(window, sfFalse);
    CSFML_CHECK_RETURN(event, sfFalse);

    // Get the event
    sf::Event SFMLEvent;
    sfBool ret = window->This.waitEvent(SFMLEvent);

    // Error, return
    if (!ret)
        return sfFalse;

    // Convert the sf::Event event to a sfEvent
    convertEvent(SFMLEvent, event);

    return sfTrue;
}


////////////////////////////////////////////////////////////
sfVector2i sfWindowBase_getPosition(const sfWindowBase* window)
{
    sfVector2i position = {0, 0};
    CSFML_CHECK_RETURN(window, position);

    sf::Vector2i sfmlPos = window->This.getPosition();
    position.x = sfmlPos.x;
    position.y = sfmlPos.y;

    return position;
}


////////////////////////////////////////////////////////////
void sfWindowBase_setPosition(sfWindowBase* window, sfVector2i position)
{
    CSFML_CALL(window, setPosition(sf::Vector2i(position.x, position.y)));
}


////////////////////////////////////////////////////////////
sfVector2u sfWindowBase_getSize(const sfWindowBase* window)
{
    sfVector2u size = {0, 0};
    CSFML_CHECK_RETURN(window, size);

    sf::Vector2u sfmlSize = window->This.getSize();
    size.x = sfmlSize.x;
    size.y = sfmlSize.y;

    return size;
}


////////////////////////////////////////////////////////////
void sfWindowBase_setSize(sfWindowBase* window, sfVector2u size)
{
    CSFML_CALL(window, setSize(sf::Vector2u(size.x, size.y)));
}


////////////////////////////////////////////////////////////
void sfWindowBase_setTitle(sfWindowBase* window, const char* title)
{
    CSFML_CALL(window, setTitle(title));
}


////////////////////////////////////////////////////////////
void sfWindowBase_setUnicodeTitle(sfWindowBase* window, const sfUint32* title)
{
    CSFML_CALL(window, setTitle(title));
}


////////////////////////////////////////////////////////////
void sfWindowBase_setIcon(sfWindowBase* window, unsigned int width, unsigned int height, const sfUint8* pixels)
{
    CSFML_CALL(window, setIcon(width, height, pixels));
}


////////////////////////////////////////////////////////////
void sfWindowBase_setVisible(sfWindowBase* window, sfBool visible)
{
    CSFML_CALL(window, setVisible(visible == sfTrue));
}


////////////////////////////////////////////////////////////
void sfWindowBase_setMouseCursorVisible(sfWindowBase* window, sfBool visible)
{
    CSFML_CALL(window, setMouseCursorVisible(visible == sfTrue));
}


////////////////////////////////////////////////////////////
void sfWindowBase_setMouseCursorGrabbed(sfWindowBase* window, sfBool grabbed)
{
    CSFML_CALL(window, setMouseCursorGrabbed(grabbed == sfTrue));
}


////////////////////////////////////////////////////////////
void sfWindowBase_setMouseCursor(sfWindowBase* window, const sfCursor* cursor)
{
    CSFML_CHECK(cursor);

    CSFML_CALL(window, setMouseCursor(cursor->This));
}

/*
////////////////////////////////////////////////////////////
void sfWindowBase_setVerticalSyncEnabled(sfWindowBase* window, sfBool enabled)
{
    CSFML_CALL(window, setVerticalSyncEnabled(enabled == sfTrue));
}
*/


////////////////////////////////////////////////////////////
void sfWindowBase_setKeyRepeatEnabled(sfWindowBase* window, sfBool enabled)
{
    CSFML_CALL(window, setKeyRepeatEnabled(enabled == sfTrue));
}


/*
////////////////////////////////////////////////////////////
sfBool sfWindowBase_setActive(sfWindowBase* window, sfBool active)
{
    CSFML_CALL_RETURN(window, setActive(active == sfTrue), sfFalse);
}
*/

////////////////////////////////////////////////////////////
void sfWindowBase_requestFocus(sfWindowBase* window)
{
    CSFML_CALL(window, requestFocus());
}


////////////////////////////////////////////////////////////
sfBool sfWindowBase_hasFocus(const sfWindowBase* window)
{
    CSFML_CALL_RETURN(window, hasFocus(), sfFalse);
}


/*
////////////////////////////////////////////////////////////
void sfWindowBase_display(sfWindowBase* window)
{
    CSFML_CALL(window, display());
}
*/

/*
////////////////////////////////////////////////////////////
void sfWindowBase_setFramerateLimit(sfWindowBase* window, unsigned int limit)
{
    CSFML_CALL(window, setFramerateLimit(limit));
}
*/

////////////////////////////////////////////////////////////
void sfWindowBase_setJoystickThreshold(sfWindowBase* window, float threshold)
{
    CSFML_CALL(window, setJoystickThreshold(threshold));
}


////////////////////////////////////////////////////////////
sfWindowHandle sfWindowBase_getSystemHandle(const sfWindowBase* window)
{
    CSFML_CHECK_RETURN(window, 0);

    return (sfWindowHandle)window->This.getSystemHandle();
}

////////////////////////////////////////////////////////////
void* sfWindowBase_getSystemConnection(const sfWindowBase* window)
{
    CSFML_CHECK_RETURN(window, 0);

    return window->This.getSystemConnection();
}
