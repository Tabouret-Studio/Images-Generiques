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

	static Instruction * get();
	static Instruction * get(const std::string &scriptName);

	std::vector<VectorImage *> execute(std::vector<VectorImage *> vectorImages);

private:

	PythonInstruction() {};

	std::string m_scriptName;

	void runInstruction();

	void exportInput(std::vector<VectorImage *> vectorImages);
	std::vector<VectorImage *> importOutput();

	void cleanup();
};

#endif /* PythonInstruction_hpp */
