/* ARDUINO GUITAR FX
 * silly little attempt at making arduino (teensy3.1) effects pedal
 * want to be able to implement differnt clipping shapes with some
 * simple maffs.
 */

// declare pins
int input_pin = A0;
int output_pin = A14;
int threshold_pin = A1;
int comp_rate_pin = A2;

// initialise variables
int input_val = 0;
int output_val = 0;
int threshold = 0;
int comp_rate = 0;

// constants
const comp_min = 0;
const comp_max = 10;

void setup() {
  pinMode(output_pin, OUTPUT);
  analogReadResolution(12);
  analogWriteResolution(12);
}

void loop() {
  
  // read input pin
  input_val = analogRead(input_pin);

  // read threshold pot
  threshold = analogRead(threshold_pin);
  
  // read compression pin and contrain to vals
  comp_rate = analogRead(comp_rate_pin);
  // apply the calibration to the sensor reading
  // still have to set sensor min/max
  comp_rate = map(sensorValue, sensorMin, sensorMax, comp_min, comp_max);
  // in case the sensor value is outside the range seen during calibration
  sensorValue = constrain(sensorValue, comp_min, comp_max);

  // if signal above threshold then divide 
  // its delta by the compression rate
  if (input_val > threshold) {
    
    // apply shaping to value
    output_val = threshold + ((input_val - threshold) / comp_rate);
  }
  else {
    
    // dont apply shaping to value
    output_val = input_val;
  }

  // write it out on the poutput pin :)
  analogWrite(output_pin, output_val);
  
}
