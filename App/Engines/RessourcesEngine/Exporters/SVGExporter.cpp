#include "SVGExporter.hpp"
#include "Elements/Vector/VectorImage.hpp"
#include <fstream>
#include <string>
#include "Core/AppObject.hpp"

void SVGExporter::exportSVG(VectorImage * vectorImg, const std::string &fileName)
{
	std::ofstream f;
	std::string filePath = App->getAppPath()+fileName+".svg";
	f.open(filePath);

	if(!f.is_open())
	{
		throw std::runtime_error("Unable to create file "+fileName);
	}

	f << getHeader(1200, 850);

	VectorImage * workingCopy = new VectorImage(vectorImg);
	workingCopy->applyCursor();

	float scaleFactor = std::min(1200 / workingCopy->getDimensions().x, 850 / workingCopy->getDimensions().y) * .8;

	for(Shape shape : *vectorImg->getShapes())
	{
		shape.applyCursor();
		shape.getCursor()->translate(600, 425, 0)->scale(scaleFactor, scaleFactor, scaleFactor);
		shape.applyCursor();
		f << shapeToPath(shape);
	}

	delete workingCopy;

	f << getFooter();

	f.close();
}



std::string SVGExporter::shapeToPath(Shape &shape)
{
	glm::vec3 lastPoint = (*shape.getPaths())[0].getStartPoint() + glm::vec3(1);

	std::string path = "<path fill=\"none\" stroke=\"black\" d=\"";

	for(Bezier bez : *shape.getPaths())
	{
		bez.applyCursor();

		//precent saving corrupted points
		//Should not happen but you never know
		if(bez.getStartPoint().x == -2E+5 ||
		   bez.getStartPoint().y == -2E+5 ||
		   bez.getStartHandle().x == -2E+5 ||
		   bez.getStartHandle().y == -2E+5 ||
		   bez.getEndHandle().x == -2E+5 ||
		   bez.getEndHandle().y == -2E+5 ||
		   bez.getEndPoint().x == -2E+5 ||
		   bez.getEndPoint().y == -2E+5)
			continue; //Ignore corrupted points

		std::string startPoint = vec2ToString(glm::vec2(bez.getStartPoint().x, bez.getStartPoint().y));
		std::string startHandle = vec2ToString(glm::vec2(bez.getStartHandle().x, bez.getStartHandle().y));
		std::string endHandle = vec2ToString(glm::vec2(bez.getEndHandle().x, bez.getEndHandle().y));
		std::string endPoint = vec2ToString(glm::vec2(bez.getEndPoint().x, bez.getEndPoint().y));

		if(lastPoint != bez.getStartPoint())
			path += "M"+startPoint;

		path += " C "+startHandle+" "+endHandle+" "+endPoint+" ";
		lastPoint = bez.getEndPoint();
	}

	path += "\"/>\n";

	return path;
}

std::string SVGExporter::getHeader(const int &width, const int &height)
{
	std::string svgWidth = std::to_string(width);
	std::string svgHeight = std::to_string(height);
	std::string svgHeader = "<svg height=\""+svgHeight+"\" width=\""+svgWidth+"\" xmlns=\"http://www.w3.org/2000/svg\">";

	return svgHeader;
}

std::string SVGExporter::getFooter()
{
	std::string svgFooter = "</svg>";

	return svgFooter;
}

std::string SVGExporter::vec2ToString(const glm::vec2 &vec)
{
	return toStr(vec.x)+" "+toStr(vec.y);
}
