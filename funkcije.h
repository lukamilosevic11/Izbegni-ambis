#ifndef FUNKCIJE_H
#define FUNKCIJE_H

typedef struct{
  float x;
  float y;
  float z;
} tacka;

void onKeyboard(unsigned char key, int x, int y);
void onDisplay(void);
void onReshape(int width, int height);
void postoljeDrugo(void);
void postoljePrvo(void);
void ivicaPrva(void);
void ivicaDruga(void);
void ivicaTreca(void);
void kocka(void);
void setLight(void);
void promenaPostolja(void);
void init(void);
void rezultatF(void);
void onTimer(int value);
float random_num( float min, float max );
float rastojanje(tacka A, tacka B);
#endif
