//
//  RenderEngine.hpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 09/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef RenderEngine_hpp
#define RenderEngine_hpp

#include <iostream>
#include <glimac/SDLWindowManager.hpp>

class RenderEngine
{
public:
    /**
     Create the RenderEngine Singleton in the AppObject
     */
    static void instanciate();
    
    /**
     Init OpenGL/SDL/etc. and create the window
     */
    void init();

	void swapBuffers();

	void pollEvents();
    
private:
    //Singleton
    static bool m_instanciated;
    RenderEngine();

	glimac::SDLWindowManager * m_window;
};

#endif /* RenderEngine_hpp */
