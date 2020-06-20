/*
 *  gucefCORE: GUCEF module providing O/S abstraction and generic solutions
 *  Copyright (C) 2002 - 2008.  Dinand Vanvelzen
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

#ifndef GUCEF_MT_DVMTOSWRAP_H
#include "gucefMT_dvmtoswrap.h"         /* OS wrappers for threading functionality */
#define GUCEF_MT_DVMTOSWRAP_H
#endif /* GUCEF_MT_DVMTOSWRAP_H ? */

#ifndef GUCEF_CORE_CTRACER_H
#include "CTracer.h"
#define GUCEF_CORE_CTRACER_H
#endif /* GUCEF_CORE_CTRACER_H ? */

#ifndef GUCEF_CORE_CTASKMANAGER_H
#include "gucefCORE_CTaskManager.h"
#define GUCEF_CORE_CTASKMANAGER_H
#endif /* GUCEF_CORE_CTASKMANAGER_H ? */

#include "gucefCORE_CTaskDelegator.h"

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

const CEvent CTaskDelegator::ThreadKilledEvent = "GUCEF::CORE::CTaskDelegator::ThreadKilledEvent";
const CEvent CTaskDelegator::ThreadStartedEvent = "GUCEF::CORE::CTaskDelegator::ThreadStartedEvent";
const CEvent CTaskDelegator::ThreadPausedEvent = "GUCEF::CORE::CTaskDelegator::ThreadPausedEvent";
const CEvent CTaskDelegator::ThreadResumedEvent = "GUCEF::CORE::CTaskDelegator::ThreadResumedEvent";
const CEvent CTaskDelegator::ThreadFinishedEvent = "GUCEF::CORE::CTaskDelegator::ThreadFinishedEvent";

/*-------------------------------------------------------------------------//
//                                                                         //
//      UTILITIES                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

void
CTaskDelegator::RegisterEvents( void )
{GUCEF_TRACE;

    ThreadKilledEvent.Initialize();
    ThreadStartedEvent.Initialize();
    ThreadPausedEvent.Initialize();
    ThreadResumedEvent.Initialize();
    ThreadFinishedEvent.Initialize();
}

/*-------------------------------------------------------------------------*/

CTaskDelegator::CTaskDelegator( void )
    : MT::CActiveObject()    
    , CNotifier()   
    , CIPulseGeneratorDriver()         
    , m_pulseGenerator()     
    , m_taskConsumer( GUCEF_NULL )
    , m_immediatePulseTickets( 0 )
    , m_immediatePulseTicketMax( 1 )
{GUCEF_TRACE;

    RegisterEvents();

    m_pulseGenerator.SetPulseGeneratorDriver( this );

    CCoreGlobal::Instance()->GetTaskManager().RegisterTaskDelegator( *this );
}

/*-------------------------------------------------------------------------*/

CTaskDelegator::~CTaskDelegator()
{GUCEF_TRACE;

    CCoreGlobal::Instance()->GetTaskManager().UnregisterTaskDelegator( *this );
}

/*-------------------------------------------------------------------------*/

CPulseGenerator&
CTaskDelegator::GetPulseGenerator( void )
{GUCEF_TRACE;

    return m_pulseGenerator;
}

/*-------------------------------------------------------------------------*/

void
CTaskDelegator::RequestImmediatePulse( CPulseGenerator& pulseGenerator ) 
{GUCEF_TRACE;
       
    if ( &pulseGenerator == &m_pulseGenerator )
    {
        m_immediatePulseTickets = m_immediatePulseTicketMax;
    }
}

/*-------------------------------------------------------------------------*/

void 
CTaskDelegator::RequestPulsesPerImmediatePulseRequest( CPulseGenerator& pulseGenerator                     ,
                                                       const Int32 requestedPulsesPerImmediatePulseRequest )
{GUCEF_TRACE;

    if ( &pulseGenerator == &m_pulseGenerator )
    {
        if ( requestedPulsesPerImmediatePulseRequest > 1 )
            m_immediatePulseTicketMax = requestedPulsesPerImmediatePulseRequest;
        else
            m_immediatePulseTicketMax = 1;
    }
}

/*-------------------------------------------------------------------------*/

void
CTaskDelegator::RequestPeriodicPulses( CPulseGenerator& pulseGenerator    ,
                                       const UInt32 pulseDeltaInMilliSecs )

{GUCEF_TRACE;

    if ( &pulseGenerator == &m_pulseGenerator )
    {
        m_delayInMilliSecs = pulseDeltaInMilliSecs;
        Resume();
    }
}

/*-------------------------------------------------------------------------*/

void
CTaskDelegator::RequestPulseInterval( CPulseGenerator& pulseGenerator    ,
                                      const UInt32 pulseDeltaInMilliSecs )
{GUCEF_TRACE;

    if ( &pulseGenerator == &m_pulseGenerator )
    {
        m_delayInMilliSecs = pulseDeltaInMilliSecs;
    }
}

/*-------------------------------------------------------------------------*/

void
CTaskDelegator::RequestStopOfPeriodicUpdates( CPulseGenerator& pulseGenerator )
{GUCEF_TRACE;

    if ( &pulseGenerator == &m_pulseGenerator )
    {
        Pause( false );
    }
}

/*-------------------------------------------------------------------------*/

bool
CTaskDelegator::OnThreadStart( void* taskdata )
{GUCEF_TRACE;

    NotifyObservers( ThreadStartedEvent );
    return true;
}

/*-------------------------------------------------------------------------*/

void
CTaskDelegator::OnThreadStarted( void* taskdata )
{GUCEF_TRACE;

}

/*-------------------------------------------------------------------------*/

void
CTaskDelegator::TaskCleanup( CTaskConsumer* taskConsumer ,
                             CICloneable* taskData       )
{GUCEF_TRACE;

    CCoreGlobal::Instance()->GetTaskManager().TaskCleanup( taskConsumer ,
                                                           taskData     );

    m_taskConsumer = GUCEF_NULL;
}

/*-------------------------------------------------------------------------*/

bool
CTaskDelegator::OnThreadCycle( void* taskdata )
{GUCEF_TRACE;

    CICloneable* taskData = GUCEF_NULL;

    if ( CCoreGlobal::Instance()->GetTaskManager().GetQueuedTask( &m_taskConsumer ,
                                                                  &taskData       ) )
    {
        ProcessTask( *m_taskConsumer ,
                     taskData        );

        TaskCleanup( m_taskConsumer ,
                     taskData       );
        m_taskConsumer = GUCEF_NULL;
    }

    // Return false, this is an infinate task processing thread
    return false;
}

/*-------------------------------------------------------------------------*/

bool
CTaskDelegator::ProcessTask( CTaskConsumer& taskConsumer ,
                             CICloneable* taskData       )
{GUCEF_TRACE;

    bool returnStatus = false;

    // first establish the bi-directional link
    // this delegator is going to be the one to execute this task
    taskConsumer.SetTaskDelegator( this );

    // Now we go through the execution sequence within a cycle as if this
    // where a thread sequence
    m_consumerBusy = true;
    if ( taskConsumer.OnTaskStart( taskData ) )
    {
        taskConsumer.OnTaskStarted( taskData );

        // cycle the task as long as it is not "done"
        while ( !IsDeactivationRequested() && !taskConsumer.OnTaskCycle( taskData ) ) 
        {
            SendDriverPulse( m_pulseGenerator );
            if ( m_immediatePulseTickets > 0 )
            {
                --m_immediatePulseTickets;
            }
            else
            {
                m_pulseGenerator.WaitTillNextPulseWindow( m_minimalCycleDeltaInMilliSecs );
            }
        }

        taskConsumer.OnTaskEnd( taskData );
        taskConsumer.OnTaskEnded( taskData, false );
        returnStatus = true;
    }
    else
    {
        taskConsumer.OnTaskStartupFailed( taskData );
    }
    m_consumerBusy = false;
    return returnStatus;
}

/*-------------------------------------------------------------------------*/

void
CTaskDelegator::OnThreadEnd( void* taskdata )
{GUCEF_TRACE;

    // if we get here and the m_consumerBusy flag is set then the task was killed
    // and we did not finish whatever the consumer was doing gracefully
    // We should give the consume a chance to cleanup
    if ( m_consumerBusy )
    {
        if ( NULL != m_taskConsumer )
        {
            m_taskConsumer->OnTaskEnd( static_cast< CICloneable* >( taskdata ) );
        }
    }
}

/*-------------------------------------------------------------------------*/

void
CTaskDelegator::OnThreadPausedForcibly( void* taskdata )
{GUCEF_TRACE;

    if ( m_consumerBusy )
    {
        if ( NULL != m_taskConsumer )
        {
            m_taskConsumer->OnTaskPaused( static_cast< CICloneable* >( taskdata ), true );
        }
    }
}

/*-------------------------------------------------------------------------*/

void
CTaskDelegator::OnThreadResumed( void* taskdata )
{GUCEF_TRACE;

    if ( m_consumerBusy )
    {
        if ( NULL != m_taskConsumer )
        {
            m_taskConsumer->OnTaskResumed( static_cast< CICloneable* >( taskdata ) );
        }
    }
}

/*-------------------------------------------------------------------------*/

void
CTaskDelegator::OnThreadEnded( void* taskdata ,
                               bool forced    )
{GUCEF_TRACE;

    // if we get here and the m_consumerBusy flag is set then the task was killed
    // and we did not finish whatever the consumer was doing gracefully
    // We should give the consume a chance to cleanup
    if ( m_consumerBusy )
    {
        if ( NULL != m_taskConsumer )
        {
            m_taskConsumer->OnTaskEnded( static_cast< CICloneable* >( taskdata ), true );
        }
    }
}

/*-------------------------------------------------------------------------*/

CTaskConsumer*
CTaskDelegator::GetTaskConsumer( void )
{GUCEF_TRACE;

    return m_taskConsumer;
}

/*-------------------------------------------------------------------------*/

bool
CTaskDelegator::Lock( void ) const
{GUCEF_TRACE;

    return MT::CActiveObject::Lock();
}

/*-------------------------------------------------------------------------*/

bool
CTaskDelegator::Unlock( void ) const
{GUCEF_TRACE;

    return MT::CActiveObject::Unlock();
}

/*-------------------------------------------------------------------------//
//                                                                         //
//      NAMESPACE                                                          //
//                                                                         //
//-------------------------------------------------------------------------*/

}; /* namespace CORE */
}; /* namespace GUCEF */

/*-------------------------------------------------------------------------*/
