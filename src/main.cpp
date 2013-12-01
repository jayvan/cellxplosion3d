#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/time.h>
#include <algorithm>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "SoundManager.hpp"
#include "game.hpp"
#include "constants.hpp"
#include "shader.hpp"

#ifdef WIN32
#include <windows.h>
#endif /* WIN32 */


using namespace std;

//-------------------------------------------------------------------
// defines
//-------------------------------------------------------------------
#define FRAME_TIME 16.0
#define CALLBACK_QUIT 'q'

//-------------------------------------------------------------------
// GLUT data
//-------------------------------------------------------------------
int scrWidth, scrHeight;
Game* game;

extern shaderProgram g_shader;

//-------------------------------------
// fix lights
//-------------------------------------

void lights(){
  GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
  GLfloat light_diffuse[] = { 0.3, 0.3, 0.3, 1.0 };
  GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, CONSTANTS::LIGHT_POSITION);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}

//-------------------------------------------------------------------
// display
//-------------------------------------------------------------------
void display(void) {
  // set up for perspective drawing
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, scrWidth, scrHeight);
  gluPerspective(40.0, (GLfloat)scrWidth/(GLfloat)scrHeight, 0.1, 1000.0);

  // change to model view for drawing
  glMatrixMode(GL_MODELVIEW);

  // Reset modelview matrix
  glLoadIdentity();

  // Clear framebuffer (both colour and depth buffers)
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // enable rescalling of the normals
  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

  game->render();

  // dump the whole buffer onto the screen should fix my bug
  glFinish();
  glutSwapBuffers();
}

//-------------------------------------------------------------------
// keyboard
//-------------------------------------------------------------------
void keyboard(unsigned char k, int x, int y) {
  // No use for the mouse coordinates on keypress
  (void)x;
  (void)y;

  switch(k) {
    case CALLBACK_QUIT:
      exit(0);
      break;
  }

  game->handleKey(k, true);
}

void keyboardUp(unsigned char k, int x, int y) {
  // No use for the mouse coordinates on keypress
  (void)x;
  (void)y;
  game->handleKey(k, false);
}

// No special keys used yet
void keyboardSpecial(int key, int x, int y) {
  (void)key;
  (void)x;
  (void)y;
}

//-------------------------------------------------------------------
// init
//-------------------------------------------------------------------
void init(int argc, char** argv) {
  (void)argc;
  (void)argv;
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_NORMALIZE);
  //glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);

  // Black Background
  glClearColor(0.00f, 0.00f, 0.00f, 0.0f);

  lights();

  srand(getpid());
  game = new Game();

  //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

//-------------------------------------------------------------------
// reshape
//-------------------------------------------------------------------
void reshape(int w, int h) {
  scrWidth = w;
  scrHeight = h;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, w, h);
  gluPerspective(40.0, (GLfloat)w/(GLfloat)h, 0.1, 1000.0);

  // Reset to modelview matrix mode to avoid confusion later
  glMatrixMode(GL_MODELVIEW);
}

void update(int value) {
  (void)value;
  game->update(FRAME_TIME / 1000.0);
  glutPostRedisplay();
  glutTimerFunc(FRAME_TIME, update, 0);
}

//-------------------------------------------------------------------
// main
//-------------------------------------------------------------------
int main(int argc, char** argv){
  scrWidth = 700;
  scrHeight = 700;

  // intialize glut and main window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH|GLUT_MULTISAMPLE);
  glutInitWindowSize(scrWidth, scrHeight);
  glutCreateWindow("Cellxplosion 3D");
  glewInit();

  // initialize callback
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutKeyboardUpFunc(keyboardUp);
  glutSpecialFunc(keyboardSpecial);
  glutTimerFunc(FRAME_TIME, update, clock());

  init(argc, argv);
  g_shader.initShaders();

  reshape(scrWidth, scrHeight);

  glutMainLoop();

  return 0;
}

