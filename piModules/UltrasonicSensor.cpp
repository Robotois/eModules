/* 
 * File:   UltrasonicSensor.cpp
 * Author: yova
 * 
 * Created on 16 de abril de 2016, 06:17 PM
 * 
 * This Class is intendend to handle the Ultrasonic sensor HC-SR04, therefore it
 * is needed two digital IO of the RPI. For this reason we connect the sensor to one 
 * of the Digital Headers and the order of the pins is:
 * Header->io_pin1 => Trigger
 * Header->io_pin2 => Echo
 * 
 */

#include "UltrasonicSensor.h"
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <stdint.h>
#include <chrono>
#include <bcm2835.h>
#include "Libraries/Timer/AccurateTiming.h"

#include "Modules/DigitalIO/DigitalIO.h"
#include "Modules/DigitalIO/DigitalHeader.h"

using namespace std;
UltrasonicSensor::UltrasonicSensor() {}

UltrasonicSensor::UltrasonicSensor(uint8_t header) {
    initialize(header);
}

UltrasonicSensor::UltrasonicSensor(const UltrasonicSensor& orig) {
}

UltrasonicSensor::~UltrasonicSensor() {
    delete IOHeader;
}

/**
 * Initializes the IO pins of the given header to match the default Trigger and
 * Echo pins.
 * @param header
 */
void UltrasonicSensor::initialize(uint8_t header){
    // The first IO pin must be stablished as Output since it its the Trigger Pin.
    // The second IO pin of the header is the Echo pin of the sensor, so it is an input.
    IOHeader = new DigitalHeader(header,AS_OUTPUT,AS_INPUT);
    // We save the io adresses just to simplify their usage.
    triggerPin = IOHeader->io_pin1;
    echoPin = IOHeader->io_pin2;

}

double UltrasonicSensor::getDistance(){
    return measure(2);
}

double UltrasonicSensor::measure(int samples){
    long int echoSum = 0; // suma total de los ecos en [ns]
    double average = 0;
    for(int i = 0; i < samples; i++){
        echoSum += readSensor();
        uDelay(60000); // Se da un tiempo al sensor para evitar saturarlo
    }
    // Se retorna el promedio del tiempo en [ns]
    average = (( (double)echoSum/samples ))/58; // La regla es T[us]/58 = dist[cm]
    return average;
}

long int UltrasonicSensor::readSensor(){
    long int echoTime = 0;

    // High enable, cuando se detecta un alto se dispara un evento EDS (Event Detect Status)
    // - Enviar el trigger
//    sendTrigger();
    IOHeader->write(triggerPin,HIGH);
    uDelay(10); // 10us de trigger
    IOHeader->write(triggerPin,LOW);
    
    // - Rise Event Enable
    IOHeader->riseEnable(echoPin);    

    echoTime = readEcho();
    // std::cout<<"echoTime in ns: "<<echoTime<<std::endl;
    // std::cout<<"distance in cm: "<<(echoTime/1000.0)/58<<std::endl;    
    return echoTime;
}

//void UltrasonicSensor::sendTrigger(){
//    triggerPin.write(HIGH);
//    uDelay(10); // 10us de trigger
//    triggerPin.write(LOW);
//}

//void UltrasonicSensor::setPins(int _triggerPin, int _echoPin){
//    bcm2835_gpio_fsel(_triggerPin, BCM2835_GPIO_FSEL_OUTP);
//
//    // Cambiar la configuracion
//    bcm2835_gpio_fsel(_echoPin,BCM2835_GPIO_FSEL_INPT);
//    bcm2835_gpio_set_pud(_echoPin, BCM2835_GPIO_PUD_UP);
//}

unsigned int UltrasonicSensor::readEcho(){
    auto startTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::high_resolution_clock::now() - startTime;
    unsigned int maxWaitTime = 60000;
    long long microseconds;
    unsigned int echolength = 0;

    while(true){        
      // Echo Signal has arrived
        if(IOHeader->riseDetected(echoPin)){
            // -- Start measuring the Echo time length
            startTime = std::chrono::high_resolution_clock::now();
            // -- Enble fall edge event on the echo pin
            IOHeader->fallEnable(echoPin);

            while(true){
                // -- Echo has reached the end
                if(IOHeader->fallDetected(echoPin)){

                      elapsedTime = std::chrono::high_resolution_clock::now() - startTime;
                      microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count();
                      break;
                }
            }
          
            echolength = microseconds;
            if(echolength > 11650){
                echolength = 11650;
            }
            break;
          }

      // - Si nunca llega el echo, se manda una distancia de 200[cm]
        elapsedTime = std::chrono::high_resolution_clock::now() - startTime;
        microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count();

        if(microseconds > maxWaitTime){
          echolength = 11650;
          break;
        }
    }
    return echolength;
}

//long int UltrasonicSensor::echoLength(long int start_time){
//  long int time_difference;
//  struct timespec gettime_now;
//
//  time_difference = 0;
//
//  // clock_gettime(CLOCK_REALTIME, &gettime_now);
//  // start_time = gettime_now.tv_nsec;   //Get nS value
//
//  bcm2835_gpio_set_eds(echoPin);
//  bcm2835_gpio_clr_aren(echoPin);
//              
//  //            bcm2835_gpio_set_eds(_echoPin);
//  // Low enable, cuando se detecta un alto se dispara un evento EDS (Event Detect Status)
//  bcm2835_gpio_afen(echoPin);
//
//  while(true){
//    // Detectar evento en LOW
//    if(bcm2835_gpio_eds(echoPin)){
//        bcm2835_gpio_set_eds(echoPin);
//        bcm2835_gpio_clr_afen(echoPin);
//
//        clock_gettime(CLOCK_REALTIME, &gettime_now);
//        time_difference = gettime_now.tv_nsec - start_time;
//        if (time_difference < 0){
//            time_difference += 1000000000; //(Rolls over every 1 second)
//        }
////                    return time_difference;
//        break;
//    }
//  }
//  return time_difference;
//}