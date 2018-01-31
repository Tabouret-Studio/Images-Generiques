//  Created by Marie-Lou Barbier on 29/01/2018.

#include "VectorImageExcerpt.hpp"
#include "Utils/Utils.hpp"

VectorImage * VectorImageExcerpt::getExcerpt(const excerptApplication &application)
{
    switch(application) {
        case EXCERPT_SHAPE :
            return getShapeExcerpt();
            break;
        case EXCERPT_BEZIER :
            return getBezierExcerpt();
            break;
    }
    
    return nullptr;
}
    
VectorImage * VectorImageExcerpt::getBezierExcerpt()
{
	//Select shape
	m_shapeIndex = Utils::rand((int)m_sourceVectorImage->getShapes()->size());

	if(m_shapeIndex >= m_sourceVectorImage->getShapes()->size())
		m_shapeIndex -= 1;

	//Get reference to selected shape
	Shape * selectedShape = &(*m_sourceVectorImage->getShapes())[m_shapeIndex];

	//Select excerpt range
    m_excerptBegin = Utils::rand((int)selectedShape->getPaths()->size());

	if(m_excerptBegin >= selectedShape->getPaths()->size())
		m_excerptBegin -= 1;

    m_excerptEnd = m_excerptBegin + Utils::rand((int)selectedShape->getPaths()->size() - m_excerptBegin);

	//Extract beziers according to interval
	Shape shapeExcerpt;
	shapeExcerpt.getCursor()->setMatrix(selectedShape->getCursor()->getMatrix());

    for(std::vector<Bezier>::iterator it = selectedShape->getPaths()->begin() + m_excerptBegin;
        it != (selectedShape->getPaths()->begin() + m_excerptEnd); ++it)
    {
        shapeExcerpt << *it;
    }

	//Generate excerpt vector image
    VectorImage * excerptVectorImage = new VectorImage(shapeExcerpt);
    excerptVectorImage->getCursor()->setMatrix(*m_sourceVectorImage->getCursor());

    return excerptVectorImage;
}



VectorImage * VectorImageExcerpt::getShapeExcerpt()
{
	//Select excerpt range
	m_excerptBegin = Utils::rand((int)m_sourceVectorImage->getShapes()->size());

	if(m_excerptBegin >= m_sourceVectorImage->getShapes()->size())
		m_excerptBegin -= 1;

    m_excerptEnd = m_excerptBegin + Utils::rand((int)m_sourceVectorImage->getShapes()->size() - m_excerptBegin);

	VectorImage * excerptVectorImage = new VectorImage();
	excerptVectorImage->getCursor()->setMatrix(*m_sourceVectorImage->getCursor());

    for(std::vector<Shape>::iterator it = m_sourceVectorImage->getShapes()->begin() + m_excerptBegin;
        it != m_sourceVectorImage->getShapes()->begin() + m_excerptEnd; ++it)
    {
        *excerptVectorImage << *it;
    }

    return excerptVectorImage;
}


VectorImage * VectorImageExcerpt::replaceExcerpt(VectorImage * excerptVector, const excerptApplication &application)
{
    switch(application) {
        case EXCERPT_SHAPE :
            return replaceExcerptShape(excerptVector);;
            break;
        case EXCERPT_BEZIER :
            return replaceExcerptBezier(excerptVector);;
            break;
    }

    return nullptr;
}


VectorImage * VectorImageExcerpt::replaceExcerptBezier(VectorImage * excerpt)
{
	//Gather source & excerpt paths
    std::vector<Bezier> * srcPaths = (*m_sourceVectorImage->getShapes())[m_shapeIndex].getPaths();
	std::vector<Bezier> * excerptPaths = (*excerpt->getShapes())[0].getPaths();

	//Create empty shape
	Shape newShape;
	newShape.getCursor()->setMatrix((*m_sourceVectorImage->getShapes())[m_shapeIndex].getCursor()->getMatrix());

	//Fill shape with merged beziers from source & excerpt
    newShape.getPaths()->insert(newShape.getPaths()->end(), srcPaths->begin(), srcPaths->begin() + m_excerptBegin);
	newShape.getPaths()->insert(newShape.getPaths()->end(), excerptPaths->begin(), excerptPaths->end());
	newShape.getPaths()->insert(newShape.getPaths()->end(), srcPaths->begin() + m_excerptEnd, srcPaths->end());

	//Replace shape in source image (and making copy)
	VectorImage * m_updatedVecorImage = new VectorImage(m_sourceVectorImage);
    (*m_updatedVecorImage->getShapes())[m_shapeIndex] = newShape;

    return m_updatedVecorImage;
}

VectorImage * VectorImageExcerpt::replaceExcerptShape(VectorImage * excerpt)
{
	std::vector<Shape> * srcShapes = m_sourceVectorImage->getShapes();
	std::vector<Shape> * excerptShapes = excerpt->getShapes();

	//Create an empty vector image
	VectorImage * vectorImageMerged = new VectorImage();
	vectorImageMerged->getCursor()->setMatrix(m_sourceVectorImage->getCursor()->getMatrix());

    vectorImageMerged->getShapes()->insert(vectorImageMerged->getShapes()->end(), srcShapes->begin(), srcShapes->begin() + m_excerptBegin);
    vectorImageMerged->getShapes()->insert(vectorImageMerged->getShapes()->end(), excerptShapes->begin(), excerptShapes->end());
    vectorImageMerged->getShapes()->insert(vectorImageMerged->getShapes()->end(), srcShapes->begin() + m_excerptEnd, srcShapes->end());

    return vectorImageMerged;
}
