# RenderingOutline

这是我进行渲染学习的一个大纲（不是NPR里面的描边！虽然我学习图形学的初衷是NPR~），之后可能会补上一些图形学相关算法或技术的（伪）代码。

这个大纲基本是参考[技术美术百人计划](https://docs.qq.com/doc/DUFdKZE1oVFd3ZlBs)，增加了“第七章 GPU逻辑管线”，同时会补充上一些通俗且尽量简短的、至少我自己日后还能看懂的解释，保证所有知识点的"Why, What, How"都能在文字上解释清楚，即为什么会出现这种技术，这种技术的主要内容，这种技术的实现。

斜体字表示待学习、待补充的内容。

## 渲染的一些参考资料

最容易入门的图形学教程：[LearnOpenGL CN](https://learnopengl-cn.github.io/)

图形学孔子闫令琪老师：[GAMES101-现代计算机图形学入门](https://www.bilibili.com/video/BV1X7411F744)和[GAMES202-高质量实时渲染](https://www.bilibili.com/video/BV1YK4y1T7yY)

技术美术百人计划（还在更新中）：[【技术美术百人计划】前言概况介绍](https://www.bilibili.com/video/BV1oo4y1d71a)

《Real-Time Rendering》第4版

## 全篇第一个"Why, What, How"

**为什么学图形学？：** Computer Graphics is AWESOME!!!

**图形学是什么？：** 计算机图形学是计算机科学的一个子领域，它研究数字合成和处理视觉内容的方法。 尽管该术语通常指的是对三维计算机图形的研究，但它也包括二维图形和图像处理。

**图形学怎么学？：** 

- 看：把中文网络的视频资料和开源项目先搜刮干净，积累必要的图形学相关的英语词汇，再去读图形学的几本经典，以及搜刮英文网络、日文网络……
- 写：写代码，查文档，写代码，谷歌，写代码，写总结和笔记。

## 第一章 基础

### 1.渲染管线简介/Rendering Pipeline

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

### 2.数学基础/Math

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

### 3.纹理介绍/Texture

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

### 4.图形API介绍/Graphics API

Khronos定义了OpenGL，微软定义了DirectX；

目前手机，不管是iOS还是Android，都是支持OpenGL ES；

Windows系统支持DirectX和OpenGL，Linux/Mac(Unix)系统支持OpenGL。

这两个链接可以查看对应的手机芯片支持的OpenGL ES支持的版本：
[根据芯片查GPU](https://zh.wikipedia.org/wiki/%E9%AB%98%E9%80%9A%E9%A9%8D%E9%BE%8D%E5%85%83%E4%BB%B6%E5%88%97%E8%A1%A8#Snapdragon_888)、
[根据GPU查OpenGL ES版本](https://zh.wikipedia.org/wiki/Adreno)

## 第二章 光照基础

### 1.颜色空间/Color Space

我们常用的sRGB色彩空间，其构成为：

**1.色域：** sRGB首先设定了RGB三个基色的坐标；

**2.白点：** sRGB规定了白点位置；

**3.gamma：** sRGB的gamma设定为≈2.2，也就是说从外向内切，先切的很细，然后逐渐变粗。

![设备相关的RGB色彩空间](https://pic4.zhimg.com/v2-847b6a6e229101f4163b1a0c584330ff_r.jpg)

参考：[章佳杰-色彩空间基础](https://zhuanlan.zhihu.com/p/24214731)和[GAMES101-色彩与感知](https://www.bilibili.com/video/BV1X7411F744?p=20&t=2930)

### 2.模型与材质/Model&Materials

**模型包含的信息：** 其每个顶点会包含法线，纹理坐标，顶点色等信息。

**材质：** 漫反射、镜面反射、折射、粗糙镜面反射、粗糙镜面折射、多层材质（涂了透明油漆的木地板）、次表面散射（半透明的物体。例如玉石、蜡烛、牛奶、皮肤）

**模型数据在渲染中的作用：**

1.顶点动画：在顶点着色器中，修改模型的顶点位置，进而达到模型运动的效果。

2.纹理动画：在片段着色器中，修改模型的UV信息，使得采样贴图时，发生位移而产生运动效果。

3.顶点色：在渲染时，影响输出结果，控制颜色范围。

**重心坐标：** 原理见下面的参考文章。重心坐标在图形学中最重要的运用便是插值，他可以根据三个顶点A,B,C的属性插值出任意点的属性，无论是位置，颜色，深度，法线向量等等，而这些属性在之后的着色或是消除隐藏曲面都有很大的作用。 

参考：[孙小磊-重心坐标(barycentric coordinates)详解及其作用](https://zhuanlan.zhihu.com/p/144360079)

### 3.基础hlsl函数介绍/HLSL Functions

参考：[HLSL内部函数](https://docs.microsoft.com/zh-cn/windows/win32/direct3dhlsl/dx-graphics-hlsl-intrinsic-functions?redirectedfrom=MSDN)

### 4.传统经验光照模型/Empirical Shading Model

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

### 5.凹凸贴图/Bump Mapping

**为什么选择凹凸贴图？：** 减少建模的工作量，存储空间需求也能减少。

**法线贴图：** 根据经验光照模型的原理，引入一种叫做法线贴图的纹理。 法线贴图的法线向量需要定义在**切线空间**中，我们会定义一个**TBN矩阵**， 这三个字母分别代表tangent、bitangent和normal向量，这个矩阵可以把切线坐标空间的向量转换到世界坐标空间，不过我们一般是用其逆矩阵将向量从世界空间转换到切线空间，具体原因可参考[LearnOpenGL CN-法线贴图](https://learnopengl-cn.github.io/05%20Advanced%20Lighting/04%20Normal%20Mapping/)；

**视差贴图：** 视差贴图属于位移贴图技术的一种，它会引入一种叫高度贴图（或反色高度贴图）的纹理，通过对纹理坐标进行位移来实现凹凸的效果，它会和法线贴图配合使用，保证光照能和位移相匹配。关于视差贴图的具体计算可以参考[LearnOpenGL CN-视差贴图](https://learnopengl-cn.github.io/05%20Advanced%20Lighting/05%20Parallax%20Mapping/)；陡峭视差映射通过增加采样的数量提高了位移的精确性，视差遮蔽映射通过对目标高度之间的两个高度层对应的纹理坐标进行插值来进一步提升精确性。

**浮雕贴图：** 与使用插值的视差遮蔽映射不同，浮雕贴图则是通过二分查找来决定uv的偏移量。

### 6.伽马校正/Gamma Correction

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

### 7.LDR&HDR

**基本概念：**

- HDR = High Dynamic Range。远高于8位的精度、单通道可超过1，例如HDRI、真实世界
- LDR = Low Dynamic Range。8位精度、单通道0-1，例如拾色器、一般的图片、电脑屏幕
- 动态范围 = 最高亮度 / 最低亮度

**为什么需要HDR？：** ①HDR能呈现更好的色彩，更高的动态范围和更丰富的细节,  并且有效的防止画面过曝；②只有HDR才有超过1的数值，才有光晕（bloom）的效果，高质量的bloom能体现画面的渲染品质。

**色调映射（Tone Mapping）：** 一个损失很小的转换浮点颜色值至我们所需的LDR[0.0, 1.0]范围内的过程，通常会伴有特定的风格的色平衡（Stylistic Color Balance）。 ACES（Academy Color Encoding System 学院颜色编码系统）是现在最流行、最被广泛使用的Tonemapping映射曲线。

**泛光（Bloom）：** 光晕效果，可以使用泛光这种后处理来实现，具体算法见4.1。

参考：[LearnOpenGL CN-HDR](https://learnopengl-cn.github.io/05%20Advanced%20Lighting/06%20HDR/)

### *8.FlowMap的实现*

## 第三章 进阶应用

### 1.深度与模板测试/Depth Testing&Stencil Testing

**模板测试：** 模板测试位于透明度测试之后、深度测试之前，与之相关的概念首先是模板缓冲，其中的每个模板值通常是8位的。模板缓冲允许我们在渲染片段时将模板缓冲设定为一个特定的值，我们可以**读取**这些值，来决定丢弃还是保留某个片段。总之，大体的步骤如下：

- 启用模板缓冲的写入。
- 渲染物体，更新模板缓冲的内容。
- 禁用模板缓冲的写入。
- 渲染（其它）物体，这次根据模板缓冲的内容丢弃特定的片段。

**模板测试的应用：** 描边、多边形填充、反射区域控制、shadow volume

**深度测试：** 深度测试位于模板测试之后，与之相关的概念当然是深度缓冲，在大部分的系统中，深度缓冲的精度都是24位的。

现在大部分的GPU都提供一个叫做提前深度测试（Early Depth Testing）的硬件特性。提前深度测试允许深度测试在片段着色器之前运行。只要我们清楚一个片段永远不会是可见的（它在其他物体之后），我们就能提前丢弃这个片段。 

经过mvp变换之后的z值和最终的深度缓冲值之间其实是一个非线性关系 ，这样的话，摄像机近处的物品精度更高，越不容易发生深度冲突（Z-fighting）。防止深度冲突还有一些其他的方法，例如不要把多个物体摆得太靠近、将近平面设置远一些，以及牺牲一些性能，使用更高精度（例如32位）的深度缓冲。

需要注意的是，深度测试和混合一起使用的话会产生一些麻烦。当绘制一个有不透明和透明物体的场景的时候，大体的原则如下：

- 先绘制所有不透明的物体（从前到后）。
- 对所有透明的物体排序。
- 按顺序（从后到前）绘制所有透明的物体。

**深度测试的应用：** 基于深度的着色（湖水渲染）、阴影贴图、透明物体、粒子渲染、 透视X-Ray效果、切边效果

参考：[LearnOpenGL CN-深度测试](https://learnopengl-cn.github.io/04%20Advanced%20OpenGL/01%20Depth%20testing/)和[LearnOpenGL CN-模板测试](https://learnopengl-cn.github.io/04%20Advanced%20OpenGL/02%20Stencil%20testing/)

### *2.混合模式及剔除*

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

PBR，即基于物理的渲染（Physically Based Rendering），它指的是一些在不同程度上都基于**与现实世界的物理原理更相符的**基本理论所构成的渲染技术的集合。在实时渲染中，我们提到PBR，往往指的是PBR材质。

基于物理的渲染目的是使用一种更符合物理学规律的方式来模拟光线，这种渲染方式与我们原来的Phong或者Blinn-Phong光照算法相比总体上看起来要更真实一些。而且，由于它与物理性质非常接近，因此美术师们可以直接以物理参数为依据来编写表面材质，因此，不论光照条件如何，这些材质看上去都会是十分正确的。

判断一种PBR光照模型是否是基于物理的，必须满足以下三个条件：

- 基于微平面（Microfacet）的表面模型。
- 能量守恒。
- 应用基于物理的BRDF。

### 1.1 辐射度量学/Radiometry

**为什么需要辐射度量学？：** 无论是Blinn-Phong模型，还是Whitted-style光线追踪，都存在较多经验成分。

注：GitHub 的 markdown 渲染现在还不支持公式，请安装这个插件：[MathJax Plugin for Github](https://chrome.google.com/webstore/detail/mathjax-plugin-for-github/ioemnmodlmafdkllaclgeombjnmnbima)。

辐射能量（Radiant energy），指电磁辐射的能量，单位为焦耳（ J ），用符号 Q 表示。

辐射功率（Radiant power），或者称之为辐射通量（Radiant flux），指每单位时间辐射而出的能量，单位为瓦特（W）。

$$
\Phi = \frac{dQ}{dt}
$$

立体角（solid angle），就是二维空间中圆的弧度在三维空间中球上的拓展。

$$
\omega = \frac{A}{r^2}
$$

辐射强度（Radiant Intensity），指每单位立体角，单位时间所接收到的能量。

$$
I = \frac{d\Phi}{d\omega}
$$

辐照度（Irradiance），指每单位面积，单位时间所接收到的能量。

$$
E = \frac{d\Phi}{dA}
$$

辐出度（Radiance），指每单位**垂直**面积，单位立体角，单位时间接受到的能量。

$$
L = \frac{d^2\Phi}{d\omega dA^\perp} = \frac{dE}{d\omega \cos\theta}
$$

注意！辐照度与辐出度定义中的单位面积可不是同一回事！下图一目了然：

![](https://files.catbox.moe/qyse3f.jpg)

所以，假设有一个斜方向的面光源照到平面上，此时的照射面积就要除以一个cosθ，即Irradiance要乘上一个cosθ（有一点绕！可以看看这篇文章：[计算机图形学十四：基于物理渲染的基础知识(辐射度量学，BRDF和渲染方程)](https://zhuanlan.zhihu.com/p/145410416)，解释得更加清晰）

由上面的最后一个公式，我们可以推导出反射率方程，它其实是kajiya的渲染方程的特化版本。

$$
L_o(p,\omega_o) = \int\limits_{\Omega} f_r(p,\omega_i,\omega_o) L_i(p,\omega_i) n \cdot \omega_i  d\omega_i
$$

### 1.2 BRDF

**微表面（Microfacet）模型：** 在宏观上看上去是平的，但在微观上看去会看到各种各样的微表面，这些微表面的朝向，也就是法线各不相同，这些微表面法线的分布导致不同的材质渲染出的结果各不相同，这就是微表面模型。

**微表面BRDF：** ：我们先直接给出它的表达式：
$$
f = \frac{DFG}{4(\omega_o \cdot n)(\omega_i \cdot n)}
$$

表达式的分子包含三个函数，此外分母部分还有一个标准化因子 。字母D，F与G分别代表着一种类型的函数，各个函数分别用来近似地计算出表面反射特性的一个特定部分。三个函数分别为**法线分布函数**（Normal Distribution Function）（**注意！不要翻译成正态分布函数！**），**菲涅尔项**（Fresnel Term）和**几何项**（Geometry Term）。下面对其依次展开描述：

**菲涅尔项：** 表示观察角度与反射的关系。由于光路的可逆性，我们可以认为眼睛看过去的方向就是光线入射方向。有多少能量被反射取决于入射光的角度，当入射方向接近掠射角度（grazing angle）的时候，光线是被反射的最多的。

菲涅尔项的推导要考虑光线的S极化和P极化效果，公式比较复杂，一个对其简单的近似是：Schlick’s approximation：

$$
F_{Schlick}(h, v, F_0) = F_0 + (1 - F_0) ( 1 - (h \cdot v))^5
$$

其中：

$$
F_0 = \frac{(n_1 - n_2)^2}{(n_1 + n_2)^2}
$$

F<sub>0</sub>表示平面的基础反射率，它是利用所谓折射指数（Indices of Refraction）计算得出的。但是对于导体（conductor）表面，使用它们的折射指数来计算基础反射率往往并不能得出正确的结果，所以需要我们预计算出它们的基础反射率，一些常见材质的数值我们可以参考Naty Hoffman的课程讲义：[Physics and Math of Shading](https://blog.selfshadow.com/publications/s2015-shading-course/hoffman/s2015_pbs_physics_math_slides.pdf)。

### 1.3 PBR实现算法

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

## 第七章 GPU逻辑管线

### 1.逻辑管线简介/GPU Logical Pipeline

机会难得就直接用英文了。中间穿插一些中文注释，让人有种回到高中做英语阅读的感觉。

![](https://developer.nvidia.com/sites/default/files/akamai/gameworks/images/lifeofatriangle/fermipipeline_begin.png)

1.The program makes a **drawcall** in the graphics api (DX or GL). This reaches the driver at some point which does a bit of validation to check if things are "legal" and inserts the command in a GPU-readable encoding inside a **pushbuffer**. A lot of bottlenecks can happen here on the CPU side of things, which is why it is important programmers use apis well, and techniques that leverage the power of today's GPUs.

2.After a while or explicit "flush" calls, the driver has buffered up enough work in a pushbuffer and sends it to be processed by the GPU (with some involvement of the OS). The **Host Interface** of the GPU picks up the commands which are processed via the **Front End**（前端）.

3.We start our work distribution in the **Primitive Distributor**（ 图元分配器 ） by processing the indices in the indexbuffer and generating triangle work batches（批次） that we send out to multiple GPCs（Graphics Processing Cluster）.

![](https://developer.nvidia.com/sites/default/files/akamai/gameworks/images/lifeofatriangle/fermipipeline_sm.png)

4.Within a GPC, the **Poly Morph Engine**（多边形引擎） of one of the SMs（Stream Multiprocessor，流多处理器） takes care of fetching the vertex data from the triangle indices (**Vertex Fetch**).

5.After the data has been fetched, warps（ 线程束 ） of 32 threads are scheduled inside the SM and will be working on the vertices. warp是典型的单指令多线程（SIMT，SIMD单指令多数据的升级）的实现，也就是32个线程同时执行的指令是一模一样的，只是线程数据不一样，这样的好处就是一个warp只需要一个套逻辑对指令进行解码和执行就可以了，芯片可以做的更小更快，之所以可以这么做是由于GPU需要处理的任务是天然并行的。 

6.The SM's warp scheduler（warp调度器） issues the instructions for the entire warp in-order. The threads run each instruction in lock-step（锁步） and can be masked out（遮掩） individually if they should not actively execute it. There can be multiple reasons for requiring such masking. For example when the current instruction is part of the "if (true)" branch and the thread specific data evaluated "false", or when a loop's termination criteria was reached in one thread but not another（例如一条线程break了但是别的还在走）. Therefore having lots of branch divergence in a shader can increase the time spent for all threads in the warp significantly. Threads cannot advance individually, only as a warp! Warps, however, are independent of each other.

7.The warp's instruction may be completed at once or may take several dispatch turns. For example the SM typically has less units for load/store than doing basic math operations.（确实是这样的，一个SM有16组加载存储单元，有2组共32个Core（运算核心））

8.As some instructions take longer to complete than others, especially memory loads, the warp scheduler may simply switch to another warp that is not waiting for memory. This is the key concept how GPUs overcome latency of memory reads, they simply switch out groups of active threads. To make this switching very fast, all threads managed by the scheduler have their own registers in the register-file. The more registers a shader program needs, the less threads/warps have space. The less warps we can switch between, the less useful work we can do while waiting for instructions to complete (foremost memory fetches).

![](https://developer.nvidia.com/sites/default/files/akamai/gameworks/images/lifeofatriangle/fermipipeline_memoryflow.png)

9.Once the warp has completed all instructions of the vertex-shader, it's results are being processed by **Viewport Transform**. The triangle gets clipped by the clipspace volume and is ready for rasterization. We use L1 and L2 Caches for all this cross-task communication data.

![](https://developer.nvidia.com/sites/default/files/akamai/gameworks/images/lifeofatriangle/fermipipeline_raster.png)

10.Now it gets exciting, our triangle is about to be chopped up and potentially leaving the GPC it currently lives on. The bounding box of the triangle is used to decide which raster engines（光栅引擎） need to work on it, as each engine covers multiple tiles of the screen. It sends out the triangle to one or multiple GPCs via the **Work Distribution Crossbar**. We effectively split our triangle into lots of smaller jobs now.

![](https://developer.nvidia.com/sites/default/files/akamai/gameworks/images/lifeofatriangle/fermipipeline_mid.png)

11.**Attribute Setup** at the target SM will ensure that the interpolants (for example the outputs we generated in a vertex-shader) are in a pixel shader friendly format.

12.The **Raster Engine** of a GPC works on the triangle it received and generates the pixel information for those sections that it is responsible for (also handles back-face culling and Z-cull).

13.Again we batch up 32 pixel threads, or better say 8 times 2x2 pixel quads, which is the smallest unit we will always work with in pixel shaders. This 2x2 quad allows us to calculate derivatives（导数） for things like texture mip map filtering (big change in texture coordinates within quad causes higher mip). Those threads within the 2x2 quad whose sample locations are not actually covering the triangle, are masked out (gl_HelperInvocation). One of the local SM's warp scheduler will manage the pixel-shading task.

14.The same warp scheduler instruction game, that we had in the vertex-shader logical stage, is now performed on the pixel-shader threads. The lock-step processing is particularly handy because we can access the values within a pixel quad almost for free, as all threads are guaranteed to have their data computed up to the same instruction point.

![](https://developer.nvidia.com/sites/default/files/akamai/gameworks/images/lifeofatriangle/fermipipeline_end.png)

15.Are we there yet? Almost, our pixel-shader has completed the calculation of the colors to be written to the rendertargets and we also have a depth value. At this point we have to take the original api ordering of triangles into account before we hand that data over to one of the ROP (render output unit) subsystems, which in itself has multiple ROP units. Here depth-testing, blending with the framebuffer and so on is performed. These operations need to happen atomically（原子操作） (one color/depth set at a time) to ensure we don't have one triangle's color and another triangle's depth value when both cover the same pixel. NVIDIA typically applies memory compression（内存压缩）, to reduce memory bandwidth requirements, which increases "effective" bandwidth (see GTX 980 pdf).

参考：[Life of a triangle - NVIDIA's logical pipeline](https://developer.nvidia.com/content/life-triangle-nvidias-logical-pipeline)

### 2.光栅化、插值、保守光栅化/Rasterization&Interpolation&Conservative Rasterization



### 3.if，以及分支/if, and branch

在 shader 中，尽量避免使用 if 已成为绝大多数开发者的共识，究其原因是人们认为 if 会打断 GPU 的 warp 内部的并行化。 

![](https://files.catbox.moe/6ng7rh.jpg)

从这张图片开始这个话题的讨论。 如上图，SM中有8个ALU（Core），由于SIMD的特性，每个ALU的数据不一样，导致 if-else 语句在某些ALU中执行的是 true 分支（橙色），有些ALU执行的是  false 分支（灰色），这样导致很多ALU的执行周期被浪费掉了，拉长了整个执行周期。最坏的情况，同一个SM中只有1/8（8是同一个SM的线程数，不同架构的GPU有所不同）的利用率。

同样， for 循环也会导致类似的情形，例如以下shader代码：
```
void func(int count, int breakNum)
{
	for(int i=0; i < count; ++i) {
		if (i == breakNum)
			break;
		else
			// do something
	}
}
```
由于每个ALU的 count 不一样，加上有 break 分支，导致最快执行完shader的ALU可能是最慢的N分之一的时间，但由于SIMD的特性，最快的那个ALU依然要等待最慢的ALU执行完毕，才能接下一组指令的活！这就白白浪费了很多时间周期！

如何优化呢？避免使用if、switch分支语句，for 循环语句（特别是循环次数可变的）是一方面，另一方面，我们还需要知道：if ≠ 分支！我们真正要规避的是分支，而不是 if。

这是什么意思呢？事实上，对于简单逻辑的 if 而言，编译器大多生成的是一条现代GPU会硬件支持的 "select"（或称为 "conditional move"）指令，在D3D、PowerVR 等指令集中对应的就是一条 movc 指令。所以，if 有可能生成分支，也有可能生成 "select"。if 最终是否会生成和执行分支指令，取决于具体厂商的“编译器 + driver + GPU”。

分支无法避免，如果最终生成了分支指令，能尝试做些什么？首先从渲染流水线的角度来看，我们使用最频繁的还是 vertex shader 和 pixel shader，所以我们仅考虑这两个 stage。

而分支大体可以分为：

- static branch：如判断变量为 uniform 类型；
- dynamic branch & invariant（coherent）：如判断变量为 varying 类型，且在 warp 中有相关性甚至一致；
- dynamic branch & variant（incoherent）：如判断变量为 varying 类型，但在 warp 中无任何相关性。

静态分支性能上几乎无损，而 "ps + varaiant" 分支则是需要尽量避免的。如有可能，优化方向尽量从 "ps + variant" --> "ps + invariant" 或 "vs + variant" --> "vs + invariant"。

参考：[YAO-Shader中的 if 和分支](https://zhuanlan.zhihu.com/p/122467342)

## 第八章 其他

1.体素

2.球谐光照

3.欧拉旋转与四元变换

4.空间分割加速

5.通过法线2d渲3d的角色效果