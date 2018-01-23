#ifndef SVGExporter_hpp
#define SVGExporter_hpp

//Forward declaration
class VectorImage;

#include "Utils/Vector/Bezier.hpp"
#include "Utils/Vector/Shape.hpp"

/**
 Export a VectorImage as an SVG file
 */
class SVGExporter
{
public:
	void exportSVG(VectorImage * vectorImg, const std::string &fileName);


private:
	/**
	 Convert a Bezier to the SVG Path format

	 @return a string with Path format
	 */
	std::string shapeToPath(const Shape &shape);

	/**
	 Initialize a SVG header tag with dimensions of the VectorImage
	 
	 @return a string with SVG header format
	 */
	std::string getHeader(const int &width, const int &height);

	/**
	 Initialize a SVG footer tag
	 
	 @return a string with SVG footer format
	 */
	std::string getFooter();

	inline std::string toStr(const int &val) { return std::to_string(val); };

	std::string vec2ToString(const glm::vec2 &vec);
};

#endif /* SVGExporter_hpp */
