#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Creates WebGL context on DOM canvas element with ID "canvas". Sets CSS size and render target size to width&height.
void InitWebgl(int width, int height);

// WebGL canvas clear
void ClearScreen(float r, float g, float b, float a);

// Draws an image from given url to pixel coordinates x0,y0, applying uniform scaling factor scale, modulated with rgba. 
void UpdateVideo(float x0, float y0, float scale, float r, float g, float b, float a, const char *url);

#ifdef __cplusplus
}
#endif
