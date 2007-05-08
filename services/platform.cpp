/*
    This file is part of Icecream.

    Copyright (c) 2006 Mirko Boehm <mirko@kde.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

extern "C" {
#include <sys/utsname.h>
}

#include "logging.h"
#include "platform.h"

std::string determine_platform_once()
{
    using namespace std;
    string platform;

    struct utsname uname_buf;
    if ( uname( &uname_buf ) ) {
        log_perror( "uname call failed" );
        throw( "determine_platform: cannot determine OS version and machine architecture" );
        // return platform;
    }

    string os = uname_buf.sysname;
    if ( os != "Linux" )
        platform = os + '_' + uname_buf.machine;
    else // Linux
        platform = uname_buf.machine;

    while (true)
    {
        string::size_type pos = platform.find(" ");
        if (pos == string::npos)
            break;
        platform.erase(pos, 1);
    }

    return platform;
}

const std::string& determine_platform()
{
    const static std::string platform( determine_platform_once() );
    return platform;
}
