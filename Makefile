
BOARD = uemb4

PROJECT_NAME = embedded-lua
LUA_SRC = lua-5.3.1/src
#LIBS = $(LUA_SRC)/liblua.a
#CC= $(CCPREFIX)gcc -std=gnu99
#CCPREFIX = arm-none-eabi-
#MYCFLAGS = -mthumb -mcpu=cortex-m4
#MYCFLAGS += -D __FPU_PRESENT=1 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -fno-strict-aliasing -Wdouble-promotion -fsingle-precision-constant
#MYCFLAGS += -DLUA_32BITS

SOURCE = main.c
SOURCE += $(LUA_SRC)/lapi.c
SOURCE += $(LUA_SRC)/lua.c
SOURCE += $(LUA_SRC)/lcode.c
SOURCE += $(LUA_SRC)/lctype.c
SOURCE += $(LUA_SRC)/ldebug.c
SOURCE += $(LUA_SRC)/ldo.c
SOURCE += $(LUA_SRC)/ldump.c
SOURCE += $(LUA_SRC)/lfunc.c
SOURCE += $(LUA_SRC)/lgc.c
SOURCE += $(LUA_SRC)/llex.c
SOURCE += $(LUA_SRC)/lmem.c
SOURCE += $(LUA_SRC)/lobject.c
SOURCE += $(LUA_SRC)/lopcodes.c
SOURCE += $(LUA_SRC)/lparser.c
SOURCE += $(LUA_SRC)/lstate.c
SOURCE += $(LUA_SRC)/lstring.c
SOURCE += $(LUA_SRC)/ltable.c
SOURCE += $(LUA_SRC)/ltm.c
SOURCE += $(LUA_SRC)/lundump.c
SOURCE += $(LUA_SRC)/lvm.c
SOURCE += $(LUA_SRC)/lzio.c
SOURCE += $(LUA_SRC)/lauxlib.c
SOURCE += $(LUA_SRC)/lbaselib.c
SOURCE += $(LUA_SRC)/lbitlib.c
SOURCE += $(LUA_SRC)/lcorolib.c
SOURCE += $(LUA_SRC)/ldblib.c
SOURCE += $(LUA_SRC)/liolib.c
SOURCE += $(LUA_SRC)/lmathlib.c
SOURCE += $(LUA_SRC)/loslib.c
SOURCE += $(LUA_SRC)/lstrlib.c
SOURCE += $(LUA_SRC)/ltablib.c
SOURCE += $(LUA_SRC)/lutf8lib.c
SOURCE += $(LUA_SRC)/loadlib.c
SOURCE += $(LUA_SRC)/linit.c

CFLAGS = -I $(LUA_SRC)
CFLAGS += -DLUA_32BITS

USE_PTHREADS= 1
USE_FREERTOS = 1
USE_MINLIBC = 1
USE_LOGGER = 1
USE_STDIO_USART = 1
USE_LIKEPOSIX = 1
USE_DRIVER_LEDS = 1
USE_DRIVER_SYSTEM_TIMER = 1
USE_DRIVER_USART = 1
USE_STDIO_USART = 1
USE_DRIVER_SDCARD = 1
USE_DRIVER_FAT_FILESYSTEM = 1

USE_CONFPARSE = 1
USE_SHELL = 1

USE_FULL_ASSERT = 1
DEBUG_PRINTF_EXCEPTIONS = 1

STM32DEVSUPPORTDIR = ../lollyjar
include $(STM32DEVSUPPORTDIR)/build-env/setup.mk