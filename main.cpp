#include "mbed.h"
#include "LSM6DSLSensor.h"
#include <cmath>

#define PI 3.141592654

static DevI2C devI2c(PB_11,PB_10);
static LSM6DSLSensor acc_gyro(&devI2c,0xD4,D4,D5);

float computeRoll(int x, int y, int z) {
    return atan2(y, sqrt(x * x + z * z)) * 180.0 / PI;
}

float computePitch(int x, int y, int z) {
    return atan2(x, sqrt(y * y + z * z)) * 180.0 / PI;
}

int main() {
    uint8_t id;
    int32_t axes[3];
    float roll, pitch;
    acc_gyro.init(NULL);

    acc_gyro.enable_x();
    acc_gyro.enable_g();

    printf("This is an accelerometer example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    acc_gyro.read_id(&id);
    printf("LSM6DSL accelerometer & gyroscope = 0x%X\r\n", id);

    while(1) {
        acc_gyro.get_x_axes(axes);
        roll = computeRoll(axes[0], axes[1], axes[2]);
        pitch = computePitch(axes[0], axes[1], axes[2]);
        printf("LSM6DSL: %6d, %6d, %6d, roll: %3.2f, pitch: %3.2f\r\n", axes[0], axes[1], axes[2], roll, pitch);

        thread_sleep_for(2000);
    }
}
