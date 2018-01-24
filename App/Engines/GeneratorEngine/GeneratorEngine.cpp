
	boost::filesystem::path instructionsFolder = App->getAppPath() + "assets/instructions/";

	boost::filesystem::path scriptPath;
	std::string scriptName;

	if(!boost::filesystem::exists(instructionsFolder))
		return; //No folder, nothing to iterate

	std::vector<boost::filesystem::directory_entry> entries;
	std::copy(boost::filesystem::directory_iterator(instructionsFolder), boost::filesystem::directory_iterator(), std::back_inserter(entries));

	for(std::vector<boost::filesystem::directory_entry>::const_iterator entry = entries.begin(); entry != entries.end(); ++entry)
	{
		scriptPath = (*entry).path();

		if(boost::filesystem::is_directory(scriptPath))
		   continue; //Ignore sub-directories (for now ?)

		if(scriptPath.filename_is_dot() || scriptPath.filename_is_dot_dot() || scriptPath.empty())
			continue; //Ignore useless entries

		if(scriptPath.extension() != ".py")
			continue; //Ignore non python script

		scriptName = scriptPath.filename().generic_string();
		scriptName = scriptName.substr(0, scriptName.length() - 3);

		registerInstruction(INSTRUCTION_PYTHON, scriptName, nullptr);
	}
}

void GeneratorEngine::registerInstruction(const instructionFormat &format, const std::string &instructionName, std::function<Instruction *(void)> loader)
{
	m_instructionsIndex.insert(std::pair<std::string, std::function<Instruction *(void)>>(instructionName, loader));
	m_instructionsFormats.insert(std::pair<std::string, instructionFormat>(instructionName, format));
}

Instruction * GeneratorEngine::getPythonInstruction(const std::string &scriptName)
{
	return PythonInstruction::get(scriptName);
}

	//Ugly conversion because Py_SetProgramName is not marked as const despite not modifying the var (thx c89)
	std::string pathToInstruction = App->getAppPath() + "assets/instructions/";
	char *cstr = new char[pathToInstruction.length() + 1];
	strcpy(cstr, pathToInstruction.c_str());

	std::cout << pathToInstruction << std::endl;

	//init Python
	Py_SetProgramName(cstr);

	//The cstr is keeped because Py needs it later --'
	//delete cstr;

	registerCPPInstructions();
	registerPythonInstructions();
	boost::filesystem::path instructionsFolder = App->getAppPath() + "assets/instructions/";

	boost::filesystem::path scriptPath;
	std::string scriptName;

	if(!boost::filesystem::exists(instructionsFolder))
		return; //No folder, nothing to iterate

	std::vector<boost::filesystem::directory_entry> entries;
	std::copy(boost::filesystem::directory_iterator(instructionsFolder), boost::filesystem::directory_iterator(), std::back_inserter(entries));

	for(std::vector<boost::filesystem::directory_entry>::const_iterator entry = entries.begin(); entry != entries.end(); ++entry)
	{
		scriptPath = (*entry).path();

		if(boost::filesystem::is_directory(scriptPath))
		   continue; //Ignore sub-directories (for now ?)

		if(scriptPath.filename_is_dot() || scriptPath.filename_is_dot_dot() || scriptPath.empty())
			continue; //Ignore useless entries

		if(scriptPath.extension() != ".py")
			continue; //Ignore non python script

		scriptName = scriptPath.filename().generic_string();
		scriptName = scriptName.substr(0, scriptName.length() - 3);

		registerInstruction(INSTRUCTION_PYTHON, scriptName, nullptr);
	}
}

void GeneratorEngine::registerInstruction(const instructionFormat &format, const std::string &instructionName, std::function<Instruction *(void)> loader)
{
	m_instructionsIndex.insert(std::pair<std::string, std::function<Instruction *(void)>>(instructionName, loader));
	m_instructionsFormats.insert(std::pair<std::string, instructionFormat>(instructionName, format));
}

Instruction * GeneratorEngine::getPythonInstruction(const std::string &scriptName)
{
	return PythonInstruction::get(scriptName);
}
