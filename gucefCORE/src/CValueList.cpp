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

#include <assert.h>

#ifndef GUCEF_CORE_LOGGING_H
#include "gucefCORE_Logging.h"
#define GUCEF_CORE_LOGGING_H
#endif /* GUCEF_CORE_LOGGING_H ? */

#ifndef GUCEF_CORE_CDATANODE_H
#include "CDataNode.h"
#define GUCEF_CORE_CDATANODE_H
#endif /* GUCEF_CORE_CDATANODE_H ? */

#include "CValueList.h"

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

GUCEF_IMPLEMENT_MSGEXCEPTION( CValueList, EUnknownKey );
GUCEF_IMPLEMENT_MSGEXCEPTION( CValueList, EIndexOutOfRange );

/*-------------------------------------------------------------------------*/

CValueList::CValueList( void )
    : CIConfigurable( false )       ,
      m_list()                      ,
      m_allowDuplicates( false )    ,
      m_allowMultipleValues( true ) ,
      m_configNamespace()
{GUCEF_TRACE;
}

/*-------------------------------------------------------------------------*/

CValueList::CValueList( const CValueList& src )
    : CIConfigurable( false )                            ,
      m_list( src.m_list )                               ,
      m_allowDuplicates( src.m_allowDuplicates )         ,
      m_allowMultipleValues( src.m_allowMultipleValues ) ,
      m_configNamespace()
{GUCEF_TRACE;
               
}

/*-------------------------------------------------------------------------*/

CValueList::~CValueList()
{GUCEF_TRACE;

}

/*-------------------------------------------------------------------------*/

CValueList&
CValueList::operator=( const CValueList& src )
{GUCEF_TRACE;

     if ( this != &src )
     {
        m_list = src.m_list;
        m_allowDuplicates = src.m_allowDuplicates;
        m_allowMultipleValues = src.m_allowMultipleValues;
     }
     return *this;
}

/*-------------------------------------------------------------------------*/

CString&
CValueList::operator[]( const CString& key )
{GUCEF_TRACE;

    return GetValue( key );
}

/*-------------------------------------------------------------------------*/

const CString&
CValueList::operator[]( const CString& key ) const
{GUCEF_TRACE;

    return GetValue( key );
}

/*-------------------------------------------------------------------------*/

void
CValueList::SetMultiple( int argc    ,
                         char** argv )
{GUCEF_TRACE;

    for ( int i=0; i<argc; ++i )
    {
        Set( argv[ i ] );
    }
}

/*-------------------------------------------------------------------------*/

void
CValueList::SetConfigNamespace( const CString& configNamespace )
{GUCEF_TRACE;

    m_configNamespace = configNamespace;
}

/*-------------------------------------------------------------------------*/

const CString&
CValueList::GetConfigNamespace( void ) const
{GUCEF_TRACE;

    return m_configNamespace;
}

/*-------------------------------------------------------------------------*/

bool
CValueList::SaveConfig( CDataNode& tree ) const
{GUCEF_TRACE;

    // not currently supported
    return true;
}

/*-------------------------------------------------------------------------*/

bool
CValueList::LoadConfig( const CDataNode& treeroot )
{GUCEF_TRACE;

    const CDataNode* nodeNamespaceRoot = treeroot.Search( m_configNamespace, '/', true, true );
    if ( NULL != nodeNamespaceRoot )
    {
        // Get the key-value combos from the attributes
        CDataNode::TAttributeMap::const_iterator i = nodeNamespaceRoot->AttributeBegin();
        while ( i != nodeNamespaceRoot->AttributeEnd() )
        {
            Set( (*i).first, (*i).second.value );
            ++i;
        }

        // Also get the key-value combo's of Child nodes names + default value
        CDataNode::const_iterator n = nodeNamespaceRoot->Begin();
        while ( n != nodeNamespaceRoot->End() )
        {
            const CString& value = (*n)->GetValue();
            if ( !value.IsNULLOrEmpty() )
            {
                Set( (*n)->GetName(), value );
            }
            ++n;
        }
    }
    return true;
}

/*-------------------------------------------------------------------------*/

void
CValueList::SetMultiple( const CString& keyandvalue ,
                         const char seperator       )
{GUCEF_TRACE;

    CString remnant = keyandvalue;
    while ( remnant.Length() > 0 )
    {
        CString tmp = remnant.SubstrToChar( seperator, true );
        if ( ( tmp.Length() > 0 )          || 
             ( remnant[ 0 ] == seperator )  )
        {
            remnant = remnant.CutChars( tmp.Length()+1, true );
            
            CString keyValueStr = remnant.SubstrToChar( seperator, true );
            if ( keyValueStr.Length() > 0 )
            {
                Set( keyValueStr );
                remnant = remnant.CutChars( keyValueStr.Length()+1, true );
            }
            else
            {
                return;
            }
        }
        else
        {
            return;
        }
    }
}

/*-------------------------------------------------------------------------*/

void
CValueList::SetAllowDuplicates( const bool allowDuplicates )
{GUCEF_TRACE;

    m_allowDuplicates = allowDuplicates;
}

/*-------------------------------------------------------------------------*/
    
bool
CValueList::GetAllowDuplicates( void ) const
{GUCEF_TRACE;

    return m_allowDuplicates;
}

/*-------------------------------------------------------------------------*/

void
CValueList::SetAllowMultipleValues( const bool allowMultipleValues )
{GUCEF_TRACE;

    m_allowMultipleValues = allowMultipleValues;
}

/*-------------------------------------------------------------------------*/
    
bool
CValueList::GetAllowMultipleValues( void ) const
{GUCEF_TRACE;

    return m_allowMultipleValues;
}

/*-------------------------------------------------------------------------*/

void 
CValueList::Set( const CString& keyAndValue )
{GUCEF_TRACE;

    CString key( keyAndValue.SubstrToChar( '=', true ) );
    CString value( keyAndValue.SubstrToChar( '=', false ) );
    
    Set( key   ,
         value );
}

/*-------------------------------------------------------------------------*/

void 
CValueList::Set( const CString& key   ,
                 const CString& value )
{GUCEF_TRACE;
        
    if ( key.Length() > 0 )
    {
        TStringVector& values = m_list[ key ];
        if ( m_allowDuplicates )
        {
            values.push_back( value );
        }
        else
        {
            // Duplicates are not allowed so if an identical
            // value is already in the list we should not add it
            TStringVector::iterator n = values.begin();
            while ( n != values.end() )
            {
                if ( (*n) == value )
                {
                    // The given value is already in the list
                    return;
                }
                ++n;
            }
            
            if ( !m_allowMultipleValues )
            {
                values.clear();
            }
            values.push_back( value );
        }    
    }
}

/*-------------------------------------------------------------------------*/                
        
CString
CValueList::GetValueAlways( const CString& key ) const
{GUCEF_TRACE;

    CString emptyStr;
    return GetValueAlways( key, emptyStr );
}

/*-------------------------------------------------------------------------*/                
        
CString
CValueList::GetValueAlways( const CString& key          , 
                            const CString& defaultValue ) const
{GUCEF_TRACE;

    TValueMap::const_iterator i = m_list.find( key );
    if ( i != m_list.end() )
    {
        return (*i).second[ 0 ];
    }

    return defaultValue; 
}

/*-------------------------------------------------------------------------*/                
        
const CString&
CValueList::GetValue( const CString& key ) const
{GUCEF_TRACE;

    TValueMap::const_iterator i = m_list.find( key );
    if ( i != m_list.end() )
    {
        return (*i).second[ 0 ];
    }

    GUCEF_EMSGTHROW( EUnknownKey, CString( "CValueList::GetValue(): The given key \"" + key + "\" is not found" ).C_String() );
}

/*-------------------------------------------------------------------------*/                
        
CString&
CValueList::GetValue( const CString& key )
{GUCEF_TRACE;

    TValueMap::iterator i = m_list.find( key );
    if ( i != m_list.end() )
    {
        return (*i).second[ 0 ];
    }

    GUCEF_EMSGTHROW( EUnknownKey, "CValueList::GetValue(): The given key is not found" );
}

/*-------------------------------------------------------------------------*/

CValueList::TStringVector&
CValueList::GetValueVector( const CString& key )
{GUCEF_TRACE;

    TValueMap::iterator i = m_list.find( key );
    if ( i != m_list.end() )
    {
        return (*i).second;
    }

    GUCEF_EMSGTHROW( EUnknownKey, "CValueList::GetValue(): The given key is not found" );    
}

/*-------------------------------------------------------------------------*/

const CValueList::TStringVector&
CValueList::GetValueVector( const CString& key ) const
{GUCEF_TRACE;

    TValueMap::const_iterator i = m_list.find( key );
    if ( i != m_list.end() )
    {
        return (*i).second;
    }

    GUCEF_EMSGTHROW( EUnknownKey, "CValueList::GetValue(): The given key is not found" );    
}

/*-------------------------------------------------------------------------*/

const CString&
CValueList::GetValue( const UInt32 index ) const
{GUCEF_TRACE;

    if ( index < m_list.size() )
    {
        TValueMap::const_iterator i = m_list.begin();
        for ( UInt32 n=0; n<index; ++n ) { ++i; }
        
        return (*i).second[ 0 ];
    }
    
    GUCEF_EMSGTHROW( EIndexOutOfRange, "CValueList::GetValue( index ): The given index is invalid" );        
}

/*-------------------------------------------------------------------------*/

CString&
CValueList::GetValue( const UInt32 index )
{GUCEF_TRACE;

    if ( index < m_list.size() )
    {
        TValueMap::iterator i = m_list.begin();
        for ( UInt32 n=0; n<index; ++n ) { ++i; }
        
        return (*i).second[ 0 ];
    }
    
    GUCEF_EMSGTHROW( EIndexOutOfRange, "CValueList::GetValue( index ): The given index is invalid" );        
}

/*-------------------------------------------------------------------------*/

CString 
CValueList::GetPair( const UInt32 index ) const
{GUCEF_TRACE;
    
    const CString& key = GetKey( index );
    const CString& value = GetValue( index );

    // if no exception was thrown we can now proceed to build the pair
    CString pair = key + '=' + value;
    return pair;
}

/*-------------------------------------------------------------------------*/

CString
CValueList::GetAllPairs( const UInt32 index          , 
                         const CString& seperatorStr ) const
{GUCEF_TRACE;

    const CString& key = GetKey( index );
    const TStringVector& values = GetValueVector( index );
    
    CString resultStr;
    bool first = true;
    for ( UInt32 i=0; i<values.size(); ++i )
    {
        if ( !first )
        {
            resultStr += seperatorStr;
        }
        else
        {
            first = false;
        }
     
        resultStr += key + '=' + values[ i ];
    }
    
    return resultStr;
}

/*-------------------------------------------------------------------------*/

CString
CValueList::GetAllPairs( const CString& seperatorStr ) const
{GUCEF_TRACE;

    CString resultStr;
    bool first = true;
    TValueMap::const_iterator i = m_list.begin();
    while ( i != m_list.end() )
    {
        const CString& key = (*i).first;
        const TStringVector& values = (*i).second;
        
        TStringVector::const_iterator n = values.begin();
        while ( n != values.end() )
        {
            if ( !first )
            {
                resultStr += seperatorStr;
            }
            else
            {
                first = false;
            }
            
            resultStr += key + '=' + (*n);
        }
        ++i;
    }
    return resultStr;
}

/*-------------------------------------------------------------------------*/

CString 
CValueList::GetPair( const CString& key ) const
{GUCEF_TRACE;

    const CString& value = GetValue( key );

    // if no exception was thrown we can now proceed to build the pair
    CString pair = key + '=' + value;
    return pair;
}

/*-------------------------------------------------------------------------*/

const CString&
CValueList::GetKey( const UInt32 index ) const
{GUCEF_TRACE;

    if ( index < m_list.size() )
    {
        TValueMap::const_iterator i = m_list.begin();
        for ( UInt32 n=0; n<index; ++n ) { ++i; }
        
        return (*i).first;
    }
    
    GUCEF_EMSGTHROW( EIndexOutOfRange, "CValueList::GetKey( index ): The given index is invalid" );
}

/*-------------------------------------------------------------------------*/

bool 
CValueList::HasKey( const CString& key ) const
{GUCEF_TRACE;

    return m_list.end() != m_list.find( key );
}

/*-------------------------------------------------------------------------*/
        
void 
CValueList::Delete( const CString& key )
{GUCEF_TRACE;
    
    m_list.erase( key );
}

/*-------------------------------------------------------------------------*/

void 
CValueList::DeleteAll( void )
{GUCEF_TRACE;

    m_list.clear();
}

/*-------------------------------------------------------------------------*/

UInt32 
CValueList::GetCount( void ) const
{GUCEF_TRACE;

    return (UInt32) m_list.size();
}

/*-------------------------------------------------------------------------*/

const CValueList::TStringVector&
CValueList::GetValueVector( const UInt32 index ) const
{GUCEF_TRACE;

    if ( index < m_list.size() )
    {
        TValueMap::const_iterator i = m_list.begin();
        for ( UInt32 n=0; n<index; ++n ) { ++i; }
        
        return (*i).second;
    }
    
    GUCEF_EMSGTHROW( EIndexOutOfRange, "CValueList::GetValueVector( index ): The given index is invalid" )
}

/*-------------------------------------------------------------------------*/

CValueList::TValueMap::const_iterator
CValueList::GetDataBeginIterator( void ) const
{GUCEF_TRACE;

    return m_list.begin();
}

/*-------------------------------------------------------------------------*/
    
CValueList::TValueMap::const_iterator
CValueList::GetDataEndIterator( void ) const
{GUCEF_TRACE;

    return m_list.end();
}

/*-------------------------------------------------------------------------*/

void
CValueList::Clear( void )
{GUCEF_TRACE;

    m_list.clear();
    m_allowDuplicates = false;
    m_allowMultipleValues = true;
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------*/
