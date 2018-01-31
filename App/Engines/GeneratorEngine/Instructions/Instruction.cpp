//
//  Instruction.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "Instruction.hpp"

std::string Instruction::getSourceName() const
{
	switch(m_instructionSource)
	{
		case INSTRUCTION_SOURCE_PATHS : return "Traces"; break;
		case INSTRUCTION_SOURCE_SHAPES : return "Formes"; break;
	}
}

std::string Instruction::getSourcePrefix() const
{
	switch(m_instructionSource)
	{
		case INSTRUCTION_SOURCE_PATHS : return "des "; break;
		case INSTRUCTION_SOURCE_SHAPES : return "des "; break;
	}
}

std::string Instruction::getTypeName() const
{
	switch(m_instructionProperty)
	{
		case INSTRUCTION_PROPERTY_ORDER : return "Ordre"; break;
		case INSTRUCTION_PROPERTY_GEOMETRY : return "Geometrie"; break;
	}
}

std::string Instruction::getTypePrefix() const
{
	switch(m_instructionProperty)
	{
		case INSTRUCTION_PROPERTY_ORDER : return "l'"; break;
		case INSTRUCTION_PROPERTY_GEOMETRY : return "de la "; break;
	}
}

std::string Instruction::getFullName() const
{
	return getAction() + " " + getTypePrefix() + getTypeName() + " " + getSourcePrefix() + getSourceName();
}
