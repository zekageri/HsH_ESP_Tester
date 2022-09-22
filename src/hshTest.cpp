#include <hshTest.h>

void hshTest::setArraySize(int size) {
    arraySize = size;
}

void hshTest::ramFill() {
    if (!psramFound()) {
        display.printf(DISP_ERROR, "There is no external ram on this module. Test aborted.");
        return;
    }

    display.printf(DISP_INFO, "- Size: %d byte\n\n",
        ESP.getPsramSize());

    display.printf(DISP_INFO, "- Free: %d byte\n\n",
        ESP.getFreePsram());

    display.printf(DISP_INFO, "- Used: %d byte\n\n",
        ESP.getPsramSize() - ESP.getFreePsram());

    // Allocate a char array in external ram with size of arraySize
    charArr = (char*)ps_malloc(arraySize * sizeof(char));

    // Fill this array with 0xFF
    for (size_t i = 0; i < sizeof(charArr); i++) {
        charArr[i] = 0xFF;
    }
    display.printf(DISP_INFO, "- Array filled with 0xFF\n\n");

    // Fill this array with 0x00
    for (size_t i = 0; i < sizeof(charArr); i++) {
        charArr[i] = 0x00;
    }
    display.printf(DISP_INFO, "- Array filled with 0x00\n\n");

    // Fill this array with 0x00
    for (size_t i = 0; i < sizeof(charArr); i++) {
        charArr[i] = 0x00;
    }
    display.printf(DISP_INFO, "- Array filled with 0x00\n\n");

    if (charArr == NULL || !charArr) {
        display.printf(DISP_ERROR, "- Failed to allocate buffer with size: %d\n\n",
        arraySize);
        return;
    }

    display.printf(DISP_INFO, "- Used after allocation of %d bytes is: %d byte\n\n",
        arraySize, ESP.getPsramSize() - ESP.getFreePsram());

    free(charArr);

    display.printf(DISP_INFO, "- Used after free of %d bytes is: %d byte\n\n",
        arraySize, ESP.getPsramSize() - ESP.getFreePsram());
}

void hshTest::json(const char* jsonChar) {
    size_t size = (strlen(jsonChar) * 2) + 1;

    jsonDoc testDoc(size);
    DeserializationError error = deserializeJson(testDoc, jsonChar);

    if (error) {
        display.printf(DISP_ERROR, "Failed to deserialize jsonChar. Size of the jsonChar is: %d bytes. Error: %s\n", size, error.c_str());
        return;
    }

    display.printf(DISP_INFO, "- Used after allocation of %d bytes is: %d byte\n\n",
        size, ESP.getPsramSize() - ESP.getFreePsram());

    serializeJsonPretty(testDoc, Serial);
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