#include "SDL_OGL.hpp"
#include "SoundManager.hpp"
#include <string>

using namespace std;

#define MICKEY 1
float xpos = 0, ypos = 0;
int oldx = 0, oldy = 0;

int music_on = 0;

void makeMickey()
	{
          GLUquadricObj* qsphere = gluNewQuadric();
          glNewList(MICKEY, GL_COMPILE);

          gluQuadricDrawStyle(qsphere, GLU_FILL);
          gluQuadricNormals(qsphere, GLU_SMOOTH);
          gluQuadricOrientation(qsphere, GLU_OUTSIDE);
          gluQuadricTexture(qsphere, GL_FALSE);

          glColor3f(1,1,0);
          gluSphere(qsphere, 13, 20, 20);
          glTranslatef(14,14,0);
          gluSphere(qsphere, 10, 20, 20);
          glTranslatef(-28,0,0);
          gluSphere(qsphere, 10, 20, 20);
          glEndList();
          gluDeleteQuadric(qsphere);
	}

void DrawGLScene(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glLoadIdentity(); // Reset the view

    // move the scene
    glTranslatef(xpos, ypos, -150);
    // draw s simple sphere
    glCallList(MICKEY);

    SDL_GL_SwapBuffers(); // Swap the buffers
}


void handleKey(SDL_KeyboardEvent key) {
  switch(key.keysym.sym) {
  case SDLK_m:
    if(key.state == SDL_PRESSED) {
	SM.PlaySound(0);
    } else {
	SM.StopSound(0);
    }// if
    break;
  case SDLK_n:
    if(key.state == SDL_PRESSED) {
	SM.PlaySound(1);
    } else {
	SM.StopSound(1);
    }// if
    break;
  case SDLK_b:
    if(key.state == SDL_PRESSED) {
	SM.PlaySound(2);
    } else {
	SM.StopSound(2);
    }// if
    break;
  case SDLK_t:
    if(key.state == SDL_PRESSED) {
       if (music_on == 0) {
          SM.PlayMusic(0);
          music_on = 1;
       } else {
	   SM.StopMusic(0);
	   music_on = 0;
       }
    }// if
    break;
  }// switch

}

int main(int argc, char *argv[])
{
  Uint8* keys;
  int done=0;

  SM.LoadSound("card.wav");
  SM.LoadSound("OBS.wav");
  SM.LoadSound("ghost.wav");
  SM.LoadMusic("UNREAL.S3M");


  // Create a new OpenGL window with the title "Cone3D Basecode" at
  // 640x480x32, fullscreen and check for errors along the way
  if(CreateGLWindow("SDL & OpenGL", 640, 480, 16, 0) == 0){
      printf("Could not initalize OpenGL :(\n\n");
      KillGLWindow();
      return 0;
  }


  // Hide the mouse cursor
  // SDL_ShowCursor(0);


  makeMickey();
  while(!done){

    // Draw the scene
    DrawGLScene();

    // And poll for events
    SDL_Event event;
    while ( SDL_PollEvent(&event) ) {
      switch (event.type) {
      case SDL_KEYDOWN:
      case SDL_KEYUP:
	  handleKey(event.key);
	  break;
      case SDL_QUIT:
        // then we're done and we'll end this program
        done=1;
        break;
      default:
        break;
      }// switch

    }// while

    // Get the state of the keyboard keys
    keys = SDL_GetKeyState(NULL);

    // and check if ESCAPE has been pressed. If so then quit
    if(keys[SDLK_ESCAPE]) done=1;
  }


  KillGLWindow();
  return 0;
}
