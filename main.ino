#include "MIDIUSB.h"
#include <Encoder.h>

void controlChange(byte channel, byte control, byte value) {
    midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
    MidiUSB.sendMIDI(event);
}

class MidiEncoder {
public:
    Encoder encoder;
    int btnPin;
    byte encoderCC;
    byte btnCC;
    long oldPosition = -999;
    int btnPState = HIGH;
    long lastSentValue = -1;
    unsigned long lastDebounceTime = 0;

    MidiEncoder(int clkPin, int dtPin, int _btnPin, byte _encoderCC, byte _btnCC)
        : encoder(dtPin, clkPin), btnPin(_btnPin), encoderCC(_encoderCC), btnCC(_btnCC) {
        pinMode(btnPin, INPUT_PULLUP);
    }

    void read() {
        readEncoder();
        readButton();
    }

private:
    private:
    void readEncoder() {
    long newPosition = encoder.read() / 2;

    // Constrain newPosition
    if (newPosition < 0) {
        newPosition = 0;
        encoder.write(newPosition * 2);  // Reset the encoder's internal count
    } else if (newPosition > 127) {
        newPosition = 127;
        encoder.write(newPosition * 2);  // Reset the encoder's internal count
    }

    // Only send if the position has changed (and avoid the rapid sending)
    if (newPosition != oldPosition) {
        sendControlChange(encoderCC, newPosition);
        oldPosition = newPosition;
        lastSentValue = newPosition;
    }
}


    void readButton() {
        int btnCState = digitalRead(btnPin);
        if ((millis() - lastDebounceTime) > 20) {
            if (btnPState != btnCState) {
                lastDebounceTime = millis();
                if (btnCState == LOW) {
                    byte valueToSend = (btnPState == HIGH) ? 127 : 0; 
                    sendControlChange(btnCC, valueToSend);
                }
                btnPState = btnCState;
            }
        }
    }

    void sendControlChange(byte control, byte value) {
        controlChange(0, control, value);
        MidiUSB.flush();
        Serial.print("Sent CC: ");
        Serial.print(control);
        Serial.print(" Value: ");
        Serial.println(value);
    }
};

// Define the encoder/button combinations
MidiEncoder encoders[] = {

    {21, 22, 23, 12, 13},   // Encoder 01
    {18, 19, 20, 14, 15},   // Encoder 02
    {12, 11, 10, 16, 17}    // Encoder 03
//    {-1, -1, -1, 18, 19}    // Encoder 04?

        //{X1, X2, Y1, Z1, Z2},  // Add more encoders with buttons by replicating the format
      //x1: Encoder CLK Pin
      //x2: Encoder DT Pin
      //y1: Encoder Button Pin
      //z1: MIDI CC number for the encoder rotation
      //z2: MIDI CC number for the encoder button press
};

void setup() {
    Serial.begin(9600);
}

void loop() {
    for (int i = 0; i < sizeof(encoders) / sizeof(MidiEncoder); i++) {
        encoders[i].read();
    }
}
