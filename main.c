
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "leds.h"
#include "usart.h"
#include "sdcard_diskio.h"
#include "logger.h"
#include "lua.h"
#include "pthread.h"

/**
 * a data structure that holds data used by this application
 *
 * just holds a logger for this project.
 * for a large project loggers are good because they can be turned on and off in software,
 * can pipe log data to various endpoints, and can be compiled out to save space using
 * the option USE_LOGGER=0 in the makefile.
 */
typedef struct {
    logger_t log;
} appdata_t;

static disk_interface_t sddisk;

void app_task(appdata_t* appdata);
void init_devices(appdata_t* appdata);

#define  init_devices_task(appdata) xTaskCreate((TaskFunction_t)init_devices,\
                                         "init devices", \
                                         configMINIMAL_STACK_SIZE + 256, \
                                         appdata, \
                                         tskIDLE_PRIORITY + 1, \
                                         NULL)

#define  start_app_task(appdata) xTaskCreate((TaskFunction_t)app_task,\
                                       "test task",\
                                       configMINIMAL_STACK_SIZE + 4096, \
                                       appdata,\
                                       tskIDLE_PRIORITY + 1, \
                                       NULL)


/**
 * the test device is to be named /dev/ttyS0, attached to the CONSOLE_USART
 * Note: the CONSOLE_USART transmit is captured by default for use by SDTOUT
 * in this application we will only use CONSOLE_USART receiver
 */
#define TEST_USART_DEV        "/dev/ttyS0"
#define TEST_USART            CONSOLE_USART
#define TEST_USART_MODE        O_RDWR
#define TEST_USART_BUFSIZE    128
#define TEST_DATAFILE        "datafile.txt"

/**
 * devices must be initialised before the application can make use of them...
 */
void init_devices(appdata_t* appdata)
{
    log_init(&appdata->log, "main");

    // init filesystem
    sdcard_mount(&sddisk, 0);

    // initialize the lua usart device file
    log_info(&appdata->log, "init %s...", "/dev/ttyS0");
    usart_init(CONSOLE_USART, "/dev/ttyS0", false, USART_FULLDUPLEX);

    start_app_task(appdata);

    vTaskDelete(NULL);
}

char* args[] = {
     "lua", NULL
};

void app_task(appdata_t* appdata)
{
    log_info(&appdata->log, "open lua repl");

    FILE* luaconsole = fopen("/dev/ttyS0", "r+");
    lua_main(luaconsole, luaconsole, 1, args);
    fclose(luaconsole);
    log_info(&appdata->log, "closed lua repl");
    vTaskDelete(NULL);
}

int main(void)
{
    // use the system led flasher to flash one of the leds
    flash_led(LED1);

    appdata_t appdata;

    // create task to initialise hardware devices
    init_devices_task(&appdata);

    pthread_exit(0);
    return 0;
}
