#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// 初始化webgl
void initWebgl(int width, int height);

// 设置背景颜色
void clearScreen(float r, float g, float b, float a);
// 绘制三角形
void draw();


#ifdef __cplusplus
}
#endif
