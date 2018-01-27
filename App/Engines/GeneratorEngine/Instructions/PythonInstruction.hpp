//
//  PythonInstruction.hpp
//  Xcode
//
//  Created by Valentin Dufois on 22/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef PythonInstruction_hpp
#define PythonInstruction_hpp

#include "Instruction.hpp"

class PythonInstruction: public Instruction
{
public:

	/**
	 Return the instruction built for the given python instruction

	 @param scriptName Name of the python script without extension and path
	 @return The newly created instruction
	 */
	static Instruction * get(const std::string &scriptName);
	static Instruction * get();

	/**
	 Execute the python instruction

	 @param vectorImages Input vectors
	 @return Output vectors
	 */
	std::vector<VectorImage *> execute(const std::vector<VectorImage *> &vectorImages);

private:

	PythonInstruction() {};

	std::string m_scriptName;

	/**
	 Execute the python instruction
	 */
	void runInstruction();

	/**
	 Export inputs vector to the python script

	 @param vectorImages Vectors to export
	 */
	void exportInput(std::vector<VectorImage *> vectorImages);

	/**
	 Import the script outputs

	 @return The newly modified vectors
	 */
	std::vector<VectorImage *> importOutput();

	/**
	 Remove bridge files
	 */
	void cleanup();
};

#endif /* PythonInstruction_hpp */
