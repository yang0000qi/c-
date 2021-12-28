#include <iostream>
#include <exception>
#include <string>

class ExceptionInit : public std::exception
{
public:
    ExceptionInit(const std::string &msg) : msg_(std::string(baseMsg) + msg) {}
    ~ExceptionInit() = default;

    virtual const char *what() const throw() {return msg_.c_str();}
    const std::string &msg() const {return msg_;}

public:
    const std::string msg_;
    static constexpr const char *baseMsg = "Initialization Exception: ";
};

class ExceptionRuntime : public std::exception
{
public:
    ExceptionRuntime(const std::string &msg) {
        msg_ = std::string(baseMsg) + msg;
    }

    ~ExceptionRuntime() = default;
    virtual const char *what() const throw() {
        return msg_.c_str();
    }
    const std::string &msg() const {
        return msg_;
    }
private:
    std::string msg_;
    static constexpr const char *baseMsg = "Runtime Exception: ";
};

class CoreExceptionInit final : public ExceptionInit {
public:
    CoreExceptionInit(const std::string &name, const std::string &msg = "")
        : ExceptionInit(name + msg) {}
    ~CoreExceptionInit()  = default;
};

class CoreExceptionRuntime : public ExceptionRuntime {
public:
  CoreExceptionRuntime(const std::string &msg) : ExceptionRuntime(msg) {}
  ~CoreExceptionRuntime() = default;
};

class CoreExceptionNullPtr final : public CoreExceptionRuntime {
public:
  CoreExceptionNullPtr(const std::string &name)
      : CoreExceptionRuntime(name + " NullPtr") {}
  ~CoreExceptionNullPtr() = default;
};

using namespace std;

int main()
{
  std::cout << "main..." << std::endl;
  throw CoreExceptionRuntime("stop");
  std::cout << "main end" << std::endl;

  return 0;
}