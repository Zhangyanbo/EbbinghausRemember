# 循环复习提醒器

## 概述

此程序存储所学习之项目的名称，以及其时间，可以手动查看当日所需复习之内容。

注意使用前需先新建一个名为`tData.csv`的空CSV文件，放在程序目录下。

## 用法简介

此程序目前极为简陋，只有命令行版本，且控制符较少，但已可满足基本之需求。下面将操作简述：

### 获取当日所需复习的内容

输入`todo`、`TODO`或`Todo`，即可获得，例子如下：

```
>> todo
dt = 0	: xxx1
dt = 0	: xxx2
dt = 2	: xxx3
```

其中，`dt`代表距今的天数，冒号之后，是名称。

### 添加计划

输入`add`，之后可以添加计划：

```
	>> add
Add	>> Naive!
```

这样就将`Naive!`作为一个当日学习的内容添加进去了，之后会自动提醒。

要输入前几日完成的学习内容，可用`adds`，例如：

```
	>> adds
name>> xxxxx
dt	>> 2
```

这样就加入了一个两日前完成的一个学习内容。

### 存储

输入`save`。

### 查看所有学习内容

输入`print`。

### 退出

输入`quite`。

