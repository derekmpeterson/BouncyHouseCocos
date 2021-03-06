//
//  Component.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//

#ifndef Component_hpp
#define Component_hpp

#include <stdio.h>

#include "../../Libraries/rapidjson/document.h"

#include "../TypeDefs.h"

class Component
{
private:
    bool m_active;
public:
    static std::string s_componentType;
    
    EntityHandle m_entityHandle;
    
    Component() {};
    virtual ~Component() {};
    
    virtual void Init( EntityHandle i_entityHandle ) {};
    virtual void DNADataInit( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject ) {};
    void Activate() { m_active = true; OnActivate(); };
    void Deactivate() { OnDeactivate(); };
    virtual void OnActivate() { };
    virtual void OnDeactivate() { };
    
    virtual void Update( float i_dt ) { };
};

#endif /* Component_hpp */
