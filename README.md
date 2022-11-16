# IoT Engineer C Test Project (ESP32 C)
Secure communucation between two node based on request and reply 

# Protocol definition
  1) Srame format: 
      [Start] [CMD_H]  [CMD_L] [Payload_Len]  [Payload .... ]
  2) Start byte is 0xAA (one byte)
  3) Command id is two bytes.
  4) Maximum payload is 200 bytes 
  5) Maximum packet length is limmited to 204 bytes

# Protocol implementation files 
  1) path is: main/com folder
  2) encdec.c/h files are used for encryption and decription
  3) pktformat.c/h files are used packet format definition 
  


  # Protocol test files 
  1) path is: main/test folder
  2) comtest.c/h files are used for testing communication protocol implemented functions
 
