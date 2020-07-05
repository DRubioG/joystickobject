# joystickobject
 Clase para el control de un joystick

## implementación

### Entradas
Para la implementación se han definido 6 variables, de las que 2 son para un joystick que devuelve un valor analógico, otras 2 son para un joystick que devuelva el código y las dos últimas variables son para todos los joysticks
``` C
int _max, _sen, _pin0 , _pin1, _codX, _codY;
```

### Salidas
La clase Joystick devuelve el valor del módulo y el ángulo del Joystick

### Constructor

El constructor puede recibir como variables el valor máximo, el pin0, el pin1 y la sensibilidad, o ninguna de las dos.

``` C
Joystick::Joystick(int max, int pin0, int pin1, int sen) {
  _max = max;
  _pin0 = pin0;
  _pin1 = pin1;
  _sen = sen;
}
```
Este caso es para cuando el joystick devuelve un valor analógico
o
``` C
Joystick::Joystick(){}
```
Este case es para cuando el joystick devuelve un código

### Métodos

Estos son los métodos que implementa la clase.
- int **_leer_**_(int pin)_: este método lee el valor analógico de _pin_ que da el joystick y devuelve su valor digital referenciado al centro del joystick
- int **_maxabs_**_(int valorX, int valorY)_: este método da el valor máximo entre _valorX_ y _valorY_. Este método se utiliza para calcular el "radio" en coordenadas cartesianas.
- int **_getX_**_()_: este método devulve el valor en del pin de la coordenada X
- int **_getY_**_()_: este método devulve el valor en del pin de la coordenada Y
- float **_calcAng_**_()_: este método calcula el ángulo en el que se encuentra el joystick
- **_calcPend_**_()_: este método calcula la pendiente para luego calcular cual es el valor que se llevará al motor.
- **_calcCOD_**_()_: este método calcula el valor que va al motor
- **_calcRadio_**_()_: este método calcula el radio en coordenadas cartesianas, este método tiene en cuenta el valor de la sensibilidad
- **_Motor_**_**_Derecho_**_()_: este método devuelve el valor, que va directo al motor derecho, obtenido con el ángulo y el radio
- **_Motor_**_**_Izquierdo_**_()_: este método devuelve el valor, que va directo al motor derecho, obtenido con el ángulo y el radio
- int **_valor_**_()_: este método es el encargado de comprobar que todo los datos tienen lógica, y saber cuales son los valores que van al motor




## Código

 - ## Joystick.h
 ``` C
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
    int Motor_derecho();
    int Motor_izquierdo();

    //implcit declaration
    Joystick();
    int leer(int, int, int, int);
    float calcAng(int, int);
};

 ```

 - ## Joystick.cpp
``` C
#include "Joystick.h"
#include <Math.h>
#include "Arduino.h"


Joystick::Joystick(int max, int pin0, int pin1, int sen) {
  _max = max;
  _pin0 = pin0;
  _pin1 = pin1;
  _sen = sen;

}

int Joystick::leer(int pin) {
  int lectura, lect_r = 0;
  lectura = analogRead(pin);
  //Serial.println(lectura);
  lect_r = lectura - (_max / 2);
  if (lect_r > ((_max / 2) - 1)) {
    return lect_r = ((_max / 2) - 1);
  }
  if (lect_r < -((_max / 2) - 1)) {
    return lect_r = -((_max / 2) - 1);
  }
  return lect_r;
}

int Joystick::maxabs(int q, int w) {  //obtengo la coordenada de mayor valor, que es la que me da la mitad del lado con la que obtengo el codigo que va al motor
  int e = abs(q);
  int r = abs(w);
  return max(e, r);
}
/*
  void Joystick::cuadrante(int a, int b) {    //me da el cuadrante
  if ((a > 0) && (b > 0)) {
    Serial.println("Primer cuadrante");
  }
  if ((a > 0) && (b < 0)) {
    Serial.println("Segundo cuadrante");
  }
  if ((a < 0) && (b < 0)) {
    Serial.println("tercer cuadrante");
  }
  if ((a < 0) && (b > 0)) {
    Serial.println("cuarto cuadrante");
  }
  if ((a == 0) && (b == 0)) {
    Serial.println("Centro");
  }
  }
*/
int Joystick::getX() {
  _codX = leer(_pin0);
  return _codX;
}
int Joystick::getY() {
  _codY=leer(_pin1);
  return _codY;
}
float Joystick::calcAng() {   //me calcula el angulo
  float angulo = 0;
  int a = getX();
  int b = getY();
  angulo = atan2(a , (b * 1.0)) * (180 / PI);
  return angulo;
}

float Joystick::calcPend() {
  float m = 0;

  m = ((255 - 0) / ((((_max / 2) - 1) - _sen) * 1.0));
  return m;
}

int Joystick::calcCOD() {  //me calcula el código que va al motor
  int radio = calcRadio();
  int codigo = 0;
  float m = calcPend();
  if (radio != 0) {
    codigo = m * (radio - _sen);
  }
  return codigo;
}
int Joystick::calcRadio() {
  int radio = 0;
  if (maxabs(_codX, _codY) < _sen) {
    _codX = 0;
    _codY = 0;
    radio = 0;
  } else {
    radio = maxabs(_codX, _codY);
  }
  return radio;
}
int Joystick::Motor_derecho() {
  int cod = 0, angulo = 0;

  cod = calcCOD();
  Serial.print("Codigo derecha ->");
  Serial.println(cod);
  angulo = calcAng();
  if ((0 <= angulo) && (angulo <= 90)) {
    return cod / (90 / (angulo * 1.0));
  } else if ((angulo > 90) && (angulo <= 180)) {
    return cod;
  } else if ((angulo < 0) && (angulo > -90)) {
    return cod / (90 / (angulo * 1.0));
  } else if ((angulo > -180) && (angulo <= -90)) {
    return -cod;
  }
  /*if (angulo == 0) {
    return cod;
    }*/
}
int Joystick::Motor_izquierdo() {
  int cod = 0, angulo = 0;

  cod = calcCOD();
  angulo = calcAng();
  if ((0 <= angulo) && (angulo <= 90)) {
    return cod;
  }
  if ((angulo > 90) && (angulo < 180)) {
    return cod / (90 / ((180 - angulo) * 1.0));
  }
  if ((angulo < 0) && (angulo > -90)) {
    return -cod;
  }
  if ((angulo > -180) && (angulo <= -90)) {
    return -cod / (90 / ((angulo + 180)));
  }
}
int Joystick::valor() {
  int  angulo = 0 , cod = 0, codD = 0, codI = 0;
  float radio = 0, pend = 0;

  //Serial.print("\tCuadrante: ");
  //cuadrante(x, y);
  angulo = calcAng();
  Serial.print("\t\tangulo: ");
  Serial.println(angulo);
  // pend = calcPen();
  cod = calcCOD();
  Serial.print("\t\tcodigo: ");
  Serial.println(cod);
  codD = Motor_derecho();
  Serial.print("\t\tcodigo Derecho: ");
  Serial.println(codD);
  codI = Motor_izquierdo();
  Serial.print("\t\tcodigo Izquierdo: ");
  Serial.println(codI);
}



//implicit declaration
Joystick::Joystick(){}

int Joystick::leer(int max, int codX, int codY, int sen) {
  _max = max;
  _codX = codX;
  _codY = codY;
  _sen = sen;

  int  angulo = 0 , cod = 0, codD = 0, codI = 0;
  float radio = 0, pend = 0;

  //Serial.print("\tCuadrante: ");
  //cuadrante(x, y);
  angulo = calcAng(_codX, _codY);
  Serial.print("\t\tangulo: ");
  Serial.println(angulo);
  // pend = calcPen();
  cod = calcCOD();
  Serial.print("\t\tcodigo: ");
  Serial.println(cod);
  codD = Motor_derecho();
  Serial.print("\t\tcodigo Derecho: ");
  Serial.println(codD);
  codI = Motor_izquierdo();
  Serial.print("\t\tcodigo Izquierdo: ");
  Serial.println(codI);
}
float Joystick::calcAng(int a, int b) {   //me calcula el angulo
  float angulo = 0;
  angulo = atan2(a , (b * 1.0)) * (180 / PI);
  return angulo;
}

```