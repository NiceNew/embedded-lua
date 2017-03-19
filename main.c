
#include <unistd.h>
#include <fcntl.h>
#include <minlibc/stdio.h>
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

#include "shell.h"
#include "builtins.h"
#include "fs_cmds.h"
#include "os_cmds.h"
//#include "net_cmds.h"


static disk_interface_t sddisk;
static shellserver_t serial_shell;
static shell_cmd_t lua_cmd;

int lua_func(int fdes, const char** args, unsigned char nargs)
{
	char* a[] = {"lua", NULL};
    FILE* f = fdopen(fdes, "r+");
    lua_main(f, f, 1, a);
    fclose(f);
    return SHELL_CMD_EXIT;
}

void init_hardware(disk_interface_t* sdcard_interface, const char* serial_dev)
{
    flash_led(LED1);

    log_info(NULL, "init sdcard...");
    sdcard_mount(sdcard_interface, 0);

    log_info(NULL, "init serial on %s", serial_dev);
    usart_create_dev(serial_dev, CONSOLE_USART, USART_FULLDUPLEX, 115200, 128);
}

void init_serial_shell(shellserver_t* shell, const char* serial_dev, shell_cmd_func_t luafunc, shell_cmd_t* luacmd)
{
	bool threaded = true;
	bool exit_on_eof = false; // for serial shell set to false
	int fd = open(serial_dev, O_RDWR);

	install_builtin_cmds(shell);
	install_fs_cmds(shell);
//	install_net_cmds(shell);
	install_os_cmds(shell);
	register_command(shell, luacmd, luafunc, "lua", "");
	start_shell(shell, NULL, NULL, threaded, exit_on_eof, fd, fd);
}

int main(void)
{
	init_hardware(&sddisk, "/dev/ttyS0");
    init_serial_shell(&serial_shell, "/dev/ttyS0", lua_func, &lua_cmd);
    pthread_exit(0);
    return 0;
}
