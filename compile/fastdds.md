
1.编译foonathan_memory_vendor
  fastddr库的第三方memory库，需要确定NODE_SIZE的大小，x86可以自动确定，
  但是arm平台需要先编译nodesize_dbg工具，再在arm平台上执行生成container_node_sizes_impl.hpp，将其替换掉memory目录下的container_node_sizes_impl.hpp

  linux-aarch64:
    linux--aarch64.cmake:
      set(CMAKE_CROSSCOMPILING TRUE)
      SET(CMAKE_SYSTEM_NAME Linux)
      set (CMAKE_C_COMPILER "/home/yangqi/work/3j3/prebuilts/host/gcc-linaro-6.5.0-2018.12-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-gcc")
      set (CMAKE_CXX_COMPILER "/home/yangqi/work/3j3/prebuilts/host/gcc-linaro-6.5.0-2018.12-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-g++")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
      set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    
     #compile
      mdkir build; cd build;
      /home/yangqi/work/cybert/cmake/cmake-3.16.8-Linux-x86_64/bin/cmake  -DCMAKE_TOOLCHAIN_FILE=../qnx-aarch64.cmake  -DCMAKE_INSTALL_PREFIX=./install .
      
  qnx-aarch64:
    qnx-aarch64.cmake:
        set(CMAKE_CROSSCOMPILING TRUE)
        SET(CMAKE_SYSTEM_NAME Linux)
        SET(CMAKE_SYSROOT $ENV{QNX_HOST})
        SET(CMAKE_C_COMPILER $ENV{QNX_HOST}/usr/bin/aarch64-unknown-nto-qnx7.1.0-gcc)
        SET(CMAKE_CXX_COMPILER $ENV{QNX_HOST}/usr/bin/aarch64-unknown-nto-qnx7.1.0-g++)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
     #compile
      mdkir build; cd build;
      source  /home/yangqi/work/icu/qnx/qnx710_host/qnxsdp-env.sh
      /home/yangqi/work/cybert/cmake/cmake-3.16.8-Linux-x86_64/bin/cmake  -DCMAKE_TOOLCHAIN_FILE=../qnx-aarch64.cmake  -DCMAKE_INSTALL_PREFIX=./install .. 
      
2. 编译fastdds
   linux--aarch64.cmake:
      linux--aarch64.cmake:
        set(CMAKE_CROSSCOMPILING TRUE)
        SET(CMAKE_SYSTEM_NAME Linux)
        set (CMAKE_C_COMPILER "/home/yangqi/work/3j3/prebuilts/host/gcc-linaro-6.5.0-2018.12-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-gcc")
        set (CMAKE_CXX_COMPILER "/home/yangqi/work/3j3/prebuilts/host/gcc-linaro-6.5.0-2018.12-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-g++")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
        set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
        set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
        set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
      
      #compile
      mdkir build; cd build;
      /home/yangqi/work/cybert/cmake/cmake-3.16.8-Linux-x86_64/bin/cmake  -DCMAKE_TOOLCHAIN_FILE=../linux-aarch64.cmake  -DCMAKE_INSTALL_PREFIX=./install -DCMAKE_PREFIX_PATH=/home/yangqi/work/cybert/foonathan_memory_vendor/linux-aarch64/install -DOPENSSL_INCLUDE_DIR=/home/yangqi/work/3j3/prebuilts/root/include -DOPENSSL_CRYPTO_LIBRARY=/home/yangqi/work/3j3/prebuilts/root/lib/libcrypto.so -DOPENSSL_SSL_LIBRARY=/home/yangqi/work/3j3/prebuilts/root/lib/libssl.so -DTHIRDPARTY=ON -DCOMPILE_EXAMPLES=ON ..
      
      qnx-aarch64:
        qnx-aarch64.cmake:
          set(CMAKE_CROSSCOMPILING TRUE)
          SET(CMAKE_SYSTEM_NAME Linux)
          SET(CMAKE_SYSROOT $ENV{QNX_HOST})
          set(QNX_ARCH aarch64le)
          SET(CMAKE_C_COMPILER $ENV{QNX_HOST}/usr/bin/aarch64-unknown-nto-qnx7.1.0-gcc)
          SET(CMAKE_CXX_COMPILER $ENV{QNX_HOST}/usr/bin/aarch64-unknown-nto-qnx7.1.0-g++)
          set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
          set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
          unset(CMAKE_CXX_FLAGS CACHE)
          add_definitions("-D_QNX_SOURCE -DASIO_HAS_PTHREADS")
          add_definitions("-std=c++11")
          # where is the target environment
          include_directories("${QNX_TARGET}/target/qnx7/usr/include/c++/8.3.0/")
          # search for programs in the build host directories (not necessary)
          SET(CMAKE_FIND_ROOT_PATH ${QNX_TARGET}/${QNX_ARCH})
          #SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
          #SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
          #SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
          
         #compile
          mdkir build; cd build;
          source  /home/yangqi/work/icu/qnx/qnx710_host/qnxsdp-env.sh
          /home/yangqi/work/cybert/cmake/cmake-3.16.8-Linux-x86_64/bin/cmake  -DCMAKE_TOOLCHAIN_FILE=../qnx-aarch64.cmake  -DCMAKE_INSTALL_PREFIX=./install -DCMAKE_PREFIX_PATH=/home/yangqi/work/cybert/foonathan_memory_vendor/qnx-aarch64/install -DOPENSSL_INCLUDE_DIR=/home/yangqi/work/icu/qnx/qnx710_host/target/qnx7/usr/include -DOPENSSL_CRYPTO_LIBRARY=/home/yangqi/work/icu/qnx/qnx710_host/target/qnx7/aarch64le/usr/lib/libcrypto.so -DOPENSSL_SSL_LIBRARY=/home/yangqi/work/icu/qnx/qnx710_host/target/qnx7/aarch64le/usr/lib/libssl.so -DCMAKE_SHARED_LINKER_FLAGS='-lsocket' -DTHIRDPARTY=ON -DCOMPILE_EXAMPLES=ON .. 
          # 此时编译DeadlineQoSExample会出现“-lpthread”错误，方法是将其模块下CmakeLists.txt注释#  target_link_libraries(DeadlineQoSExample pthread)
