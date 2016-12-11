#ifndef RADIUM_MANIFEST_HPP
#define RADIUM_MANIFEST_HPP


#include <string>
#include <list>


namespace radium {


std::list<std::string> parseManifestFile(const std::string& path);


}


#endif
