# RenderingOutline

这是我进行渲染学习的一个大纲，之后可能会补上一些图形学相关算法或技术的伪代码。这个大纲基本是参考[技术美术百人计划](https://docs.qq.com/doc/DUFdKZE1oVFd3ZlBs)，同时补充上一些通俗且尽量简短的、同时至少我自己日后还能看懂的解释。尽量不会使用图片，保证所有知识点的"Why, What, How"都能在文字上解释清楚，即为什么会出现这种技术，这种技术的主要内容，这种技术的实现。
斜体字表示待补充的内容。

## 渲染的一些参考资料

最容易入门的图形学教程：[LearnOpenGL CN](https://learnopengl-cn.github.io/)

图形学孔子闫令琪老师：[GAMES101-现代计算机图形学入门](https://www.bilibili.com/video/BV1X7411F744)和[GAMES202-高质量实时渲染](https://www.bilibili.com/video/BV1YK4y1T7yY)

技术美术百人计划（还在更新中）：[【技术美术百人计划】前言概况介绍](https://www.bilibili.com/video/BV1oo4y1d71a)

## 第一章 基础

1.渲染管线简介
总参考：[闫令琪讲pipeline](https://www.bilibili.com/video/BV1X7411F744?p=8&t=1960)
渲染管线就是通过一系列的处理，把3D元素转换成屏幕上的2D图像的一个线性过程，它一般分为3个阶段：应用阶段、几何阶段、光栅化阶段。现在的游戏引擎还会增加一个后处理阶段。
（一）应用阶段：一般在CPU上完成，从磁盘或者内存上读取模型或者贴图数据，然后加载到应用程序里。
①准备基本场景数据：
物理变换数据：MVP变换；物理网格数据：顶点位置、UV贴图等；
光源数据：光源的类型，光源的位置、方向等其他参数，与之相对的阴影的参数设置；
摄像机数据：位置、方向、远近裁剪平面、正交/透视（FOV）、视口比例；
参考：
[LearnOpenGL讲变换](https://learnopengl-cn.github.io/01%20Getting%20started/07%20Transformations/)
[LearnOpenGL讲坐标系统](https://learnopengl-cn.github.io/01%20Getting%20started/08%20Coordinate%20Systems/)
[LearnOpenGL讲摄像机](https://learnopengl-cn.github.io/01%20Getting%20started/09%20Camera/)
②加速算法、粗粒度剔除等：
*碰撞检测*
加速算法：八叉树、BSP树、KD树、BVH包围盒等；参考：[闫令琪讲加速算法](https://www.bilibili.com/video/BV1X7411F744?p=14&t=1100)
遮挡剔除：参考：[LearnOpenGL讲面剔除](https://learnopengl-cn.github.io/04%20Advanced%20OpenGL/04%20Face%20culling/)
*其他算法*
③渲染设置：
*合批方式：比如GPU instance或者动态批处理等等*
绘制物体的顺序：比如相对于摄像机的远近来进行排序
渲染目标：输出到FrameBuffer还是到RenderTexture
渲染模式：前向渲染或者延迟渲染
④输出渲染图元到显存
## 第二章 光照基础

## 第三章 进阶应用

## 第四章 高级扩展

## 第五章 物理世界

## 第六章 卡通渲染

## 第七章 其他