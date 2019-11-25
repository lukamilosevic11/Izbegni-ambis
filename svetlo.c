#include <GL/glut.h>

/*svetlo*/
void setLight() {

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE) ;
    glEnable (GL_COLOR_MATERIAL) ;
    glShadeModel(GL_SMOOTH);

    GLfloat light_position[] = { 1, 1, 0, 0 };
    GLfloat light_ambient[]  = { 0.2, 0.2, 0.2, 1 };
    GLfloat light_diffuse[]  = { 0.8, 0.8, 0.8, 1 };
    GLfloat light_specular[] = { 1, 1, 1, 1 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}
