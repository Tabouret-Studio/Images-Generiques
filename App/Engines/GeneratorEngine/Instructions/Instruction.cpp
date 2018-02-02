//
//  Instruction.cpp
//  Xcode
//
//  Created by Valentin Dufois on 19/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#include "Instruction.hpp"

std::u16string Instruction::getSourceName() const
{
	switch(m_instructionSource)
	{
		case INSTRUCTION_SOURCE_PATHS : return u"tracés"; break;
		case INSTRUCTION_SOURCE_SHAPES : return u"formes"; break;
	}
}

std::u16string Instruction::getSourcePrefix() const
{
	switch(m_instructionSource)
	{
		case INSTRUCTION_SOURCE_PATHS : return u"des "; break;
		case INSTRUCTION_SOURCE_SHAPES : return u"des "; break;
	}
}

std::u16string Instruction::getTypeName() const
{
	switch(m_instructionProperty)
	{
		case INSTRUCTION_PROPERTY_ORDER : return u"ordre"; break;
		case INSTRUCTION_PROPERTY_GEOMETRY : return u"géometrie"; break;
		case INSTRUCTION_PROPERTY_SCATTER : return u"diffusion"; break;
	}
}

std::u16string Instruction::getTypePrefix() const
{
	switch(m_instructionProperty)
	{
		case INSTRUCTION_PROPERTY_ORDER : return u"l'"; break;
		case INSTRUCTION_PROPERTY_GEOMETRY : return u"la "; break;
		case INSTRUCTION_PROPERTY_SCATTER : return u"la "; break;
	}
}

std::u16string Instruction::getFullName() const
{
	return getAction() + u" " + getTypePrefix() + getTypeName() + u" " + getSourcePrefix() + getSourceName();
}
