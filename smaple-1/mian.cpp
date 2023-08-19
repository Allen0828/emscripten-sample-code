#include <math.h>
#include <memory.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include "ImageWebGL.h"


EM_BOOL draw_frame(double t, void *)
{
  clearScreen(0.1f, 0.2f, 0.3f, 1.f);
  draw();

  return EM_TRUE;
}

int main()
{
  initWebgl(300, 300);
  // 设置循环
  emscripten_request_animation_frame_loop(&draw_frame, 0);
}
