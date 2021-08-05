# RenderingOutline

这是我进行渲染学习的一个大纲，之后可能会补上一些图形学相关算法或技术的（伪）代码。这个大纲基本是参考[技术美术百人计划](https://docs.qq.com/doc/DUFdKZE1oVFd3ZlBs)，同时补充上一些通俗且尽量简短的、同时至少我自己日后还能看懂的解释。尽量不会使用图片，保证所有知识点的"Why, What, How"都能在文字上解释清楚，即为什么会出现这种技术，这种技术的主要内容，这种技术的实现。

斜体字表示待学习、待补充的内容。

## 渲染的一些参考资料

最容易入门的图形学教程：[LearnOpenGL CN](https://learnopengl-cn.github.io/)

图形学孔子闫令琪老师：[GAMES101-现代计算机图形学入门](https://www.bilibili.com/video/BV1X7411F744)和[GAMES202-高质量实时渲染](https://www.bilibili.com/video/BV1YK4y1T7yY)

技术美术百人计划（还在更新中）：[【技术美术百人计划】前言概况介绍](https://www.bilibili.com/video/BV1oo4y1d71a)

## 第一章 基础

1.渲染管线简介

总参考：[闫令琪-渲染管线](https://www.bilibili.com/video/BV1X7411F744?p=8&t=1960)

渲染管线就是通过一系列的处理，把3D元素转换成屏幕上的2D图像的一个线性过程，它一般分为3个阶段：应用阶段、几何阶段、光栅化阶段。现在的游戏引擎还会增加一个后处理阶段。

（一）应用阶段：一般在CPU上完成，从磁盘或者内存上读取模型或者贴图数据，然后加载到应用程序里。

①准备基本场景数据：

物理变换数据：MVP变换；物理网格数据：顶点位置、纹理uv坐标等；
参考：
[LearnOpenGL-变换](https://learnopengl-cn.github.io/01%20Getting%20started/07%20Transformations/)

光源数据：光源的类型，光源的位置、方向等其他参数，与之相对的阴影的参数设置；

摄像机数据：位置、方向、远近裁剪平面、正交/透视（FOV）、视口比例；
参考：
[LearnOpenGL-坐标系统](https://learnopengl-cn.github.io/01%20Getting%20started/08%20Coordinate%20Systems/)、
[LearnOpenGL-摄像机](https://learnopengl-cn.github.io/01%20Getting%20started/09%20Camera/)

②加速算法、粗粒度剔除等：

*碰撞检测*

加速算法：八叉树、BSP树、KD树、BVH包围盒等；参考：[闫令琪-加速算法](https://www.bilibili.com/video/BV1X7411F744?p=14&t=1100)

*遮挡剔除*

*其他算法*

③渲染设置：

*合批方式：比如GPU instance或者动态批处理等等*

绘制物体的顺序：比如相对于摄像机的远近来进行排序，这在blending中很重要；

渲染目标：输出到FrameBuffer还是到RenderTexture；

渲染模式：前向渲染或者延迟渲染；

④输出渲染图元到显存

（二）几何阶段：顶点着色器-视图变换→（曲面细分）→（几何着色器）→投影→裁剪（正面或背面剔除）→屏幕映射；

（三）光栅化阶段：

①三角形设置与遍历：抗锯齿；

②像素着色器：插值；

③颜色混合：透明度测试，模板测试，深度测试，混合；

④目标缓冲区：FrameBuffer或RenderTexture；

（四）后处理：

Bloom（泛光）、HDR（高动态范围）；

*FXAA、DepthOfView、边缘检测、径向模糊*

2.数学基础

3.纹理介绍：纹理，纹理过滤，mipmap，cubemap，各种贴图；

4.图形API介绍：DX，OpenGL，OpenGL ES；

## 第二章 光照基础

1.颜色空间

2.模型与材质

3.基础hlsl函数介绍：参考：[HLSL内部函数](https://docs.microsoft.com/zh-cn/windows/win32/direct3dhlsl/dx-graphics-hlsl-intrinsic-functions?redirectedfrom=MSDN)

4.传统经验光照模型：除了PBR以外的光照模型；

5.BumpMap的改进：说清楚法线、视差、位移、浮雕的计算原理。

6.伽马矫正

7.LDR与HDR

8.FlowMap的实现

9.待续

## 第三章 进阶应用

1.深度与模板测试

2.混合模式及剔除

3.曲面细分着色器与几何着色器

4.延迟渲染原理介绍

5.early-Z与Z Press

6.纹理压缩

7.现代移动端的TBR和TBR渲染管线以及Cbuffer

8.DepthPeeling 深度剥离

## 第四章 高级扩展

1.Bloom算法

2.SSAO算法

3.阴影的各类实现方法

4.抗锯齿之FXAA、MSAA

5.DOF景深算法

6.运动模糊

7.雾效实现方法

8.基于屏幕空间的溶解

## 第五章 物理世界

1.PBR

2.光线追踪，路径追踪与光线投射

3.体渲染

4.体积云的生成

5.水体渲染

6.毛发模拟

7.屏幕空间反射

8.渲染加速与性能优化概述

9.皮肤渲染

## 第六章 卡通渲染

1.NPR与卡通渲染的风格流派

2.卡通渲染描边方案

3.卡通渲染着色方案

4.卡通渲染案例讲解

5.待续

## 第七章 其他

1.欧拉旋转与四元变换

2.通过法线2d渲3d的角色效果