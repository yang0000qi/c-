#include <dlfcn.h>
#include <memory>
#include <mutex>
#include <string>
#include <iostream>

typedef enum {
  QS_SUCCESS = 0,
  /// Permission denied
  QS_PERM = 1,
  /// Try again
  QS_AGAIN = 2,
  /// Not enough memory
  QS_NOMEM = 3,
} QStatus;


typedef QStatus (*qaicGetAicVersion_t)(uint16_t *major, uint16_t *minor,
                 const char **patch, const char **variant);
typedef QStatus (*qaicGetDeviceInfo_t)(int device, char *devInfo);
typedef QStatus (*qaicGetResourceInfo_t)(int device,
                                         char *resourceInfo);

typedef struct {
  qaicGetAicVersion_t qaicGetAicVersion;
  qaicGetDeviceInfo_t qaicGetDeviceInfo;
  qaicGetResourceInfo_t qaicGetResourceInfo;
} QAicApiFunctionTable;

typedef const QAicApiFunctionTable *(*qaicGetFunctionTable_t)();


using namespace std;

int main()
{
  const char *customLibPath_;
  void *libraryHandle_;
  static constexpr const char *aicLibName_ = "libQAic.so";
  const QAicApiFunctionTable *aicApi_;


  qaicGetFunctionTable_t qaicGetFunctionTable;

  const char *customLibPath = std::getenv("QAIC_LIB");
  if (customLibPath != nullptr) {
    auto libPath = std::string(customLibPath);
    std::cout << "loading " << customLibPath << std::endl;
    libraryHandle_ = dlopen(libPath.c_str(), RTLD_LAZY);
  } else {
    libraryHandle_ = dlopen(aicLibName_, RTLD_LAZY);
  }

  qaicGetFunctionTable =
      (qaicGetFunctionTable_t)dlsym(libraryHandle_, "qaicGetFunctionTable");

  if (!qaicGetFunctionTable) {
    std::cerr << "Failed to get Function table " << std::endl;
    return false;
  }

  aicApi_ = qaicGetFunctionTable();

  return 0;
}
