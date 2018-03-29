//  Created by Marie-Lou Barbier on 29/01/2018.

#ifndef VectorImageExcerpt_hpp
#define VectorImageExcerpt_hpp

enum excerptApplication {
    EXCERPT_SHAPE,
    EXCERPT_BEZIER
};

#include "Elements/Vector/VectorImage.hpp"

class VectorImageExcerpt
{
public:

    VectorImageExcerpt(VectorImage * srcVecImg) : m_sourceVectorImage(srcVecImg) {}
	

    /**
	 Call getter of the corresponding excerpt type
     Sets the values of excpert end/begin

	 @param application (Bezier or Shape) enum type on which the function should apply
	 */
    VectorImage * getExcerpt(const excerptApplication &application);

    /**
	 Call replacement function of the corresponding excerpt type
	 */
    VectorImage * replaceExcerpt(VectorImage * excerptVector, const excerptApplication &application);

    VectorImage * getSourceImageWithoutExcerpt();

	~VectorImageExcerpt() {};

private:
    uint m_excerptBegin;
    uint m_excerptEnd;
    uint m_shapeIndex;
    excerptApplication m_excerptType;
    VectorImage * m_sourceVectorImage;


	/**
	 Apply Shape transformations on excerpt and return it as a new VectorImage
	 */
	VectorImage * getShapeExcerpt();

	/**
	 Apply Bezier transformations on excerpt and return it as a new VectorImage
	 */
	VectorImage * getBezierExcerpt();

	VectorImage * replaceExcerptBezier(VectorImage * excerpt);
	VectorImage * replaceExcerptShape(VectorImage * excerpt);
};

#endif /* VectorImageExcerpt_hpp */
