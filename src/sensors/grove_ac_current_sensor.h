#ifndef __GROVE_AC_CURRENT_SENSOR_H
#define __GROVE_AC_CURRENT_SENSOR_H

#include <SHT2x.h>
#include "sensor.h"
#include "utils.h"
#include "SoftwareI2C.h"
#include <Seeed_Arduino_ooFreeRTOS.h>

#define AC_CURRENT_SDAPIN D1
#define AC_CURRENT_SCLPIN D0

using namespace cpp_freertos;

class ACCurrentThread : public Thread {

  public:
    ACCurrentThread();  //was Sgp30
    int     data[2];
    uint8_t dsize;
    bool    status;
    SHT2x       mySensor;  //was SGP30
    SoftwareI2C softwarei2c;
  protected:
    virtual void Run();
};

class grove_ac_current : public sensor_base {   //grove_sgp30_sensor
  public:
    grove_ac_current();
    void        init();
    const char *get_name();
    bool        read(struct sensor_data *data);

  private:
    const char *name = "Current_PF"; 
    const char *data_unit = "Amps,NA";
    int         sht20_value[2];  //sgp30_value

    ACCurrentThread *accurrentThread;  //Sgp30 *sgp30;
};

#endif