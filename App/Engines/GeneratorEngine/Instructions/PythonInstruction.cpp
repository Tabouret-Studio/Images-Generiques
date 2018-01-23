//
//  PythonInstruction.cpp
//  Xcode
//
//  Created by Valentin Dufois on 22/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "PythonInstruction.hpp"

#include "Core/AppObject.hpp"
#include "Engines/RessourcesEngine/Exporters/VectorImagesToJSONExporter.hpp"
#include "Engines/RessourcesEngine/Importers/JSONToVectorImagesImporter.hpp"

#include <Python.h>
#include <fstream>
#include <cstdio>

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
	//Export input
	exportInput(vectorImages);

	//Export vector images
	exportInput(vectorImages);

	//Execute instruction
	runInstruction();

	//Import vector images
	vectorImages = importOutput();

	//Erase bridge files
	cleanup();

	return vectorImages;
}

void PythonInstruction::runInstruction()
{
	//Build paths
	std::string scriptFileName = m_scriptName + ".py";
	std::string scriptPath = App->getAppPath() + "assets/instructions/" + scriptFileName;

	char *cstr = new char[scriptPath.length() + 1];
	char *cstr2 = new char[2];
	strcpy(cstr, scriptPath.c_str());
	strcpy(cstr2, "r");

	Py_Initialize();

	//Execute instruction
	std::cout << scriptPath << std::endl;
	PyObject* PyFileObject = PyFile_FromString(cstr, cstr2);
	PyRun_SimpleFileEx(PyFile_AsFile(PyFileObject), cstr, 1);

	Py_Finalize();

	delete[] cstr;
	delete[] cstr2;
}

void PythonInstruction::exportInput(std::vector<VectorImage *> vectorImages)
{
	VectorImagesToJSONExporter exporter;
	exporter.exportJSON(vectorImages, "assets/instructions/input");

	//Create both input & output file to allow for pass-through content if needed
	exporter.exportJSON(vectorImages, "assets/instructions/output");
}

std::vector<VectorImage *> PythonInstruction::importOutput()
{
	JSONToVectorImagesImporter importer;
	return importer.import("assets/instructions/output");
}

void PythonInstruction::cleanup()
{
	std::string input = App->getAppPath() + "assets/instructions/input.json";
	std::remove(input.c_str());

	std::string output = App->getAppPath() + "assets/instructions/output.json";
	std::remove(output.c_str());
}
