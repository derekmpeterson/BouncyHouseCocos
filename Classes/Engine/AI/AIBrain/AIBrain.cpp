//
//  AIBrain.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#include "AIBrain.h"
#include "../AISystem.h"

AIBrain::AIBrain( EntityHandle i_entityHandle )
{
    m_entityHandle = i_entityHandle;
    m_shouldPop = false;
    m_shouldPush = false;
}

AIBrain::~AIBrain()
{
    while ( m_states.size() > 0 )
    {
        AIBrainState* pState = m_states.top();
        if ( pState )
        {
            delete pState;
        }
        m_states.pop();
    }
}

void AIBrain::Update( float i_dt )
{
    if ( m_states.size() > 0 )
    {
        AIBrainState* pState = m_states.top();
        if ( pState )
        {
            pState->Update( i_dt );
        }
    }
    if ( m_shouldPop )
    {
        PerformPopState();
    }
    if ( m_shouldPush )
    {
        PerformPushState( m_pushStateName );
    }
}

void AIBrain::PopState()
{
    m_shouldPop = true;
}

void AIBrain::PushState( std::string i_stateName )
{
    m_shouldPush = true;
    m_pushStateName = i_stateName;
}

void AIBrain::PerformPopState()
{
    if ( m_states.size() > 0 )
    {
        AIBrainState* pState = m_states.top();
        if ( pState )
        {
            pState->OnDeactivate();
            pState->Exit();
            delete pState;
        }
        m_states.pop();
    }
    if ( m_states.size() > 0 )
    {
        AIBrainState* pState = m_states.top();
        if ( pState )
        {
            pState->OnActivate();
        }
    }
    m_shouldPop = false;
}

void AIBrain::PerformPushState( std::string i_stateName )
{
    if ( m_states.size() > 0 )
    {
        AIBrainState* pState = m_states.top();
        if ( pState )
        {
            pState->OnDeactivate();
        }
    }
    AIBrainState* pState = AISystem::GetInstance()->CreateBrainState( i_stateName );
    ASSERTS( pState, "AIBrain state not found" );
    if ( pState )
    {
        pState->Init( m_entityHandle );
        pState->Enter();
        pState->OnActivate();
        m_states.push( pState );
    }
    m_shouldPush = false;
}