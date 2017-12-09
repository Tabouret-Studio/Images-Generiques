//
//  GameEngine.cpp
//  Music Composer
//
//  Created by Valentin Dufois on 24/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "../../main.hpp"

bool AppEngine::m_instanciated = false;

/**
 * Instanciate the engine as a Singleton
 */
void AppEngine::instanciate()
{
    if(m_instanciated)
        return;
    
    App->appEngine = new AppEngine();
    
    m_instanciated = true;
}

AppEngine::AppEngine() {};
