//
//  LocomotionComponent.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/1/15.
//
//

#ifndef LocomotionComponent_hpp
#define LocomotionComponent_hpp

#include "cocos2d.h"

#include "../Entity/Component.h"
#include "LocomotionMode.h"
#include "../TypeDefs.h"

class LocomotionComponent : public Component
{
    float m_runSpeed;
    float m_walkSpeed;
public:
    static std::string s_componentType;
    
    LocomotionComponent() {};
    virtual ~LocomotionComponent();
    
    void Init( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject );
    
    float GetRunSpeed() { return m_runSpeed; };
    void SetRunSpeed( float i_runSpeed ) { m_runSpeed = i_runSpeed; };
    float GetWalkSpeed() { return m_walkSpeed; };
    void SetWalkSpeed( float i_walkSpeed ) { m_walkSpeed = i_walkSpeed; };
    
    LocomotionMode* m_locomotionMode;
    JumpState m_jumpState;
};

#endif /* LocomotionComponent_hpp */