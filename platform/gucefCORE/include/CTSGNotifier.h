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

#ifndef GUCEF_CORE_CTSGNOTIFIER_H
#define GUCEF_CORE_CTSGNOTIFIER_H

/*-------------------------------------------------------------------------//
//                                                                         //
//      INCLUDES                                                           //
//                                                                         //
//-------------------------------------------------------------------------*/

#ifndef GUCEF_MT_CMUTEX_H
#include "gucefMT_CMutex.h"
#define GUCEF_MT_CMUTEX_H
#endif /* GUCEF_MT_CMUTEX_H ? */

#ifndef GUCEF_CORE_CTSGOBSERVER_H
#include "CTSGObserver.h"       /* observer implementation used internally by the CTSGNotifier */
#define GUCEF_CORE_CTSGOBSERVER_H
#endif /* GUCEF_CORE_CTSGOBSERVER_H ? */

#ifndef GUCEF_CORE_CNOTIFIER_H
#include "CNotifier.h"          /* notification base class */
#define GUCEF_CORE_CNOTIFIER_H
#endif /* GUCEF_CORE_CNOTIFIER_H ? */

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

class CPulseGenerator;

/*-------------------------------------------------------------------------*/

/**
 *  ThreadSafe Gateway Notifier class a.k.a TSGNotifier class a.k.a CTSGNotifier
 *
 *  Implements a base class for notifiers that can listnen to another notifier
 *  that is dispatching events from within a thread.
 *  Using this mechanism you can use a Notifier-Observer based design while
 *  mixing threadsafe code with non-threadsafe code.
 *  So basicly like the name says,... it is a messaging gateway between
 *  threadsafe code and non-threadsafe code.
 *
 *  Note that if you do not override OnPumpedNotify() then the instance
 *  will simply function as a pass-trough notifier. Override to manipulate
 *  the event data before it is sent to the observers.
 *  Keep in mind that the CTSGNotifier will become the source notifier !!!
 */
class GUCEF_CORE_PUBLIC_CPP CTSGNotifier : public CNotifier
{
    public:

    CTSGNotifier( void );

    CTSGNotifier( CPulseGenerator& pulsGenerator );

    CTSGNotifier( const CTSGNotifier& src );

    virtual ~CTSGNotifier();

    CTSGNotifier& operator=( const CTSGNotifier& src );

    /**
     *  Subscribes to the given notifier to all
     *  notification events. Every event dispatched by
     *  the threadedNotifier will be sent to the
     *  instance of this class.
     */
    void SubscribeTo( CNotifier* threadedNotifier );

    void UnsubscribeFrom( CNotifier* threadedNotifier );

    /**
     *  Subscribes to the given notifier's four standard
     *  notifier events, if it is not yet subscribed, plus
     *  subscribes to the given custom event.
     */
    void SubscribeTo( CNotifier* threadedNotifier ,
                      const CEvent& eventid       );

    /**
     *  Cancels the subscription at the given threadedNotifier
     *  for the given event.
     *
     *  Note that subscriptions to the standard notifier events
     *  cannot be cancelled, attempts to do so will be ignored.
     */
    void UnsubscribeFrom( CNotifier* threadedNotifier ,
                          const CEvent& eventid       );

    virtual const CString& GetClassTypeName( void ) const GUCEF_VIRTUAL_OVERRIDE;

    CObserver& AsObserver( void );

    protected:

    virtual bool Lock( void ) const GUCEF_VIRTUAL_OVERRIDE;

    virtual bool Unlock( void ) const GUCEF_VIRTUAL_OVERRIDE;

    protected:
    friend class CTSGObserver;

    /**
     *  Same as NotifyObservers() except the notification is pumped first
     */
    void NotifyObserversFromThread( void );

    /**
     *  Same as NotifyObservers( eventid, CICloneable* ) except the
     *  notification is pumped first.
     */
    void NotifyObserversFromThread( const CEvent& eventid         ,
                                    CICloneable* eventData = NULL );

    /**
     *  Event callback member function.
     *  Implement this in your descending class to handle
     *  notification events.
     *
     *  Note that this call is always made from the thread running the
     *  puls generator. As such it is well suited for linking non-treadsafe
     *  code via an observer behavior to a notifier that operates from
     *  within another thread.
     *
     *  @param notifier the notifier that sent the notification
     *  @param eventid the unique event id for an event
     *  @param eventdata optional notifier defined user data
     */
    virtual void OnPumpedNotify( CNotifier* notifier                 ,
                                 const CEvent& eventid               ,
                                 CICloneable* eventdata = GUCEF_NULL );

    private:

    CTSGObserver m_tsgObserver;
    MT::CMutex m_dataLock;
};

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------*/

#endif /* GUCEF_CORE_CTSGNOTIFIER_H  ? */
