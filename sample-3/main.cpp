#include "webgl.h"
#include <math.h>
#include <memory.h>
#include <emscripten.h>
#include <emscripten/html5.h>

#define WIDTH 1024
#define HEIGHT 768



EM_BOOL DrawFrame(double t, void *)
{
  ClearScreen(0.1f, 0.2f, 0.3f, 1.f);
  UpdateVideo(WIDTH-250.f, HEIGHT - 250.f, 2.f, 1.f, 1.f, 1.f, 1.f, "dance.mp4");

  return EM_TRUE;
}

int main()
{
  InitWebgl(WIDTH, HEIGHT);
  emscripten_request_animation_frame_loop(&DrawFrame, 0);
}
