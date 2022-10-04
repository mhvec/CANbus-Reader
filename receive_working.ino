#include <SPI.h>

#define CAN_2515
// #define CAN_2518FD

// Set SPI CS Pin according to your hardware

#if defined(SEEED_WIO_TERMINAL) && defined(CAN_2518FD)
// For Wio Terminal w/ MCP2518FD RPi Hat：
// Channel 0 SPI_CS Pin: BCM 8
// Channel 1 SPI_CS Pin: BCM 7
// Interupt Pin: BCM25
const int SPI_CS_PIN  = BCM8;
const int CAN_INT_PIN = BCM25;
#else

// For Arduino MCP2515 Hat:
// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 9;
const int CAN_INT_PIN = 2;
#endif


#ifdef CAN_2518FD
#include "mcp2518fd_can.h"
mcp2518fd CAN(SPI_CS_PIN); // Set CS pin

// To TEST MCP2518FD CAN2.0 data transfer
#define MAX_DATA_SIZE 8
// To TEST MCP2518FD CANFD data transfer, uncomment below lines
// #undef  MAX_DATA_SIZE
// #define MAX_DATA_SIZE 64

#endif

#ifdef CAN_2515
#include "mcp2515_can.h"
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
#define MAX_DATA_SIZE 8
#endif

void setup() {
    SERIAL_PORT_MONITOR.begin(115200);
    while (!SERIAL_PORT_MONITOR) {}

    #if MAX_DATA_SIZE > 8
    /*
     * To compatible with MCP2515 API,
     * default mode is CAN_CLASSIC_MODE
     * Now set to CANFD mode.
     */
    CAN.setMode(CAN_NORMAL_MODE);
    #endif

    while (CAN_OK != CAN.begin(CAN_250KBPS)) {             // init can bus : baudrate = 250k
        SERIAL_PORT_MONITOR.println(F("CAN init fail, retry..."));
        delay(100);
    }
    SERIAL_PORT_MONITOR.println(F("CAN init ok!"));
}

uint32_t id;
uint8_t  type; // bit0: ext, bit1: rtr
uint8_t  len;
byte cdata[MAX_DATA_SIZE] = {8};
int rpm,ect,lambda,mappress,battvoltage;

void loop() {
    // check if data coming
    if (CAN_MSGAVAIL != CAN.checkReceive()) {
        return;
    }

    char prbuf[32 + MAX_DATA_SIZE * 3];
    int i, n;

    unsigned long t = millis();
    // read data, len: data length, buf: data buf
    CAN.readMsgBuf(&len, cdata);

    id = CAN.getCanId();
    type = (CAN.isExtendedFrame() << 0) |
           (CAN.isRemoteRequest() << 1);
    /*
     * MCP2515(or this driver) could not handle properly
     * the data carried by remote frame
     */

      rpm = (cdata[0]*256 + cdata[1]);  //write the data from Byte 0 & 1 to variable "rpm"
      ect = (cdata[2]);  //write the data from Byte 2 & 3 to variable "b"
      lambda = (cdata[3]*256 + cdata[4]);  //write the data from Byte 4 & 5 to variable "c"
      mappress = (cdata[5]);  //write the data from Byte 6 & 7 to variable "d"
      battvoltage = (cdata[6]*256 + cdata[7]);  //write the data from Byte 4 & 5 to variable "c"
      
    Serial.print(rpm);
    Serial.print("\t");
    Serial.print(ect);
    Serial.print("\t");
    Serial.print(lambda);
    Serial.print("\t");
    Serial.print(mappress);
    Serial.print("\t");
    Serial.print(battvoltage);
    Serial.println("");
    
}
// END FILE
