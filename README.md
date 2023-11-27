# Carrot-Fantasy-by-cocos2dx
程设期末项目：用cocos2dx实现游戏《保卫萝卜》
组员：李子凝 王成威 陈凌凡


由于代码大小限制，本仓库只提交项目源码对应的classes文件夹与sources文件夹，分别用来存储代码实现和对应素材。

本项目代码使用方式：

1，用cocos2dx搭建环境；
2，cmd中调用 cocos new filename -l cpp来创建新项目（filename是对应项目名称）；
3，在创建的项目的proj.win32目录下，用cmd调用cmake .. -G"Visual Studio 17 2022" -AWin32来创建vs项目；
4，将本仓库的classes和resources覆盖原文件目录下的对应文件夹；
5，在proj.win32目录下找到对应的.sln文件，打开，设置启动项目，调试运行即可。
