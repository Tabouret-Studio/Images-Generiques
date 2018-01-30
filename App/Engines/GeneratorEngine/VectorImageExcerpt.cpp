//  Created by Marie-Lou Barbier on 29/01/2018.

#include "VectorImageExcerpt.hpp"
#include "Utils/Utils.hpp"


void VectorImageExcerpt::getExcerpt(const excerptApplication &application) {
    
    switch(application) {
        case EXCERPT_SHAPE :
            getBezierExcerpt();
            return;
            break;
        case EXCERPT_BEZIER :
            getShapeExcerpt();
            return;
            break;
    }
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

    Shape * shapeExcerpt = new Shape(excerptBeziers);
    shapeExcerpt->getCursor()->setMatrix(*m_sourceVectorImage->getShapes()[m_shapeIndex].getCursor());
    
    VectorImage * excerptVectorImage = new VectorImage(excerptBeziers);
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