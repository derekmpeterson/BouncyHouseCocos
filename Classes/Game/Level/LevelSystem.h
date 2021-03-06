//
//  LevelSystem.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/4/15.
//
//

#ifndef LevelSystem_hpp
#define LevelSystem_hpp

#include "Level.h"
#include "../../Engine/System/System.h"
class LevelSystem : public System
{
public:
    static LevelSystem* GetInstance();
    static void DestroyInstance();
    
    void Update( float i_dt );
    Level* GetLevel() { return m_level; };
    void StartLevel( Level* i_level );
    
private:
    static LevelSystem* s_instance;
    Level* m_level;
};

#endif /* LevelSystem_hpp */
