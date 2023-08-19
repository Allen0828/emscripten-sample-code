#include <emscripten.h>
#include <emscripten/html5.h>
#include "WechatWebGL.h"

EM_BOOL draw_frame(double t, void *)
{
  clearScreen(1.0f, 0.0f, 0.0f, 1.f);
  
  return EM_TRUE;
}

static void emscriptenExecute()
{
	clearScreen(1.0f, 0.0f, 0.0f, 1.f);
  draw();
}

int main()
{
  initWebgl(300, 300);
  // 设置循环
  emscripten_set_main_loop(&emscriptenExecute, -1, 1);
}