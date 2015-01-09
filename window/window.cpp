#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

using namespace std;

int width = 600;
int height = 600;
int frameCount = 0;

void initWindow(int argc, char*[]);
void renderFunction(void);
void idleFunction(void);
void timerFunction(int value);

int main(int argc, char* argv[]) {

  initWindow(argc, argv);
  
  GLenum glewInitResult = glewInit();
  if(GLEW_OK != glewInitResult) {
    cout << "ERROR: " << glewGetErrorString(glewInitResult);
    exit(EXIT_FAILURE);
  }

  cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

  glClearColor(1.0f, 0.0f, 0.0f, 0.0f);

  glutMainLoop();

  return 0;

}

void initWindow(int argc, char* argv[]) {

  glutInit(&argc, argv);

  glutSetOption(
    GLUT_ACTION_ON_WINDOW_CLOSE,
    GLUT_ACTION_GLUTMAINLOOP_RETURNS
  );

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(width, height);
  glutInitWindowPosition(200, 200);
  
  glutCreateWindow("My Window");
  
  glutDisplayFunc(renderFunction);
  glutIdleFunc(idleFunction);
  glutTimerFunc(0, timerFunction, 0);

}

void renderFunction(void) {

  frameCount++;

  glClear(GL_COLOR_BUFFER_BIT);
  glutSwapBuffers();
  glutPostRedisplay();

}

void idleFunction(void) {

  glutPostRedisplay();

}

void timerFunction(int value) {

  if(value != 0)
    cout << frameCount << " FPS" << endl;

  frameCount = 0;
  glutTimerFunc(1000, timerFunction, 1);

}
