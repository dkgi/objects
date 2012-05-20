#ifndef OBJECTS_LOG_H_
#define OBJECTS_LOG_H_

#include <iostream>

namespace objects {

enum LogLevel {Info, Debug, Warning, Error};

/**
  * This class provides the basic loging facilities.
  */
class Log {
 public:
  static std::ostream& info() {
    return std::cout << "INFO: ";
  }

  static std::ostream& debug() {
    return std::cout << "DEBUG: ";
  }

 private:
  Log() {}
  virtual ~Log() {}
};

}

#endif // OBJECTS_LOG_H_

