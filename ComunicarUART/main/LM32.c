#include "LM32.h"

float lm75aGetValues(){
    uint8_t rawData[2];
    bool neg = 0;
    int16_t data = 0;
    float temperatura = 0;

    i2c_cmd_handle_t cmd_handle = i2c_cmd_link_create();
    i2c_master_start(cmd_handle);
    i2c_master_write_byte(cmd_handle,(LM75A_ADDR << 1) | I2C_MASTER_READ,true);
    i2c_master_read(cmd_handle,(uint8_t *) rawData,2,I2C_MASTER_ACK);
    i2c_master_stop(cmd_handle);
    i2c_master_cmd_begin(I2C_NUM_0, cmd_handle, pdMS_TO_TICKS(250));
    i2c_cmd_link_delete(cmd_handle);

    if (rawData[0] >> 8 == 1){
        neg = true;
        rawData[0] = rawData[0] & 0b01111111;
    }

    data = (rawData[0] << 8 | rawData[1]) >> 5;
    temperatura = (data * 0.125);
    if (neg == 1){
        temperatura = temperatura*(-1);
    }

    return temperatura;
}
