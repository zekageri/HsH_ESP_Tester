#include <hshTest.h>

void hshTest::setArraySize(int size) {
    arraySize = size;
}

boolean hshTest::isEven(int x){
    if((x & 1) == 0){ return true; }
    return false;
}

void hshTest::ramFill() {
    if (!psramFound()) {
        display.printf(DISP_ERROR, "There is no external ram on this module. Test aborted.");
        return;
    }
    display.printf(DISP_INFO,"\n******* RAM FILL *******\n");

    display.printf(DISP_INFO, "Size: %d byte\n",
        ESP.getPsramSize());

    display.printf(DISP_INFO, "Free: %d byte\n",
        ESP.getFreePsram());

    display.printf(DISP_INFO, "Used: %d byte\n",
        ESP.getPsramSize() - ESP.getFreePsram());

    // Allocate memory in external ram with size of arraySize
    psAlloc.reserve(arraySize);

    display.printf(DISP_INFO, "Used after allocation of %d bytes is: %d byte\n",
        arraySize, ESP.getPsramSize() - ESP.getFreePsram());

    boolean memIsOk = true;
    for (uint32_t x=0; x<psAlloc.size(); x++) {
        //psAlloc.push_back(0xFFFF);
        //psAlloc.assign(x,0xFFF);
        psAlloc[x] = 0xFFFF;
        if( psAlloc.at(x) != 0xFFFF ){
            memIsOk = false;
            break;
        }
    }
    display.printf(DISP_INFO, "Memory is %s for 0xFFFF.\n",memIsOk?"ok":"faulted");
    memIsOk = true;
    for (uint32_t x=0; x<psAlloc.size(); x++) {
        //psAlloc.push_back(0x0000);
        //psAlloc.assign(x,0x0000);
        psAlloc[x] = 0x0000;
        if( psAlloc.at(x) != 0x0000 ){
            memIsOk = false;
            break;
        }
    }
    display.printf(DISP_INFO, "Memory is %s for 0x0000.\n",memIsOk?"ok":"faulted");
    memIsOk = true;
    for (uint32_t x=0; x<psAlloc.size(); x++) {
        if( isEven(x) ){
            //psAlloc.push_back(0x0000);
            //psAlloc.assign(x,0x0000);
            psAlloc[x] = 0x0000;
            if( psAlloc.at(x) != 0x0000 ){
                memIsOk = false;
                break;
        }
        }else{
            //psAlloc.push_back(0xFFFF);
            //psAlloc.assign(x,0xFFFF);
            psAlloc[x] = 0xFFFF;
            if( psAlloc.at(x) != 0xFFFF ){
                memIsOk = false;
                break;
            }
        }
    }
    display.printf(DISP_INFO, "Memory is %s for odd-even.\n",memIsOk?"ok":"faulted");
    psAlloc.clear();
    psAlloc.shrink_to_fit();

    display.printf(DISP_INFO, "Used after free of %d bytes is: %d byte\n",
        arraySize, ESP.getPsramSize() - ESP.getFreePsram());

    display.printf(DISP_INFO,"******* RAM FILL DONE *******\n");
}

void hshTest::json(const char* jsonChar) {
    display.printf(DISP_INFO,"\n******* JSON TEST *******\n");

    size_t size = (strlen(jsonChar) * 2) + 1;

    jsonDoc testDoc(size);
    DeserializationError error = deserializeJson(testDoc, jsonChar);

    if (error) {
        display.printf(DISP_ERROR, "Failed to deserialize jsonChar. Size of the jsonChar is: %d bytes. Error: %s\n", size, error.c_str());
        return;
    }

    display.printf(DISP_INFO, "Used after allocation of %d bytes is: %d byte\n",
        size, ESP.getPsramSize() - ESP.getFreePsram());
    
    serializeJsonPretty(testDoc, Serial);
    display.printf(DISP_INFO,"\n");
    display.printf(DISP_INFO,"******* JSON TEST DONE *******\n");
}

double hshTest::getTime() { return (double)esp_timer_get_time() / 1000000; }

int hshTest::ramSpeed( boolean isExtRam ) {
    display.clear();
    if( isExtRam ){
        display.printf(DISP_INFO,"\n******************** External ram test ********************\n");
    }else{
        display.printf(DISP_INFO,"\n******************** Internal ram test ********************\n");
    }

    char xx = 0;
    for (int a = 0; a < 13; a++) {
        // Internal ram overflow protection
        if( !isExtRam && rs[a] > 128 ){ display.printf(DISP_INFO,"\n");break; }
        display.printf(DISP_INFO, "Read Speed 8bit ArraySize %4dkb ", rs[a]);
        int ramsize = rs[a] * 1024;

        char* rm;
        if( isExtRam ){
            rm = (char*)ps_malloc(ramsize);
        }else{
            rm = (char*)malloc(ramsize);
        }

        int iters = 10;  // Just enuff to boot the dog
        if (rs[a] < 512) iters = 50;
        double st = getTime();
        for (int b = 0; b < iters; b++)
            for (int c = 0; c < ramsize; c++)
                xx |= rm[c];
        st = getTime() - st;
        vTaskDelay(1);  // Dog it!
        double speed = ((double)(iters * ramsize) / (1024 * 1024)) / (st);
        display.printf(DISP_INFO, " time: %2.1f sec %2.1f mb/sec  \n", st, speed);
        free(rm);
    }
    display.printf(DISP_INFO, "\n");
    for (int a = 0; a < 13; a++) {
        // Internal ram overflow protection
        if( !isExtRam && rs[a] > 128 ){ display.printf(DISP_INFO,"\n");break; }

        display.printf(DISP_INFO, "Read Speed 16bit ArraySize %4dkb ", rs[a]);
        int ramsize = rs[a] * 1024;

        short* rm;
        if( isExtRam ){
            rm = (short*)ps_malloc(ramsize);
        }else{
            rm = (short*)malloc(ramsize);
        }

        int iters = 10;  // Just enuff to boot the dog
        if (rs[a] < 512) iters = 50;
        double st = getTime();
        for (int b = 0; b < iters; b++)
            for (int c = 0; c < ramsize / 2; c++)
                xx |= rm[c];
        st = getTime() - st;
        vTaskDelay(1);  // Dog it!
        double speed = ((double)(iters * ramsize) / (1024 * 1024)) / (st);
        display.printf(DISP_INFO, " time: %2.1f sec %2.1f mb/sec  \n", st, speed);
        free(rm);
    }
    display.printf(DISP_INFO, "\n");
    for (int a = 0; a < 13; a++) {
        // Internal ram overflow protection
        if( !isExtRam && rs[a] > 128 ){ display.printf(DISP_INFO,"\n");break; }
        
        display.printf(DISP_INFO, "Read Speed 32bit ArraySize %4dkb ", rs[a]);
        int ramsize = rs[a] * 1024;

        int* rm;
        if( isExtRam ){
            rm = (int*)ps_malloc(ramsize);
        }else{
            rm = (int*)malloc(ramsize);
        }

        int iters = 10;  // Just enuff to boot the dog
        if (rs[a] < 512) iters = 50;
        double st = getTime();
        for (int b = 0; b < iters; b++)
            for (int c = 0; c < ramsize / 4; c++)
                xx |= rm[c];
        st = getTime() - st;
        vTaskDelay(1);  // Dog it!
        double speed = ((double)(iters * ramsize) / (1024 * 1024)) / (st);
        display.printf(DISP_INFO, " time: %2.1f sec %2.1f mb/sec  \n", st, speed);
        free(rm);
    }
    if( isExtRam ){
        display.printf(DISP_INFO,"****************** External ram test DONE ******************\n\n");
    }else{
        display.printf(DISP_INFO,"****************** Internal ram test DONE ******************\n\n");
    }
    return xx;
}

void hshTest::flashSpeed() {
    display.clear();
    display.printf(DISP_INFO,"\n******************** Flash speed test ********************\n");
    fs.begin();
    
    int fileNum = 0;
    char fileName[20];
    unsigned long startMillis;
    unsigned long elapsedMillis;
    for (int a = 0; a < 10; a++) {
        sprintf(fileName, "%s%d%s", "/file",fileNum,".txt");
        int fileSize = rs[a] * 1024;

        startMillis = millis();
            fs.createFile(fileName, fileSize);
        elapsedMillis = millis() - startMillis;
        display.printf(DISP_INFO, "%-10s(%-11s, %6lu): %6lu millis\n",
            "createFile", fileName, (unsigned long)fileSize, elapsedMillis);

        fileNum++;
    }
    fileNum = 0;
    for (int a = 0; a < 10; a++) {
        sprintf(fileName, "%s%d%s", "/file",fileNum,".txt");
        int fileSize = rs[a] * 1024;

        startMillis = millis();
            fs.readFile(fileName, fileSize);
        elapsedMillis = millis() - startMillis;
        display.printf(DISP_INFO, "%-10s(%-11s, %6lu): %6lu millis\n",
            "readFile", fileName, (unsigned long)fileSize, elapsedMillis);

        fileNum++;
    }

    fileNum = 0;
    for (int a = 0; a < 10; a++) {
        sprintf(fileName, "%s%d%s", "/file",fileNum,".txt");
        int size = rs[a] * 1024;

        startMillis = millis();
            fs.seekFile(fileName, size, 1000, 30);
        elapsedMillis = millis() - startMillis;
        display.printf(DISP_INFO, "%-10s(%-11s, %4u, %4lu): %6lu millis\n",
            "seekFile", fileName, (unsigned)1000, (unsigned long)30,
                elapsedMillis);

        fileNum++;
    }

    fileNum = 0;
    for (int a = 0; a < 10; a++) {
        sprintf(fileName, "%s%d%s", "/file",fileNum,".txt");
        int size = rs[a] * 1024;
        
        startMillis = millis();
            fs.seekFile(fileName, size, 1000, 100);
        elapsedMillis = millis() - startMillis;
        display.printf(DISP_INFO, "%-10s(%-11s, %4u, %4lu): %6lu millis\n",
            "seekFile", fileName, (unsigned)1000, (unsigned long)100,
                elapsedMillis);

        fileNum++;
    }
    
    display.printf(DISP_INFO,"******************** Flash speed DONE ********************\n");
}