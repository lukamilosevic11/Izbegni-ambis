#include <GL/glut.h>
#include <stdio.h>
#include "funkcije.h"

extern tacka kameraPogled;
extern int rezultat;

void rezultatF() {
  char string[15], *pom;
	sprintf(string, "Rezultat: %d", rezultat);

	glDisable(GL_LIGHTING);
	glColor3f(0.69803921568, 0.0666666666, 0.5176470588);

  glRasterPos3f(kameraPogled.x,kameraPogled.y-5,kameraPogled.z-30);
  for (pom = string; *pom != '\0'; pom++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *pom);
  }

	glEnable(GL_LIGHTING);
}
