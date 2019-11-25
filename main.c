#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "funkcije.h"
#include <time.h>
#include <math.h>

#define TIMER_ID 0
#define TIMER_INTERVAL 20
#define KORAK 4

/*koordinate centra objekata*/
tacka centarPrva;
tacka centarDruga;

tacka centarIvicaPrva;
tacka centarIvicaDruga;
tacka centarIvicaTreca;
tacka ivicaSkalirano;
tacka ivicaSkaliranoTreca;
tacka ivicaRGB;

tacka centarKocka;
tacka kockaRGB;

tacka kameraPogled;
tacka kameraGleda;

int animation_ongoing = 1;
/*sluzi pri kretanju kockice levo desno i pri prelasku na sledeci objekat da bi se znalo da li ide po x ili po z osi*/
int znak_x = 1,
    trans = 0,
    znak_z = 0,
    promena =0;

float animation = 0;
/*flag koji govori da li je kockica prosla na sledeci objekat tj. da nije pala u ambis*/
int prosao = 1;
/*sluzi da izbroji koliko puta je neko presao na sledeci objekat da bi se kockica ubrzavala vremenom
ubrzajNakon sluzi da se ubrzava nakon tog odredjenog broja prelaza*/
int brPredjenih = 0, ubrzajNakon = 4;
/*koordinate "prolaska" za sledeci objekat tj. kockica mora da prodje izmedju ovi koordinata da bi uspesno prosla na sledeci objekat*/
float prolazLevo, prolazDesno;
/*brzine*/
float brzina = 0.2, brzinaPada = 0.04, brzinaKamera = 0.05;
/*sluzi da se objekat napravi kada se odaberu slucajni brojevi da ne bi bili uvek iste velicine*/
float visina,
      skaliraj_prelaz,
      skaliraj_pocetno;
/*pracenje oba objekta kamerom pri promeni se uvek udaljavaju */
float kameraPogledPomeraj = 0, kameraGledaPomeraj = 0;

int rezultat = 0;

int main(int argc, char** argv) {

    /*inicijalizacija gluta*/
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1200,700);
    glutCreateWindow("Izbegni amibs");

    /*f-ja za incijalizaciju*/
    init();

    /*funkcije za dogadjaje*/
    glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID);
    glutDisplayFunc(onDisplay);
    glutReshapeFunc(onReshape);
    glutKeyboardFunc(onKeyboard);

    glutMainLoop();

    return 0;
}

void onDisplay(void) {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(kameraPogled.x,kameraPogled.y, kameraPogled.z,
              kameraGleda.x , kameraGleda.y, kameraGleda.z ,
              0           ,      1       ,       0        );
    glPushMatrix();
    kocka();
    postoljePrvo();
    postoljeDrugo();
    ivicaPrva();
    ivicaDruga();
    ivicaTreca();
    setLight();
    glPopMatrix();
    rezultatF();

    glutSwapBuffers();
}


void onKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    /*izlazak iz programa*/
    case 27:
        exit(0);
        break;
    /*promena smera kretanja tj. prelazak na sledeci objekat*/
    case ' ':
        if(!promena && animation_ongoing) {
            brPredjenih++;
            if(brPredjenih > ubrzajNakon){
              brzina += 0.1;
              ubrzajNakon += KORAK;
            }
            promena = 1;
            if(trans ==1) {
                trans = 0;
                /*provera da li je kocka presla na sledeci objekat ili je pala u ambis*/
                prosao = (centarKocka.z > prolazLevo && centarKocka.z < prolazDesno) ? 1 : 0;
                if(prosao == 1)
                  rezultat++;
            }
            else {
                /*provera da li je kocka presla na sledeci objekat ili je pala u ambis*/
                prosao = (centarKocka.x > prolazLevo && centarKocka.x < prolazDesno) ? 1 : 0;
                if(prosao == 1)
                  rezultat++;
                trans = 1;
            }
        }
        break;
    case 'w':
        /*ubrzavanje kamere*/
        brzinaKamera += 0.01;
        break;
    case 'e':
        /*usporavanje kamere*/
        brzinaKamera -=0.01;
        break;
    case 'p':
    case 'P':
        /*pauza*/
        if(!animation_ongoing){
          animation_ongoing = 1;
          glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID);
        }
        else
          animation_ongoing = 0;
        break;
    }
}

void onTimer(int value) {
    if (value != TIMER_ID)
        return;
    if(trans == 0) {
        /*ako je objekat na velikom rastojanju od kamere ubrzati kameru*/
        if(rastojanje(kameraPogled,centarPrva) >= 50)
            brzinaKamera = 0.07;
        /*pomeranje kamere ako je udaljena dovoljno od objekta*/
        if(rastojanje(kameraPogled,centarPrva) >= 30) {
            kameraPogled.x += brzinaKamera;
            kameraPogled.z -= brzinaKamera;

            kameraGleda.x += brzinaKamera;
            kameraGleda.z -= brzinaKamera;
        }
    } else {
        if(rastojanje(kameraPogled,centarDruga) >= 50)
            brzinaKamera = 0.07;
        if(rastojanje(kameraPogled,centarDruga) >= 30) {
            kameraPogled.x += brzinaKamera;
            kameraPogled.z -= brzinaKamera;

            kameraGleda.x += brzinaKamera;
            kameraGleda.z -= brzinaKamera;
        }
    }

    /*pomeranje zavisi od trans tj. da li se pomera po x ili po z osi*/
    if(trans == 0) {
        /*pad kockice u slucaju da nije presao na sledeci objekat*/
        if(!prosao) {
            brzinaKamera = 0;
            if(centarKocka.x >= centarDruga.x + visina/2.0 - 1) {
                animation += brzinaPada;
                centarKocka.y -= animation*animation;
                centarKocka.x += brzina;
            } else
                centarKocka.x += brzina;
        } else {
            /*pomeranje kockice po objektu*/
            if(centarKocka.x < centarPrva.x - skaliraj_pocetno * visina/2.0 + 1.5)
                znak_x = 0;
            else if(centarKocka.x > centarPrva.x + skaliraj_pocetno * visina/2.0 - 1.5) {
                znak_x = 1;
                if(promena)
                    promenaPostolja();
            }
            if(znak_x == 1)
                centarKocka.x = centarKocka.x - brzina;
            else
                centarKocka.x = centarKocka.x + brzina;
        }
    } else {
        /*pad kockice*/
        if(!prosao) {
            brzinaKamera = 0;
            if(centarKocka.z<= centarPrva.z - visina/2.0 + 1) {
                animation += brzinaPada;
                centarKocka.y -= animation*animation;
                centarKocka.z -= brzina;
            } else
                centarKocka.z -= brzina;
        } else {
            /*pomeranje kockice po objektu*/
            if(centarKocka.z < centarDruga.z - skaliraj_prelaz * visina/2.0 + 1.5) {
                znak_z = 0;
                if(promena)
                    promenaPostolja();
            }
            else if(centarKocka.z > centarDruga.z + skaliraj_prelaz * visina/2.0 - 1.5)
                znak_z = 1;
            if(znak_z == 1)
                centarKocka.z = centarKocka.z - brzina;
            else
                centarKocka.z = centarKocka.z + brzina;

        }
    }

    /*ponovno iscrtavanje*/
    glutPostRedisplay();

    /*pozivanje funkcije glutTimerFunc ako je animacija u toku*/
    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID);
    }
}


void onReshape(int width, int height) {
    if (height == 0)
        height = 1;

    float ratio =  width * 1.0 / height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    gluPerspective(60,ratio,1,10000);
    glMatrixMode(GL_MODELVIEW);
}


/*funkcija koja izracunava novi centar za objekte kada kockica predje na sledeci objekat*/
void promenaPostolja() {
    promena = 0;
    if(trans == 0) {
        /*bira se slucajni broj da bi se duzina razlikovala od prethodne duzine objekta*/
        skaliraj_prelaz = random_num(3,6);
        /*racuna se novi centar objekta koji se premesta i koji postaje novi objekat na koji treba kocka da predje*/
        centarDruga.x = random_num(centarPrva.x + visina*skaliraj_pocetno/2.0-1-visina/2.0,
                                   centarPrva.x - visina*skaliraj_pocetno/2.0+1+visina/2.0);
        centarDruga.z = centarPrva.z - visina*skaliraj_prelaz/2.0 - visina/2.0;

        /*racuna se centar jedne od ivica*/
        centarIvicaPrva.x = centarPrva.x - visina * skaliraj_pocetno/2.0 + 0.5;
        centarIvicaPrva.z = centarPrva.z;
        centarIvicaPrva.y = visina/2.0 + 0.5;

        /*ivica se skalira u zavisnosti od trans tj. da li se skalira po x ili po z osi*/
        ivicaSkalirano.x = ivicaSkalirano.y = 1;
        ivicaSkalirano.z = visina;

        /*racuna se centar jedne od ivica*/
        centarIvicaDruga.x = centarPrva.x + visina * skaliraj_pocetno/2.0 - 0.5;
        centarIvicaDruga.y = visina/2.0 + 0.5;
        centarIvicaDruga.z = centarPrva.z;

        /*racuna se centar jedne od ivica*/
        centarIvicaTreca.x = centarDruga.x;
        centarIvicaTreca.y = visina/2.0 + 0.5;
        centarIvicaTreca.z = centarDruga.z - skaliraj_prelaz*visina/2.0 + 0.5;

        /*ivica se skalira u zavisnosti od trans tj. da li se skalira po x ili po z osi*/
        ivicaSkaliranoTreca.x = visina;
        ivicaSkaliranoTreca.y = ivicaSkaliranoTreca.z = 1;

        /*slucajne vrednosti za boju ivica*/
        ivicaRGB.x = random_num(0,1);
        ivicaRGB.y = random_num(0,1);
        ivicaRGB.z = random_num(0,1);

        centarKocka.y = visina/2.0 + 0.5;

        /*racunaju se koordinate prolaza na sledeci objekat*/
        prolazLevo = centarDruga.x - visina/2.0;
        prolazDesno = centarDruga.x + visina/2.0;

    }
    else {
        /*isto kao iznad samo sto se pomera drugi objekat*/
        skaliraj_pocetno = random_num(3,6);
        centarPrva.x = visina*skaliraj_pocetno/2.0 + centarDruga.x + visina/2.0;
        centarPrva.z = random_num(centarDruga.z + visina*skaliraj_prelaz/2.0 - 1 - visina/2.0,
                                  centarDruga.z - visina*skaliraj_prelaz/2.0 + 1 + visina/2.0);

        centarIvicaPrva.x = centarDruga.x;
        centarIvicaPrva.y = visina/2.0 + 0.5;
        centarIvicaPrva.z = centarDruga.z - visina * skaliraj_prelaz/2.0 + 0.5;

        ivicaSkalirano.z = 1;
        ivicaSkalirano.x = visina;

        ivicaRGB.x = random_num(0,1);
        ivicaRGB.y = random_num(0,1);
        ivicaRGB.z = random_num(0,1);

        centarIvicaDruga.x = centarDruga.x;
        centarIvicaDruga.y = visina/2.0 + 0.5;
        centarIvicaDruga.z = centarDruga.z + visina * skaliraj_prelaz/2.0 - 0.5;

        centarIvicaTreca.x = centarPrva.x + skaliraj_pocetno*visina/2.0 - 0.5;
        centarIvicaTreca.y = visina/2.0 + 0.5;
        centarIvicaTreca.z = centarPrva.z;

        ivicaSkaliranoTreca.x = ivicaSkaliranoTreca.y = 1;
        ivicaSkaliranoTreca.z = visina;

        centarKocka.y = visina/2.0 + 0.5;

        prolazLevo  = centarPrva.z - visina/2.0;
        prolazDesno = centarPrva.z + visina/2.0;
    }
}


/*funkcija za odredjivanje slucajnog broja*/
float random_num( float min, float max ) {
    float scale = rand() / (float) RAND_MAX;
    return min + scale * ( max - min );
}

/*funkcija koja racuna rastojanje izmedju dve tacke*/
float rastojanje(tacka A, tacka B) {
    return sqrt((B.x-A.x)*(B.x-A.x)+(B.y-A.y)*(B.y-A.y)+(B.z-A.z)*(B.z-A.z));
}
