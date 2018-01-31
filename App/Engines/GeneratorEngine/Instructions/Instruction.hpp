//
//  Instruction.hpp
//  Images-Generiques
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef Instruction_h
#define Instruction_h

#include "../InstructionObject.hpp"
#include "../InstructionParameters.hpp"

enum instructionSource
{
	INSTRUCTION_SOURCE_PATHS,
	INSTRUCTION_SOURCE_SHAPES
};

enum instructionProperty
{
	INSTRUCTION_PROPERTY_ORDER,
	INSTRUCTION_PROPERTY_GEOMETRY
};

/**
 An Instruction uses one or more VectorImage.
 It returns a new one based on modifications made with the given ones.
 Each instruction is independant and can be used in combination with any other.
 */
class Instruction: public InstructionObject
{
public:
	/**
	 Return the instruction properly instaciated

	 @return The instruction
	 */
	static Instruction * get();

	/**
	 Execute the instruction with the given VectorImage

	 @param vectorImages The VectorImage to use
	 @return A new, transformed VectorImage
	 */
	virtual std::vector<VectorImage *> execute(const std::vector<VectorImage *> &vectorImages) = 0;

	/**
	 Set the parameters to use when executing

	 @param parameters An InstructionParameters object
	 */
	inline void setParameters(InstructionParameters * parameters) { m_parameters = parameters; };

	/**
	 Return the parameters object used by the instruction

	 @return An InstructionParameters object
	 */
	inline InstructionParameters *  getParameters() { return m_parameters; };

	/**
	 Default destructor
	 Erase the parameters
	 */
	virtual ~Instruction()
	{
		if(m_parameters != nullptr)
			delete m_parameters;
	};

	/////////////////////////
	//Naming & classification

	/**
	 Get the source of the instruction

	 @return PATHS or SHAPES
	 */
	instructionSource inline getSource() const { return m_instructionSource; };

	/**
	 Get the name of the source

	 @return Name of the source
	 */
	std::string getSourceName() const;

	/**
	 Get the source prefix for pretty-printing

	 @return The prefix
	 */
	std::string getSourcePrefix() const;

	/**
	 Get the property the instruction is working on

	 @return ORDER or GEOMETRY
	 */
	instructionProperty inline getType() const { return m_instructionProperty; };

	/**
	 Get the name of the type

	 @return The type name
	 */
	std::string getTypeName() const;

	/**
	 Get the type prefix for pretty printing

	 @return The prefix
	 */
	std::string getTypePrefix() const;

	/**
	 Get the instruction name

	 @return The name
	 */
	std::string inline getAction() const { return m_instructionAction; };

	/**
	 Return the full name for pretty-printing

	 @return The full name
	 */
	std::string getFullName() const;

protected:
	Instruction(const instructionSource &source, const instructionProperty &property, const std::string &action):
		m_parameters(nullptr),
		m_instructionSource(source),
		m_instructionProperty(property),
		m_instructionAction(action) {};

	InstructionParameters * m_parameters;

	instructionSource m_instructionSource;
	instructionProperty m_instructionProperty;
	std::string m_instructionAction;
};

#include "PythonInstruction.hpp"

//Paths
#include "Paths/PathsOrderRandomizer.hpp"
#include "Paths/PathsChaining.hpp"
#include "Paths/PathsInvert.hpp"
#include "Paths/PathsLinearAlizer.hpp"
#include "Paths/PathsNoise.hpp"
#include "Paths/PathsOrientRandomizer.hpp"
#include "Paths/PathsSquarify.hpp"



#endif /* Instruction_h */
