#include <iostream>
#include <GL/gl.h>
#include <GL/freeglut.h>

using namespace std;

static void RenderScene() {

  glClear(GL_COLOR_BUFFER_BIT);
  glutSwapBuffers();

}

int main(int argc, char* argv[]) {

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(400, 400);
  glutInitWindowPosition(200, 200);
  glutCreateWindow("My First Window with FreeGLUT");
  glutDisplayFunc(RenderScene);

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  glutMainLoop();

  cout << "First Window with FreeGLUT!" << endl;;

  return 0;

}
