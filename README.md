# Carrot-Fantasy-by-cocos2dx
程设期末项目：用cocos2dx实现游戏《保卫萝卜》
组员：李子凝 王成威 陈凌凡


由于代码大小限制，本仓库只提交项目源码对应的Classes文件夹与Resources文件夹，分别用来存储代码实现和对应素材。

本项目代码使用方式：

1，用cocos2dx搭建环境；
2，cmd中调用 cocos new Carrot_Fantasy -l cpp来创建新项目；
3，在创建的项目的proj.win32目录下，用cmd调用cmake .. -G"Visual Studio 17 2022" -AWin32来创建vs项目；
4，将本仓库的Classes和Resources覆盖原文件目录下的对应文件夹；
5，在proj.win32目录下找到对应的.sln文件，打开，设置启动项目，调试运行即可。


/*更新说明*/
在实际运行中发现，实际程序会根据Resources文件夹里的内容在proj.win32/bin/Carrot_Fantasy/Debug/目录下重新创建一个Resources文件夹。
所以每次更新Resources文件，请再将其覆盖proj.win32/bin/Carrot_Fantasy/Debug/目录下的Resources文件以保证正常使用。

/*再更新说明*/
由于Classes文件中不断加入新的.cpp和.h文件，使用时需要在覆盖文件夹后，在项目的Calsses分类中手动添加已有项目，再运行。

/*再再更新说明*/
由于本游戏存档设置为D:/Carrot Fantasy/Carrot_Fantasy/proj.win32内，所以建议创建新项目时严格遵守路径创建。或在AppDelegate.cpp中，将文档路径设置为自己的对应的proj.win32内以实现对应功能。