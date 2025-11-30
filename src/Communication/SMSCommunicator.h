#ifndef SMS_COMMUNICATOR_H
#define SMS_COMMUNICATOR_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class SMSCommunicator {
private:
    int rxPin;
    int txPin;
    Stream* gsmSerial; // Changed to generic Stream for testing
    bool isSoftSerial;

public:
    SMSCommunicator(int rx, int tx);
    SMSCommunicator(Stream& stream); // Constructor for testing
    void init();
    void sendSOS(double lat, double lon);
};

#endif
