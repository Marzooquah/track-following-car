#include <AFMotor.h>

AF_DCMotor motor1(3, MOTOR12_64KHZ);
AF_DCMotor motor2(4, MOTOR12_64KHZ);

int LeftSensor = A3;
int RightSensor = A2;

int L_sensor_val = 0;
int R_sensor_val = 0;

int threshold_L = 530;
int threshold_R = 130;

int debug = 10;  // Set 1 to Debug & Set Greater than 1 or 10 to Run car


const int trigPin = 2;   // Trig pin of the ultrasonic sensor
const int echoPin = 13;  // Echo pin of the ultrasonic sensor

void setup() {
  motor1.setSpeed(130);
  motor2.setSpeed(130);
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  L_sensor_val = analogRead(LeftSensor);
  R_sensor_val = analogRead(RightSensor);
  //printInfo();

/*

  if (checkObstacle()) {
    Serial.println("obstacle so Stop");
    stopCar();
    delay(1000);
  }
*/
  if (L_sensor_val < threshold_L && R_sensor_val < threshold_R) {
    stopCar();
    /* if (!checkObstacle()) {
      Serial.println("No obstacle so mv FORWARD");
      moveForward();
    }
    */
  }

  if (L_sensor_val > threshold_L && R_sensor_val > threshold_R) {
    moveForward();
  }

  if (L_sensor_val > threshold_L && R_sensor_val < threshold_R) {
    turnLeft();
  }

  if (L_sensor_val < threshold_L && R_sensor_val > threshold_R) {
    turnRight();
  }
}

void turnLeft() {
  Serial.println("turnLeft");

  if (debug > 1) {
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
  } else {
    delay(500);
  }
}

void turnRight() {
  Serial.println("turnRight");

  if (debug > 1) {

    motor1.run(BACKWARD);
    motor2.run(FORWARD);

  } else {
    delay(500);
  }
}

void stopCar() {
  Serial.println("stopCar");

  if (debug > 1) {

    motor1.run(RELEASE);
    motor2.run(RELEASE);
  } else {
    delay(500);
  }
}

void moveForward() {
  Serial.println("FORWARD");

  if (debug > 1) {

    motor1.run(FORWARD);
    motor2.run(FORWARD);
  } else {
    delay(500);
  }
}

void printInfo() {

  Serial.print("L");
  Serial.print(L_sensor_val);
  Serial.print("-");

  Serial.print("R");
  Serial.print(R_sensor_val);
  Serial.println("");
}

bool checkObstacle() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;

  bool obstacleDetected = (distance <= 10);
  if (obstacleDetected) {
    Serial.print("Obstacle detected at distance: ");
    Serial.println(distance);
  }


  return obstacleDetected;
}
/*
void avoidObstacle() {
  // Perform obstacle avoidance here
  // For example, you can make the robot turn left or right to avoid the obstacle
  Serial.println("Avoiding obstacle...");
  turnLeft();

  delay(1000); // Adjust the delay based on your robot's speed and turning capability
}*/
