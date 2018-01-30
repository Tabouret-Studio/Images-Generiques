//  Created by Marie-Lou Barbier on 29/01/2018.

#include "VectorImageExcerpt.hpp"
#include "Utils/Utils.hpp"

VectorImage * VectorImageExcerpt::getExcerpt(const excerptApplication &application) {
    switch(application) {
        case EXCERPT_SHAPE :
            return getBezierExcerpt();
            break;
        case EXCERPT_BEZIER :
            return getShapeExcerpt();
            break;
    }
    
    return nullptr;
}
    
VectorImage * VectorImageExcerpt::getBezierExcerpt() {   
    // create vector of Bezier for src and new VectorImage
    std::vector<Bezier> excerptBeziers;
    std::vector<Bezier> srcBeziers;

    m_shapeIndex = Utils::rand(m_sourceVectorImage->getShapes().size());

    // determining range of random
    srcBeziers = m_sourceVectorImage->getShapes()[m_shapeIndex].getPaths();

    m_excerptBegin = Utils::rand(srcBeziers.size());

    
    m_excerptEnd = Utils::rand(srcBeziers.size() - m_excerptBegin);
    m_excerptEnd += m_excerptBegin;

    for(std::vector<Bezier>::iterator it = srcBeziers.begin() + m_excerptBegin;
        it != srcBeziers.end() - m_excerptEnd; ++it)
    {
        excerptBeziers.push_back(*it);
    }

    Shape shapeExcerpt(excerptBeziers);
    shapeExcerpt.getCursor()->setMatrix(*m_sourceVectorImage->getShapes()[m_shapeIndex].getCursor());
    
    VectorImage * excerptVectorImage = new VectorImage(shapeExcerpt);
    excerptVectorImage->getCursor()->setMatrix(*m_sourceVectorImage->getCursor());

    return excerptVectorImage;
}



VectorImage * VectorImageExcerpt::getShapeExcerpt() {
// create vector of Shape for src and new VectorImage
    std::vector<Shape> excerptShapes;
    std::vector<Shape> srcShapes = m_sourceVectorImage->getShapes();
    
    // determining range of random
    uint srcShapeNumbers = srcShapes.size();

    m_excerptBegin = Utils::rand(srcShapeNumbers);

    
    m_excerptEnd = Utils::rand(srcShapeNumbers - m_excerptBegin);
    m_excerptEnd += m_excerptBegin;

    for(std::vector<Shape>::iterator it = srcShapes.begin() + m_excerptBegin;
        it != srcShapes.end() - m_excerptEnd; ++it)
    {
        excerptShapes.push_back(*it);
    }

    VectorImage * excerptVectorImage = new VectorImage(excerptShapes);
    excerptVectorImage->getCursor()->setMatrix(*m_sourceVectorImage->getCursor());

    return excerptVectorImage;
}


VectorImage * VectorImageExcerpt::replaceExcerpt(VectorImage * excerptVector, const excerptApplication &application) {
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


VectorImage * VectorImageExcerpt::replaceExcerptBezier(VectorImage * excerpt) {
    std::vector<Bezier> newBeziers;
    std::vector<Bezier> srcBeziers = m_sourceVectorImage->getShapes()[m_shapeIndex].getPaths();

    Shape shapeToExcerpt = excerpt->getShapes()[0];
    
    newBeziers.insert(newBeziers.end(), srcBeziers.begin(), srcBeziers.begin() + m_excerptBegin);
    newBeziers.insert(newBeziers.end(), shapeToExcerpt.getPaths().begin(), shapeToExcerpt.getPaths().end());
    newBeziers.insert(newBeziers.end(), srcBeziers.begin() + m_excerptBegin, srcBeziers.end());

    Shape newShape(newBeziers);
    newShape.getCursor()->setMatrix(m_sourceVectorImage->getShapes()[m_shapeIndex].getCursor()->getMatrix());

    m_sourceVectorImage->getShapes()[m_shapeIndex] = newShape;

    return m_sourceVectorImage;
}

VectorImage * VectorImageExcerpt::replaceExcerptShape(VectorImage * excerpt) {
    std::vector<Shape> newShapes;
    std::vector<Shape> srcShapes = m_sourceVectorImage->getShapes();

    newShapes.insert(newShapes.end(), srcShapes.begin(), srcShapes.begin() + m_excerptBegin);
    newShapes.insert(newShapes.end(), excerpt->getShapes().begin(), excerpt->getShapes().end());
    newShapes.insert(newShapes.end(), srcShapes.begin() + m_excerptBegin, srcShapes.end());

    VectorImage * vectorImageExcerptShape = new VectorImage(newShapes);
    vectorImageExcerptShape->getCursor()->setMatrix(m_sourceVectorImage->getCursor()->getMatrix());

    return vectorImageExcerptShape;
}