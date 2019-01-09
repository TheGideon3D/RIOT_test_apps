#include <stdio.h>
#include <string.h>

#include "board.h"
#include "xtimer.h"
#include "periph/i2c.h"
#include "errno.h"
#include "config.h"

#define i2c_dev I2C_DEV(0)

static kernel_pid_t pid_thread;
static char stack_thread[THREAD_STACKSIZE_MAIN];


void printError(int test) {
    switch (test) {
        case 0:
            break;
        case -EIO:
            puts("When slave device doesn't ACK the byte ");
            break;
        case -ENXIO:
            puts("When no devices respond on the address sent on the bus" );
            break;
        case -ETIMEDOUT:
            puts("Error: Sensor did not apply configuration");
            break;
        case -EINVAL:
            puts("When an invalid argument is given");
            break;
        case -EOPNOTSUPP:
            puts("When MCU driver doesn't support the flag operation");
            break;
        case -EAGAIN:
            puts("When a lost bus arbitration occurs");
            break;
        default:
            /* Will never happen, but better safe than sorry */
            puts("Unknown error");
            break;
    }
    if (test != 0) {
        printf("test: %X\n", test);
    }
}


void *thread_handler(void *arg) {
    (void) arg;

    //ADD YOUR DEVICE ADRESS!!!
    
    //uint16_t addr = 0x0050;    //1010 A1 A2 A3 -> A1-3 = 0 
    //uint16_t reg = 0x6543;   //between 0x0000 and 0x7fff
    
    //uint16_t addr = 0x001e;
    //uint16_t reg = 0x00c1;

    uint16_t *wdata = 0;
    *wdata = 0x6543;
    void *rdata = 0;

    uint16_t test = 0;


    while(1) {
        LED0_TOGGLE;
        
        //acquire i2c bus
        //write wdata
        //release i2c bus
        //test for errors
        if (i2c_acquire(dev) != 0) {puts("Acquire failed");}

        test = i2c_write_reg(dev, addr, reg, *wdata, 0);

        if (i2c_release(dev) != 0) {puts("release failed");}
        printError(test);


        xtimer_usleep(1000 * 1000)




        //acquire i2c bus
        //read to rdata
        //release i2c bus
        //test for errors
        //print data
        if (i2c_acquire(dev) != 0) {puts("Acquire failed");}
        
        test = i2c_read_reg(dev, addr, reg, rdata, 0);        
        
        if (i2c_release(dev) != 0) {puts("release failed");}
        printError(test);

        printf("data: %d\n" ,*(uint8_t *) rdata);


        xtimer_usleep(1000 * 1000);

    }

    return NULL;
}


int main(void) {
     
    //init i2c device
    i2c_init(i2c_dev);

    pid_thread = thread_create(stack_thread, sizeof(stack_thread),
            THREAD_PRIORITY_MAIN - 1, 0, thread_handler, NULL, "DEEZ THREAD IS AWESOME");
   
    if(pid_thread != 0) return 0;

    return 1;
}
