#include <stdio.h>
#include <string.h>

#include "board.h"
#include "thread.h"
#include "xtimer.h"
#include "periph/pwm.h"

#define pwm_dev0    PWM_DEV(0)
//#define pwm_dev1    PWM_DEV(1)
#define pwm_mode    PWM_LEFT

//TODO: get meaningfull freq and res from microcontroller datasheet
#define pwm_freq    (1000)
#define pwm_res     (83)
#define pwm_chan    ()

static kernel_pid_t pid_thread;
static char stack_thread[THREAD_STACKSIZE_MAIN];


void *thread_handler(void *arg) {
    (void) arg;
    
    uint8_t pwm_val = 0;
    uint8_t up = 1; 
    printf("thread started");

    //pulse leds on channel 1,2 and 3.
    //toggle on-board led to indicate running status
    while(1) {
        LED0_TOGGLE;

        pwm_set(pwm_dev0, 1, 20);
        pwm_set(pwm_dev0, 2, 45);
        pwm_set(pwm_dev0, 3, 80);

        if(up) {
            pwm_val++;
        } else {
            pwm_val--;
        }
        
        if(pwm_val >= 84) {
            up  = 0;
        } 
        if (pwm_val <= 0) {
            up = 1;
        }

        xtimer_usleep(20*1000);
    }

    return NULL;
}


int main(void) {
    //initialize pwm port
    pwm_init(pwm_dev0, pwm_mode, pwm_freq, pwm_res);
    pwm_poweron(pwm_dev0);

    pid_thread = thread_create(stack_thread, sizeof(stack_thread),
            THREAD_PRIORITY_MAIN - 1, 0, thread_handler, NULL, "DEEZ THREAD IS AWESOME");
   
    if(pid_thread != 0) return 0;

    return 1;
}
