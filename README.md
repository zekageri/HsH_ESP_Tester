# HsH_ESP_Tester

This uses an external display to debug the data.
If you don't have an external display just init the display with a ```false``` flag on setup like this: ```display.init(false);```
and it will print the results only to serial if ```USE_SERIAL_DEBUG``` defined as true in ```displayTest.h``` which is default true.

**Tests are:**

```cpp
  // Fill the ram with predefined size
  test.ramFill();
   
  // Test a json document custom allocator with any size json string
  test.json("{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}");
   
  // Set the predefined array size
  test.setArraySize(4000000);
   
  // Fill the ram with defined size
  test.ramFill();

  // External ram speed test
  test.ramSpeed();
  // Internal ram speed test
  test.ramSpeed(false);
  // Flash speed test
  test.flashSpeed();
```

**To get going:**

```cpp
#include <Arduino.h>
#include <hshTest.h>
#include <displayTest.h>
spiDisplay display;
hshTest test;

void setup() {
  Serial.begin(115200);
  vTaskDelay(1000);

  display.init();

  test.ramFill();
  test.json("{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}");
  test.setArraySize(4000000);
  test.ramFill();

  test.ramSpeed();
  test.ramSpeed(false);
  test.flashSpeed();
}

void loop() { }
```

Here is my ESP-Wrover-E ( 8mb PSRAM 16mb Flash ) test results compiled with

- PIO PLATFORM: Espressif 32 (5.1.1) > Espressif ESP-WROVER-KIT
- framework-arduinoespressif32 @ 3.20004.220825 (2.0.4)

```cpp
******************** External ram test ********************
Read Speed 8bit ArraySize    1kb  time: 0.0 sec 12.5 mb/sec
Read Speed 8bit ArraySize    2kb  time: 0.0 sec 12.6 mb/sec  
Read Speed 8bit ArraySize    4kb  time: 0.0 sec 12.6 mb/sec  
Read Speed 8bit ArraySize    8kb  time: 0.0 sec 12.6 mb/sec  
Read Speed 8bit ArraySize   16kb  time: 0.1 sec 12.5 mb/sec  
Read Speed 8bit ArraySize   32kb  time: 0.1 sec 12.3 mb/sec  
Read Speed 8bit ArraySize   64kb  time: 0.4 sec 8.6 mb/sec  
Read Speed 8bit ArraySize  128kb  time: 0.7 sec 8.6 mb/sec  
Read Speed 8bit ArraySize  256kb  time: 1.5 sec 8.6 mb/sec  
Read Speed 8bit ArraySize  512kb  time: 0.6 sec 8.6 mb/sec  
Read Speed 8bit ArraySize 1024kb  time: 1.2 sec 8.6 mb/sec  
Read Speed 8bit ArraySize 2048kb  time: 2.3 sec 8.6 mb/sec  
Read Speed 8bit ArraySize 4000kb  time: 4.6 sec 8.5 mb/sec  

Read Speed 16bit ArraySize    1kb  time: 0.0 sec 22.3 mb/sec
Read Speed 16bit ArraySize    2kb  time: 0.0 sec 22.5 mb/sec  
Read Speed 16bit ArraySize    4kb  time: 0.0 sec 22.5 mb/sec  
Read Speed 16bit ArraySize    8kb  time: 0.0 sec 22.5 mb/sec  
Read Speed 16bit ArraySize   16kb  time: 0.0 sec 22.5 mb/sec  
Read Speed 16bit ArraySize   32kb  time: 0.1 sec 21.8 mb/sec  
Read Speed 16bit ArraySize   64kb  time: 0.3 sec 12.4 mb/sec  
Read Speed 16bit ArraySize  128kb  time: 0.5 sec 12.3 mb/sec  
Read Speed 16bit ArraySize  256kb  time: 1.0 sec 12.3 mb/sec  
Read Speed 16bit ArraySize  512kb  time: 0.4 sec 12.3 mb/sec  
Read Speed 16bit ArraySize 1024kb  time: 0.8 sec 12.3 mb/sec  
Read Speed 16bit ArraySize 2048kb  time: 1.6 sec 12.3 mb/sec  
Read Speed 16bit ArraySize 4000kb  time: 3.2 sec 12.4 mb/sec  

Read Speed 32bit ArraySize    1kb  time: 0.0 sec 43.7 mb/sec
Read Speed 32bit ArraySize    2kb  time: 0.0 sec 44.6 mb/sec
Read Speed 32bit ArraySize    4kb  time: 0.0 sec 44.6 mb/sec  
Read Speed 32bit ArraySize    8kb  time: 0.0 sec 44.7 mb/sec  
Read Speed 32bit ArraySize   16kb  time: 0.0 sec 44.5 mb/sec  
Read Speed 32bit ArraySize   32kb  time: 0.0 sec 42.2 mb/sec  
Read Speed 32bit ArraySize   64kb  time: 0.2 sec 17.0 mb/sec  
Read Speed 32bit ArraySize  128kb  time: 0.4 sec 16.9 mb/sec  
Read Speed 32bit ArraySize  256kb  time: 0.7 sec 16.9 mb/sec  
Read Speed 32bit ArraySize  512kb  time: 0.3 sec 16.9 mb/sec  
Read Speed 32bit ArraySize 1024kb  time: 0.6 sec 16.9 mb/sec  
Read Speed 32bit ArraySize 2048kb  time: 1.2 sec 16.9 mb/sec  
Read Speed 32bit ArraySize 4000kb  time: 2.3 sec 17.0 mb/sec  
****************** External ram test DONE ******************


******************** Internal ram test ********************
Read Speed 8bit ArraySize    1kb  time: 0.0 sec 12.6 mb/sec
Read Speed 8bit ArraySize    2kb  time: 0.0 sec 12.6 mb/sec  
Read Speed 8bit ArraySize    4kb  time: 0.0 sec 12.6 mb/sec  
Read Speed 8bit ArraySize    8kb  time: 0.0 sec 12.5 mb/sec  
Read Speed 8bit ArraySize   16kb  time: 0.1 sec 12.5 mb/sec  
Read Speed 8bit ArraySize   32kb  time: 0.1 sec 12.3 mb/sec  
Read Speed 8bit ArraySize   64kb  time: 0.4 sec 8.6 mb/sec  
Read Speed 8bit ArraySize  128kb  time: 0.7 sec 8.6 mb/sec  


Read Speed 16bit ArraySize    1kb  time: 0.0 sec 22.7 mb/sec
Read Speed 16bit ArraySize    2kb  time: 0.0 sec 22.7 mb/sec
Read Speed 16bit ArraySize    4kb  time: 0.0 sec 22.7 mb/sec
Read Speed 16bit ArraySize    8kb  time: 0.0 sec 22.3 mb/sec
Read Speed 16bit ArraySize   16kb  time: 0.0 sec 22.5 mb/sec
Read Speed 16bit ArraySize   32kb  time: 0.1 sec 21.8 mb/sec
Read Speed 16bit ArraySize   64kb  time: 0.3 sec 12.4 mb/sec
Read Speed 16bit ArraySize  128kb  time: 0.5 sec 12.3 mb/sec


Read Speed 32bit ArraySize    1kb  time: 0.0 sec 45.2 mb/sec
Read Speed 32bit ArraySize    2kb  time: 0.0 sec 45.3 mb/sec
Read Speed 32bit ArraySize    4kb  time: 0.0 sec 45.3 mb/sec
Read Speed 32bit ArraySize    8kb  time: 0.0 sec 43.9 mb/sec
Read Speed 32bit ArraySize   16kb  time: 0.0 sec 44.5 mb/sec
Read Speed 32bit ArraySize   32kb  time: 0.0 sec 42.1 mb/sec
Read Speed 32bit ArraySize   64kb  time: 0.2 sec 17.0 mb/sec
Read Speed 32bit ArraySize  128kb  time: 0.4 sec 16.9 mb/sec

****************** Internal ram test DONE ******************


******************** Flash speed test ********************
File system mounted.
createFile(/file0.txt ,   1024):    332 millis
createFile(/file1.txt ,   2048):    102 millis
createFile(/file2.txt ,   4096):    134 millis
createFile(/file3.txt ,   8192):    973 millis
createFile(/file4.txt ,  16384):    433 millis
createFile(/file5.txt ,  32768):    813 millis
createFile(/file6.txt ,  65536):   1565 millis
createFile(/file7.txt , 131072):   3051 millis
createFile(/file8.txt , 262144):   6047 millis
createFile(/file9.txt , 524288):  12366 millis
readFile  (/file0.txt ,   1024):     49 millis
readFile  (/file1.txt ,   2048):     60 millis
readFile  (/file2.txt ,   4096):     80 millis
readFile  (/file3.txt ,   8192):    121 millis
readFile  (/file4.txt ,  16384):    200 millis
readFile  (/file5.txt ,  32768):    362 millis
readFile  (/file6.txt ,  65536):    689 millis
readFile  (/file7.txt , 131072):   1346 millis
readFile  (/file8.txt , 262144):   2666 millis
readFile  (/file9.txt , 524288):   5311 millis
seekFile  (/file0.txt , 1000,   30):    338 millis
seekFile  (/file1.txt , 1000,   30):    341 millis
seekFile  (/file2.txt , 1000,   30):    342 millis
seekFile  (/file3.txt , 1000,   30):    829 millis
seekFile  (/file4.txt , 1000,   30):   1263 millis
seekFile  (/file5.txt , 1000,   30):   1617 millis
seekFile  (/file6.txt , 1000,   30):   1881 millis
seekFile  (/file7.txt , 1000,   30):   2034 millis
seekFile  (/file8.txt , 1000,   30):   2229 millis
seekFile  (/file9.txt , 1000,   30):   2378 millis
seekFile  (/file0.txt , 1000,  100):    971 millis
seekFile  (/file1.txt , 1000,  100):   1006 millis
seekFile  (/file2.txt , 1000,  100):   1007 millis
seekFile  (/file3.txt , 1000,  100):   1494 millis
seekFile  (/file4.txt , 1000,  100):   1972 millis
seekFile  (/file5.txt , 1000,  100):   2351 millis
seekFile  (/file6.txt , 1000,  100):   2595 millis
seekFile  (/file7.txt , 1000,  100):   2801 millis
seekFile  (/file8.txt , 1000,  100):   2937 millis
seekFile  (/file9.txt , 1000,  100):   3054 millis
******************** Flash speed DONE ********************
```


