#ifndef RADIUM_VERSION_HPP
#define RADIUM_VERSION_HPP


#include <ostream>


namespace radium {


class Version {
  public:
    Version()
      : major{0}, minor{0} {}

    Version(int major, int minor)
      : major{major}, minor{minor} {}

    int major;
    int minor;

    bool operator<(const Version& rhs) const {
      return (major < rhs.major) || (major == rhs.major && minor < rhs.minor);
    }

    bool operator>(const Version& rhs) const {
      return *this != rhs && !(*this <= rhs);
    }

    bool operator<=(const Version& rhs) const {
      return (major <= rhs.major) || (major == rhs.major && minor <= rhs.minor);
    }

    bool operator>=(const Version& rhs) const {
      return *this != rhs && !(*this < rhs);
    }

    bool operator==(const Version& rhs) const {
      return major == rhs.major && minor == rhs.minor;
    }

    bool operator!=(const Version& rhs) const {
      return !(*this == rhs);
    }
};

inline std::ostream& operator<<(std::ostream& out, const Version& version) {
  out << version.major << "." << version.minor;
  return out;
}


}


#endif
