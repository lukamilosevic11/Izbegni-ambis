#include "funkcije.h"
#include <time.h>
#include <stdlib.h>

extern tacka centarPrva;
extern tacka centarDruga;
extern tacka centarTreca;

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

extern tacka kameraPogled;
extern tacka kameraGleda;

extern float prolazLevo;
extern float prolazDesno;

extern float random_num(float min, float max );


/*funkcija koja inicijalizuje koordinate centra za prvo isrctavanje*/
void init() {
    srand(time(NULL));
    /*biranje slucajnih brojeva za velicine objekata*/
    skaliraj_prelaz = random_num(3,6);
    skaliraj_pocetno = random_num(3,6);
    visina = random_num(2,4);

    /*koordinate centra prvog objekta*/
    centarPrva.x = 0;
    centarPrva.y = 0;
    centarPrva.z = 0;

    /*koordinate centra drugog objekta*/
    centarDruga.x = random_num(centarPrva.x + visina*skaliraj_pocetno/2.0 - 1 - visina/2.0,
                               centarPrva.x - visina*skaliraj_pocetno/2.0 + 1 + visina/2.0);
    centarDruga.y = 0;
    centarDruga.z = -visina*skaliraj_prelaz/2.0 + centarPrva.z - visina/2.0;

    /*koordinate centra jedne od ivica*/
    centarIvicaPrva.x = centarPrva.x - visina*skaliraj_pocetno/2.0 + 0.5;
    centarIvicaPrva.y = visina/2.0 + 0.5;
    centarIvicaPrva.z = centarPrva.z;

    /*ivica se skalira u zavisnosti od trans tj. da li se skalira po x ili po z osi*/
    ivicaSkalirano.x = ivicaSkalirano.y = 1;
    ivicaSkalirano.z = visina;

    /*boja ivica*/
    ivicaRGB.x = random_num(0,1);
    ivicaRGB.y = random_num(0,1);
    ivicaRGB.z = random_num(0,1);

    /*koordinate centra jedne od ivica*/
    centarIvicaDruga.x = centarPrva.x + visina*skaliraj_pocetno/2.0 - 0.5;
    centarIvicaDruga.y = visina/2.0 + 0.5;
    centarIvicaDruga.z = centarPrva.z;

    /*koordinate centra jedne od ivica*/
    centarIvicaTreca.x = centarDruga.x;
    centarIvicaTreca.y = visina/2.0 + 0.5;
    centarIvicaTreca.z = centarDruga.z - skaliraj_prelaz*visina/2.0 + 0.5;

    /*ivica se skalira u zavisnosti od trans tj. da li se skalira po x ili po z osi*/
    ivicaSkaliranoTreca.x = visina;
    ivicaSkaliranoTreca.y = ivicaSkaliranoTreca.z = 1;

    /*koordinate centra kocke*/
    centarKocka.x = centarKocka.z = 0;
    centarKocka.y = visina/2.0 + 0.5;

    /*boja kocke*/
    kockaRGB.x = random_num(0,1);
    kockaRGB.y = random_num(0,1);
    kockaRGB.z = random_num(0,1);

    /*koordinate prolaza gde treba kocka da prodje na sledeci objekat*/
    prolazLevo  = centarDruga.x - visina/2.0;
    prolazDesno = centarDruga.x + visina/2.0;

    /*namestanje koordinata kamere*/
    kameraPogled.x = -15;
    kameraPogled.y = 5*visina;
    kameraPogled.z = 20;

}
