/*
 *  gucefCORE: GUCEF module providing O/S abstraction and generic solutions
 *  Copyright (C) 2002 - 2007.  Dinand Vanvelzen
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA 
 */

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/ 

#include "CStreamerEvents.h"

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF {
namespace CORE {

/*-------------------------------------------------------------------------//
//                                                                         //
//      GLOBAL VARS                                                        //
//                                                                         //
//-------------------------------------------------------------------------*/

const CEvent CStreamerEvents::IDStreamEvent = "GUCEF::CORE::CStreamerEvents::IDStreamEvent";
const CEvent CStreamerEvents::DataStreamEvent = "GUCEF::CORE::CStreamerEvents::DataStreamEvent";

/*-------------------------------------------------------------------------//
//                                                                         //
//      UTILITIES                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

void
CStreamerEvents::RegisterEvents( void )
{GUCEF_TRACE;

    IDStreamEvent.Initialize();
    DataStreamEvent.Initialize();
}

/*-------------------------------------------------------------------------*/

CStreamerEvents::CStreamerEvents( void )
{GUCEF_TRACE;

    RegisterEvents();
}

/*-------------------------------------------------------------------------*/

CStreamerEvents::CStreamerEvents( const CStreamerEvents& src )
{GUCEF_TRACE;

}

/*-------------------------------------------------------------------------*/

CStreamerEvents::~CStreamerEvents()
{GUCEF_TRACE;

}

/*-------------------------------------------------------------------------*/

CStreamerEvents&
CStreamerEvents::operator=( const CStreamerEvents& src )
{GUCEF_TRACE;

    return *this;
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------*/