# IoT Engineer C Test Project (ESP32 C)
Secure communucation between two node based on request and reply 

# Protocol definition
  1) Frame format: 
      [Start] [CMD_H]  [CMD_L] [Payload_Len]  [Payload .... ][EoF-1][EoF-2]
  2) Start byte is 0xAA (one byte)
  3) Command id is two bytes.
  4) Maximum payload is 200 bytes 
  5) Maximum packet length is limmited to 206 bytes
  6) End of frame indicators are two bytes [\r][\n]

# Protocol implementation files 
  1) path is: [main/com](/IoTEngCTestPrj/IoTEngCTestPrj/main/com/) folder
  2) [encdec.c/h](/IoTEngCTestPrj/IoTEngCTestPrj/main/com/encdec.c) files are used for encryption and decription
  3) [pktformat.c/h](/IoTEngCTestPrj/IoTEngCTestPrj/main/com/pktformat.c) files are used for packet format definition 
  4) [pktreceive.c/h](/IoTEngCTestPrj/IoTEngCTestPrj/main/com/pktreceive.c) files are used for handling received packet
  5) [cmdhandler.c/h](/IoTEngCTestPrj/IoTEngCTestPrj/main/com/cmdhandler.c) files are used for handling large number of commands with multiple items in responce 
  5) [pktsend.c/h](/IoTEngCTestPrj/IoTEngCTestPrj/main/com/pktsend.c) files are used for sending data to the client
  


  # Protocol test files 
  1) path is: [main/test](/IoTEngCTestPrj/IoTEngCTestPrj/main/test/) folder
  2) [comtest.c/h](/IoTEngCTestPrj/IoTEngCTestPrj/main/test/comtest.c) files are used for testing communication protocol implemented functions

  # Sample output with 20 items and 3 byte for each item      
	   Send fcn: Communication_openResponse
     Send fcn: Send result: AA 00 01 00
     Send fcn: Send result: A0 01 0A A0 02 0A A0 03 0A A0 04
     Send fcn: Send result: 0A A0 05 0A A0 06 0A A0 07 0A A0
     Send fcn: Send result: 08 0A A0 09 0A A0 0A 0A A0 0B 0A
     Send fcn: Send result: A0 0C 0A A0 0D 0A A0 0E 0A A0 0F
     Send fcn: Send result: 0A A0 10 0A A0 11 0A A0 12 0A A0
     Send fcn: Send result: 13 0A A0 14 0A 
     Send fcn: Send result: 0D 0A 
     Send fcn: Communication_closeResponse
     TestComm: CMD[0x0001], ItemCount: 20
	 
 
