#include <PS2X_lib.h>



class Joystick{
  private:
    int _max, _sen, _pin0 , _pin1, _codX, _codY;

  public:
    Joystick(int, int, int, int);
    int leer(int);
    float calcPend();
    int maxabs(int, int);
    int calcCOD();
    float calcAng();
    void cuadrante(int, int);
    int valor();
    int getX();
    int getY();
    int calcRadio();
    int MotorDerecho();
    int MotorIzquierdo();

    //implcit declaration
    Joystick();
    int leer(int, int, int, int);
    float calcAng(int, int);
};
