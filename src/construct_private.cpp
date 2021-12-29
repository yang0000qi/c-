#include <iostream>
#include <memory>
#include <string>

class ProfileHandle;
using shProfileHandle = std::shared_ptr<ProfileHandle>;

class ProfileHandle {
public:
    static shProfileHandle
    Factory(int index) {
        shProfileHandle obj = shProfileHandle(
	    new (std::nothrow) ProfileHandle(index));
	if (!obj) return nullptr;

	return obj;
    }
private:
    ProfileHandle(const ProfileHandle &); // Disable Copy Constructor
    ProfileHandle &operator=(const ProfileHandle &); // Disable Assignment Operator
    ProfileHandle(int index) {
        std::cout << "construct ProfileHandle() index " << index << std::endl;
    }
};

int main()
{
    shProfileHandle handle1_ = ProfileHandle::Factory(1);
    shProfileHandle handle2_ = ProfileHandle::Factory(2);

    return 0;
}
