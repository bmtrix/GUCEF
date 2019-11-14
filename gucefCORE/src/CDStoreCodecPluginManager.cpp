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

#ifndef GUCEF_CORE_DVCPPSTRINGUTILS_H
#include "dvcppstringutils.h"           /* C++ string utils */
#define GUCEF_CORE_DVCPPSTRINGUTILS_H
#endif /* GUCEF_CORE_DVCPPSTRINGUTILS_H ? */

#ifndef GUCEF_CORE_DVFILEUTILS_H
#include "dvfileutils.h"                /* file handling utils */
#define GUCEF_CORE_DVFILEUTILS_H
#endif /* GUCEF_CORE_DVFILEUTILS_H ? */

#ifndef GUCEF_CORE_CDSTORECODECREGISTRY_H
#include "CDStoreCodecRegistry.h"       /* registry for dstore codecs */
#define GUCEF_CORE_CDSTORECODECREGISTRY_H
#endif /* GUCEF_CORE_CDSTORECODECREGISTRY_H ? */

#ifndef GUCEF_CORE_CDATANODE_H
#include "CDataNode.h"          /* node for data storage */
#define GUCEF_CORE_CDATANODE_H
#endif /* GUCEF_CORE_CDATANODE_H ? */

#ifndef GUCEF_CORE_CLOGMANAGER_H
#include "CLogManager.h"
#define GUCEF_CORE_CLOGMANAGER_H
#endif /* GUCEF_CORE_CLOGMANAGER_H ? */

#ifndef GUCEF_CORE_CDSTORECODECREGISTRY_H
#include "CDStoreCodecRegistry.h"
#define GUCEF_CORE_CDSTORECODECREGISTRY_H
#endif /* GUCEF_CORE_CDSTORECODECREGISTRY_H ? */

#ifndef GUCEF_CORE_CDSTORECODECPLUGIN_H
#include "CDStoreCodecPlugin.h"
#define GUCEF_CORE_CDSTORECODECPLUGIN_H
#endif /* GUCEF_CORE_CDSTORECODECPLUGIN_H ? */

#include "CDStoreCodecPluginManager.h"  /* definition of the class implemented here */

#ifndef GUCEF_CORE_GUCEF_ESSENTIALS_H
#include "gucef_essentials.h"
#define GUCEF_CORE_GUCEF_ESSENTIALS_H
#endif /* GUCEF_CORE_GUCEF_ESSENTIALS_H ? */

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

namespace GUCEF {
namespace CORE {

/*-------------------------------------------------------------------------//
//                                                                         //
//      UTILITIES                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

CDStoreCodecPluginManager::CDStoreCodecPluginManager( void )
    : CPluginManager()
{GUCEF_TRACE;

}

/*-------------------------------------------------------------------------*/

CDStoreCodecPluginManager::~CDStoreCodecPluginManager()
{GUCEF_TRACE;

}

/*-------------------------------------------------------------------------*/

CString
CDStoreCodecPluginManager::GetPluginType( void ) const
{GUCEF_TRACE;

    return "GucefDataStoreCodecPlugin";
}

/*-------------------------------------------------------------------------*/

CDStoreCodecPluginManager::TDStoreCodecPluginPtr
CDStoreCodecPluginManager::GetCodec( const CString& codectype ) const
{GUCEF_TRACE;

    _datalock.Lock();
    TDStoreCodecPluginSet::const_iterator i = _codecs.begin();
    while ( i != _codecs.end() )
    {
        if ( (*i)->GetTypeName() == codectype )
        {
            _datalock.Unlock();
            return (*i);
        }
        ++i;
    }
    _datalock.Unlock();
    return NULL;
}

/*-------------------------------------------------------------------------*/
//
//bool
//CDStoreCodecPluginManager::SaveConfig( CDataNode& tree ) const
//{GUCEF_TRACE;
//
//    _datalock.Lock();
//    CDataNode* n = tree.Structure( "GUCEF%CORE%CDStoreCodecPluginManager" ,
//                                   '%'                                    );
//
//    n->SetAttribute( "plugincount", UInt32ToString( _codecs.size() ) );
//
//    n->DelSubTree();
//    CDataNode plugin( "CDStoreCodecPlugin" );
//    TDStoreCodecPluginPtr cp;
//
//    TDStoreCodecPluginSet::const_iterator i = _codecs.begin();
//    while ( i != _codecs.end() )
//    {
//        cp = (*i);
//        plugin.SetAttribute( "name", cp->GetName() );
//        plugin.SetAttribute( "type", cp->GetTypeName() );
//        plugin.SetAttribute( "version", VersionToString( cp->GetVersion() ) );
//        plugin.SetAttribute( "path", cp->GetModulePath() );
//        plugin.SetAttribute( "copyright", cp->GetCopyright() );
//        n->AddChild( plugin );
//
//        ++i;
//    }
//
//    _datalock.Unlock();
//    return true;
//}
//
///*-------------------------------------------------------------------------*/
//
//bool
//CDStoreCodecPluginManager::LoadConfig( const CDataNode& tree )
//{GUCEF_TRACE;
//
//    GUCEF_SYSTEM_LOG( LOGLEVEL_BELOW_NORMAL, "CDStoreCodecPluginManager: Loading config" );
//
//    _datalock.Lock();
//    CDataNode* n = tree.Search( "GUCEF%CORE%CDStoreCodecPluginManager",
//                                '%'                                   ,
//                                false                                 );
//    if ( n )
//    {
//        CString cmpstr( "CDStoreCodecPlugin" );
//        CString path( "path" );
//        const CDataNode* c;
//        const CDataNode::TKeyValuePair* att;
//        CDataNode::const_iterator i = n->ConstBegin();
//        while ( i != n->ConstEnd() )
//        {
//            c = (*i);
//            if ( c->GetName() == cmpstr )
//            {
//                att = c->GetAttribute( path );
//                if ( att )
//                {
//                    /*
//                     *      Test if this module is already loaded
//                     */
//                    bool found = false;
//                    TDStoreCodecPluginSet::const_iterator i = _codecs.begin();
//                    while ( i != _codecs.end() )
//                    {
//                        if ( att->second == (*i)->GetModulePath() )
//                        {
//                            found = true;
//                            break;
//                        }
//                        ++i;
//                    }
//                    if ( !found )
//                    {
//                        /*
//                         *      This module is not loaded yet.
//                         *      We will do so now.
//                         */
//                        LoadPlugin( att->second );
//                    }
//                }
//            }
//            ++i;
//        }
//    }
//    _datalock.Unlock();
//    return true;
//}

/*-------------------------------------------------------------------------*/

TPluginPtr
CDStoreCodecPluginManager::RegisterPlugin( void* modulePtr                   ,
                                           TPluginMetaDataPtr pluginMetaData )
{GUCEF_TRACE;

    CDStoreCodecPlugin* plugin = new CDStoreCodecPlugin();
    if ( plugin->Link( modulePtr      ,
                       pluginMetaData ) )
    {
        TDStoreCodecPluginPtr pointerToPlugin = plugin;
        if ( CCoreGlobal::Instance()->GetDStoreCodecRegistry().TryRegister( plugin->GetTypeName(), pointerToPlugin ) )
        {
            return pointerToPlugin;
        }
    }

    delete plugin;
    return NULL;
}

/*-------------------------------------------------------------------------*/

void
CDStoreCodecPluginManager::UnregisterPlugin( TPluginPtr plugin )
{GUCEF_TRACE;

    // First unregister from the registry
    TDStoreCodecPluginPtr pointerToPlugin = plugin.StaticCast< CDStoreCodecPlugin >();
    CCoreGlobal::Instance()->GetDStoreCodecRegistry().Unregister( pointerToPlugin->GetTypeName() );

    // Now unlink the plugin
    pointerToPlugin->Unlink();
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------*/
