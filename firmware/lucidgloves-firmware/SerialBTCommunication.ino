#include "HardwareSerial.h"

#define RX0 44  // Define explicitly according to your hardware
#define TX0 43  // Define explicitly according to your hardware
#define MAX_INPUT_LENGTH 128  // Adjust as needed

class SerialBTCommunication : public ICommunication {
  private:
    bool m_isOpen;
    HardwareSerial UARTSerial = HardwareSerial(0); // Using UART0 (TX0, RX0)

  public:
    SerialBTCommunication() {
      m_isOpen = false;
    }

    bool isOpen(){
      return m_isOpen;
    }

    void start(){
      UARTSerial.begin(SERIAL_BAUD_RATE, SERIAL_8N1, RX0, TX0);
      m_isOpen = true;
    }

    void output(char* data){
      if(m_isOpen){
        UARTSerial.print(data);
      }
    }

    bool readData(char* input){
      if(m_isOpen && UARTSerial.available()){
        size_t len = UARTSerial.readBytesUntil('\n', input, MAX_INPUT_LENGTH);
        input[len] = '\0';
        return true;
      }
      return false;
    }
};