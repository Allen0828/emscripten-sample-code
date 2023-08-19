#include <math.h>
#include <memory.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include "ImageWebGL.h"

// 初始化宽高
#define WIDTH 1024
#define HEIGHT 768

EM_BOOL draw_frame(double t, void *)
{
  clearScreen(0.1f, 0.2f, 0.3f, 1.f);
  draw();

  return EM_TRUE;
}

int main()
{
  initWebgl(WIDTH, HEIGHT);
  // 设置循环
  emscripten_request_animation_frame_loop(&draw_frame, 0);
}
