#ifndef WYLIBH
#define WYLIBH

#define WYLIB_VERSION  "1.1.4"
//包含通用公共函数单元
#include "CommFunc.h"
#pragma comment(lib, "wycommon.lib")

//包含zlib压缩库
#ifdef  USE_WY_ZLIB    //包含zlib打包文件格式单元
#include "ZLIBEX.hpp"
//连接文件
#pragma comment(lib, "zlibex.lib")
#endif

#endif