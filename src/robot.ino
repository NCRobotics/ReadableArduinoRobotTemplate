/*
Published under BSD 2.0 license
Code by Gary Needham

Code written for Arudino ADK based on robots seen in the
CREATE Open Robotics League.  This is an attempt to develop
template code that will allow teams to download starter code
and then adapt it to their own robots.

There are many who have worked on similar code ahead of me.
YETIbotics in particular have contributed much to this community.

Also presumed is the use of:
  Cytron MDD10A motor controllers,
  XBOX 360 remotes (use USB Host Shield 2.0 Library)
    Additional remotes may work with changes only to the remote code
  Wiring or a preprinted board compatible with the programming
    JLI Robotics ARC Reactor is an option

Development tools: Atom with PlatformIO
*/

/*
To get started:
1.  Change MDD10A.h to the correct pinout configuration
    based on your shield or wiring.
2.  Verify the XBox button mapping in the controllerRead function
3.  Set the motors in the constants later in this code to the proper
    motor controllers in the MDD10A case statement.  If you use more
    motors, define them accordingly.
    Motor controller 1, motor 1 = 0
    Motor controller 1, motor 2 = 1
    Motor controller 2, motor 1 = 2
    Motor controller 2, motor 2 = 3
    Motor controller 3, motor 1 = 4
    Motor controller 3, motor 2 = 5
    Motor controller 4, motor 1 = 6
    Motor controller 4, motor 2 = 7
*/

// Arduino standard libraries



bool autoRunning = false;
int motorDelay = 0;

/* Function descriptions
setup() - the standard arduino setup routine
loop() - the standard arduino running system after setup
autonomousRunner() - to run the autonomous during matches
controllerRead() - to read the XBox controller(s)
setMotorSpeeds() - to convert the XBox readings to drive motor speeds
writeRobot() - to make the motors move!
*/

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
}

void loop() {
    // put your main code here, to run repeatedly:
    controllerRead ();
    if (autoRunning) {
      autonomousRunner();
    }
    motorDelay++;  // Only write to the motors a few times per second
    if (motorDelay >= 20) {
      motorDelay = 0;
      setDriveSpeeds();
      writeRobot();
    }
}

// Variable definitions for variables in robot.ino functions only
const int driverMode = 1; // 1 = tank drive, 2=H-drive / drone-style
float LeftX = 0;
float LeftY = 0;
float RightX = 0;
float RightY = 0;
float DriveLeftSpeed = 0;
float DriveRightSpeed = 0;
float DriveLFSpeed = 0;
float DriveLRSpeed = 0;
float DriveRFSpeed = 0;
float DriveRRSpeed = 0;
float DriveSideSpeed = 0;
float liftSpeed = 0;
float clawSpeed = 0;
// The constants below assign motor controllers in MDD10A.cpp switch statement
// Change these and/or define more based on motor control needs. This is
// preferred to changing other variables that reference the electronics.
const int LeftDrive1 = 0;
const int LeftDrive2 = 1;
const int RightDrive1 = 2;
const int RightDrive2 = 3;
const int LiftMotor = 4;
const int ClawMotor = 5;

void autonomousRunner () {
  autoRunning = false; //this should be the last line of your atonomous code
}

// This code is modified from the USB Host Shield example code
// XBox360 is used here; to change it, copy from the appropriate example
void controllerRead() {
  Usb.Task();
  if (Xbox.XboxReceiverConnected) {
    for (uint8_t i = 0; i < 4; i++) {
      if (Xbox.Xbox360Connected[i]) {
        if (Xbox.getButtonPress(L2, i) || Xbox.getButtonPress(R2, i)) {
          Serial.print("L2: ");
          Serial.print(Xbox.getButtonPress(L2, i));
          Serial.print("\tR2: ");
          Serial.println(Xbox.getButtonPress(R2, i));
          Xbox.setRumbleOn(Xbox.getButtonPress(L2, i), Xbox.getButtonPress(R2, i), i);
        }

        if (Xbox.getAnalogHat(LeftHatX, i) > 7500) {
          LeftX = map(Xbox.getAnalogHat(LeftHatY), 7500, 32767, 0, 255);
        }
        if (Xbox.getAnalogHat(LeftHatX, i) < -7500) {
          LeftX = map(Xbox.getAnalogHat(LeftHatY), -7500, -32767, 0, -255);
        }
        if (Xbox.getAnalogHat(LeftHatY, i) > 7500) {
          LeftY = map(Xbox.getAnalogHat(LeftHatY), 7500, 32767, 0, 255);
        }
        if (Xbox.getAnalogHat(LeftHatY, i) < -7500) {
          LeftY = map(Xbox.getAnalogHat(LeftHatY), -7500, -32767, 0, -255);
        }
        if (Xbox.getAnalogHat(RightHatX, i) > 7500) {
          RightX = map(Xbox.getAnalogHat(RightHatY), 7500, 32767, 0, 255);
        }
        if (Xbox.getAnalogHat(RightHatX, i) < -7500) {
          RightX = map(Xbox.getAnalogHat(RightHatY), -7500, -32767, 0, -255);
        }
        if (Xbox.getAnalogHat(RightHatY, i) > 7500) {
          RightY = map(Xbox.getAnalogHat(RightHatY), 7500, 32767, 0, 255);
        }
        if (Xbox.getAnalogHat(RightHatY, i) < -7500) {
          RightY = map(Xbox.getAnalogHat(RightHatY), -7500, -32767, 0, -255);
        }

        if (Xbox.getButtonClick(UP, i)) {
          Xbox.setLedOn(LED1, i);
          Serial.println(F("Up"));
        }
        if (Xbox.getButtonClick(DOWN, i)) {
          Xbox.setLedOn(LED4, i);
          Serial.println(F("Down"));
        }
        if (Xbox.getButtonClick(LEFT, i)) {
          Xbox.setLedOn(LED3, i);
          Serial.println(F("Left"));
        }
        if (Xbox.getButtonClick(RIGHT, i)) {
          Xbox.setLedOn(LED2, i);
          Serial.println(F("Right"));
        }

        if (Xbox.getButtonClick(START, i)) {
          Xbox.setLedMode(ALTERNATING, i);
          Serial.println(F("Start"));
        }
        if (Xbox.getButtonClick(BACK, i)) {
          Xbox.setLedBlink(ALL, i);
          Serial.println(F("Back"));
        }
        if (Xbox.getButtonClick(L3, i))
          Serial.println(F("L3"));
        if (Xbox.getButtonClick(R3, i))
          Serial.println(F("R3"));

        if (Xbox.getButtonClick(L1, i))
          clawSpeed = -100;
        if (Xbox.getButtonClick(R1, i))
          clawSpeed = 100;
        if (Xbox.getButtonClick(XBOX, i)) {
          Xbox.setLedMode(ROTATING, i);
          Serial.print(F("Xbox (Battery: "));
          Serial.print(Xbox.getBatteryLevel(i)); // The battery level in the range 0-3
          Serial.println(F(")"));
        }
        if (Xbox.getButtonClick(SYNC, i)) {
          Serial.println(F("Sync"));
          Xbox.disconnect(i);
        }

        if (Xbox.getButtonClick(A, i))
          liftSpeed = 150;
        if (Xbox.getButtonClick(B, i))
          liftSpeed = -150;
        if (Xbox.getButtonClick(X, i))
          autoRunning = true;
        if (Xbox.getButtonClick(Y, i))
          Serial.println(F("Y"));
      }
    }
  }
}

void setDriveSpeeds() {
  switch (driverMode) {
    case 1:
      // Tank Drive
      DriveLeftSpeed = LeftY - LeftX;
      if (DriveLeftSpeed > 255) {
        DriveLeftSpeed = 255;
      }
      else if (DriveLeftSpeed < -255) {
        DriveLeftSpeed = -255;
      }
      DriveRightSpeed = LeftY + LeftX;
      if (DriveRightSpeed > 255) {
        DriveRightSpeed = 255;
      }
      else if (DriveRightSpeed < -255) {
        DriveRightSpeed = -255;
      }
    break;

    case 2:
      // H-Drive
      DriveLeftSpeed = LeftY - LeftX;
      if (DriveLeftSpeed > 255) {
        DriveLeftSpeed = 255;
      }
      else if (DriveLeftSpeed < -255) {
        DriveLeftSpeed = -255;
      }
      DriveRightSpeed = LeftY + LeftX;
      if (DriveRightSpeed > 255) {
        DriveRightSpeed = 255;
      }
      else if (DriveRightSpeed < -255) {
        DriveRightSpeed = -255;
      }
      DriveSideSpeed = RightX;
    break;

    case 3:
      // Drone-style
      DriveLFSpeed = LeftY + LeftX + RightX;
      if (DriveLFSpeed > 255) {
        DriveLFSpeed = 255;
      }
      else if (DriveLFSpeed < -255) {
        DriveLFSpeed = -255;
      }
      DriveLRSpeed = LeftY + LeftX - RightX;
      if (DriveLRSpeed > 255) {
        DriveLRSpeed = 255;
      }
      else if (DriveLRSpeed < -255) {
        DriveLRSpeed = -255;
      }
      DriveRFSpeed = LeftY - LeftX - RightX;
      if (DriveRFSpeed > 255) {
        DriveRFSpeed = 255;
      }
      else if (DriveRFSpeed < -255) {
        DriveRFSpeed = -255;
      }
      DriveRRSpeed = LeftY - LeftX + RightX;
    if (DriveRRSpeed > 255) {
      DriveRRSpeed = 255;
    }
    else if (DriveRRSpeed < -255) {
      DriveRRSpeed = -255;
    }
  break;
} //(driverMode)
}

void writeRobot() {
// Pre-set for tank drive.  Change accordingly with different motor setup
  mc.setMotorSpeed(LeftDrive1,DriveLeftSpeed);
  mc.setMotorSpeed(LeftDrive2,DriveLeftSpeed);
  mc.setMotorSpeed(RightDrive1,DriveRightSpeed);
  mc.setMotorSpeed(RightDrive2,DriveRightSpeed);
  mc.setMotorSpeed(LiftMotor,liftSpeed);
  mc.setMotorSpeed(ClawMotor,clawSpeed);
}
