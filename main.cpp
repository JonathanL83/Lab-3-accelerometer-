#include "mbed.h"
#include "LSM6DSLSensor.h"

#define PI 3.141592654

static DevI2C devI2c(PB_11, PB_10);
static LSM6DSLSensor acc_gyro(&devI2c, 0xD4, D4, D5);

void computeAngles(int x, int y, int z, float &pitch, float &roll) {
    float ax = x * 0.061 * 9.81;
    float ay = y * 0.061 * 9.81;
    float az = z * 0.061 * 9.81;

    pitch = atan2(ay, sqrt(ax * ax + az * az));
    roll = atan2(-ax, az);

    pitch = pitch * 180.0 / PI;
    roll = roll * 180.0 / PI;
}

int main() {
    uint8_t id;
    int32_t axes[3];
    float pitch = 0, roll = 0;

    acc_gyro.init(NULL);
    acc_gyro.enable_x();
    acc_gyro.enable_g();

    printf("This is an accelerometer example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    acc_gyro.read_id(&id);
    printf("LSM6DSL accelerometer & gyroscope = 0x%X\r\n", id);

    while (1) {
        acc_gyro.get_x_axes(axes);
        computeAngles(axes[0], axes[1], axes[2], pitch, roll);
        printf("LSM6DSL: X=%6d, Y=%6d, Z=%6d, Pitch=%3.2f, Roll=%3.2f\r\n", axes[0], axes[1], axes[2], pitch, roll);

        thread_sleep_for(2000);
    }
}