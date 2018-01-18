#include "SVGExporter.hpp"
#include "Engines/RessourcesEngine/Elements/VectorImage.hpp"

void SVGExporter::exportSVG(VectorImage * vectorImg, const std::string &fileName)
{
	std::string svgText = getHeader(vectorImg->getWidth(), vectorImg->getHeight());
	for(Shape shape : vectorImg->getShapes())
	{
		svgText += shapeToPath(shape);
	}

	svgText += getFooter();
	std::cout << svgText << std::endl;
}



std::string SVGExporter::shapeToPath(const Shape &shape)
{
	std::string path = "<path d=\"";

	for(Bezier bez : shape.getPaths())
	{
		bez.applyCursor();

		std::string startPoint = vec2ToString(bez.getStartPoint());
		std::string startHandle = vec2ToString(bez.getStartHandle());
		std::string endHandle = vec2ToString(bez.getEndHandle());
		std::string endPoint = vec2ToString(bez.getEndPoint());

		path += "M"+startPoint+" C "+startHandle+" "+endHandle+" "+endPoint+" ";
	}

	path += "Z\"/>";

	return path;
}

std::string SVGExporter::getHeader(const int &width, const int &height)
{
	std::string svgWidth = std::to_string(width);
	std::string svgHeight = std::to_string(height);
	std::string svgHeader = "<svg height=\""+svgHeight+"\" width=\""+svgWidth+"\" xmlns=\"http://www.w3.org/2000/svg\">";
	std::cout << svgHeader << std::endl;

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
