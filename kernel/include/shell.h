#ifndef SHELL_H
#define SHELL_H

#include "../include/drivers/rtc.h"

typedef void (*command_handler_t)();

typedef struct {
    char* name;
    command_handler_t handler;
} shell_command_t;


void handle_keyboard_input(char c);
void execute_command(char *input);

//commands
void cmd_help();
void cmd_clear();
void cmd_system_time();

#endif