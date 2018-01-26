#include "SVGExporter.hpp"
#include "Elements/Vector/VectorImage.hpp"
#include <fstream>
#include <string>
#include "Core/AppObject.hpp"

void SVGExporter::exportSVG(const VectorImage * vectorImg, const std::string &fileName)
{
	std::ofstream f;
	std::string filePath = App->getAppPath()+fileName+".svg";
	f.open(filePath);

	if(!f.is_open())
	{
		throw std::runtime_error("Unable to create file "+fileName);
	}

	f << getHeader(vectorImg->getWidth(), vectorImg->getHeight());

	for(Shape shape : vectorImg->getShapes())
	{
		shape.getCursor()->translate(vectorImg->getWidth()/2, vectorImg->getHeight()/2, 0);
		shape.applyCursor();
		f << shapeToPath(shape);
	}

	f << getFooter();
	
	f.close();
}



std::string SVGExporter::shapeToPath(const Shape &shape)
{
	glm::vec3 lastPoint = shape.getPaths()[0].getStartPoint() + glm::vec3(1);

	std::string path = "<path d=\"";

	for(Bezier bez : shape.getPaths())
	{
		bez.applyCursor();

		std::string startPoint = vec2ToString(bez.getStartPoint());
		std::string startHandle = vec2ToString(bez.getStartHandle());
		std::string endHandle = vec2ToString(bez.getEndHandle());
		std::string endPoint = vec2ToString(bez.getEndPoint());

		if(lastPoint != bez.getStartPoint())
			path += "M"+startPoint;

		path += " C "+startHandle+" "+endHandle+" "+endPoint+" ";
		lastPoint = bez.getEndPoint();
	}

	path += "Z\"/>\n";

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
