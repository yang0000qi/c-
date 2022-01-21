#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include<fstream>
#include <chrono>
#include <thread>
#include <string>
#include <iostream>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include<unistd.h>
#include<fcntl.h>

using std::this_thread::sleep_for;
using std::istringstream;


   bool startProcess(std::string &name, std::string &info, bool con = false)
    {
        FILE *ptr;
        size_t len = 0;
        char* c_line = NULL;
        std::string cmd = name;
        if((ptr=popen(cmd.c_str(), "r")) != NULL) {
            if (con) {
                while ((getline(&c_line, &len, ptr)) != -1) {
                    std::string line(c_line);
                    info += line;
                }
            }
            pclose(ptr);
            ptr = NULL;
        } else {
            printf("start Process '%s' failed\n", cmd.c_str());
            return false;
        }

        return true;
    }


int main(int argc, char* argv[])
{
    if (argc != 5) {
      std::cout << "please input: ./test source destination times" << std::endl;
    }
    std::string src = argv[1];
    std::string dest = argv[2];
    int times = atoi(argv[3]);
    
    if(access(src.c_str(), F_OK) != -1) {
       std::cout << "access file " << src << " is exist" << std::endl;
    } else {
       std::cout << "access file " << src << " is not exist" << std::endl;
       return -1;
    }

    
    int time = 1;
    while(time < times) {
     std::cout << "******** test " << time << " ********" << std::endl;
     std::string dest_temp = dest;
     dest_temp.append(std::to_string(time));
     std::string info{};
     std::string cmd = "cp ";
     cmd.append(src);       
     cmd.append(" ");       
     cmd.append(dest_temp);
     std::cout << "cmd: " << cmd << std::endl;       
     // 1. cp file
     if (!startProcess(cmd, info, false)) return -1;
     if(access(dest_temp.c_str(), F_OK) != -1) {
       std::cout << "access dest path " << dest_temp << " is exist. cp success" << std::endl;
     } else {
       std::cout << "access dest path " << dest_temp << " is not exist. cp failed" << std::endl;
       return -1;
     }
     
      std::string info1{};
      std::string cmd1 = "ls -al ";
      cmd1.append(dest_temp);
      if (startProcess(cmd1, info1, true)) {
         std::cout << "check file: " << info1 << std::endl;
       }

     // 2. remove file
      int ret = remove(dest_temp.c_str());
      if (ret == 0) {
         std::cout << "remove file " << dest_temp << " success" << std::endl;
         std::string info2{};
         //3. check file again . it will be "NO such..."
         std::cout << "check file " << dest_temp << std::endl;;
         std::cout << std::endl;
         std::string cmd2 = "ls -al ";
         cmd2.append(dest_temp);
         if (startProcess(cmd2, info2, true)) {
             std::cout << info2 << std::endl;
          }


         int check_times = 100;
         while(check_times-- > 0) {
           // check file again, ERROR
           if(access(dest_temp.c_str(), F_OK) == 0) {
              std::cout << "access file " << dest_temp << " is exist. remove failed" << std::endl;
              std::cout << "---------------------------" << time << "-----------------------" << std::endl;
              std::string info3{};
              std::string cmd3 = "ls -al ";
              cmd3.append(dest_temp);
              if (startProcess(cmd3, info3, true)) {
                std::cout << "check file: " << info3 << std::endl;
              }
              return -1;
           }
           sleep_for(std::chrono::milliseconds(1));// 1ms
         }

      } else {
         std::cout << "remove file " << dest_temp << " failed ret ="  << ret << std::endl;
          break;
      }


      std::cout << "******** test " << time << " ******** pass" << std::endl;
      std::cout << std::endl;
      std::cout << std::endl;
      time++;
}
    return 0;
}
