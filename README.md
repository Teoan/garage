# 基于粤嵌ARM6818开发板的智能车库

## 介绍
设计并开发了一个简易的智能车库系统，使用的硬件有粤嵌的rfid射频模块、2000AF V2摄像头、zigbee协议栈、粤嵌ARM6818开发板，使用的软件和开源库有v4l2、opencv图像处理、Easypr车牌识别、Qt、VM虚拟机、使用Qt利用开源库开发一个拥有可以自动计费、识别车牌、检测温度、身份验证功能的智能车库。

## 目录文件解释

| 名字                                  | 解释                                    |
| ------------------------------------- | --------------------------------------- |
| garage                                | 项目目录                                |
| EasyPR_arm.zip                        | 交叉编译后的EasyPR                      |
| libfcitxplatforminputcontextplugin.so | Qt中文字库插件，解决Qt输入中文问题      |
| opencv-3.2.0_ARM.tar                  | 交叉编译后的opencv                      |
| Qt-5.5.0-gec2015.11.tar.gz            | 交叉编译后的Qt，可生成ARM板上的执行文件 |

## 注意
本项目所使用的交叉编译工具为**gcc-linaro-5.4.1-2017.05-i686_arm-linux-gnueabi**

