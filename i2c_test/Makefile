APPLICATION=test_project

BOARD ?= olimex-stm32-p405

RIOTBASE ?= $(CURDIR)/../../RIOT

DEVELHELP ?= 1

CFLAGS += '-DSTDIO_UART_DEV=UART_DEV(1)'

USEMODULE += periph_gpio
USEMODULE += periph_i2c
USEMODULE += xtimer
USEMODULE += shell


include $(RIOTBASE)/Makefile.include
