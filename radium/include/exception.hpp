#ifndef RADIUM_EXCEPTION_HPP
#define RADIUM_EXCEPTION_HPP


#include <stdexcept>
#include <sstream>


#define EXCEPTION(msg) \
  { \
    std::stringstream ss; \
    ss << msg; \
    throw radium::Exception(ss.str()); \
  }


namespace radium {


class Exception : public std::runtime_error {
  public:
    Exception(const std::string& msg)
      : runtime_error(msg) {}
};


}


#endif
