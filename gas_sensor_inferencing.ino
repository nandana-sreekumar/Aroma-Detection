#include <Multichannel_Gas_GMXXX.h>
#include <Wire.h>
#define SAMPLING_PERIOD_MS  1000 / SAMPLING_FREQ_HZ
#define SAMPLING_FREQ_HZ    4
#define NUM_SAMPLES         8 

// //From Arduino to Processing to Txt or cvs etc.
// //import
// import processing.serial.*;
// //declare
// PrintWriter output;
// Serial udSerial;

// void setup() {
  
// }

//   void draw() {
//     if (udSerial.available() > 0) {
//       String SenVal = udSerial.readString();
//       if (SenVal != null) {
//         output.println(SenVal);
//       }
//     }
//   }

//   void keyPressed(){
//     output.flush();
//     output.close();
//     exit(); 
//   }

GAS_GMXXX<TwoWire> gas;
 
void setup() {
  Serial.begin(115200);
  gas.begin(Wire, 0x08); // use the hardware I2C
  // udSerial = new Serial(this, Serial.list()[0], 115200);
  // output = createWriter ("garlic.txt");
}
 
// void draw() {
//     if (udSerial.available() > 0) {
//       String SenVal = udSerial.readString();
//       if (SenVal != null) {
//         output.println(SenVal);
//       }
//     }
//   }
  
void loop() {
  // put your main code here, to run repeatedly:

  unsigned long timestamp;
  // GM102B NO2 sensor
  // float valNO2 = gas.calcVol(gas.getGM102B());
  // // if (valNO2 > 999) valNO2 = 999;
  // // GM302B C2H5CH sensor
  // float valC2H5CH = gas.calcVol(gas.getGM302B());
  // // if (valC2H5CH > 999) valC2H5CH = 999;
  // // GM502B VOC sensor
  // float valVOC = gas.calcVol(gas.getGM502B());
  // // if (valVOC > 999) valVOC = 999;
  // // GM702B CO sensor
  // float valCO = gas.calcVol(gas.getGM702B());
  // if (valCO > 999) valCO = 999;

  // Print the readings to the console
  // Serial.print("NO2: ");
  // Serial.print(valNO2);
  // Serial.println("");

  // Serial.print("C2H5CH: ");
  // Serial.print(valC2H5CH);
  // Serial.println("");

  // Serial.print("VOC: ");
  // Serial.print(valVOC);
  // Serial.println("");

  // Serial.print("CO: ");
  // Serial.print(valCO);
  // Serial.println("");

  // Serial.println();

  Serial.println("timestamp,voc1,no2,eth,co");
  // Transmit samples over serial port
  for (int i = 0; i < NUM_SAMPLES; i++) {

    // Take timestamp so we can hit our target frequency
    timestamp = millis();

    // Read from GM-X02b sensors (multichannel gas)
    float gm_no2_v = gas.calcVol(gas.getGM102B());
    float gm_eth_v = gas.calcVol(gas.getGM302B());
    float gm_voc_v = gas.calcVol(gas.getGM502B());
    float gm_co_v = gas.calcVol(gas.getGM702B());
  

    // Print CSV data with timestamp
    Serial.print(timestamp);
    Serial.print(",");
    Serial.print(gm_voc_v);
    Serial.print(",");
    Serial.print(gm_no2_v);
    Serial.print(",");
    Serial.print(gm_eth_v);
    Serial.print(",");
    Serial.print(gm_co_v);
    Serial.println();

    // Wait just long enough for our sampling period
    while (millis() < timestamp + SAMPLING_PERIOD_MS);
  }

  // Print empty line to transmit termination of recording
  Serial.println();


  delay(2000);
  
 
}