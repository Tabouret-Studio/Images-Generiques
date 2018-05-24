#ifndef SVGExporter_hpp
#define SVGExporter_hpp

//Forward declaration
class VectorImage;

#include "Elements/Vector/Bezier.hpp"
#include "Elements/Vector/Shape.hpp"

/**
 Export a VectorImage as an SVG file
 */
class SVGExporter
{
public:
	/**
	 Export given vector img as an SVG

	 @param vectorImg VectorImage to export
	 @param fileName exprt filename
	 */
	void exportSVG(VectorImage * vectorImg, const std::string &fileName);


private:
	/**
	 Convert a Bezier to the SVG Path format

	 @return a string with Path format
	 */
	std::string shapeToPath(Shape &shape);

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

	/**
	 std::to_string shortcut, because, you know

	 @param val val to transliterate
	 @return int as string
	 */
	inline std::string toStr(const int &val) { return std::to_string(val); };

	std::string vec2ToString(const glm::vec2 &vec);
};

#endif /* SVGExporter_hpp */
