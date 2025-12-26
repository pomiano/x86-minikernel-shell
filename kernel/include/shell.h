#ifndef SHELL_H
#define SHELL_H

#include "../include/drivers/rtc.h"
#include <stdbool.h>

typedef void (*command_handler_t)();

typedef struct {
    char* name;
    command_handler_t handler;
} shell_command_t;

typedef struct {
    uint8_t user_bg_fg;     
    uint8_t system_bg_fg;  
    uint8_t main_bg_fg;
} shell_settings;



void handle_keyboard_input(char c);
void execute_command(char *input);

void init_shell();

//commands
void cmd_help();
void cmd_clear();
void cmd_system_time();


#endif