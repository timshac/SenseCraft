#include "grove_ac_current_sensor.h"
#include "Arduino.h"
#include "SensorsUtils.h"

#define AC_CURRENT_SDAPIN D1
#define AC_CURRENT_SCLPIN D0

ACCurrentThread::ACCurrentThread() : Thread("ACCurrentThread", 128, 1) {
}
void ACCurrentThread::Run() {
    softwarei2c.begin(AC_CURRENT_SDAPIN, AC_CURRENT_SCLPIN);
    // Initialize sensor
    mySensor.begin(&softwarei2c);
    while (true) {
        softwarei2c.begin(AC_CURRENT_SDAPIN, AC_CURRENT_SCLPIN);
        status =  mySensor.read();
        data[0] = (int32_t)(mySensor.getTemperature()*100);  
        data[1] = (int32_t)(mySensor.getHumidity());
 
        Delay(Ticks::MsToTicks(SENSOR_READ_DELAY));
    }
}

grove_ac_current::grove_ac_current() {
    accurrentThread = new ACCurrentThread();
}
void grove_ac_current::init() {
    accurrentThread->Start();
}

bool grove_ac_current::read(struct sensor_data *sdata) {

    sdata->data      = accurrentThread->data;
    sdata->data_type = SENSOR_DATA_TYPE_FLOAT;
    sdata->size      = sizeof(accurrentThread->data);
    sdata->id        = GROVE_AC_CURRENT;
    sdata->name      = name;
    sdata->status    = accurrentThread->status;
    sdata->ui_type   = SENSOR_UI_TYPE_NORMAL;
    sdata->data_unit = data_unit;
    return sdata->status;
}

const char *grove_ac_current::get_name() {
    return "ACCurrent";
}

