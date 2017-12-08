//
//  AppEngine.hpp
//  Music Composer
//
//  Created by Valentin Dufois on 24/11/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef AppEngine_hpp
#define AppEngine_hpp

//The engine
class AppEngine
{
public:
	/**
	 Create the AppEngine Singleton in the AppObject
	 */
	static void instanciate();

private:
	//Singleton
	static bool m_instanciated;
	AppEngine();


};

#endif /* AppEngine_hpp */
