#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

using namespace std;

int windowWidth = 800;
int windowHeight = 600;

GLuint
  vertexShaderId,
  fragmentShaderId,
  vaoId,
  vboId,
  programId;

const char *VertexShader =
{
  "#version 130\n"\
  "in vec4 in_position;"

  "void main(void)\n"\
  "{\n"\
  "  gl_Position = in_position;"
  "}\n"\
};

const char *FragmentShader =
{
  "#version 130\n"\

  "out vec4 out_color;"

  "void main(void)\n"\
  "{\n"\
  "  out_color = vec4(1, 0, 0, 0);"
  "}\n"\
};

void createWindow(int argc, char *argv[]);
void renderFunction();
void createVBO();
void destroyVBO();
void createShaders();
void destroyShaders();
void cleanup();

int main(int argc, char *argv[])
{
  createWindow(argc, argv);

  glewExperimental = GL_TRUE;
  GLenum glewInitResult = glewInit();
  
  if(glewInitResult != GLEW_OK)
  {
    cout << "ERROR: " << glewGetErrorString(glewInitResult) << endl;
    exit(EXIT_FAILURE);
  }

  cout << "INFO: Opengl Version: " << glGetString(GL_VERSION) << endl;

  createShaders();
  createVBO();

  glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

  glutMainLoop();
  
  return 0;
}

void createWindow(int argc, char *argv[])
{
  glutInit(&argc, argv);

  glutSetOption(
   GLUT_ACTION_ON_WINDOW_CLOSE,
   GLUT_ACTION_GLUTMAINLOOP_RETURNS
  );

  glutInitWindowSize(windowWidth, windowHeight);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

  glutCreateWindow("OpenGL Triangle");

  glutDisplayFunc(renderFunction);
  glutCloseFunc(cleanup);

}

void renderFunction()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); 

  glutSwapBuffers();
}

void createVBO()
{
  GLfloat vertices[] = {
    -0.8f, 0.8f, 0.0f, 1.0,
    0.8f, 0.8f, 0.0f, 1.0,
    -0.8f, -0.8f, 0.0f, 1.0,
    0.8f, -0.8f, 0.0f, 1.0
  };

  GLenum errorCheckValue = glGetError();

  glGenVertexArrays(1, &vaoId);
  glBindVertexArray(vaoId);

  glGenBuffers(1, &vboId);
  glBindBuffer(GL_ARRAY_BUFFER, vboId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

  errorCheckValue = glGetError();
  if(errorCheckValue != GL_NO_ERROR)
  {
    cout << "ERROR: Could not create the VBO. " << gluErrorString(errorCheckValue) << endl;
    exit(-1);
  }

}

void destroyVBO()
{
  GLenum errorCheckValue = glGetError();
  
  glDisableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glDeleteBuffers(1, &vboId);

  glBindVertexArray(0);
  glDeleteVertexArrays(1, &vaoId);

  errorCheckValue = glGetError();
  if(errorCheckValue != GL_NO_ERROR)
  {
    cout << "ERROR: Could not destroy the VBO. " << gluErrorString(errorCheckValue) << endl;
    exit(-1);
  }

}

void createShaders()
{
  GLenum errorCheckValue = glGetError();
  
  vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShaderId, 1, &VertexShader, NULL);
  glCompileShader(vertexShaderId);

  fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderId, 1, &FragmentShader, NULL);
  glCompileShader(fragmentShaderId);

  programId = glCreateProgram();
  
  glAttachShader(programId, vertexShaderId);
  glAttachShader(programId, fragmentShaderId);

  glLinkProgram(programId);
  glUseProgram(programId);

  errorCheckValue = glGetError();
  if(errorCheckValue != GL_NO_ERROR)
  {
    cout << "ERROR: Could not create the shaders. " << gluErrorString(errorCheckValue) << endl;
    exit(-1);
  }

}

void destroyShaders()
{
    GLenum errorCheckValue = glGetError();

    glUseProgram(0);

    glDetachShader(programId, vertexShaderId);
    glDetachShader(programId, fragmentShaderId);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    glDeleteProgram(programId);

    errorCheckValue = glGetError();
    if(errorCheckValue != GL_NO_ERROR)
    {
      cout << "ERROR: Could not destroy the shaders. " << gluErrorString(errorCheckValue) << endl;
      exit(-1);
    }

}

void cleanup()
{
  destroyShaders();
  destroyVBO();
}
