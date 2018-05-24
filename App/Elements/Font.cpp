//
//  Font.cpp
//  IMACMAN
//
//  Created by Valentin Dufois on 28/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "Font.hpp"

#include "Utils/SDL.hpp"
#include "Utils/ShaderProgram.hpp"
#include "Engines/RenderEngine/RenderEngine.hpp"

#include "Vector/Bezier.hpp"
#include "Vector/Shape.hpp"
#include "Vector/VectorImage.hpp"

#include "Utils/FontOutliner.hpp"

#include "Mesh.hpp"

Font::Font(FT_Face &face): Asset(FONT), m_face(face)
{
	if(Font::m_program == nullptr)
		m_program = new ShaderProgram("main.vs.glsl", "textRenderer.fs.glsl");

	if(Font::m_textDisplayProgram == nullptr)
		m_textDisplayProgram = new ShaderProgram("main.vs.glsl", "textPrinter.fs.glsl");
}

bool Font::sizeIsLoaded(const float &fontSize)
{
	if(m_sizedFaces.find(fontSize) != m_sizedFaces.end())
		return true; //Size is already loaded

	return false;
}

void Font::loadSize(const float &fontSize)
{
	if(fontSize < 1.0)
		throw std::runtime_error("A font cannot be generated if its size is under 1px");

	if(sizeIsLoaded(fontSize))
		return;

	//Create the sized face and store its height
	FontFace sizedFace;
	sizedFace.size = fontSize;

	FT_Set_Pixel_Sizes(m_face, 0, fontSize);

	//Store its values
	storeSizedFont(sizedFace);

	m_sizedFaces.insert(std::pair<float, FontFace>(fontSize, sizedFace));
}

void Font::storeSizedFont(FontFace &sizedFace)
{
	//Disable GL Alignement
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//Store all ASCII chars
	FT_ULong  charcode;
	FT_UInt   glyphIndex;

	charcode = FT_Get_First_Char(m_face, &glyphIndex);
	while(glyphIndex != 0 )
	{
		sizedFace.chars.insert(std::pair<FT_ULong, FontCharacter>(charcode,genFontCharacter(charcode)));
		charcode = FT_Get_Next_Char(m_face, charcode, &glyphIndex);
	}

	//Re-Enable GL Alignement
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

Mesh * Font::genCaption(const std::u16string &caption, const float &fontSize)
{
	FontFace * fontFace = getSizedFace(fontSize);

	//Gather informations for rendering
	uint textureWidth = 0;
	uint textureHeight = fontFace->size * 2;

	//Get texture width
	for(FT_ULong c : caption)
		textureWidth += fontFace->chars[c].advance;

	FontCharacter lastChar = fontFace->chars[caption[caption.size()-1]];
	textureWidth -= lastChar.advance;
	textureWidth += lastChar.bearing.x + lastChar.size.x;

	//generate the frameBuffer & texture
	GLuint frameBuffer;
	GLuint texture;
	prepareTexture(textureWidth, textureHeight, frameBuffer, texture);

	//Bind framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glm::vec4 externClearColor = App->renderEngine->getClearColor();
	App->renderEngine->setClearColor(glm::vec4(0.0, 0.0, 0.0, 0.0));

	glClear(GL_COLOR_BUFFER_BIT);

	//Set projection to 2D
	App->renderEngine->setProjection2D(textureWidth, textureHeight);

	Mesh * charMesh;
	uint advanceX = 0;
	FontCharacter fChar;

	for(const FT_ULong c : caption)
	{
		fChar = fontFace->chars[c];

		charMesh = App->ressourcesEngine->gen2DTile(0, 0, fChar.size.x, fChar.size.y);

		charMesh->getCursor()->reset();
		charMesh->getCursor()->translate(advanceX + fChar.bearing.x + fChar.size.x / 2.0,			//X
										 fontFace->size - fChar.size.y / 2 - fChar.bboxMin.y,	    //Y
										 0)->scale(fChar.size.x, fChar.size.y, 1);					//Scale

		charMesh->setProgram(m_program);
		charMesh->setTexture(fChar.texture);
		charMesh->generate();

		//Render char
		charMesh->render();

		//advance
		advanceX += fChar.advance;

		delete charMesh;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &frameBuffer);

	App->renderEngine->setClearColor(externClearColor);

	Mesh * mesh = App->ressourcesEngine->gen2DTile(0, 0, textureWidth, textureHeight);
	mesh->setTexture(texture, true);
	mesh->getCursor()->scale(1, -1, 1);
	mesh->applyCursor();
	mesh->setProgram(Font::m_textDisplayProgram);
	mesh->setColor(glm::vec4(0, 0, 0, 1));

	return mesh;
}

FontFace * Font::getSizedFace(const float &fontSize)
{
	if(!sizeIsLoaded(fontSize))
		loadSize(fontSize);

	return &m_sizedFaces[fontSize];
}

FontCharacter Font::genFontCharacter(FT_ULong charID)
{
	GLuint texture;
	FontCharacter character;

	/*Load glyph*/
	FT_Load_Char(m_face, charID, FT_LOAD_RENDER);

	/*Generate texture with the glyph*/
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 GL_RGBA,
				 m_face->glyph->bitmap.width,
				 m_face->glyph->bitmap.rows,
				 0,
				 GL_RED,
				 GL_UNSIGNED_BYTE,
				 m_face->glyph->bitmap.buffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/*Set texture options*/
	glBindTexture(GL_TEXTURE_2D, 0); /*Leave the texture*/

	FT_BBox bbox;
	FT_Glyph glyph;

	FT_Get_Glyph(m_face->glyph, &glyph);
	FT_Glyph_Get_CBox(glyph, FT_GLYPH_BBOX_PIXELS, &bbox);


	character.texture = texture;

	character.size.x = m_face->glyph->bitmap.width;
	character.size.y = m_face->glyph->bitmap.rows;

	character.bearing.x = m_face->glyph->bitmap_left;
	character.bearing.y = m_face->glyph->bitmap_top;

	character.advance = (uint)m_face->glyph->advance.x >> 6;

	character.bboxMin = glm::vec2(bbox.xMin, bbox.yMin);
	character.bboxMax = glm::vec2(bbox.xMax, bbox.yMax);

	FT_Done_Glyph(glyph);

	return character;
}

bool Font::prepareTexture(const uint &width, const uint &height, GLuint &frameBuffer, GLuint &texture)
{
	GLuint format = GL_RGBA;

	//generate the frameBuffer
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	//Generate and bind the texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, 0);

	//filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//Link texture to framebuffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, DrawBuffers);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}

VectorImage * Font::genOutlines(const std::u16string &caption)
{
	VectorImage * captionImage = new VectorImage();

	float advanceX = 0;

	for(const FT_ULong c : caption)
	{
		FT_Load_Glyph(m_face, FT_Get_Char_Index(m_face, (FT_ULong)c), FT_LOAD_NO_SCALE | FT_LOAD_NO_BITMAP);
		FT_GlyphSlot slot = m_face->glyph;

		Shape letterShape = genCharacterOutline(c);
		letterShape.getCursor()->translate(advanceX, 0, 0);

		advanceX += slot->advance.x;

		*captionImage << letterShape;
	}

	captionImage->applyCursor();

	//Center on origin
	captionImage->getCursor()->translate(-captionImage->getDimensions().x / 2.0, captionImage->getDimensions().y / 2.0, 0);

	return captionImage;
}

Shape Font::genCharacterOutline(FT_ULong charID)
{
	//Load glyph

	FT_GlyphSlot slot = m_face->glyph;
	FT_Outline &outline = slot->outline;

	//Check outline
	if (slot->format != FT_GLYPH_FORMAT_OUTLINE)
		return Shape(); // Not outline wtf.

	if (outline.n_contours <= 0 || outline.n_points <= 0)
		return Shape(); // Empty letter

	if(FT_Outline_Check(&outline) != 0)
		return Shape(); // FT said no

	//Flip glyph vertically
	const FT_Fixed multiplier = 65536L;
	FT_Matrix matrix;

	matrix.xx = 1L * multiplier;
	matrix.xy = 0L * multiplier;
	matrix.yx = 0L * multiplier;
	matrix.yy = -1L * multiplier;

	FT_Outline_Transform(&outline, &matrix);

	FT_Outline_Funcs callbacks;

	callbacks.move_to = FontOutliner::MoveToFunction;
	callbacks.line_to = FontOutliner::LineToFunction;
	callbacks.conic_to = FontOutliner::ConicToFunction;
	callbacks.cubic_to = FontOutliner::CubicToFunction;

	callbacks.shift = 0;
	callbacks.delta = 0;

	FontOutliner outliner;

	FT_Error error = FT_Outline_Decompose(&outline, &callbacks, &outliner);
	if(error != 0)
	{
		std::cerr << "An error occured while outlining the letter " << charID << "." << std::endl;
		return Shape(); //Error on outlining, skip this letter
	}

	return outliner.m_letterShape;
}

void Font::freeFontSize(const float &fontSize)
{
	if(!sizeIsLoaded(fontSize))
		return;

	FontFace * faceToRemove = getSizedFace(fontSize);

	for(std::pair<FT_ULong, FontCharacter> fChar : faceToRemove->chars)
		glDeleteTextures(1, &fChar.second.texture);

	faceToRemove->chars.clear();

	m_sizedFaces.erase(fontSize);
}

Font::~Font()
{
	//Free loaded sizes
	for(std::map<float, FontFace>::iterator sizedFace = m_sizedFaces.begin(); sizedFace != m_sizedFaces.end(); ++sizedFace)
		freeFontSize(sizedFace->first);

	//Free the face
	FT_Done_Face(m_face);
}

//Load shader program
ShaderProgram * Font::m_program = nullptr;
ShaderProgram * Font::m_textDisplayProgram = nullptr;
