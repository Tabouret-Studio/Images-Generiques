//
//  PythonInstruction.cpp
//  Xcode
//
//  Created by Valentin Dufois on 22/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "PythonInstruction.hpp"

#include <Python.h>
#include <fstream>

Instruction * PythonInstruction::get()
{
	throw std::runtime_error("The PythonInstruction method must be called with a python script name as argument.");
	return nullptr;
}

Instruction * PythonInstruction::get(const std::string &scriptName)
{
	PythonInstruction * instruction = new PythonInstruction();
	instruction->m_scriptName = scriptName;

	return instruction;
}

std::vector<VectorImage *> PythonInstruction::execute(std::vector<VectorImage *> vectorImages)
{
	std::vector<Bezier> paths = vectorImages[0]->getBeziers();
	std::string scriptFileName = m_scriptName + ".py";
	std::string scriptPath = "assets/instructions/" + scriptFileName;

	//Export vector images
	//TODO

	//Import script
	FILE * scriptFile = fopen(scriptPath.c_str(), "r");

	Py_Initialize();

	//Execute script
	PyRun_AnyFile(scriptFile, scriptFileName.c_str());

	Py_Finalize();

	//Import vector images
	//TODO

	return vectorImages;
}
