#include <fstream>
#include "manifest.hpp"
#include "exception.hpp"


using std::string;
using std::list;
using std::ifstream;


namespace radium {


list<string> parseManifestFile(const string& path) {
  ifstream fin(path);

  if (!fin.is_open() || !fin.good()) {
    fin.close();
    EXCEPTION("Error opening file '" << path << "'");
  }

  list<string> libs;

  string line;
  while (std::getline(fin, line)) {
    libs.push_back(line);
  }

  fin.close();

  return libs;
}


}
