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

#ifndef GUCEF_CORE_CBASICBRACKETLOGGINGFORMATTER_H
#define GUCEF_CORE_CBASICBRACKETLOGGINGFORMATTER_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_CORE_CILOGGINGFORMATTER_H
#include "gucefCORE_CILoggingFormatter.h"
#define GUCEF_CORE_CILOGGINGFORMATTER_H
#endif /* GUCEF_CORE_CILOGGINGFORMATTER_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF {
namespace CORE {

/*-------------------------------------------------------------------------//
//                                                                         //
//      CLASSES                                                            //
//                                                                         //
//-------------------------------------------------------------------------*/

/**
 *  Basic log formatter implementation which envelops the various fields with square brackets and their name
 *      [<FieldName>=<FieldContent>]
 *  This is the historical default formatter
 */
class GUCEF_CORE_PUBLIC_CPP CBasicBracketLoggingFormatter : public CILoggingFormatter
{
    public:

    virtual CString FormatLogMessage( const TLogMsgType logMsgType ,
                                      const Int32 logLevel         ,
                                      const CString& logMessage    ,
                                      const UInt32 threadId        ) GUCEF_VIRTUAL_OVERRIDE;

    CBasicBracketLoggingFormatter( void );            
    virtual ~CBasicBracketLoggingFormatter();    
    CBasicBracketLoggingFormatter( const CBasicBracketLoggingFormatter& src ); 
    CBasicBracketLoggingFormatter& operator=( const CBasicBracketLoggingFormatter& src );
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------*/

#endif /* GUCEF_CORE_CBASICBRACKETLOGGINGFORMATTER_H ? */

