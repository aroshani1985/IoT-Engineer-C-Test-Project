# IoT Engineer C Test Project (ESP32 C)
Secure communucation between two node based on request and reply 

# Protocol definition
  1) Frame format: 
      [Start] [CMD_H]  [CMD_L] [Payload_Len]  [Payload .... ][EoF-1][EoF-2]
  2) Start byte is 0xAA (one byte)
  3) Command id is two bytes.
  4) Maximum payload is 200 bytes 
  5) Maximum packet length is limmited to 206 bytes
  6) End of frame indicator are two bytes [\r][\n]

# Protocol implementation files 
  1) path is: [main/com](/IoTEngCTestPrj/IoTEngCTestPrj/main/com/) folder
  2) [encdec.c/h](/IoTEngCTestPrj/IoTEngCTestPrj/main/com/encdec.c) files are used for encryption and decription
  3) [pktformat.c/h](/IoTEngCTestPrj/IoTEngCTestPrj/main/com/pktformat.c) files are used for packet format definition 
  4) [pktreceive.c/h](/IoTEngCTestPrj/IoTEngCTestPrj/main/com/pktreceive.c) files are used for handling received packet
  5) [cmdhandler.c/h](/IoTEngCTestPrj/IoTEngCTestPrj/main/com/cmdhandler.c) files are used for handling large number of commands and dispaching related functions
  


  # Protocol test files 
  1) path is: [main/test](/IoTEngCTestPrj/IoTEngCTestPrj/main/test/) folder
  2) [comtest.c/h](/IoTEngCTestPrj/IoTEngCTestPrj/main/test/comtest.c) files are used for testing communication protocol implemented functions
 
