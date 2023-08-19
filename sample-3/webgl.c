#include <emscripten.h> // For emscripten_get_device_pixel_ratio()
#include <emscripten/html5.h> // For Emscripten HTML5 WebGL context creation API
#include <webgl/webgl1.h> // For Emscripten WebGL API headers (see also webgl/webgl1_ext.h and webgl/webgl2.h)
#include <string.h> // For NULL and strcmp()
#include <assert.h> // For assert()
#include <stdio.h>


void set_texture_id(GLuint texture_id);
void video_update();


static EMSCRIPTEN_WEBGL_CONTEXT_HANDLE glContext;
static GLuint quad, colorPos, matPos;
static float pixelWidth, pixelHeight;

static GLuint compile_shader(GLenum shaderType, const char *src)
{
   GLuint shader = glCreateShader(shaderType);
   glShaderSource(shader, 1, &src, NULL);
   glCompileShader(shader);
   return shader;
}

static GLuint create_program(GLuint vertexShader, GLuint fragmentShader)
{
   GLuint program = glCreateProgram();
   glAttachShader(program, vertexShader);
   glAttachShader(program, fragmentShader);
   glBindAttribLocation(program, 0, "pos");
   glLinkProgram(program);
   glUseProgram(program);
   return program;
}

static GLuint create_texture()
{
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  return texture;
}


static GLuint videoId; 


void InitWebgl(int width, int height)
{
  double dpr = emscripten_get_device_pixel_ratio();
  emscripten_set_element_css_size("canvas", width / dpr, height / dpr);
  emscripten_set_canvas_element_size("canvas", width, height);

  EmscriptenWebGLContextAttributes attrs;
  emscripten_webgl_init_context_attributes(&attrs);
  attrs.alpha = 0;
#if MAX_WEBGL_VERSION >= 2
  attrs.majorVersion = 2;
#endif
  printf("webgl version = %d \n", attrs.majorVersion);
  glContext = emscripten_webgl_create_context("canvas", &attrs);
  assert(glContext);
  emscripten_webgl_make_context_current(glContext);

  pixelWidth = 2.f / width;
  pixelHeight = 2.f / height;

  static const char vertex_shader[] =
    "attribute vec4 pos;"
    "varying vec2 uv;"
    "uniform mat4 mat;"
    "void main(){"
      "uv=pos.xy;"
      "gl_Position=mat*pos;"
    "}";
  GLuint vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);

  static const char fragment_shader[] =
    "precision lowp float;"
    "uniform sampler2D tex;"
    "varying vec2 uv;"
    "uniform vec4 color;"
    "void main(){"
      "gl_FragColor=color*texture2D(tex,uv);"
    "}";
  GLuint fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

  GLuint program = create_program(vs, fs);
  colorPos = glGetUniformLocation(program, "color");
  matPos = glGetUniformLocation(program, "mat");
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glGenBuffers(1, &quad);
  glBindBuffer(GL_ARRAY_BUFFER, quad);
  const float pos[] = { 0, 0, 1, 0, 0, 1, 1, 1 };
  glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  unsigned int whitePixel = 0xFFFFFFFFu;
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &whitePixel);
}


void ClearScreen(float r, float g, float b, float a)
{
  glClearColor(r, g, b, a);
  glClear(GL_COLOR_BUFFER_BIT);
}

void UpdateVideo(float x0, float y0, float scale, float r, float g, float b, float a, const char *url)
{
  if (!videoId)
  {
    videoId = create_texture();
    set_texture_id(videoId);
  } 
  else 
  {
    video_update();
    float mat[16] = { (160-x0)*pixelWidth, 0, 0, 0, 
                      0, (90-y0)*pixelHeight, 0, 0, 
                      0, 0, 1, 0, 
                      x0*pixelWidth-1.f, y0*pixelHeight-1.f, 0, 1};

    glUniformMatrix4fv(matPos, 1, 0, mat);
    glUniform4f(colorPos, r, g, b, a);
    glBindTexture(GL_TEXTURE_2D, videoId);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  }

}
