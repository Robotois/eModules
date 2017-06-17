/* 
 * File:   Robotina.cpp
 * Author: yova
 * 
 * Created on 26 de abril de 2016, 05:22 PM
 */

#include "Robotina.h"

#include <bcm2835.h>
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <cmath>

#include "../../Libraries/Timer/AccurateTiming.h"

Robotina::Robotina() {
    stopButton = RPI_V2_GPIO_P1_11;
    debugButton = RPI_V2_GPIO_P1_13;

    bcm2835_gpio_fsel(stopButton,BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(stopButton, BCM2835_GPIO_PUD_DOWN);
    bcm2835_gpio_hen(stopButton);
//    bcm2835_gpio_set_eds(stopButton);

    bcm2835_gpio_fsel(debugButton,BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(debugButton, BCM2835_GPIO_PUD_DOWN);
    bcm2835_gpio_hen(debugButton);
//    bcm2835_gpio_set_eds(debugButton);

    accelGyroAddress = 0x69;    
    motorModule = new Motors();
    accelGyro = new AccelGyroModule();
    motorModule->motorsSetup25D();
}

Robotina::Robotina(const Robotina& orig) {
}

Robotina::~Robotina() {
}

void Robotina::setup(void)
{
    accelGyro->initialize();
    printf(accelGyro->testConnection() ? "MPU6050 connection successful\n" : "MPU6050 connection failed\n");
    accelGyro->setXAccelOffset((int16_t)-2422);
    accelGyro->setYAccelOffset((int16_t)-607);
    accelGyro->setZAccelOffset((int16_t)629);
    accelGyro->setXGyroOffset((int16_t)136);
    accelGyro->setYGyroOffset((int16_t)-74);
    accelGyro->setZGyroOffset((int16_t)-55);    
    PitchCalOffset = 0;
    gyroXzero = 0;
    
//#ifdef CALCTIME_SERIALOUT
//  Serial.begin(9600);
//  Serial.println();
//#endif

//    printf("Lay Zippy down and press button\n");

//  lcd.begin(16, 2);
//  lcd.print("Lay Zippy down");
//  lcd.setCursor(0, 1);
//  lcd.print("and press button");
//    printf("");
//  while (analogRead(buttonPin) < 800);
    
//    while(!bcm2835_gpio_eds(debugButton));
//    bcm2835_gpio_set_eds(debugButton);
//    printf("Calibrating...\n");
    
//  lcd.clear();
//  lcd.print("Calibrating");

//    // Motor PWM Setup
//    InitTimersSafe();  // Initialize timers for new PWM frequency
//    SetPinFrequencySafe(MotorL_PWM, PWMFREQ);
//    SetPinFrequencySafe(MotorR_PWM, PWMFREQ);
//
//    // RC Receiver Setup
//    pinMode(ThrottlePin, INPUT);
//    digitalWrite(ThrottlePin, HIGH); //use the internal pullup resistor
//    pinMode(SteeringPin, INPUT);
//    digitalWrite(SteeringPin, HIGH); //use the internal pullup resistor
//
//    PCintPort::attachInterrupt(ThrottlePin, calcThrottle, CHANGE);
//    PCintPort::attachInterrupt(SteeringPin, calcSteering, CHANGE);

//    // Quadrature encoder Setup
//    // Left encoder
//    pinMode(c_LeftEncoderPinA, INPUT);      // sets pin A as input
//    digitalWrite(c_LeftEncoderPinA, LOW);  // turn on pulldown resistor
//    pinMode(c_LeftEncoderPinB, INPUT);      // sets pin B as input
//    digitalWrite(c_LeftEncoderPinB, LOW);  // pulldown resistor
//    attachInterrupt(c_LeftEncoderInterrupt, HandleLeftMotorInterruptA, RISING);
//
//    // Right encoder
//    pinMode(c_RightEncoderPinA, INPUT);      // sets pin A as input
//    digitalWrite(c_RightEncoderPinA, LOW);  // pulldown resistor
//    pinMode(c_RightEncoderPinB, INPUT);      // sets pin B as input
//    digitalWrite(c_RightEncoderPinB, LOW);  // pulldown resistor
//    attachInterrupt(c_RightEncoderInterrupt, HandleRightMotorInterruptA, RISING);

    // Set up Gyro
//    Wire.begin();
//    Wire.setClock(400000UL); // Set I2C frequency to 400kHz
    
//    bcm2835_i2c_setSlaveAddress(accelGyroAddress);   
//    wBuf[0] = 0x6B;
//    wBuf[1] = 0x80;
//    bcm2835_i2c_write(wBuf, 2);
//    
//    do{
//        wBuf[0] = 0x6B;
//        bcm2835_i2c_read_register_rs(wBuf,rBuf,1);
//    } while (rBuf[0] & 0x80); // Wait for the bit to clear
//    mDelay(5);
//
////    while (i2cWrite(0x6B, 0x09, true)); // PLL with X axis gyroscope reference, disable temperature sensor and disable sleep mode
//    wBuf[0] = 0x6B;
//    wBuf[1] = 0x09;
//    bcm2835_i2c_write(wBuf, 2);
//
//    wBuf[0] = 0x19; // Set the sample rate to 200Hz = 1kHz/(1+4)
//    wBuf[1] = 4; // Set the sample rate to 200Hz = 1kHz/(1+4)
//    wBuf[2] = 0x03; // Disable FSYNC and set 44 Hz Acc filtering, 42 Hz Gyro filtering, 1 KHz sampling
//    wBuf[3] = 0x00; // Set Gyro Full Scale Range to ±250deg/s
//    wBuf[4] = 0x00; // Set Accelerometer Full Scale Range to ±2g
//    bcm2835_i2c_write(wBuf, 5);    
////    while (i2cWrite(0x19, i2cBuffer, 4, true)); // Write to all four registers at once
//    mDelay(100); // Wait for the sensor to get ready
//
//    /* Calibrate gyro zero value */
//    while (calibrateGyro()); // Run again if the robot is moved while calibrating
//
//    while (PitchCalOffset > 0) { // Calibrate on -90 deg side
//        printf("Flip over and press button\n");
////      lcd.clear();
////      lcd.print("Flip over");
////      lcd.setCursor(0, 1);
////      lcd.print("and press button");
//        while(!bcm2835_gpio_eds(debugButton));
//        bcm2835_gpio_set_eds(debugButton);
//        mDelay(500);
//        while (calibrateGyro());
//    }
//    PitchCalOffset += 90.8f;
//
//    if (PitchCalOffset < -3.5f || PitchCalOffset > -0.5f) {
//        printf("Not level, using default Push Button.\n");
////      lcd.clear();
////      lcd.print("Not level, using");
////      lcd.setCursor(0, 1);
////      lcd.print("dflt. Push bttn.");
//        PitchCalOffset = PitchCalOffsetDefault;
//        while(!bcm2835_gpio_eds(debugButton));
//        bcm2835_gpio_set_eds(debugButton);
//        mDelay(500);
//    }
//    printf("P: %0.5f, R: %0.5f\n Push Button...\n",PitchCalOffset,gyroXzero);
////    lcd.clear();
////    lcd.print("P: ");
////    lcd.print(PitchCalOffset);
////    lcd.setCursor(8, 0);
////    lcd.print(" R: ");
////    lcd.print(gyroXzero);
////    lcd.setCursor(0, 1);
////    lcd.print("Push Button");
//    while(!bcm2835_gpio_eds(debugButton));
//    bcm2835_gpio_set_eds(debugButton);
//    mDelay(500);
//
//    printf("Push Button when ready...\n");
//    lcd.clear();
//    lcd.print("Push when ready");
//
//    int button_pushed = 0;
//    unsigned long timer;
//    while (!button_pushed) {
//        auto startTime = std::chrono::high_resolution_clock::now();
//        PitchEst = 0;
//        for (int i = 0; i < 50; i++) {
//            wBuf[0] = 0x3B;
//            bcm2835_i2c_read_register_rs(wBuf,rBuf,14);          
//            int16_t AcY = ((rBuf[2] << 8) | rBuf[3]);
//            int16_t AcZ = ((rBuf[4] << 8) | rBuf[5]);
//            PitchEst += atan2((float)AcY, (float)AcZ) * RAD_TO_DEG;
//            
//            if(bcm2835_gpio_eds(debugButton)){
//                bcm2835_gpio_set_eds(debugButton);
//                button_pushed = 1;
//            }
//        }
//        PitchEst /= 50.0f;
//        PitchEst -= PitchCalOffset;
//        printf("Pitch: %0.5f\n",PitchEst);
//        lcd.setCursor(0, 1);
//        lcd.print("Pitch: ");
//        lcd.print(PitchEst);
//        auto elapsedTime = std::chrono::high_resolution_clock::now() - startTime;    
//        timer = std::chrono::duration_cast<std::chrono::milliseconds>(elapsedTime).count(); 
//        while (timer < 500) {
//            auto elapsedTime = std::chrono::high_resolution_clock::now() - startTime;    
//            timer = std::chrono::duration_cast<std::chrono::milliseconds>(elapsedTime).count(); 
//            if(bcm2835_gpio_eds(debugButton)){
//                bcm2835_gpio_set_eds(debugButton);
//                button_pushed = 1;
//            }
//        }
//    }
//    mDelay(500);
//    for (int i = 0; i < 20; i++) {
//      voltageFilt += (float)analogRead(voltSensePin) * VOLT_PER_COUNT;
//    }
//    voltageFilt /= 20.0f;
//
//    lcd.clear();
//    lcd.print("Go Zippy Go!!");
//    lcd.setCursor(0, 1);
//    lcd.print("Battery: ");
//    lcd.print(voltageFilt);
//    lcd.print(" V");
//    delay(100);
//    LastTime = micros();
}

void Robotina::loop(){
    int i;
    static unsigned long int timer, encoderTimer, voltageTimer, voltageTimerOut;
    static int throttle_glitch_persistent, steer_glitch_persistent;
    static float Error, lastError, wheelVelocity;
    static double wheelPosition, lastWheelPosition, rotationAngle;
//    static unsigned long int WheelSpeedTimer;
    static double PosCmd, rotationCmd;
    static float AOCmd;
    static uint16_t ThrottleIn, SteeringIn, ThrottleInGood, SteeringInGood, bUpdateFlags;
    float ThrottleF, SteeringF;
    static long LeftEncoderTicks, RightEncoderTicks;
    float TorqueCMD;
    static float TurnTorque;
    int dutyCycle_L = 0, dutyCycle_R = 0;
    float Kp_fb = 0, Ki_fb = 0, Kd_fb = 0;
    float accAngle; // Result from raw accelerometer
    float gyroRate;
    float AngleOffset;
    static unsigned long int CalcTime, MaxCalcTime, AveCalcTime, TimeCounter;
    static int NumSamples;
    
    auto WheelSpeedTimer = std::chrono::high_resolution_clock::now();
    auto LastTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::high_resolution_clock::now() - WheelSpeedTimer;
    int16_t AcY;
    int16_t AcZ;
    int16_t GyX;
    
    while(true){
        if(bcm2835_gpio_eds(stopButton)){
            bcm2835_gpio_set_eds(stopButton);
            motorModule->motorsControl(Motors::stop,Motors::stop);
            printf("Bye Bye...\n");
            return;
        }

        // Turn off interrupts and copy over data which changes during interrupts
//        if (bUpdateFlagsShared) {
////            noInterrupts();
//            bUpdateFlags = bUpdateFlagsShared;
//            if (bUpdateFlags & THROTTLE_FLAG) {
//              ThrottleIn = _ThrottleInShared;
//            }
//            if (bUpdateFlags & STEERING_FLAG)  {
//              SteeringIn = _SteeringInShared;
//            }
//            if (bUpdateFlags & LEFTENC_FLAG) {
//              LeftEncoderTicks = _LeftEncoderTicks;
//            }
//            if (bUpdateFlags & RIGHTENC_FLAG) {
//              RightEncoderTicks = _RightEncoderTicks;
//            }
//            bUpdateFlagsShared = 0;
////            interrupts(); // we have local copies of the inputs, so now we can turn interrupts back on
//        }

        // Read Gyro Data
        bcm2835_i2c_setSlaveAddress(accelGyroAddress);   
        wBuf[0] = 0x3B;
        bcm2835_i2c_read_register_rs(wBuf,rBuf,14);          
        
//        while (i2cRead(0x3B, i2cBuffer, 14));
        AcY = ((rBuf[2] << 8) | rBuf[3]);
        AcZ = ((rBuf[4] << 8) | rBuf[5]);
        GyX = ((rBuf[8] << 8) | rBuf[9]);
//        GyX = ((rBuf[10] << 8) | rBuf[11]);

        accAngle = atan2((float)AcY, (float)AcZ) * RAD_TO_DEG - PitchCalOffset;
        gyroRate = (float)GyX / 131.0f - gyroXzero; // Convert to deg/s

        KalmanFilter(accAngle, gyroRate);
        motorModule->selectModule();

        // Calculate Wheel Position & Speed at 10 Hz
        elapsedTime = std::chrono::high_resolution_clock::now() - WheelSpeedTimer;    
        timer = std::chrono::duration_cast<std::chrono::milliseconds>(elapsedTime).count();         
        if (timer > 100) {
            motorModule->GetEncoderTicks(&LeftEncoderTicks,&RightEncoderTicks);
          wheelPosition = 0.5f * (LeftEncoderTicks + RightEncoderTicks) * DEG_PER_COUNT;
          wheelVelocity = 12.0f * (wheelPosition - lastWheelPosition); // - 12cm wheel diameter
//          wheelVelocity = 10.0f * (wheelPosition - lastWheelPosition);
          rotationAngle = 0.5f * (LeftEncoderTicks - RightEncoderTicks) * DEG_PER_COUNT * 0.8f; // Rotation angle in deg.  Note: wheel diam = 12cm
                                                                                                  // and dist between wheels = 15 cm, so rotation 
                                                                                                  // angle = 120 / 150 = 0.8 * wheel angle 
          lastWheelPosition = wheelPosition;
          WheelSpeedTimer = std::chrono::high_resolution_clock::now();
        }

//        if (millis() - voltageTimer > 1000) {
//          const float voltageFiltConst = 0.73; // K = exp(s*T), where s = 0.05*2*pi (1/20 Hz), and T = 1 sec
//          float voltageFiltTemp = voltageFiltConst * voltageFilt + (1 - voltageFiltConst) * (float)analogRead(voltSensePin) * VOLT_PER_COUNT;
//          if (!isnan(voltageFiltTemp)) {
//            if (voltageFiltTemp > 9.5f && voltageFiltTemp < 13.0f) {
//              voltageFilt = voltageFiltTemp;  // Update voltage only if measurement is within reasonable range
//              MotorScaleFactor = 0.01f * 11.8f / voltageFilt;  // Adjust motor scale factor for ideal voltage of 11.8 V
//            }
//          }
//          if (voltageFilt < 11.0f) {
//            RechargeBattery = 1;
//          }
//          voltageTimer = millis();
//        }
//        if (millis() - voltageTimerOut > 10000) {
//          lcd.clear();
//          if (RechargeBattery) {
//            lcd.print("Recharge Battery");
//          }
//          else {
//            lcd.print("Go Zippy Go!!");
//          }
//          lcd.setCursor(0, 1);
//          lcd.print("Battery: ");
//          lcd.print(voltageFilt);
//          lcd.print(" V");
//          voltageTimerOut = millis();
//        }


        if ((layingDown && (PitchEst < -5 || PitchEst > 5)) || (~layingDown && (PitchEst < -45 || PitchEst > 45))) {
            layingDown = true;
            motorModule->motorsControl(Motors::stop,Motors::stop);
//            digitalWriteFast(MotorL_A, LOW);
//            digitalWriteFast(MotorL_B, LOW);
//            digitalWriteFast(MotorR_A, LOW);
//            digitalWriteFast(MotorR_B, LOW);
            IntState = 0;
            _LeftEncoderTicks = 0; LeftEncoderTicks = 0;
            _RightEncoderTicks = 0; RightEncoderTicks = 0;
            motorModule->ResetEncoderCounters();
        }
        else {
          layingDown = false;

          // Filter ThrottleIn and confert to AOCmd
          if (ThrottleIn > 800 && ThrottleIn < 2200 && !RechargeBattery) {  // Valid range
            if ((abs(ThrottleIn - ThrottleInGood) < 200) || (throttle_glitch_persistent > 20)) { // Changes greater than 200 are assumed to be a glitch
              ThrottleInGood = ThrottleIn;
              throttle_glitch_persistent = 0;
            }
            else {
              throttle_glitch_persistent++;
            }
            ThrottleF = (float)ThrottleInGood;
            AOCmd = (ThrottleF - 1540.0f) / 75.0f; // SteeringIn ranges from 1000 to 2000.  Rescale to -6.7 to +6.7 deg/sec.
            AOCmd = constrain(AOCmd, -7.0f, 7.0f);
          }
          else {
            throttle_glitch_persistent++;
            if (throttle_glitch_persistent > 20) {
              throttle_glitch_persistent = 0;
            }
            AOCmd = 0;
          }
          AngleOffset = AOCmd;
          if (abs(AOCmd) > 2.0f) {
            PosCmd = wheelPosition + 1.0f * wheelVelocity;
            AngleOffset -=  wheelVelocity * wheelRateGain;
          }
          else {
            AngleOffset -= (wheelPosition - PosCmd) * wheelPosGain  + wheelVelocity * wheelRateGain;
          }
          AngleOffset = constrain(AngleOffset, -10.0f, 10.0f);

          lastError = Error;
          Error = AngleOffset - PitchEst;
          IntState = IntState + Error / FHz;
          IntState = constrain(IntState, -5.0f, 5.0f);

          Kp_fb = K_p * Error;
          Ki_fb = K_i * IntState;
          Kd_fb = -K_d * gyroRate;

          TorqueCMD = Kp_fb + Ki_fb + Kd_fb;

          // Filter SteeringIn and confert to TurnTorque
          if (SteeringIn > 800 && SteeringIn < 2200 && !RechargeBattery) {  // Valid range
            if ((abs(SteeringIn - SteeringInGood) < 200) || (steer_glitch_persistent > 20)) { // Changes greater than 200 are assumed to be a glitch
              SteeringInGood = SteeringIn;
              steer_glitch_persistent = 0;
            }
            else {
              steer_glitch_persistent++;
            }
            SteeringF = SteeringInGood;
            TurnTorque = (SteeringF - 1500.0f) / 20.0f;  // SteeringIn ranges from 1000 to 2000.  Rescale to -25 to 25.
            TurnTorque = constrain(TurnTorque, -25.0f, 25.0f);
            if (abs(TurnTorque) < 5.0f && abs(AOCmd) < 2.0f) {
              TurnTorque += Kp_Rotation * (rotationCmd - rotationAngle);  // Maintain current rotation angle
            }
            else {
              rotationCmd = rotationAngle;
            }
          }
          else {
            steer_glitch_persistent++;
            if (steer_glitch_persistent > 20) {
              steer_glitch_persistent = 0;
            }
            TurnTorque = 0;
          }

          dutyCycle_L = 350 * ((TorqueCMD - TurnTorque) * MotorScaleFactor);
          dutyCycle_R = 350 * ((TorqueCMD + TurnTorque) * MotorScaleFactor);

            motorModule->drivePWMs(dutyCycle_L,dutyCycle_R);
//          if (dutyCycle_L < 0) {
//            digitalWriteFast(MotorL_A, LOW);
//            digitalWriteFast(MotorL_B, HIGH);
//            dutyCycle_L = -dutyCycle_L;
//          }
//          else {
//            digitalWriteFast(MotorL_A, HIGH);
//            digitalWriteFast(MotorL_B, LOW);
//          }

//          if (dutyCycle_R < 0) {
//            digitalWriteFast(MotorR_A, LOW);
//            digitalWriteFast(MotorR_B, HIGH);
//            dutyCycle_R = -dutyCycle_R;
//          }
//          else {
//            digitalWriteFast(MotorR_A, HIGH);
//            digitalWriteFast(MotorR_B, LOW);
//          }
//          if (dutyCycle_L > 255) {
//            dutyCycle_L = 255;
//          }
//          if (dutyCycle_R > 255) {
//            dutyCycle_R = 255;
//          }
        }

        //dutyCycle_L = 0;
        //dutyCycle_R = 0;
//        pwmWrite(MotorL_PWM, dutyCycle_L);
//        pwmWrite(MotorR_PWM, dutyCycle_R);

        #ifdef CALCTIME_SERIALOUT
        MaxCalcTime, AveCalcTime, TimeCounter, NumSamples;
        CalcTime = micros() - LastTime;
        if (MaxCalcTime < CalcTime) {
          MaxCalcTime = CalcTime;
        }
        AveCalcTime += CalcTime;
        NumSamples++;
        if ((millis() - TimeCounter) > 1000) {
          TimeCounter = millis();
          AveCalcTime /= NumSamples;
          NumSamples = 0;
          Serial.print("Average Calculation Time: ");
          Serial.print((float)AveCalcTime / 1000.0f);
          Serial.print(" msec,  ");
          Serial.print("Maximum Calculation Time: ");
          Serial.print((float)MaxCalcTime / 1000.0f);
          Serial.println(" msec");
          MaxCalcTime = 0;
          AveCalcTime = 0;
        }
        #endif

        elapsedTime = std::chrono::high_resolution_clock::now() - LastTime;  
        timer = std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count();
        while (timer < DT){
            elapsedTime = std::chrono::high_resolution_clock::now() - LastTime;  
            timer = std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count();
        }
        LastTime = std::chrono::high_resolution_clock::now();
    }
    
}

float Robotina::KalmanFilter(float PitchMeas, float RateMeas) {
  /*
   * Steady State Kalman Filter -- Hard code gains into function
   *
   * [pitch; bias]_(k+1) = A * [pitch; bias]_(k) + B * rate_meas + G * w
   * pitch = C * [pitch; bias] + v
   *
   * A = [1 -dt; 0 1];
   * B = [dt; 0];
   * C = [1 0];
   *
   * G = [1 0; 0 1];
   * cov(w) = Q;
   * cov(v) = R;
   *
   * Kalman Filter gain solved using dlqe in Octave (GNU version of Matlab), assuming:
   * Q = diag([0.001 0.001]);
   * R = 1.5;
   * dt = 0.01;
   * then: K = dlqe(A,G,C,Q,R) = [0.033810; -0.025380];
   */
  const float dt = 0.005;
  const float K[2] = {0.016905, -0.012690}; // Gains originally calculated for 100 Hz,
  // Divide by 2 for 200 Hz gains
  float y = PitchMeas - PitchEst;
  PitchEst += dt * (RateMeas - BiasEst);
  PitchEst += K[0] * y;
  BiasEst  += K[1] * y;
}

bool Robotina::calibrateGyro() {
    int16_t gyroXbuffer[50], AcY, AcZ;

    gyroXzero = 0;
    PitchCalOffset = 0;

    for (uint8_t i = 0; i < 50; i++) {
        wBuf[0] = 0x3B;
        bcm2835_i2c_read_register_rs(wBuf,rBuf,14);          
//        while (i2cRead(0x3B, i2cBuffer, 14));
        AcY = ((rBuf[2] << 8) | rBuf[3]);
        AcZ = ((rBuf[4] << 8) | rBuf[5]);
        PitchCalOffset += atan2((float)AcY, (float)AcZ) * RAD_TO_DEG;
        gyroXbuffer[i] = ((rBuf[8] << 8) | rBuf[9]);
        gyroXzero += gyroXbuffer[i];
        delay(10);
    }
    if (!checkMinMax(gyroXbuffer, 50, 2000)) {
        return 1;
    }

    PitchCalOffset /= 50.0f;
    gyroXzero /= (50.0f * 131.0f);
    return 0;
}

bool Robotina::checkMinMax(int16_t *array, uint8_t length, int16_t maxDifference) { // Used to check that the robot is laying still while calibrating
  int16_t min = array[0], max = array[0];
  for (uint8_t i = 1; i < length; i++) {
    if (array[i] < min)
      min = array[i];
    else if (array[i] > max)
      max = array[i];
  }
  return max - min < maxDifference;
}

float Robotina::constrain(float value, float min, float max){
    if(value < min)
        return min;
    if(value > max)
        return max;
    
    return value;
}