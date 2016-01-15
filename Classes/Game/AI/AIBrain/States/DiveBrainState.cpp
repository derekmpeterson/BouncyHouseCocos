//
//  DiveBrainState.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#include "DiveBrainState.h"
#include "../../../../Engine/AI/AIComponent.h"
#include "../../../../Engine/Animation/AnimationSystem.h"
#include "../../../../Engine/Entity/EntitySystem.h"
#include "../../../../Engine/Event/EventManager.h"
#include "../../../../Engine/GroundDetect/GroundDetectComponent.h"
#include "../../../../Engine/Locomotion/LocomotionComponent.h"
#include "../../../../Engine/Locomotion/LocomotionSystem.h"
#include "../../../../Engine/Physics/PhysicsComponent.h"
#include "../../../../Engine/Render/DebugDrawSystem.h"

DiveBrainState::DiveBrainState()
{
    m_runDir = -1.0f;
}

DiveBrainState::~DiveBrainState()
{
    
}

void DiveBrainState::Enter()
{
    LocomotionComponent* pLocomotionComponent = EntitySystem::GetInstance()->GetComponent<LocomotionComponent>( m_entityHandle );
    if ( pLocomotionComponent )
    {
        pLocomotionComponent->SetLocomotionMode( "SideScrollerLocomotionMode" );
    }
    PhysicsComponent* pPhysicsComponent = EntitySystem::GetInstance()->GetComponent<PhysicsComponent>( m_entityHandle );
    if ( pPhysicsComponent )
    {
        m_runDir = pPhysicsComponent->GetVelocity().x > 0.0f ? 1.0f : -1.0f;
    }
    
    cocos2d::Vec2 pVelocity = pPhysicsComponent->GetVelocity();
    pVelocity.y = 0.0f;
    pPhysicsComponent->SetVelocity( pVelocity );
    pPhysicsComponent->ApplyImpulse( cocos2d::Vec2( 0.0f, -2.0f * JUMP_VELOCITY ) );
    
    AnimationSystem::GetInstance()->SendEvent( m_entityHandle, "DIVE" );
}

void DiveBrainState::Exit()
{
    
}

void DiveBrainState::OnActivate()
{
    EventManager::GetInstance()->RegisterForEvent( "GroundChanged", CC_CALLBACK_1( DiveBrainState::OnGroundChangedEvent, this ), this );
}

void DiveBrainState::OnDeactivate()
{
    EventManager::GetInstance()->UnregisterForEvent( "GroundChanged", this );
}

void DiveBrainState::OnGroundChangedEvent( cocos2d::EventCustom *i_event )
{
    EntityHandle pEntityHandle = *((int*)(i_event->getUserData()));
    if ( m_entityHandle == pEntityHandle )
    {
        GroundDetectComponent* pGroundDetectComponent = EntitySystem::GetInstance()->GetComponent<GroundDetectComponent>( m_entityHandle );
        if ( pGroundDetectComponent && pGroundDetectComponent->GetOnGround() )
        {
            AIComponent* pAIComponent = EntitySystem::GetInstance()->GetComponent<AIComponent>( m_entityHandle );
            if ( pAIComponent )
            {
                if ( pAIComponent->GetBrain() )
                {
                    pAIComponent->GetBrain()->PopState();
                }
            }
        }
    }
}
