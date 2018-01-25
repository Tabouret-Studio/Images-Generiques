//  Created by Marie-Lou Barbier on 25/01/2018.


#ifndef JSONExporter_HPP
#define JSONExporter_HPP

#include "libraries.hpp"

//Forward declaration


class JSONExporter {
public:
    void exportJSON(const nlohmann::json &j, const std::string &fileName);
};

#endif /* JSONExporter_hpp */
