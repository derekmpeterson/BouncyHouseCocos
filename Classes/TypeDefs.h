//
//  TypeDefs.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//

#ifndef TypeDefs_hpp
#define TypeDefs_hpp

#include <stdio.h>

typedef int EntityHandle;

// TODO: Somehow we need to be defining these up in game, not in the engine
enum CollisionCategory : uint32_t
{
    None = 0,
    Solid = (1 << 0),
    Player = (1 << 1),
    Enemy = (1 << 2),
    All = INT_MAX
};

enum ActionTag : int
{
    AnimationAction
};


#endif /* TypeDefs_hpp */
