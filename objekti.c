#include <GL/glut.h>
#include "funkcije.h"

extern tacka centarPrva;
extern tacka centarDruga;

extern tacka centarIvicaPrva;
extern tacka centarIvicaDruga;
extern tacka centarIvicaTreca;
extern tacka ivicaSkalirano;
extern tacka ivicaSkaliranoTreca;
extern tacka ivicaRGB;

extern tacka centarKocka;
extern tacka kockaRGB;

extern float visina;
extern float skaliraj_prelaz;
extern float skaliraj_pocetno;

extern float brzina;
/*postolje po kojem se kockica krece*/
void postoljeDrugo() {
    glPushMatrix();
    brzina > 0.5 ? glColor3f(random_num(0,1),random_num(0,1),random_num(0,1)): glColor3f(0.918, 0.263,0.208);
    glTranslatef(centarDruga.x, centarDruga.y, centarDruga.z);
    glScalef(1,1,skaliraj_prelaz);
    glutSolidCube(visina);
    glPopMatrix();
}

/*postolje po kojem se kockica krece*/
void postoljePrvo() {
    glPushMatrix();
    brzina > 0.5 ? glColor3f(random_num(0,1),random_num(0,1),random_num(0,1)):glColor3f(0.984,0.737, 0.02);
    glTranslatef(centarPrva.x,centarPrva.y,centarPrva.z);
    glScalef(skaliraj_pocetno,1,1);
    glutSolidCube(visina);
    glPopMatrix();
}

/*jedna od ivica od koju se kockica odbija*/
void ivicaPrva() {
    glPushMatrix();
    brzina > 0.5 ?glColor3f(random_num(0,1),random_num(0,1),random_num(0,1)): glColor3f(ivicaRGB.x,ivicaRGB.y, ivicaRGB.z);
    glTranslatef(centarIvicaPrva.x,centarIvicaPrva.y,centarIvicaPrva.z);
    glScalef(ivicaSkalirano.x,ivicaSkalirano.y,ivicaSkalirano.z);
    glutSolidCube(1);
    glPopMatrix();
}


/*jedna od ivica od koju se kockica odbija*/
void ivicaDruga() {

    glPushMatrix();
    brzina > 0.5 ? glColor3f(random_num(0,1),random_num(0,1),random_num(0,1)):glColor3f(ivicaRGB.x,ivicaRGB.y, ivicaRGB.z);
    glTranslatef(centarIvicaDruga.x,centarIvicaDruga.y,centarIvicaDruga.z);
    glScalef(ivicaSkalirano.x,ivicaSkalirano.y,ivicaSkalirano.z);
    glutSolidCube(1);
    glPopMatrix();
}

/*jedna od ivica od koju se kockica odbija*/
void ivicaTreca() {
    glPushMatrix();
    brzina > 0.5 ? glColor3f(random_num(0,1),random_num(0,1),random_num(0,1)):glColor3f(ivicaRGB.x,ivicaRGB.y, ivicaRGB.z);
    glTranslatef(centarIvicaTreca.x,centarIvicaTreca.y,centarIvicaTreca.z);
    glScalef(ivicaSkaliranoTreca.x,ivicaSkaliranoTreca.y,ivicaSkaliranoTreca.z);
    glutSolidCube(1);
    glPopMatrix();
}

/*kockica kojom se upravlja*/
void kocka() {
    glPushMatrix();
    brzina > 0.5 ? glColor3f(random_num(0,1),random_num(0,1),random_num(0,1)):glColor3f(kockaRGB.x,kockaRGB.y,kockaRGB.z);
    glTranslatef(centarKocka.x,centarKocka.y,centarKocka.z);
    glutSolidCube(1);
    glPopMatrix();
}
