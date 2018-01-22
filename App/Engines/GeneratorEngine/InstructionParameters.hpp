//
//  InstructionParameters.hpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef InstructionParameters_hpp
#define InstructionParameters_hpp

#include <string>
#include <map>

/**
 List of float parameters to send to Instructions.
 @warning This is a sensible class, it will throw exception in case of bad manipulation.
 */

class InstructionParameters
{
public:

	/**
	 Create a new parameters
	 If the parameter already exists, update

	 @param paramName Name of the param
	 @param paramValue Value of parameter
	 */
	void createParam(const std::string &paramName, const float &paramValue);


	/**
	 Update the given parameter with the given value
	 Fail if the parameter does not exist

	 @param paramName Parameter to update
	 @param paramValue New value
	 */
	void updateParam(const std::string &paramName, const float &paramValue);

	/**
	 Tell if the given param name exist

	 @param paramName The param name to check
	 @return True if exist, false otherwise
	 */
	bool hasParam(const std::string &paramName);

	/**
	 Return the asked param
	 Fails if the param doesn't exist

	 @param paramName The param to return
	 @return The value of the param
	 */
	float getParam(const std::string &paramName);

	/**
	 Return all the params in the object

	 @return Map of all vectors
	 */
	inline std::map<std::string, float> getParams() { return m_parameters; };

	/**
	 Remove the given paramName from the parameters
	 Fails if the param does not exist

	 @param paramName The param to remove
	 */
	void removeParam(const std::string &paramName);

private:
	std::map<std::string, float> m_parameters;
};

#endif /* InstructionParameters_hpp */
