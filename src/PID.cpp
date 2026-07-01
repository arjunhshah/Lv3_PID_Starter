#include "PID.h"
#include "vex.h"

void PID(double target, double maxIntegral, double tolerance) {
  double error = target;

  double derivative = 0;
  double integral = 0;
  double lastError = error;
  double total = 0;
  double kP = 7;
  double kI = 0.5;
  double kD = 0.05;
  inertialSensor.setRotation(0, degrees);
  const double gearRatio = 5.0 / 3;
  const double wheelDiameter = 3.25;
  const double deltaT = 0.015;
  double wheelRotation = M_PI * wheelDiameter;
  while (fabs(error) > tolerance) {
    double sensorValue =
        (inertialSensor.rotation(degrees) / 360) * wheelRotation / gearRatio;
    error = target - sensorValue;
    integral += error * deltaT;

    if (integral > maxIntegral) {
      integral = maxIntegral;
    } else if (integral < -maxIntegral) {
    }

    derivative = (error - lastError) / deltaT;
    lastError = error;

    total = kP * error + kI * integral + kD * derivative;
    LeftBack.spin(forward, total, percent);
    RightBack.spin(reverse, total, percent);
    LeftFront.spin(forward, total, percent);
    RightFront.spin(reverse, total, percent);
    LeftMiddle.spin(forward, total, percent);
    RightMiddle.spin(reverse, total, percent);

    wait(15, msec);
  }
  LeftBack.stop(brake);
  RightBack.stop(brake);
  RightFront.stop(brake);
  LeftFront.stop(brake);
  LeftMiddle.stop(brake);
  RightMiddle.stop(brake);
  wait(50, msec);
}
