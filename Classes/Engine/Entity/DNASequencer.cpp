//
//  DNASequencer.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/29/15.
//
//
#include <fstream>

#include "cocos2d.h"
#include "../../Libraries/rapidjson/document.h"

#include "DNASequencer.h"
#include "EntitySystem.h"

Entity* DNASequencer::CreateEntity( std::string i_dnaPath )
{
    Entity* pEntity = EntitySystem::GetInstance()->CreateEntity();
    
    std::string fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename( i_dnaPath );
    std::string pFileData = cocos2d::FileUtils::getInstance()->getStringFromFile( fullPath );

    rapidjson::Document pDocument;
    pDocument.Parse<rapidjson::kParseStopWhenDoneFlag>( pFileData.c_str() );
    ASSERTS(!pDocument.HasParseError(), "DNA parse error!");
    
    
    pEntity->SetName( pDocument["Name"].GetString() );
    //printf( "Creating Entity '%s'\n", pEntity->GetName().c_str() );
    
    for (rapidjson::Value::ConstMemberIterator itr = pDocument["Components"].MemberBegin();
         itr != pDocument["Components"].MemberEnd(); ++itr)
    {
        //printf( "  Attaching component %s\n", itr->name.GetString() );
        
        if ( itr->value.GetType() == rapidjson::Type::kObjectType )
        {
            EntitySystem::GetInstance()->AttachAndInitComponent( pEntity->m_entityHandle, itr->name.GetString(), itr->value );
        }
    }
    
    if ( pEntity->m_components.find( "PhysicsComponent" ) != pEntity->m_components.end() )
    {
        Component* pPhysicsComponent = pEntity->m_components.at( "PhysicsComponent" );
        if ( pPhysicsComponent )
        {
            //printf( "  Activating component PhysicsComponent\n" );
            pPhysicsComponent->Activate();
        }
    }
    if ( pEntity->m_components.find( "RenderComponent" ) != pEntity->m_components.end() )
    {
        Component* pRenderComponent = pEntity->m_components.at( "RenderComponent" );
        if ( pRenderComponent )
        {
            //printf( "  Activating component RenderComponent\n" );
            pRenderComponent->Activate();
        }
    }
    
    for ( std::map<std::string, Component*>::iterator it = pEntity->m_components.begin(); it != pEntity->m_components.end(); it++ )
    {
        if ( strcmp( it->first.c_str(), "PhysicsComponent" ) == 0 || strcmp( it->first.c_str(), "RenderComponent" ) == 0 )
        {
            continue;
        }
        //printf( "  Activating component %s\n", it->first.c_str() );
        
        it->second->Activate();
    }
    
    
    return pEntity;
}

uint32_t DNASequencer::CreateCollisionCategory( const rapidjson::Value& i_dnaObject )
{
    uint32_t pCategory = 0;
    bool first = true;
    for ( rapidjson::Value::ConstValueIterator itr = i_dnaObject.Begin(); itr != i_dnaObject.End(); ++itr )
    {
        if ( first )
        {
            pCategory = PhysicsSystem::GetInstance()->GetCollisionCategory( itr->GetString() );
            first = false;
        }
        else
        {
            pCategory |= PhysicsSystem::GetInstance()->GetCollisionCategory( itr->GetString() );
        }
    }
    return pCategory;
}
