//
//  Font.hpp
//  IMACMAN
//
//  Created by Valentin Dufois on 28/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#ifndef Font_hpp
#define Font_hpp

//Forward Declaration
class Asset;
class ShaderProgram;

#include "libraries.hpp"
#include "Asset.hpp"

#include <iostream>
#include <vector>
#include <map>

//////////////////
//Font structures
struct FontCharacter
{
	GLuint texture;

	glm::vec2 size;
	glm::vec2 bearing;
	GLuint advance;

	glm::vec2 bboxMin;
	glm::vec2 bboxMax;
};

struct FontFace
{
	float size;
	std::vector<FontCharacter> chars;
};

/////////////
//Font class
class Font : public Asset
{
public:
	Font(FT_Face &face);

	/**
	 Tell if the given fontSize is already loaded

	 @param fontSize The font size to check
	 @return True if loaded, false otherwise
	 */
	bool sizeIsLoaded(const float &fontSize);


	/**
	 Generate the font for a specified size
	 */
	void loadSize(const float &fontSize);

	/**
	 Generate a 2D tile with the caption as its texture
	 The return Mesh has not been generated
	 If the font has not been loaded for the given size, it will be loaded

	 @param caption The text to display
	 @param fontSize The size to render the text
	 @return The tile in a mesh
	 */
	Mesh * genCaption(const std::string &caption, const float &fontSize);

	/**
	 Liberate the font for the given size if it has been generated

	 @param fontSize The font size to free
	 */
	void freeFontSize(const float &fontSize);

	~Font();

private:

	//The face
	FT_Face m_face;
	float m_size;

	//All loaded sized faces
	std::map<float, FontFace> m_sizedFaces;

	/**
	 Store glyphs and metrics for a specific size
	 */
	void storeSizedFont(FontFace &sizedFace);

	/**
	 Return a pointer to sized face for the given size
	 The font face is loaded if not available

	 @param fontSize The size to get
	 @return Pointer to the sized face
	 */
	FontFace * getSizedFace(const float &fontSize);

	/**
	 Generate and store in OpenGL the specified character

	 @param charID The character to render
	 @return The character infos
	 */
	FontCharacter genFontCharacter(char charID);

	/**
	 Prepare a texture to hold up caption generation

	 @param width Width of the texture
	 @param height Height of the texture
	 @param frameBuffer Framebuffer to attach the texture to
	 @param texture TextureID generated
	 @return True on success, false otherwise
	 */
	bool prepareTexture(const uint &width, const uint &height, GLuint &frameBuffer, GLuint &texture);

	/**
	 The font shaderPrograms
	 Static because they're shared by all font elements
	 */
	static ShaderProgram * m_program;
	static ShaderProgram * m_textDisplayProgram;
};

#endif /* Font_hpp */
