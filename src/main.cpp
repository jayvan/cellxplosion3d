#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/time.h>
#include <algorithm>

#include "SoundManager.hpp"
#include "game.hpp"

#ifdef WIN32
#include <windows.h>
#endif /* WIN32 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

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
Game game;

//-------------------------------------
// fix lights
//-------------------------------------

void lights(){
  GLfloat light_position1[] = {50, 50, 0, 1};
  GLfloat light1[] = {0.5, 0.5, 0.5, 1};
  GLfloat light2[] = {0.5, 0.5, .5, 1.0};
  GLfloat zero[] = {0, 0, 0 , 0};

  // setup
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

  glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 25);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light2);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light1);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light2);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
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

  game.render();

  // dump the whole buffer onto the screen should fix my bug
  glFinish();
  glutSwapBuffers();
}

//-------------------------------------------------------------------
// keyboard
//-------------------------------------------------------------------
void keyboard(unsigned char k, int x, int y) {
  switch(k) {
    case CALLBACK_QUIT:
      exit(0);
      break;
  }

  game.handleKey(k, true);
}

void keyboardUp(unsigned char k, int x, int y) {
  game.handleKey(k, false);
}

//-------------------------------------------------------------------
// init
//-------------------------------------------------------------------
void init(int argc, char** argv) {
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);

  // Black Background
  glClearColor(0.00f, 0.80f, 0.80f, 0.0f);

  lights();

  srand(getpid());
  game = Game();

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
  game.update(FRAME_TIME / 1000.0);
  glutPostRedisplay();
  glutTimerFunc(FRAME_TIME, update, 0);
}

//-------------------------------------------------------------------
// main
//-------------------------------------------------------------------
int main(int argc, char** argv){
  int main_window;
  scrWidth = 700;
  scrHeight = 700;

  //SND_ID_1 = SM.LoadSound("card.wav");

  // intialize glut and main window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
  glutInitWindowSize(scrWidth, scrHeight);
  main_window = glutCreateWindow("Cellxplosion 3D");

  // initialize callback
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutKeyboardUpFunc(keyboardUp);
  glutTimerFunc(FRAME_TIME, update, clock());

  init(argc, argv);

  reshape(scrWidth, scrHeight);

  glutMainLoop();

  return 0;
}

