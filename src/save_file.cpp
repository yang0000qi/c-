#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include<fstream>

using std::istringstream;

int main()
{
    std::string filepath = "./test.txt";
    std::ofstream outfile(filepath);
    std::cout << "write file: " << filepath << std::endl;
    if (!outfile.is_open()) {
        std::cout << "Failed to open " << filepath << std::endl;
        return -1;
    }

    std::stringstream ss;
    ss << "data: ";
    char data[24];
    memset(&data, 'A', sizeof(data));
    ss.write(reinterpret_cast<const char *>(&data), sizeof(data));
    std::cout << "input data: " << ss.str() << std::endl;
    outfile << ss.str();
    outfile << std::endl;
    outfile.flush();
    outfile.close();
    return 0;
}
