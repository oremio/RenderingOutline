# RenderingOutline

这是我进行渲染学习的一个大纲（~不是NPR里的描边~），之后可能会补上一些图形学相关算法或技术的（伪）代码。

这个大纲基本是参考[技术美术百人计划](https://docs.qq.com/doc/DUFdKZE1oVFd3ZlBs)，增加了“第七章 GPU逻辑管线”，同时会补充上一些通俗且尽量简短的、至少我自己日后还能看懂的解释，保证所有知识点的"Why, What, How"都能在文字上解释清楚，即为什么会出现这种技术，这种技术的主要内容，这种技术的实现。

## 渲染的一些参考资料

最容易入门的图形学教程：[LearnOpenGL CN](https://learnopengl-cn.github.io/)

图形学孔子闫令琪老师：[GAMES101-现代计算机图形学入门](https://www.bilibili.com/video/BV1X7411F744)和[GAMES202-高质量实时渲染](https://www.bilibili.com/video/BV1YK4y1T7yY)

技术美术百人计划（还在更新中）：[【技术美术百人计划】前言概况介绍](https://www.bilibili.com/video/BV1oo4y1d71a)

《Real-Time Rendering》第4版

anything about game：[ComputerGraphics && Shading](https://github.com/killop/anything_about_game#computergraphics--shading)

## 全篇第一个"Why, What, How"

**为什么学图形学？：** Computer Graphics is AWESOME!!!

**图形学是什么？：** 计算机图形学，是一个具有广泛学科关联的科学体系，无法使用某种简单的语句进行准确的定义，但这并不妨碍我们去理解它。通俗来讲，计算机图形学就是研究如何使用计算机来创建和显示图形的一门科学。

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

碰撞检测、加速算法、遮挡剔除以及其他算法

③渲染设置：

合批方式：比如GPU instance或者动态批处理等等

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

Bloom（泛光）、HDR（高动态范围）、FXAA、DepthOfView、边缘检测、径向模糊；

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

### 3.纹理/Texture

**为什么选择纹理？：** 牺牲一些几何细节，能够大量减少建模的工作量，存储空间需求也能减少，读取速度也能增加。

**包装模式/纹理寻址模式：** Repeat，Mirror，Clamp（拉长边缘），Border

**纹理太小：** 会显得很糊，需要双线性插值（Bilinear）、双三次插值（Bicubic）、*Qu´ılez的光滑曲线插值*；

**纹理太大：** 近处会有锯齿，远处会产生摩尔纹。需要Mipmap以及Ripmap（各向异性的Mipmap）、EWA过滤、积分图（Summed-Area Table）；

**细讲Mipmap：** 根据某一个像素点与其周围像素点的距离，可以算出其对应的纹素点与其对应的纹素点的距离，通过这个距离可以画出一个以该纹素点为中心、边长为L的正方形，那么对应的Mipmap级数就是log<sub>2</sub>L。这样就能快速查询到某一像素的颜色值，而多出来的开销仅仅是原来的三分之一！

**细讲SAT：** 一种帮助我们快速求一个范围的平均的数据结构。求一个范围的平均其实也就等同于求一个范围的和，这就可以借用前缀和的思想，可以参考leetcode上的这道题[560. 和为K的子数组](https://leetcode-cn.com/problems/subarray-sum-equals-k/)。

上面两个概念在后面第四章实现阴影的部分还会再次提到！

CPU渲染优化常见方式：纹理图集/数组；

GPU渲染优化常见方式：纹理压缩；

**纹理的应用：** 立方体贴图，光照贴图，深度贴图，凹凸贴图，视差贴图

参考：[LearnOpenGL CN-纹理](https://learnopengl-cn.github.io/01%20Getting%20started/06%20Textures/)和[GAMES101-纹理、Mipmap](https://www.bilibili.com/video/BV1X7411F744?p=9)和[GAMES202-SAT](https://www.bilibili.com/video/BV1YK4y1T7yY?p=4&t=4315)

### 4.图形API/Graphics API

Khronos定义了OpenGL，微软定义了DirectX；

目前手机，不管是iOS还是Android，都是支持OpenGL ES；

Windows系统支持DirectX和OpenGL，Linux/Mac(Unix)系统支持OpenGL。

这两个链接可以查看对应的手机芯片支持的OpenGL ES支持的版本：
[根据芯片查GPU](https://zh.wikipedia.org/wiki/%E9%AB%98%E9%80%9A%E9%A9%8D%E9%BE%8D%E5%85%83%E4%BB%B6%E5%88%97%E8%A1%A8#Snapdragon_888)、
[根据GPU查OpenGL ES版本](https://zh.wikipedia.org/wiki/Adreno)

这篇文章对OpenGL介绍得相当不错：[柯灵杰-20分钟让你了解OpenGL——OpenGL全流程详细解读](https://zhuanlan.zhihu.com/p/56693625)

### 5.图形API坐标系对比/Coordinate System

渲染从3D到2D的过程中，经历了不少的坐标系。主要可以认为有以下几种。

**世界坐标系：** 在DirectX的**教程**中，一般倾向于使用左手坐标系。在OpenGL的**教程**中，则一般倾向于右手坐标系。这两种情况，都是Y轴表示向上，只有Z不一样。

**观察坐标系：** 在DirectX的教程中，一般观察空间的坐标系统和OpenGL就已经统一了，都是一模一样的左手系坐标系。具体来说，就是摄像机观察的反方向（z）、上向量（y）、前者叉乘后者i.e.右向量（x）。

在现代管线中，世界坐标系和View坐标系是游戏引擎可以**自行选择**的，因为world view矩阵计算与硬件无关，交给了引擎来处理。 引擎在这里，只要选择一种 World+View 方案即可，DirectX 或 OpenGL风格都可以。当然，也可以选择自己更自由的设定，比如Z轴向上。

**NDC坐标系和NDC空间：** 一部分View坐标系中的点通过投影矩阵(Projection)，并进行透视除法后，我们的点变换到了NDC空间中。DirectX、OpenGL、Metal这些图形API，NDC坐标系都和View坐标系的手性是一致的。Vulkan中，NDC坐标系跟View坐标系的手性不一致，Y轴颠倒了。

**FrameBuffer坐标系：** FrameBuffer坐标系，是一个2D坐标系。我们主要从它的Y的不同来考虑。 在DirectX、Metal、Vulkan中，FrameBuffer的坐标系都是非常传统的。左上角是原点，Y轴朝下。 在OpenGL中，该坐标系的左下角是原点。 这也是很多纹理在OpenGL 模式下要Flip Y过来的原因了。

**纹理坐标系：** 其实纹理没有坐标系，我们这里说的是纹理的第一个像素的sampler(0, 0)表示这张纹理的左上角还是左下角。这个因为图片格式都是定死了，每个平台都是一样的，表示的都是图片的左上角。

参考：[露米 Lumi-Vulkan集成：图形API坐标系对比及解决方案](https://zhuanlan.zhihu.com/p/339295068)

## 第二章 光照基础

### 1.颜色空间/Color Space

我们常用的sRGB色彩空间，其构成为：

**1.色域：** sRGB首先设定了RGB三个基色的坐标；

**2.白点：** sRGB规定了白点位置；

**3.gamma：** sRGB的gamma设定为≈2.2，也就是说从外向内切，先切的很细，然后逐渐变粗。

![设备相关的RGB色彩空间](https://pic4.zhimg.com/v2-847b6a6e229101f4163b1a0c584330ff_r.jpg)

参考：[章佳杰-色彩空间基础](https://zhuanlan.zhihu.com/p/24214731)和[GAMES101-色彩与感知](https://www.bilibili.com/video/BV1X7411F744?p=20&t=2930)

### 2.模型与材质/Model & Materials

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

**法线贴图：** 根据经验光照模型的原理，引入一种叫做法线贴图的纹理。法线纹理的 RGB 通道存储了在每个顶点各自法线方向的**映射值**（因为纹理每个通道的值范围在(0, 1)！例如：法线值(0, 0, 1)实际上对应了法线纹理中RGB的值为(0.5, 0.5, 1)）。法线贴图的法线向量需要定义在**切线空间**中，我们会定义一个**TBN矩阵**， 这三个字母分别代表tangent、bitangent和normal向量，这个矩阵可以把切线坐标空间的向量转换到世界坐标空间，不过我们一般是用其逆矩阵将向量从世界空间转换到切线空间，具体原因可参考[LearnOpenGL CN-法线贴图](https://learnopengl-cn.github.io/05%20Advanced%20Lighting/04%20Normal%20Mapping/)；

**细讲TBN矩阵：** 法线贴图存储的是TBN空间中的一个向量，TBN矩阵的构造很简单，以**顶点法线**为Z轴，利用三角形的位置和纹理坐标，以公式：E1 = △U1T + △V1B 和 E2 = △U2T + △V2B 计算得到TB的**中间值**，再通过公式 T = normalize(T - dot(T, N) * N) 算出最终的T，B可由N叉乘T得到。参考：[谜之裙摆-切线空间（Tangent Space）完全解析](https://zhuanlan.zhihu.com/p/139593847)；

**视差贴图：** 视差贴图属于位移贴图技术的一种，它会引入一种叫高度贴图（或反色高度贴图）的纹理，通过对纹理坐标进行位移来实现凹凸的效果，它会和法线贴图配合使用，保证光照能和位移相匹配。关于视差贴图的具体计算可以参考[LearnOpenGL CN-视差贴图](https://learnopengl-cn.github.io/05%20Advanced%20Lighting/05%20Parallax%20Mapping/)；陡峭视差映射通过增加采样的数量提高了位移的精确性，视差遮蔽映射通过对目标高度之间的两个高度层对应的纹理坐标进行插值来进一步提升精确性。

**浮雕贴图：** 与使用插值的视差遮蔽映射不同，浮雕贴图则是通过二分查找来决定uv的偏移量。

（demo）

### 6.伽马校正/Gamma Correction

**为什么会出现伽马校正？：** 历史原因：早期我们使用的阴极射线显像管（CRT）的亮度与电压并不成线性关系，而是gamma值约为2.2类似幂律的关系；物理原因：人类对光的暗部变化更加敏感，需要使用更多位置去存储暗部值，所以利用设备的灰度系数（即gamma），能够让暗部使用更高精度保存，而亮部使用更低精度保存。

**传递函数：** OETF：光转电传递函数，负责把场景线性光转到非线性视频信号值；EOTF：电转光传递函数，负责把非线性视频信号值转换成显示光亮度。

**Gamma校正：** 步骤如下：

第一步，输入的纹理如果是sRGB（Gamma0.45），那我们要进行一个操作转换到线性空间。这个操作叫做Remove Gamma Correction，在数学上是一个2.2的幂运算。如果输入不是sRGB，而是已经在线性空间的纹理了呢？那就可以跳过Remove Gamma Correction了。

注：美术输出资源时都是在sRGB空间的，但Normal Map等其他电脑计算出来的纹理则一般在线性空间，即Linear Texture。

第二步，现在输入已经在线性空间了，那么进行Shader中光照、插值等计算后就是比较真实的结果了（上文解释了哦~），如果不对sRGB进行Remove Gamma Correction直接就进入Shader计算，那算出来的就会不自然，就像前面那两张球的光照结果一样。

第三步，Shader计算完成后，需要进行Gamma Correction，从线性空间变换到Gamma0.45空间，在数学上是一个约为0.45的幂运算。如果不进行Gamma Correction输出会怎么样？那显示器就会将颜色从线性空间转换到Gamma2.2空间，接着再被你看到，结果会更暗。

第四步，经过了前面的Gamma Correction，显示器输出在了线性空间，这就和人眼看物理世界的过程是一样的了！

**具体应用：** 项目使用的是线性空间的贴图，则不需要勾选sRGB，否则，对于勾选了sRGB的贴图，会通过硬件特性采样时进行线性转换。不过，线性空间需要图形API的硬件支持，目前支持的平台如下：

- Windows，Mac OS x 和Linux(Standalone)
- Xbox One/Series
- PS 4/5
- Android (OpenGL ES 3.0)
- iOS(Metal)
- WebGL

参考：[LearnOpenGL CN-Gamma校正](https://learnopengl-cn.github.io/05%20Advanced%20Lighting/02%20Gamma%20Correction/)和[PZZZB-Gamma、Linear、sRGB 和Unity Color Space，你真懂了吗？
](https://zhuanlan.zhihu.com/p/66558476)

### 7.LDR&HDR

**基本概念：**

- HDR = High Dynamic Range。远高于8位的精度、单通道可超过1，例如HDRI、真实世界
- LDR = Low Dynamic Range。8位精度、单通道0-1，例如拾色器、一般的图片、电脑屏幕
- 动态范围 = 最高亮度 / 最低亮度

**为什么需要HDR？：** ①HDR能呈现更好的色彩，更高的动态范围和更丰富的细节,  并且有效的防止画面过曝；②只有HDR才有超过1的数值，才有光晕（bloom）的效果，高质量的bloom能体现画面的渲染品质。

**色调映射（Tone Mapping）：** 一个损失很小的转换浮点颜色值至我们所需的LDR[0.0, 1.0]范围内的过程，通常会伴有特定的风格的色平衡（Stylistic Color Balance）。 ACES（Academy Color Encoding System 学院颜色编码系统）是现在最流行、最被广泛使用的Tonemapping映射曲线。

**泛光（Bloom）：** 光晕效果，可以使用泛光这种后处理来实现，具体算法见4.1。

参考：[LearnOpenGL CN-HDR](https://learnopengl-cn.github.io/05%20Advanced%20Lighting/06%20HDR/)

### 8.FlowMap的实现

实现流程：对FlowMap进行采样，可以得到一个值在0 ~ 1之间的向量场，将它转换到-1 ~ 1后，我们还需要构造两个周期相同、相位相差半个周期的波形函数，利用偏移向量和两个波形函数，我们对纹理采样两次并进行一个线性插值，就可以得到一个循环平滑的流动。

参考：[【技术美术百人计划】图形 2.8 flowmap的实现——流动效果实现](https://www.bilibili.com/video/BV1Zq4y157c9?p=2)

（demo）

## 第三章 进阶应用

### 1.深度与模板测试/Depth Testing & Stencil Testing

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

**深度测试的应用：** 基于深度的着色（湖水渲染）、阴影贴图、透明物体、粒子渲染、透视X-Ray效果、切边效果

参考：[LearnOpenGL CN-深度测试](https://learnopengl-cn.github.io/04%20Advanced%20OpenGL/01%20Depth%20testing/)和[LearnOpenGL CN-模板测试](https://learnopengl-cn.github.io/04%20Advanced%20OpenGL/02%20Stencil%20testing/)

（demo）

### 2.混合模式及剔除/Blending & Culling

**混合：** 混合通过下面这个方程实现：

$$
C_{result} = C_{source} * F_{source} + C_{destination} * F_{destination}
$$

其中：

- C<sub>source</sub>：源颜色向量。这是源自纹理的颜色向量。
- C<sub>destination</sub>：目标颜色向量。这是当前储存在颜色缓冲中的颜色向量。
- F<sub>source</sub>：源因子值。指定了alpha值对源颜色的影响。
- F<sub>destination</sub>：目标因子值。指定了alpha值对目标颜色的影响。

这种混合方式叫做 over 操作, 将不透明物体从远处往近处逐一渲染, 得到最终的颜色。一般的游戏引擎中也是这样来渲染透明物体: 先渲染所有的不透明物体, 再将不透明物体按照到摄影机的距离从远处到近处排序, 逐一渲染。

**剔除：** 剔除是游戏引擎中非常重要的技术：现代引擎需要在十几毫秒的预算里，渲染出数以万计的物体，场景复杂度往往是数千万面的级别，同时还需要处理千计盏灯光和数百种材质。对于开放世界类型的游戏更是如此：场景动辄就是数十公里的延伸，想要通过暴力穷举地方法逐一绘制这些物体是不现实的。因此，如何有效地减少不必要的绘制就显得格外重要。

**硬件层面的剔除：** 

**裁剪&面剔除：** Clipping是当一个三角形的顶点位置被变换到NDC后，针对NDC外的三角形和穿过NDC的三角形，会执行剔除或者裁剪的操作；Backface Culling，则是在图元装配阶段结束之后，根据用户指定的手向，把面向摄像机或者背对摄像机（一般是背对摄像机）的三角形剔除，剔除后的三角形就不会再进入到 Pixel Shader 和 Rasteriaztion 的流程里。

**Early-Z：** 绝大部分情况下，Pixel Depth在 Rasterization 之后、Pixel Shader 执行之前就可以被确定下来，如果我们能够把 Depth Test 放在 Pixel Shader 之前，对那些没通过 Depth Test 的像素不执行 Pixel Shader，就能够一定程度上减少 SM 的压力，这就是 Early-Z 这个优化策略的初衷，现在已经是GPU的标配了。默认在 Pixel Shader 里没有修改 Depth 的操作时，这个优化就会开启。

**Z-Cull：** Z-Cull 和 Early-Z 很容易混淆，它们的主要区别体现在剔除的粒度不同：Z-Cull 的剔除是粗粒度的Pixel Tile（比如一个8*8的像素块），而 Early-Z 是细粒度的 2*2 的 Pixel Quad 。在用 Z-Cull 进行 Depth Test 的时候，Pixel Tile 会被压缩以加速比较。

现代引擎基本都会利用 Z-Cull 和 Early-Z 的特性去减少SM的计算压力，具体方法是执行一个 Z-Prepass（不论是foward，forward+ 还是 deferred 管线都一样）：先将不透明物体按照距离摄像机从前向后的顺序排序，然后只开启Z-Buffer write和 compare，不执行 Pixel Shader 进行一遍渲染。在执行完 Z-Prepass 后，关闭 Z-Buffer 的写入，将 compare function 改为 equal ，然后执行后续复杂 Pixel Shader（前向渲染的光照计算或者延迟渲染的G-Buffer填充）。

**算法层面的剔除：** 

**视锥剔除：** 判断一个物体是否位于视锥棱台内。在实践中，由于模型往往是比较复杂的，很难精确计算它和视锥体的交集，因此一般是用**轴对齐包围盒**（AABB），**有向包围盒**（OBB）或者**包围球**（BSphere）代替模型本身进行相交计算。

对于复杂场景来说，线性数组的遍历方式往往不够高效，这时候也可以将场景以层次结构组织起来进行剔除，例如四叉树、八叉树。闫神在介绍加速光线追踪的时候还提到了BSP树、KD树、BVH包围盒等等，这里正好一起总结一下：

①QuadTree(4) / Octree(8)：每次将空间分为8个相等的部分，再递归的对子空间进行划分，当划分的子空间足够小或是空间中三角形面的数量很少的时候会停止划分。这种方法的显著缺点是，随着维度的上升划分的空间数量会呈指数级增长。

②KD-Tree：每次将空间划分为两部分，且划分依次沿着x-axis，y-axis，z-axis。递归终止条件与八叉树类似。

③BSP-Tree：与KD-Tree类似，唯一不同的是划分不再沿着固定一轴，可以任意方向划分，缺点自然是划分的空间没有规则性，求交困难。

④Bounding Volume Hierarchy：BVH与前几种方法最显著的区别就是，不再以空间作为划分依据，而是从对象的角度考虑，即三角形面，过程如下： 1.同样找出场景的整体包围盒作为根节点；2.找到合适的划分点，将最大包围盒内的三角形面分为两部分，再分别重新计算新的包围盒（包围盒会重叠，但一个三角形面只会被存储在唯一的包围盒内，而这也就解决了KD-Tree的缺点）；3.与KD-Tree一样，中间节点不存储物体三角面信息，只在叶节点中存储，终止条件可设定为当前包围盒内三角形数量足够少。

参考：[GAMES101-加速算法](https://www.bilibili.com/video/BV1X7411F744?p=14&t=1100)

**遮挡剔除：** 实现困难，但变化丰富。有各种各样的实现方式：

①基于 Portal 的剔除：（待补充。Portal就是美术/策划在制作关卡过程中人工标记出来的连接）

②基于 Occlusion Query 的遮挡剔除：（待补充。比较常用的的方法是让CPU回读前一帧的occlusion query的结果，用来决定当前帧某个物体是否visible）

③基于 Software Rasterization 的遮挡剔除：（待补充。纯CPU，集成起来较简单）

④GPU Driven Rendering Pipeline：（待补充，这个思路的产生和发展得益于图形API和硬件的发展）

参考：[TC130-游戏中的透明渲染](https://zhuanlan.zhihu.com/p/149982810)和[洛城-剔除：从软件到硬件](https://zhuanlan.zhihu.com/p/66407205)和[TC130-游戏中的遮挡剔除/Occlusion Culling](https://zhuanlan.zhihu.com/p/363277669)

（demo）

https://docs.unity3d.com/cn/2018.4/Manual/SL-Blend.html

http://wordpress.notargs.com/blog/blog/2015/09/24/unity5%E7%A0%B4%E9%8C%A0%E3%81%97%E3%81%AA%E3%81%84%E5%8D%8A%E9%80%8F%E6%98%8E%E6%8F%8F%E7%94%BB%E3%82%92%E8%A1%8C%E3%81%86/

### 3.曲面细分着色器与几何着色器/ts & gs

**曲面细分着色器：** 输入：Patch, 可以看成是多个顶点的集合，包含每个顶点的属性，可以指定一个Patch包含的顶点数以及自己的属性；功能：将图元细分（可以是三角形，矩形等）；输出：细分后的顶点；

**具体流程：** 

- HULL Shader（可编程）：1. 决定细分的数量（设定Tessellation factor以及Inside Tessellation factor）；2. 对输入的Patch参数进行改变（如果需要）；
- Tessellation Primitive Generation（不可编程）：进行细分操作；
- Domain Shader（可编程）：对细分后的点进行处理，从重心空间（Barycentric coordinate system）转换到屏幕空间；

**几何着色器：** 输入：图元（三角形，矩形，线等）。根据图元的不同，shader中会出现对应数量的顶点；输出：同样为图元，一个或多个，需要自己从顶点构建（构建顺序很重要）。

参考：[LearnOpenGL CN-几何着色器](https://learnopengl-cn.github.io/04%20Advanced%20OpenGL/09%20Geometry%20Shader/)

（demo）

### 4.延迟渲染原理介绍/Deferred Rendering

**前向渲染：** 我们渲染物体的一种非常直接的方式，在场景中我们根据所有光源照亮一个物体，之后再渲染下一个物体，以此类推。它非常容易理解，也很容易实现，但是同时它对程序性能的影响也很大，因为对于每一个需要渲染的物体，程序都要对每一个光源每一个需要渲染的片段进行迭代，这会浪费大量的片段着色器运行时间。

优点：1、支持半透明渲染；2、支持使用多个光照pass；3、支持自定义光照计算方式；

缺点：1、光源数量对计算复杂度影响巨大；2、访问深度等数据需要额外计算；

**延迟渲染：** 解决大量光照渲染的方案。它的实质是先不要做迭代三角形的光照计算，而是先找出来你能看到的所有像素，再去迭代光照。

延迟着色法包含两个处理阶段（Pass）：在第一个几何处理阶段（Geometry Pass）中，我们先渲染场景一次，之后获取对象的各种几何信息，并储存在一系列叫做G缓冲（G-buffer）的纹理中，例如位置向量、颜色向量、法向量和/或镜面值)。场景中这些储存在G缓冲中的几何信息将会在之后用来做（更复杂的）光照计算。

在第二个光照处理阶段（Lighting Pass）中，我们会使用G缓冲内的纹理数据。在光照处理阶段中，我们渲染一个屏幕大小的方形，并使用G缓冲中的几何数据对每一个片段计算场景的光照；在每个像素中我们都会对G缓冲进行迭代。光照计算过程还是和我们以前一样，但是现在我们需要从对应的G缓冲而不是顶点着色器（和一些uniform变量）那里获取输入变量了。

优点：1、大量光照场景优势明显；2、只渲染可见像素，节省计算量；3、对后处理支持良好；4、用更少的shader；

缺点：1、对MSAA支持不友好；2、透明物体渲染存在问题；3、占用大量的显存带宽；

参考：[LearnOpenGL CN](https://learnopengl-cn.github.io/05%20Advanced%20Lighting/08%20Deferred%20Shading/)

（demo）

### 5.early-Z & Z-Prepass

**early-Z失效的情况：** 1.开启 Alpha Test 或 clip/discard 等手动丢弃片元操作；2.手动修改GPU插值得到的深度；3.开启 Alpha Blend；4.关闭深度测试；

**如何高效利用early-Z：** 

1.将物体由近到远排序 → 问题：场景十分复杂的时候，频繁的排序操作将消耗cpu的性能！

2.使用Z-Prepass：我们对每个物体设置两个 Pass。在第一个 Pass 即 Z-Prepass 中仅仅只写入深度，不计算输出任何颜色，相当于自动形成了一个最小深度的深度缓冲区。在第二个Pass中关闭深度写入，并且将深度比较函数设置为相等。 → 问题：一个拥有 a multi-pass shader 的物体是无法进行动态批处理的

3.上面的改进方案：将原先第一个Pass单独分离为一个 Shader，并先使用这个 Shader 将整个场景的不透明的物体从前向后渲染一遍。

**Z-Prepass的使用场合：** 1.一个场景有非常多的 OverDraw，而且不能很好的将不透明物体从前往后进行排序；2.Z-Prepass也是透明渲染的一种解决方案。

### 6.纹理压缩

（待补充）

### 7.现代移动端的TBR和TBR渲染管线以及Cbuffer

参考：[【技术美术百人计划】图形 3.7 移动端TB(D)R架构基础](https://www.bilibili.com/video/BV1Bb4y167zU)

### 7.1 名词解释

**System on Chip（Soc）：** Soc是把CPU、GPU、内存、通信基带、GPS模块等等整合在一起的芯片的称呼。常见有A系Soc（苹果），骁龙Soc（高通），麒麟Soc（华为），联发科Soc，猎户座Soc（三星），去年苹果推出的M系Soc，暂用于Mac，但这说明手机、笔记本和PC的通用芯片已经出现了。

**物理内存：** Soc中GPU和CPU共用一块片内LPDDR物理内存，就是我们常说的手机内存，也叫System Memory，大概几个G。此外CPU和GPU还分别有自己的高速SRAM的Cache缓存，也叫On-chip Memory，一般几百K~几M。不同距离的内存访问存在不同的时间消耗，距离越近消耗越低，读取System Memory的时间消耗大概是On-chip Memory的几倍到几十倍。

**On-Chip Buffer：** 在TB(D)R架构下会存储Tile的颜色、深度和模板缓冲，读写修改都非常快。如果Load/Store指令中缓冲需要被Preserve，将会被写入一份到System Memory中。

**Stall：** 当一个GPU核心的两次计算结果之间有依赖关系而必须串行时，等待的过程便是Stall。

**FillRate：** 像素填充率 = ROP运行的时钟频率 x ROP的个数 x 每个时钟ROP可以处理的像素个数。

**TBR（Tile-Based (Deferred) Rendering）：** 是目前主流的移动GPU渲染架构，对应一般PC上的GPU渲染架构则是IMR（Immediate Mode Rendering ）。

### 7.2 IMR & TBR

直接用伪代码表示，一目了然：

**IMR：**

```
for draw in renderPass:
	for primitive in draw:
		for vertex in primitive:
			execute_vertex_shader(vertex)
		if primitive not culled:
			for fragment in primitive:
				execute_fragment_shader(fragment)
```

**TBR：**

```
# Pass one
for draw in renderPass:
	for primitive in draw:
		for vertex in primitive:
			execute_vertex_shader(vertex)
		if primitive not culled
			append_tile_list(primitive)
# Pass two
for tile in renderPass:
	for primitive in tile:
		for fragment in primitive:
			execute_fragment_shader(fragment)
```

下面这张图则展示了两者在内存管理上的不同点：

![](https://files.catbox.moe/g5j52f.png)

上面的TBR最终会将颜色、深度、模板缓冲都刷到片上内存里，体现了一种 cached friendly的优点，可以降低带宽、减小功耗。

### 7.3 TBR的优化策略

不使用Framebuffer的时候记得clear或者discard：清空积存在tile buff上的 frame Data，所以在unity里面对render texture的使用也特别说明了一下，当不再使用这个rt之前，调用一次Discard。在OpenGL ES上善用glClear，gllnvalidateFrameBuffer避免不必要的Resolve（刷system memory）行为。

不要在一帧里面频繁的切换framebuffer的绑定：本质上就是减少tile buffer 和system memory之间的 的 stall 操作。

手机上必须要做Alpha Test，可以利用Depth prepass。

图片尽量压缩，例如:ASTC、ETC2；图片尽量走 mipmap。

尽量使用从 Vertex Shader 传来的 Varying 变量UV值采样贴图（连续的），不要在 FragmentShader 里动态计算贴图的UV值（非连续的），否则 CacheMiss。

在延迟渲染尽量利用 Tile Buffer 存储数据。

少在FS 中使用 discard 函数，调用 gl_FragDepth 从而打断 Early-DT（HLSL中为Clip，GLSL中为discard）。

尽可能的在 Shader 里使用 Half Float，如果 Shader 中仅有少量 FP16 的运算，且 FP1 6需和 FP32 混合计算，则统一使用 Float，好处：（1）带宽用量减少；（2）GPU中使用的周期数减少，因为着色器编译器可以优化你的代码以提高并行化程度；（3）要求的统一变量寄存器数量减少，这反过来又降低了寄存器数量溢出风险。具体有哪些数据类型适合用 half 或者 float 或者 fix。具体可参考：[熊大的优化建议](http://www.xionggf.com/post/unity3d/shader/u3d_shader_optimization/)

在移动端的 TB(D)R 架构中，顶点处理部分，容易成为瓶颈，避免使用曲面细分shader，置换贴图等负操作，提倡使用模型LOD,本质上减少 FrameData 的压力。

### 7.4 Cbuffer

### 8.DepthPeeling 深度剥离

（待补充）

（demo）

https://zhuanlan.zhihu.com/p/127399447

## 第四章 高级扩展

### 1.Bloom算法

（demo）

### 2.SSAO算法

**环境光遮蔽（Ambient Occlusion）：** 环境遮挡是创建逼真的周围环境的关键因素。它提供了我们期望从全局照明和其他更复杂的间接照明技术中获得的柔和阴影。未完全暴露于环境的表面上的光照需要适当地衰减，以使它们不能获得周围环境光的全部贡献。

**AO的作用：** 通过描绘物体之间由于遮挡而产生的阴影， 能够更好地捕捉到场景中的细节，可以解决漏光，阴影漂浮等问题，改善场景中角落、锯齿、裂缝等细小物体阴影不清晰等问题，增强场景的深度和立体感。

**AO的实现方式：** ①预计算：通过离线计算的方式来计算物体表面的AO系数, 预计算光照信息和AO, 也叫做烘培/baking。预计算AO最常用的方式就是通过蒙特卡洛方法；②动态计算：1、使用 SDF 保存场景的有向距离场信息, 实时来计算AO；2、使用voxel八叉树保存场景信息；3、raytracing；4、屏幕空间：后处理在屏幕空间实现的AO, 最流行, 最简单的动态AO。

**SSAO：** 对于铺屏四边形上的每一个片段，我们都会根据周边深度值计算一个**遮蔽因子（Occlusion Factor）** 。这个遮蔽因子之后会被用来减少或者抵消片段的环境光照分量。遮蔽因子是通过采集片段周围球型核心（Kernel）的多个深度样本，并和当前片段深度值对比而得到的。高于片段深度值样本的个数就是我们想要的遮蔽因子。

SSAO的流程，下图一目了然，显然它和延迟渲染结合得很好：

![](https://learnopengl-cn.github.io/img/05/09/ssao_overview.png)

渲染效果的质量和精度与我们采样的**样本数量**有直接关系。如果样本数量太低，渲染的精度会急剧减少，我们会得到一种叫做波纹（Banding）的效果；如果它太高了，反而会影响性能。我们可以通过引入**随机性**到采样核心（Sample Kernel）的采样中从而减少样本的数目。通过**随机旋转**采样核心，我们能在有限样本数量中得到高质量的结果。然而这仍然会有一定的麻烦，因为随机性引入了一个很明显的噪声图案，我们将需要通过**模糊**结果来修复这一问题。

需要注意，我们不会使用球体的采样核心，而使用一个**沿着表面法向量的半球体**采样核心。由于对每个表面法线方向生成采样核心非常困难，也不合实际，我们将在**切线空间**内生成采样核心，法向量将指向正z方向。

参考：[TC130-游戏中的全局光照(三) 环境光遮蔽/AO](https://zhuanlan.zhihu.com/p/194198670)和[LearnOpenGL CN-SSAO](https://learnopengl-cn.github.io/05%20Advanced%20Lighting/09%20SSAO/)

（demo）

### 3.阴影的各类实现方法

1.平面映射

（待补充）

2.Shadow Volumes

（待补充）

**3.Shadow Map：** 

从光源处出发向光照的方向渲染需要产生阴影的物体，得到保存最近处物体的深度值的 shdow map。

对于 directional light 使用一个足够大的 orthographic projection frustum 包住所有需要渲染的物体，spot light 使用一个和自己光照范围相当的frustrum，omini light 沿六个方向生成类似于 cubic environment mapping 的 omnidirectional shadow maps。

渲染物体光照时，将像素点代入到光照的矩阵中，和 shadow map 中该点的深度值比较，如果深度值大于 shadow map 中深度值，说明该点在阴影中。

**4.改进Shadow Map：** 1.阴影偏移；2.修复悬浮（Peter Panning）；3.Cascaded Shadow Maps（CSM）；4.Percentage-Closer Filtering（PCF）5.（待补充）

（待补充）

（demo）

### 4.抗锯齿之FXAA、MSAA

（demo）

### 5.DOF景深算法

（demo）

### 6.运动模糊

（demo）

### 7.雾效实现方法

**DepthFog：**

在每个像素计算的正常颜色基础上，根据距离混合一个雾的颜色。

最常用的三种计算雾强度的公式:

Linear : factor = (end-z)/(end-start)

Exp: factor = exp(-density*z)

Exp2: factor = exp(-(density*z)^2)

unity中的全局雾设置和宏APPLY_FOG就是使用这种方式。

**PostProcessing Fog：**

和 Depth Fog 基本上是一样的，区别在于 PostProcessing 的 Fog 通过在 PostProcessing 时根据 depth texture 反推计算出摄影机到目标像素点的距离。除了用距离作为上述公式的参数，还可以根据高度作为参数，或者高度*距离这样的形式来作为参数。

参考：[TC130-游戏中的Volumetric Rendering](https://zhuanlan.zhihu.com/p/102114679)

### 8.基于屏幕空间的溶解

https://www.jianshu.com/p/c71076676fe6

https://www.jianshu.com/p/1bef38552775

（demo）

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
f_r(\omega_i,\omega_o) = \frac{F(\omega_i,h)G(\omega_i,\omega_o,h)D(h)}{4(\omega_i \cdot n)(\omega_o \cdot n)}
$$

表达式的分子包含三个函数，此外分母部分还有一个标准化因子 。字母D，F与G分别代表着一种类型的函数，各个函数分别用来近似地计算出表面反射特性的一个特定部分。三个函数分别为**菲涅尔项**（Fresnel Term），**几何项**（Geometry Term）和**法线分布函数**（Normal Distribution Function）（**注意！不要翻译成正态分布函数！**）。下面对其依次展开描述：

**菲涅尔项：** 表示观察角度与反射的关系。由于光路的可逆性，我们可以认为眼睛看过去的方向就是光线入射方向。有多少能量被反射取决于入射光的角度，当入射方向接近掠射角度（grazing angle）的时候，光线是被反射的最多的。

菲涅尔项的推导要考虑光线的S极化和P极化效果，公式比较复杂，一个对其简单的近似是：**Schlick’s approximation**：

$$
F_{Schlick}(h, v, F_0) = F_0 + (1 - F_0) ( 1 - (h \cdot v))^5
$$

其中：

$$
F_0 = \frac{(n_1 - n_2)^2}{(n_1 + n_2)^2}
$$

F<sub>0</sub>表示平面的基础反射率，它是利用所谓折射指数（Indices of Refraction）计算得出的。但是对于导体（conductor）表面，使用它们的折射指数来计算基础反射率往往并不能得出正确的结果，所以需要我们预计算出它们的基础反射率，一些常见材质的数值我们可以参考Naty Hoffman的课程讲义：[Physics and Math of Shading](https://blog.selfshadow.com/publications/s2015-shading-course/hoffman/s2015_pbs_physics_math_slides.pdf)。

**法线分布函数：** 决定这一项的是不同微表面朝向的法线分布。当朝向比较集中的时候会得到glossy的结果，如果朝向特别集中指向时认为是 specular 的。当分布杂乱无章时候，得到的结果也就类似diffuse。我们有很多不同的模型来描述法线分布，常用的有 **Beckmann，GGX** 等模型，值得一提的是，闫老师自己也有一系列模型。下面给出 GGX 的公式：
$$
NDF_{GGX TR}(n, h, \alpha) = \frac{\alpha^2}{\pi((n \cdot h)^2 (\alpha^2 - 1) + 1)^2}
$$

α表示表面粗糙度，h可以当成是不同粗糙度参数下，平面法向量和光线方向向量之间的中间向量。

相同的粗糙程度下，由于长尾（long tail）性质，GGX 的效果会更加自然，它的高光到非高光有一个柔和的过渡状态，而 Beckmann 的高光则是到达 grazing angle 后就戛然而止。大多数时候我们希望的是像 GGX 一样的效果。

**几何项：** 几何项又叫 **Shadiowing-Masking** ，它所解决的就是微表面之间的自遮挡问题。与NDF类似，它采用一个材料的粗糙度参数作为输入参数，粗糙度较高的表面其微平面间相互遮蔽的概率就越高。我们将要使用的几何函数是 GGX 与 Schlick-Beckmann 近似的结合体，因此又称为 **Schlick-GGX** ：
$$
G_{SchlickGGX}(n, v, k) = \frac{n \cdot v}{(n \cdot v)(1 - k) + k }
$$

这里的 k 是 α 基于几何函数是针对直接光照还是针对IBL光照的重映射（Remapping）：

$$
k_{direct} = \frac{(\alpha + 1)^2}{8}
$$

$$
k_{IBL} = \frac{\alpha^2}{2}
$$

为了有效的估算几何部分，需要将观察方向（产生几何遮蔽，即Masking）和光线方向向量（产生几何阴影，即Shadowing）都考虑进去。我们可以使用**史密斯法（Smith’s method）** 来把两者都纳入其中：

$$
G(n, v, l, k) = G_{sub}(n, v, k) G_{sub}(n, l, k)
$$

**能量守恒：** 即使当我们正确考虑了以上三项，仍然会出现问题，如下图所示：随着粗糙程度变大，我们渲染得到的结果却越暗，即使认为最左边是抛光，最右边的是哑光，这个结果也是错误的，因此再怎么哑光也不能让白金变成跟石头一样的光泽！

![](https://files.catbox.moe/9sg4yx.png)

这是因为我们没有考虑光线在表面上的**多次弹射**，只考虑了微表面遮挡的情况，当粗糙度越来越大的时候，能量是不守恒的，因此才导致了粗糙度增大引起了能量损失这一现象。因此我们需要把丢失的能量补回去！在离线渲染中，考虑多次bounce就需要在微表面用一个类似光线追踪的方法；在实时渲染，我们的核心思路是将反射光看作两种情况:

- 当不被遮挡的时候，这些光就会被看到；
- 当反射光被微表面遮挡的时候，认为这些被挡住的光将进行后续的弹射，直到能被看到。

于是就有了 **The Kulla-Conty Approximation**。不过关于这个知识点，即使是在英文网络搜索相关信息，查到的也都是 GAMES202 相关笔记等资料，所以这里先按下不表。

**工业界现在使用的近似方法（闫老师评价：COMPLETELY WRONG; COULDN'T BE WORSE; I NEVER TAUGHT YOU SO）：** 即Cook-Torrance 镜面模型结合 Lambert 漫反射：
$$
f_r = k_d f_{lambert} +  k_s f_{cook-torrance}
$$

这里的k<sub>d</sub>是入射光线中被折射部分的能量所占的比率，而k<sub>s</sub>是被反射部分的比率。BRDF的左侧表示的是漫反射部分，这里用f<sub>lambert</sub>来表示，这和漫反射着色中使用的常数因子类似，用如下的公式来表示：

$$
f_{lambert} = \frac{c}{\pi}
$$

c表示表面颜色（回想一下漫反射表面纹理）。除以π是为了对漫反射光进行标准化，因为前面含有BRDF的积分方程是受π影响的。

现在我们将这个 BRDF 模型纳入到最终的反射率方程当中：这个方程完整的描述了一个基于物理的渲染模型，它现在可以认为就是我们一般意义上理解的基于物理的渲染，也就是PBR。

$$
L_o(p,\omega_o) = \int\limits_{\Omega} (k_d\frac{c}{\pi} + k_s\frac{DFG}{4(\omega_o \cdot n)(\omega_i \cdot n)})L_i(p,\omega_i) n \cdot \omega_i  d\omega_i
$$

参考：[LearnOpenGL CN-PBR理论](https://learnopengl-cn.github.io/07%20PBR/01%20Theory/)和[GAMES202-基于物理的材质](https://www.bilibili.com/video/BV1YK4y1T7yY?p=10)

一个不错的总结：[TC130-彻底看懂PBR/BRDF方程](https://zhuanlan.zhihu.com/p/158025828)

### 1.3 PBR实现算法

（demo）

### 2.光线追踪

**还是先按时间轴介绍：** 

1968年：Ray Casting

1980年：Whitted 光线追踪：Whitted，Kay和Greenberg 提出了使用递归的光线追踪来描绘准确的折射和反射。

1984年：分布式光线追踪：Cook 等人提出了分布式光线追踪，其和 path tracing 都使用了蒙特卡洛方法。

1986年：路径追踪：Kajiya将积分输运方程（integral transport equation）称为渲染方程（rendering equation）。他提出的渲染方程成了至今为止几乎所有的全局光照算法的数学依据，在同篇论文中他也提出了最原始路径追踪算法。

再往后的先按下不表。

（待补充）

参考：[GAMES101-Ray Tracing 1~4](https://www.bilibili.com/video/BV1X7411F744?p=13)和[papalqi-光线追踪](https://zhuanlan.zhihu.com/p/72673165)和[孙小磊-重要性采样和多重重要性采样在路径追踪中的应用](https://zhuanlan.zhihu.com/p/360420413)

### 3.体渲染

数学物理原理；SDF；Raymarching；体积光；

### 4.体积云的生成

3D体纹理的制作；噪波的生成；引擎中实现体积云；

（demo）

### 5.水体渲染



### 6.毛发模拟



### 7.屏幕空间反射



### 8.渲染加速与性能优化概述



### 9.皮肤渲染



## 第六章 卡通渲染

### 1.NPR与卡通渲染的风格流派



### 2.卡通渲染描边方案



### 3.卡通渲染着色方案



### 4.卡通渲染案例讲解

（demo）

## 第七章 GPU逻辑管线

### 1.逻辑管线简介/GPU Logical Pipeline

懒了，直接上英文了。

![](https://developer.nvidia.com/sites/default/files/akamai/gameworks/images/lifeofatriangle/fermipipeline_begin.png)

**1.读指令：** The program makes a **drawcall** in the graphics api (DX or GL). This reaches the driver at some point which does a bit of validation to check if things are "legal" and inserts the command in a GPU-readable encoding inside a **pushbuffer**. A lot of bottlenecks can happen here on the CPU side of things, which is why it is important programmers use apis well, and techniques that leverage the power of today's GPUs.

**2.处理指令：** After a while or explicit "flush" calls, the driver has buffered up enough work in a pushbuffer and sends it to be processed by the GPU (with some involvement of the OS). The **Host Interface** of the GPU picks up the commands which are processed via the **Front End**（前端）.

**3.提交三角形：** We start our work distribution in the **Primitive Distributor**（ 图元分配器 ） by processing the indices in the indexbuffer and generating triangle work batches（批次） that we send out to multiple GPCs（Graphics Processing Cluster）.

![](https://developer.nvidia.com/sites/default/files/akamai/gameworks/images/lifeofatriangle/fermipipeline_sm.png)

**4.取三角形数据：** Within a GPC, the **Poly Morph Engine**（多边形引擎） of one of the SMs（Stream Multiprocessor，流多处理器） takes care of fetching the vertex data from the triangle indices (**Vertex Fetch**).

**5.warp调度：** After the data has been fetched, warps（ 线程束 ） of 32 threads are scheduled inside the SM and will be working on the vertices. warp是典型的单指令多线程（SIMT，SIMD单指令多数据的升级）的实现，也就是32个线程同时执行的指令是一模一样的，只是线程数据不一样，这样的好处就是一个warp只需要一个套逻辑对指令进行解码和执行就可以了，芯片可以做的更小更快，之所以可以这么做是由于GPU需要处理的任务是天然并行的。 

**6.warp执行：** The SM's warp scheduler（warp调度器） issues the instructions for the entire warp in-order. The threads run each instruction in lock-step（锁步递进） and can be masked out（遮掩） individually if they should not actively execute it. There can be multiple reasons for requiring such masking. For example when the current instruction is part of the "if (true)" branch and the thread specific data evaluated "false", or when a loop's termination criteria was reached in one thread but not another（例如一条线程break了但是别的还在走）. Therefore having lots of branch divergence in a shader can increase the time spent for all threads in the warp significantly. Threads cannot advance individually, only as a warp! Warps, however, are independent of each other.

**7.多次调度：** The warp's instruction may be completed at once or may take several dispatch turns. For example the SM typically has less units for load/store than doing basic math operations.（确实是这样的，一个SM有16组加载存储单元，有2组共32个Core（运算核心））

**8.内存加载：** As some instructions take longer to complete than others, especially memory loads, the warp scheduler may simply switch to another warp that is not waiting for memory. This is the key concept how GPUs overcome latency of memory reads, they simply switch out groups of active threads. To make this switching very fast, all threads managed by the scheduler have their own registers in the register-file. The more registers a shader program needs, the less threads/warps have space. The less warps we can switch between, the less useful work we can do while waiting for instructions to complete (foremost memory fetches).

![](https://developer.nvidia.com/sites/default/files/akamai/gameworks/images/lifeofatriangle/fermipipeline_memoryflow.png)

**9.过渡：** Once the warp has completed all instructions of the vertex-shader, it's results are being processed by **Viewport Transform**. The triangle gets clipped by the clipspace volume and is ready for rasterization. We use L1 and L2 Caches for all this cross-task communication data.

![](https://developer.nvidia.com/sites/default/files/akamai/gameworks/images/lifeofatriangle/fermipipeline_raster.png)

**10.分割三角形：** Now it gets exciting, our triangle is about to be chopped up and potentially leaving the GPC it currently lives on. The bounding box of the triangle is used to decide which raster engines（光栅引擎） need to work on it, as each engine covers multiple tiles of the screen. It sends out the triangle to one or multiple GPCs via the **Work Distribution Crossbar**. We effectively split our triangle into lots of smaller jobs now.

![](https://developer.nvidia.com/sites/default/files/akamai/gameworks/images/lifeofatriangle/fermipipeline_mid.png)

**11.数据可读性： Attribute Setup** at the target SM will ensure that the interpolants (for example the outputs we generated in a vertex-shader) are in a pixel shader friendly format.

**12.像素信息生成：** The **Raster Engine** of a GPC works on the triangle it received and generates the pixel information for those sections that it is responsible for (also handles back-face culling and Z-cull).

**13.像素块：** Again we batch up 32 pixel threads, or better say 8 times 2x2 pixel quads, which is the smallest unit we will always work with in pixel shaders. This 2x2 quad allows us to calculate derivatives（导数） for things like texture mip map filtering (big change in texture coordinates within quad causes higher mip). Those threads within the 2x2 quad whose sample locations are not actually covering the triangle, are masked out (gl_HelperInvocation). One of the local SM's warp scheduler will manage the pixel-shading task.

**14.还是wrap：** The same warp scheduler instruction game, that we had in the vertex-shader logical stage, is now performed on the pixel-shader threads. The lock-step processing is particularly handy because we can access the values within a pixel quad almost for free, as all threads are guaranteed to have their data computed up to the same instruction point.

![](https://developer.nvidia.com/sites/default/files/akamai/gameworks/images/lifeofatriangle/fermipipeline_end.png)

**15.ROP：** Are we there yet? Almost, our pixel-shader has completed the calculation of the colors to be written to the rendertargets and we also have a depth value. At this point we have to take the original api ordering of triangles into account before we hand that data over to one of the ROP (render output unit) subsystems, which in itself has multiple ROP units. Here depth-testing, blending with the framebuffer and so on is performed. These operations need to happen atomically（原子操作） (one color/depth set at a time) to ensure we don't have one triangle's color and another triangle's depth value when both cover the same pixel. NVIDIA typically applies memory compression（内存压缩）, to reduce memory bandwidth requirements, which increases "effective" bandwidth (see GTX 980 pdf).

参考：[Life of a triangle - NVIDIA's logical pipeline](https://developer.nvidia.com/content/life-triangle-nvidias-logical-pipeline)

### 2.GPU硬件架构十三问/GPU Q&A

参考：[深入GPU硬件架构及运行机制](https://www.cnblogs.com/timlly/p/11471507.html)。这篇文章写得非常不错！

问题如下：

1、GPU是如何与CPU协调工作的？

分离式架构（PC、智能手机）、耦合式架构（游戏主机）。

2、GPU也有缓存机制吗？有几层？它们的速度差异多少？

部分架构的GPU与CPU类似，也有多级缓存结构：寄存器、L1缓存、L2缓存、GPU显存、系统内存，它们的存取速度从寄存器到系统内存依次变慢。

3、GPU的渲染流程有哪些阶段？它们的功能分别是什么？

见7.1节。

4、Early-Z技术是什么？发生在哪个阶段？这个阶段还会发生什么？会产生什么问题？如何解决？

略略略。Early-Z技术会导致一个问题：深度数据冲突（depth data hazard），避免深度数据冲突的方法之一是在写入深度值之前，再次与frame buffer的值进行对比。

5、SIMD和SIMT是什么？它们的好处是什么？co-issue呢？

SIMD（Single Instruction Multiple Data）是单指令多数据，SIMT（Single Instruction Multiple Threads，单指令多线程）是SIMD的升级版，co-issue可以解决SIMD运算单元无法充分利用的问题。

6、GPU是并行处理的么？若是，硬件层是如何设计和实现的？

略。

7、GPC、TPC、SM是什么？Warp又是什么？它们和Core、Thread之间的关系如何？

GPC（Graphics Processing Cluster，图形处理簇），TPC（Texture/Processor Cluster，纹理处理簇），SM（Stream Multiprocessor，流多处理器），Warp（线程束），Warp包含Core（运算核心），每个Core处理一个线程。

8、顶点着色器（VS）和像素着色器（PS）可以是同一处理单元吗？为什么？

对于统一着色器架构（Unified shader Architecture）的GPU，VS和PS用的都是相同的Core。也就是，同一个Core既可以是VS又可以是PS。

9、像素着色器（PS）的最小处理单位是1像素吗？为什么？会带来什么影响？

不是。在像素着色器中，会将相邻的四个像素作为不可分隔的一组，送入同一个SM内4个不同的Core。

10、Shader中的if、for等语句会降低渲染效率吗？为什么？

见7.4节。

11、如下图，渲染相同面积的图形，三角形数量少（左）的还是数量多（右）的效率更快？为什么？

![](https://img2018.cnblogs.com/blog/1617944/201909/1617944-20190906000232145-1801159116.png)

上面的参考文章的后半部分利用扩展进行了一个有趣的实验，从实验结论中我们容易知道：相同面积的区域，如果所属的三角形越多，就会导致分配给SM的次数越多，消耗的渲染性能也越多。

12、GPU Context是什么？有什么作用？

Context是一个对象，是GPU使用的最小数据集，越多Context可用就越可以提升运算单元的吞吐量。

13、造成渲染瓶颈的问题很可能有哪些？该如何避免或优化它们？

见7.5节。

### 3.光栅化与透视矫正插值/Rasterization & Perspective-Correct Interpolation

**直线光栅化算法：** ①DDA数值微分算法（我的软渲染就是用的这个算法）；②中点Bresenham算法。

**三角形光栅化算法：** 

像素点网格会被划分为2X2的组，这样的组叫做 **Quad**。使用贴图LOD时，我们是需要计算UV的微分值的，因此渲染三角形时，都是以Quad作为最小单位的（这在7.1节中也提到过）。也就是说，一个三角形，即使只覆盖了一个Quad中的一个像素，整个Quad中的四个像素都会被光栅化，这样需要额外光栅化的像素点叫做 **Helper Pixel/辅助像素**。这样，如果是比较小的三角形，在渲染时，辅助像素的比例就越高，造成性能浪费。辅助像素的数量也叫做 **quad over-shading**。

如何判断一个像素的中心点是否在三角形内部呢？比较好理解的方式就是使用**叉乘**，例如， 我们事先知道想要光栅化的三角形的三个顶点P0，P1，P2，以及检测点Q。只要分别计算 P<sub>0</sub>P<sub>1</sub> x P<sub>0</sub>Q，P<sub>1</sub>P<sub>2</sub> x P<sub>1</sub>Q，P<sub>2</sub>P<sub>0</sub> x P<sub>2</sub>Q，如果三者同号则代表点P在三条线段的同一边，那么必然处于三角形内部，如果不同号则代表该点一定在三角形外部。

当像素的中心点刚好在某条边上时，就需要一些特殊的处理方案。比如现在有两个三角形共享一条边，如果像素中心刚好在这条共享边上，就需要决定这个像素点是归哪侧所有。首先肯定不能是同时属于两个三角形的，这样会导致像素被计算两次。我们需要自己制定一些规则来决定这些像素点属于哪个三角形，例如DirectX 的 **top-left 规则**：[Rasterization Rules (Windows)](https://docs.microsoft.com/zh-cn/windows/win32/direct3d11/d3d10-graphics-programming-guide-rasterizer-stage-rules?redirectedfrom=MSDN#Triangle)，这在我的软渲染中也有用到。

为了提高效率，通常我们会使用**级联（hierarchical）** 方式来遍历三角形。硬件会先算出整个三角形的AABB，然后测试每个 tile 和AABB是否相交，再测试 tile 是否和三角形相交。测试 AABB 和 tile 相交比较简单。测试 tile 和三角形相交的方式如下，可以直接选择 tile 四个顶点中距离边最近的那个进行测试。如下图中的 4x4的 tile，和边进行相交测试时，只需要判断黑色的顶点是否在边的**正半空间**内。如果测试 tile 都在三条边外侧，则认为 tile 中的像素都不在三角形内。

![](https://files.catbox.moe/nt3i65.jpg)

**透视矫正插值：** 我们的重心坐标往往都是在屏幕空间下所得到的，但如果直接使用屏幕空间下的重心坐标进行插值会造成一定的误差。这里我们省略推导过程，直接给出矫正后的结论：

透视投影下重心坐标任意属性的正确插值是：

$$
I_t = (\alpha \frac{I_A}{Z_A} + \beta \frac{I_B}{Z_B} + \gamma \frac{I_C}{Z_C}) / \frac{1}{Z_t}
$$

其中：Z代表深度值，且

$$
Z_t = \frac{1}{\frac{\alpha}{Z_A} + \frac{\beta}{Z_B} + \frac{\gamma}{Z_C}}
$$

参考：[孙小磊-计算机图形学三：直线光栅化的数值微分算法,中点Brensenham算法和三角形的光栅化](https://zhuanlan.zhihu.com/p/144330664)和[孙小磊-计算机图形学六：透视矫正插值和图形渲染管线总结](https://zhuanlan.zhihu.com/p/144331875)和[TC130-图形学硬件拾遗(一)](https://zhuanlan.zhihu.com/p/371469482)

### 4.if，以及分支/if, and branch

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

### 5.基于GPU架构的渲染优化建议



## 第八章 其他

1.体素

2.球谐光照

3.欧拉旋转与四元变换

4.空间分割加速

5.裁切技术

6.层次细节/LOD

7.通过法线2d渲3d的角色效果

### 8.渲染常用术语整理

英文|缩写|补充说明
:-:|:-:|-
Physically Based Rendering|PBR|大型3D游戏常用的一种渲染流程，有利于保证画面效果的真实感。
Local Illumination||光源直接作用于模型表面的光照效果。
Global Illumation|GI|光源与环境中所有的表面相互作用（光线在物体表面反射、透射，产生新的光线）产生的光照效果，即真实的光照效果，相关算法：辐射度算法（Radiosity）、光线追踪算法（Ray Tracing）
Image-Based Lighting|IBL|使用预处理的环境光贴图来做光源的间接照明方案。
Deferred Rendering|DR|将不接受光照的场景先渲染到Gbuffer，再对Gbuffer应用光照的一种技术，根据实现方式的不同，可以分为两类：Deferred Shading和Deferred Lighting。
Forward Rendering|FR|传统的渲染技术，逐像素点计算光照，当光源较多且场景较复杂时渲染效率较低，但能够比较方便地渲染透明物体。
Anti-Aliasing|AA|Aliasing的实际意义是”采样频率过低导致的图形失真”，学名为”混叠”，具体现象包括图形边缘产生锯齿、画面抖动等。目前主流的AA方法有：（1） MSAA：Multi-Sampling Anti-Aliasing，多重采样抗锯齿（2） FXAA：Fast Approximate Anti-Aliasing，快速近似抗锯齿（3） TXAA：Temporal Anti-Aliasing，时间性抗锯齿（4） SSAA：Super Sampling Anti-Aliasing，超级采样抗锯齿
Tile-based Rendering|TBR|当前移动设备显卡的主流渲染优化方式，将帧缓冲分割为一小块一小块，然后逐块进行渲染。
Precomputed Radiance Transfer|PRT|预处理场景中的光线相互作用，从而实现实时全局光照效果。核心实现原理是利用蒙特卡洛积分和球谐函数对光照信息进行编码。
Spherical Harmonics|SH|球谐函数是定义在单位球表面的基函数，在PRT方法中被用于优化光照计算。
Bidirectional Reflectance Distribution Function|BRDF|描述入射光线经过某个表面反射后如何在各个出射方向上分布的函数表达式。
Bidirectional Transmittance Distribution Function|BTDF|描述入射光线经过某个表面透射后如何在各个出射方向上分布的函数表达式。
Bidirectional Scattering Distribution Function|BSDF|描述入射光线经过某个表面散射后如何在各个出射方向上分布的函数表达式。BSDF = BRDF + BTDF。
Ambient Occlusion|AO|全局光照效果中物体缝隙处的柔和阴影。
Screen Space Ambient Occlusion|SSAO|一种用于模拟环境光遮蔽的近似算法。
Cascaded Shadow Map|CSM|目前大型游戏引擎中采用的主流实时阴影技术。
Parallel-Split Shadow Map|PSSM|CSM的一种实现方式。
Rendering Hardware Interface|RHI|常见的RHI：DirectX 和 OpenGL
Schmidt Orthogonalization||将三维空间内任意线性无关向量组转化为正交向量组的方法。
BlendShape / Morph Animation||顶点混合动画，即多个拓扑结构相同的模型之间根据时间插值产生的动画。
Render to Texture|RTT|将纹理设置为渲染目标，再执行渲染操作，将图元渲染到纹理上。
Level of Detail|LOD|大型3D游戏用于保证游戏帧率的一种优化方式。
Displacement Map|DMAP|用于表示材质表面沿法线方向高度细节的纹理贴图
Pass||指代输入数据（顶点、纹理、常量）经过GPU流水线（VertexShader、PixelShader）的处理后，输出到缓冲（BackBuffer / DepthBuffer / StencilBuffer）中的过程。
Multiple Render Target|MRT|允许像素着色器将计算结果输出到多个不同的缓冲，PC平台中使用Deffered Rendering所必须的一种硬件支持。
Occlusion Culling|OC|通过剔除视锥体内被遮挡的模型网格，达到降低GPU负载的目的。
Depth of Field|DoF|
Circle of Confusion|CoC|在透镜系统中，处于聚焦范围外的物体上的像素点成像会变成一个模糊圈，这是一个非线性映射过程。
Digital Content Creation Tools|DCC Tools|美术创建模型、纹理等资源使用的工具软件，如：3ds Max、Maya、Photoshop等。
Signed Distance Field|SDF|到物体（2D或3D的多边形网格）表面最近距离的采样纹理或网格。通常使用负值表示物体内部到表面的距离，使用正值表示物体外部到表面的距离。SDF常见的应用领域：布料动画碰撞检测、多物体动力学计算、字体渲染等。
Screen Space Reflection|SSR|实时渲染中用于模拟“光滑物体表面反射场景对象”的一种后处理技术
Subsurface Scattering|SSS|光线在材质内部不断折射而形成的视觉效果，常见于玉石、牛奶、人类皮肤等材质中。
Separable Subsurface Scattering|SSSS|模拟次表面散射效果的一种方式
Screen Space Subsurface Scattering|SSSSS|模拟次表面散射效果的一种后处理技术

