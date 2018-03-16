/*  Etalonnage du zéro de l'accéléromètre.
 *  Les valeurs sont à rentrer dans OZNav / compas.h -> accel_offset[3]
 *  Utiliser la méthode des 6 faces :
 *  C:\Users\Olivier\Documents\Voile\Navigation\NXP\AN4069_offset_calibration.pdf, section 3.2
 *  Online : https://www.nxp.com/docs/en/application-note/AN4069.pdf
 *  2 méthodes possibles. J'utilise la méthode du midpoint.
 */

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_FXAS21002C.h>
#include <Adafruit_FXOS8700.h>

// Pour info, non utilisés ici.
#define SENSITIVITY_2G 4096
#define SENSITIVITY_4G 2048
#define SENSITIVITY_8G 1024
#define SENSITIVITY_MAG 10

Adafruit_FXAS21002C gyro = Adafruit_FXAS21002C(0x0021002C);
Adafruit_FXOS8700 accelmag = Adafruit_FXOS8700(0x8700A, 0x8700B);

void setup()
{
Serial.begin(38400);
  // Initialize the sensors.
  if(!gyro.begin())
  {
    /* There was a problem detecting the gyro ... check your connections */
    Serial.println("Ooops, no gyro detected ... Check your wiring!");
    while(1);
  }
  if(!accelmag.begin(ACCEL_RANGE_2G))
  {
    Serial.println("Ooops, no FXOS8700 detected ... Check your wiring!");
    while(1);
  }
}

void loop() {
  sensors_event_t event; // Need to read raw data, which is stored at the same time
  float Xa_print, Ya_print, Za_print;
  
  accelmag.getEvent(&event);

  // /8 pour 2G, /4 pour 4G et /2 pour 8G. La valeur lue est de 512 pour 1G
  Xa_print = accelmag.accel_raw.x / 8 * (-1);
  Ya_print = accelmag.accel_raw.y / 8 * (-1);
  Za_print = accelmag.accel_raw.z / 8 * (-1);
  
  Serial.print("REGISTER_OFF_X : ");Serial.print(Xa_print);
  Serial.print("\tREGISTER_OFF_Y : ");Serial.print(Ya_print);
  Serial.print("\tREGISTER_OFF_Z : "); Serial.println(Za_print);
  delay(125);
}

