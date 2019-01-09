APPLICATION=pwm_test

BOARD ?= olimex-stm32-p405

DEVELHELP ?= 1

DEBUG = 1
CFLAGS += '-DSTDIO_UART_DEV=UART_DEV(1)'

USEMODULE += periph_pwm
USEMODULE += xtimer

RIOTBASE ?= $(CURDIR)/../../RIOT

include $(RIOTBASE)/Makefile.include
