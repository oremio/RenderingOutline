# RenderingOutline

这是我进行渲染学习的一个大纲，之后可能会补上一些图形学相关算法或技术的（伪）代码。这个大纲基本是参考[技术美术百人计划](https://docs.qq.com/doc/DUFdKZE1oVFd3ZlBs)，同时补充上一些通俗且尽量简短的、同时至少我自己日后还能看懂的解释，保证所有知识点的"Why, What, How"都能在文字上解释清楚，即为什么会出现这种技术，这种技术的主要内容，这种技术的实现。

斜体字表示待学习、待补充的内容。

## 渲染的一些参考资料

最容易入门的图形学教程：[LearnOpenGL CN](https://learnopengl-cn.github.io/)

图形学孔子闫令琪老师：[GAMES101-现代计算机图形学入门](https://www.bilibili.com/video/BV1X7411F744)和[GAMES202-高质量实时渲染](https://www.bilibili.com/video/BV1YK4y1T7yY)

技术美术百人计划（还在更新中）：[【技术美术百人计划】前言概况介绍](https://www.bilibili.com/video/BV1oo4y1d71a)

《Real-Time Rendering》第4版

## 第一章 基础

### 1.渲染管线简介

总参考：[GAMES101-渲染管线](https://www.bilibili.com/video/BV1X7411F744?p=8&t=1960)

渲染管线就是通过一系列的处理，把3D元素转换成屏幕上的2D图像的一个线性过程，它一般分为3个阶段：应用阶段、几何阶段、光栅化阶段。现在的游戏引擎还会增加一个后处理阶段。

**（一）应用阶段：**

**一般在CPU上完成，从磁盘或者内存上读取模型或者贴图数据，然后加载到应用程序里。**

①准备基本场景数据：

物理变换数据：MVP变换；物理网格数据：顶点位置、纹理uv坐标等；

光源数据：光源的类型，光源的位置、方向等其他参数，与之相对的阴影的参数设置；

摄像机数据：位置、方向、远近裁剪平面、正交/透视（FOV）、视口比例；

②加速算法、粗粒度剔除等：

*碰撞检测*

加速算法：八叉树、BSP树、KD树、BVH包围盒等；参考：[GAMES101-加速算法](https://www.bilibili.com/video/BV1X7411F744?p=14&t=1100)

*遮挡剔除*

*其他算法*

③渲染设置：

*合批方式：比如GPU instance或者动态批处理等等*

绘制物体的顺序：比如相对于摄像机的远近来进行排序，这在blending中很重要；

渲染目标：输出到FrameBuffer还是到RenderTexture；

渲染模式：前向渲染或者延迟渲染；

④输出渲染图元到显存

**（二）几何阶段：**

**顶点着色器→视图变换→(曲面细分)→(几何着色器)→投影→裁剪(正面或背面剔除)→屏幕映射；**

**（三）光栅化阶段：**

①三角形设置与遍历：抗锯齿；

②像素着色器：插值；

③颜色混合：透明度测试，模板测试，深度测试，混合；

④目标缓冲区：FrameBuffer或RenderTexture；

**（四）后处理：**

Bloom（泛光）、HDR（高动态范围）；

*FXAA、DepthOfView、边缘检测、径向模糊*

### 2.数学基础

**微积分，线性代数，概率论**

参考：[GAMES101-线性代数复习](https://www.bilibili.com/video/BV1X7411F744?p=2)

缩放矩阵（Scale），旋转矩阵（Rotation），位移矩阵（Translation）
![三维空间中的坐标变换](https://files.catbox.moe/x5khht.png)

参考：[GAMES101-变换](https://www.bilibili.com/video/BV1X7411F744?p=3)

**Local Space—Model Matrix—>World Space—View Matirx—>View Space—Projection Matrix—>Clip Space—View Transform—>Screen Space**

**模型矩阵、世界空间：** 将模型空间的顶点变换到世界空间，先缩放后旋转再平移。

**观察矩阵、观察空间：** 根据所有物体和摄像机的相对位置进行变换。具体而言，对世界坐标先平移，再旋转，使物体处于一个摄像机在坐标原点的空间中。这一步需要摄像机的方向、上轴、右轴。

**投影矩阵、裁剪空间：** 投影分为透视投影和正交投影，我们用投影矩阵来实现，前者需要fov的值、视口宽高比、近远平面的值，后者需要左右顶底和近远平面的值。这个变换其实并不是真正的投影，它只是在为投影做准备，它以w分量作为范围值对顶点进行缩放，如果一个顶点在我们的视椎体内，那么它的x,y,z三个值都会处于-w和+w之间。

**裁剪空间之后：** GPU会做剪裁，剔除在Clip Space范围之外的顶点，然后GPU再做**透视除法**将顶点转到NDC。

参考：[GAMES101-变换](https://www.bilibili.com/video/BV1X7411F744?p=4)

### 3.纹理介绍

**为什么选择纹理？：** 牺牲一些几何细节，能够大量减少建模的工作量，存储空间需求也能减少，读取速度也能增加。

**包装模式/纹理寻址模式：** Repeat，Mirror，Clamp（拉长边缘），Border

**纹理太小：** 会显得很糊，需要双线性插值（Bilinear）、双三次插值（Bicubic）、*Qu´ılez的光滑曲线插值*；

**纹理太大：** 近处会有锯齿，远处会产生摩尔纹。需要Mipmap以及Ripmap（各向异性的Mipmap）、EWA过滤、积分图（Summed-Area Table）；

**细讲Mipmap：** 根据某一个像素点与其周围像素点的距离，可以算出其对应的纹素点与其对应的纹素点的距离，通过这个距离可以画出一个以该纹素点为中心、边长为L的正方形，那么对应的Mipmap级数就是log<sub>2</sub>L。这样就能快速查询到某一像素的颜色值，而多出来的开销仅仅是原来的三分之一！

**细讲SAT：** 一种帮助我们快速求一个范围的平均的数据结构。求一个范围的平均其实也就等同于求一个范围的和，这就可以借用前缀和的思想，可以参考leetcode上的这道题[560. 和为K的子数组](https://leetcode-cn.com/problems/subarray-sum-equals-k/)。

上面两个概念在后面第四章实现阴影的部分还会再次提到！

*CPU渲染优化常见方式：纹理图集/数组*；

*GPU渲染优化常见方式：纹理压缩*；

**纹理的应用：** 立方体贴图，光照贴图，深度贴图，凹凸贴图，视差贴图

参考：[LearnOpenGL CN-纹理](https://learnopengl-cn.github.io/01%20Getting%20started/06%20Textures/)和[GAMES101-纹理、Mipmap](https://www.bilibili.com/video/BV1X7411F744?p=9)和[GAMES202-SAT](https://www.bilibili.com/video/BV1YK4y1T7yY?p=4&t=4315)

### 4.图形API介绍

Khronos定义了OpenGL，微软定义了DirectX；

目前手机，不管是iOS还是Android，都是支持OpenGL ES；

Windows系统支持DirectX和OpenGL，Linux/Mac(Unix)系统支持OpenGL。

这两个链接可以查看对应的手机芯片支持的OpenGL ES支持的版本：
[根据芯片查GPU](https://zh.wikipedia.org/wiki/%E9%AB%98%E9%80%9A%E9%A9%8D%E9%BE%8D%E5%85%83%E4%BB%B6%E5%88%97%E8%A1%A8#Snapdragon_888)、
[根据GPU查OpenGL ES版本](https://zh.wikipedia.org/wiki/Adreno)

## 第二章 光照基础

### 1.颜色空间

我们常用的sRGB色彩空间，其构成为：

**1.色域：** sRGB首先设定了RGB三个基色的坐标；

**2.白点：** sRGB规定了白点位置；

**3.gamma：** sRGB的gamma设定为≈2.2，也就是说从外向内切，先切的很细，然后逐渐变粗。

![设备相关的RGB色彩空间](https://pic4.zhimg.com/v2-847b6a6e229101f4163b1a0c584330ff_r.jpg)

参考：[章佳杰-色彩空间基础](https://zhuanlan.zhihu.com/p/24214731)和[GAMES101-色彩与感知](https://www.bilibili.com/video/BV1X7411F744?p=20&t=2930)

### 2.模型与材质

**模型包含的信息：** 其每个顶点会包含法线，纹理坐标，顶点色等信息。

**材质：** 漫反射、镜面反射、折射、粗糙镜面反射、粗糙镜面折射、多层材质（涂了透明油漆的木地板）、次表面散射（半透明的物体。例如玉石、蜡烛、牛奶、皮肤）

**模型数据在渲染中的作用：**

1.顶点动画：在顶点着色器中，修改模型的顶点位置，进而达到模型运动的效果。

2.纹理动画：在片段着色器中，修改模型的UV信息，使得采样贴图时，发生位移而产生运动效果。

3.顶点色：在渲染时，影响输出结果，控制颜色范围。

**重心坐标：** 原理见下面的参考文章。重心坐标在图形学中最重要的运用便是插值，他可以根据三个顶点A,B,C的属性插值出任意点的属性，无论是位置，颜色，深度，法线向量等等，而这些属性在之后的着色或是消除隐藏曲面都有很大的作用。 

参考：[孙小磊-重心坐标(barycentric coordinates)详解及其作用](https://zhuanlan.zhihu.com/p/144360079)

### 3.基础hlsl函数介绍

参考：[HLSL内部函数](https://docs.microsoft.com/zh-cn/windows/win32/direct3dhlsl/dx-graphics-hlsl-intrinsic-functions?redirectedfrom=MSDN)

### 4.传统经验光照模型

按照时间轴：

1970年：Lambert漫反射模型：color = C<sub>light</sub> * albedo * dot( **normal** , **L** )

**1971年：Gourand模型：** 以顶点为单位计算光量，再通过插值得到每个像素点的光亮度。在表现物体光滑性上有比较好的表现，但值不再是线性变化的时候，比如镜面高光，由于线性插值导致内插值不可能大于顶点值。因此高光只能出现在顶点。由于使用的颜色插值，会导致镜面高光蔓延到周边。

**1975年：Phong光照模型：** C<sub>final</sub> = A<sub>light</sub> * m<sub>diffuse</sub> + C<sub>light</sub> * (m<sub>diffuse</sub> * dot(**l**, **n**) + m<sub>specular</sub> * dot(**v**, **r**)<sup>gloss</sup>)

A<sub>light</sub>：环境光量； C<sub>light</sub>：入射光量；

m<sub>diffuse</sub>：漫反射率；m<sub>specular</sub>：镜面反射率；gloss：高光度；

**l**：入射光向量（指向光源）；**n**：物体表面法线；**r**：反射光向量；

**1977年：Blinn-Phong模型：** C<sub>final</sub> = A<sub>light</sub> * m<sub>diffuse</sub> + C<sub>light</sub> * (m<sub>diffuse</sub> * dot(**l**, **n**) + m<sub>specular</sub> * dot(**h**, **n**)<sup>gloss</sup>)

**h**：半程向量；

还有一个Flat模型：平面着色模型，计算多边形的单个强度，每个三角形只有一个法线方向。以相同的光强度值显示多边形的所有点。通常适用于lowPoly风格的场景。

下面的基于物理的光照模型留到第五章~

1980年：Whitted光线追踪模型

1982年：Cook-Torrance模型（蒙特卡洛方法被引入）

1986年： Kajiya统一了光照公式（蒙特卡洛的每个随机数只产生一条路径）

参考：[LearnOpenGL CN-基础光照](https://learnopengl-cn.github.io/02%20Lighting/02%20Basic%20Lighting/)

### 5.BumpMap

**为什么选择凹凸贴图？：** 减少建模的工作量，存储空间需求也能减少。

**法线贴图：** 根据经验光照模型的原理，引入一种叫做法线贴图的纹理。 法线贴图的法线向量需要定义在**切线空间**中，我们会定义一个**TBN矩阵**， 这三个字母分别代表tangent、bitangent和normal向量，这个矩阵可以把切线坐标空间的向量转换到世界坐标空间，不过我们一般是用其逆矩阵将向量从世界空间转换到切线空间，具体原因可参考[LearnOpenGL CN-法线贴图](https://learnopengl-cn.github.io/05%20Advanced%20Lighting/04%20Normal%20Mapping/)；

**视差贴图：** 视差贴图属于位移贴图技术的一种，它会引入一种叫高度贴图（或反色高度贴图）的纹理，通过对纹理坐标进行位移来实现凹凸的效果，它会和法线贴图配合使用，保证光照能和位移相匹配。关于视差贴图的具体计算可以参考[LearnOpenGL CN-视差贴图](https://learnopengl-cn.github.io/05%20Advanced%20Lighting/05%20Parallax%20Mapping/)；陡峭视差映射通过增加采样的数量提高了位移的精确性，视差遮蔽映射通过对目标高度之间的两个高度层对应的纹理坐标进行插值来进一步提升精确性。

**浮雕贴图：** 与使用插值的视差遮蔽映射不同，浮雕贴图则是通过二分查找来决定uv的偏移量。

### 6.伽马校正

**为什么会出现伽马校正？：** 历史原因：早期我们使用的阴极射线显像管（CRT）的亮度与电压并不成线性关系，而是gamma值约为2.2类似幂律的关系；物理原因：人类对光的暗部变化更加敏感，需要使用更多位置去存储暗部值，所以利用设备的灰度系数（即gamma），能够让暗部使用更高精度保存，而亮部使用更低精度保存。

**传递函数：** OETF：光转电传递函数，负责把场景线性光转到非线性视频信号值；EOTF：电转光传递函数，负责把非线性视频信号值转换成显示光亮度。

**Gamma校正：** 图像经过gamma编码存储在硬盘中，将获取到的物理数据做一次gamma值约为0.45的映射，这样的过程叫做gamma编码，此时图像的像素比实际物理像素要更亮（注意，电压和亮度都是在0到1的区间）。而在显示图像时，**需要将每个像素做一次gamma值约为2.2的校正**，使最终的结果为正确的物理数据。

**具体应用：** 项目使用的是线性空间的贴图，则不需要勾选sRGB，否则，对于勾选了sRGB的贴图，会通过硬件特性采样时进行线性转换。不过，线性空间需要图形API的硬件支持，目前支持的平台如下：

- Windows，Mac OS x 和Linux(Standalone)
- Xbox One/Series
- PS 4/5
- Android (OpenGL ES 3.0)
- iOS(Metal)
- WebGL

参考：[LearnOpenGL CN-Gamma校正](https://learnopengl-cn.github.io/05%20Advanced%20Lighting/02%20Gamma%20Correction/)

### 7.LDR与HDR

**基本概念：**

- HDR = High Dynamic Range。远高于8位的精度、单通道可超过1，例如HDRI、真实世界
- LDR = Low Dynamic Range。8位精度、单通道0-1，例如拾色器、一般的图片、电脑屏幕
- 动态范围 = 最高亮度 / 最低亮度

**为什么需要HDR？：** ①HDR能呈现更好的色彩，更高的动态范围和更丰富的细节,  并且有效的防止画面过曝；②只有HDR才有超过1的数值，才有光晕（bloom）的效果，高质量的bloom能体现画面的渲染品质。

**色调映射（Tone Mapping）：** 一个损失很小的转换浮点颜色值至我们所需的LDR[0.0, 1.0]范围内的过程，通常会伴有特定的风格的色平衡（Stylistic Color Balance）。 ACES（Academy Color Encoding System 学院颜色编码系统）是现在最流行、最被广泛使用的Tonemapping映射曲线。

**泛光（Bloom）：** 光晕效果，可以使用泛光这种后处理来实现，具体算法见4.1。

参考：[LearnOpenGL CN-HDR](https://learnopengl-cn.github.io/05%20Advanced%20Lighting/06%20HDR/)

### 8.FlowMap的实现



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

### 1.PBR

#### 1.1 辐射度量学

**为什么需要辐射度量学？：** 无论是Blinn-Phong模型，还是whited-style光线追踪，都存在较多经验成分。

下面是三个重要概念的图解：

![三个重要概念](https://pic1.zhimg.com/v2-039fbcb784ca5531560b50b69a9cca68_r.jpg)

### 2.光线追踪



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