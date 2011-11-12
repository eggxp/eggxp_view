/*
简体<->繁体转换类
实现简体繁体字的相互转换
作者:游勇鹏
最后更新日期: 2005.01.01
*/
#ifndef __GB2BIG_H__
  #define __GB2BIG_H__

  #ifdef __cplusplus
extern "C"
{
  #endif //__cplusplus
void    InitConvertTable();             //初始化码表,建议在项目的最开始部分加入
String  Gb2Big(String lpString);       // 简体->繁体
String  Big2GBK(String lpString);     //繁体->简体

  #ifdef __cplusplus
}
  #endif //__cplusplus
#endif __GB2BIG_H__