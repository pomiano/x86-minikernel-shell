#ifndef SHELL_H
#define SHELL_H

#include "../include/drivers/rtc.h"
#include <stdbool.h>

#define HISTORY_SIZE 5
#define MAX_CMD_LEN 60

#define KEY_UP -1
#define KEY_DOWN -2
#define KEY_LEFT -3
#define KEY_RIGHT -4


typedef void (*command_handler_t)(char*);

typedef struct {
    char* name;
    command_handler_t handler;
} shell_command_t;

typedef struct {
    uint8_t user_bg_fg;     
    uint8_t system_bg_fg;  
    uint8_t error_bg_fg;    
    uint8_t success_bg_fg;
    uint8_t main_bg_fg;
} shell_settings;


typedef struct {
    char lines[HISTORY_SIZE][MAX_CMD_LEN]; 
    int count;
    int view_index;   
} command_history_t;


void handle_keyboard_input(char c);
void execute_command(char *input);

void init_shell();

//commands
void cmd_help(char *args);
void cmd_clear(char *args);
void cmd_system_time(char *args);
void cmd_set(char * args);
void cmd_colors();
void cmd_fetch();
void cmd_shutdown();

//funckje pomocniczne
void set_system_bg(uint8_t bg_color);
void set_system_fg(uint8_t fg_color);
void set_user_bg(uint8_t bg_color);
void set_user_fg(uint8_t fg_color);
void set_main_bg(uint8_t bg_color);

void history_add(char * command);
void load_history_to_buffer();



#endif