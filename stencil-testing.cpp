/*利用模板测试绘制物体轮廓
1.在绘制（需要添加轮廓的）物体之前，将模板函数设置为GL_ALWAYS，每当物体的片段被渲染时，将模板缓冲更新为1。
渲染物体。
2.禁用模板写入以及深度测试。
3.将每个物体放大一点点。
4.使用一个不同的片段着色器，输出一个单独的（边框）颜色。
5.再次绘制物体，但只在它们片段的模板值不等于1时才绘制。
6.再次启用模板写入和深度测试。
*/
glEnable(GL_DEPTH_TEST);
glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);  

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); 

glStencilMask(0x00); // 记得保证我们在绘制地板的时候不会更新模板缓冲
normalShader.use();
DrawFloor()  

glStencilFunc(GL_ALWAYS, 1, 0xFF); 
glStencilMask(0xFF); 
DrawTwoContainers();

glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
glStencilMask(0x00); 
glDisable(GL_DEPTH_TEST);
shaderSingleColor.use(); 
DrawTwoScaledUpContainers();

glStencilMask(0xFF);
glEnable(GL_DEPTH_TEST);  