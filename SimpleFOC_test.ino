#include <SimpleFOC.h>
#include <PciManager.h>
#include <PciListenerImp.h>

// encoder instance
Encoder encoder = Encoder(A0, A1, 400);
// interrupt routine intialisation
void doA() {
  encoder.handleA();
}
void doB() {
  encoder.handleB();
}

// encoder interrupt init
PciListenerImp listenerA(encoder.pinA, doA);
PciListenerImp listenerB(encoder.pinB, doB);

//driver instance
BLDCDriver3PWM driver = BLDCDriver3PWM(3, 5, 6);

// BLDCMotor(int pole_pairs)
BLDCMotor motor = BLDCMotor(24, 3.7);

void setup() {
  // monitoring port
  Serial.begin(115200);

  // enable/disable quadrature mode
  encoder.quadrature = Quadrature::ON;
  // check if you need internal pullups
  encoder.pullup = Pullup::USE_EXTERN;
  // initialise encoder hardware
  encoder.init();
  // interrupt initialization
  PciManager.registerListener(&listenerA);
  PciManager.registerListener(&listenerB);
  // link the motor to the sensor
  motor.linkSensor(&encoder);
  Serial.println("Encoder ready");

  // driver init
  driver.pwm_frequency = 32000;
  // power supply voltage [V]
  driver.voltage_power_supply = 9;
  driver.voltage_limit = 9;
  driver.init();
  
  // linking the driver to the motor
  motor.linkDriver(&driver);
  Serial.println("Driver ready");

  // set the torque control type
  motor.torque_controller = TorqueControlType::voltage;
  // set motion control loop to be used
  motor.controller = MotionControlType::torque;
  
  motor.useMonitoring(Serial);
  motor.monitor_variables = _MON_TARGET | _MON_VEL | _MON_ANGLE; 

  // initialize motor
  motor.init();
  // align sensor and start FOC
  motor.initFOC();

  _delay(1000);
}

void loop() {
  // display the angle and the angular velocity to the terminal
  //Serial.print(encoder.getAngle());
  //Serial.print("\t");
  //Serial.println(encoder.getVelocity());

  motor.loopFOC(); //FOC
  motor.move(1);
  motor.monitor();
}
