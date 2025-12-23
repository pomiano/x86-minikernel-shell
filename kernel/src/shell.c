#include "../include/shell.h"
#include "../include/drivers/screen.h"
#include "../include/lib/string.h"

static char key_buffer[256];
static int buffer_index = 0;

static shell_command_t commands[] = {
    {"help",   cmd_help},
    {"clear",  cmd_clear},
    {"system-time", cmd_system_time}
};

static const int num_commands = sizeof(commands) / sizeof(shell_command_t);



void handle_keyboard_input(char c) {
    if (c == '\n') {
        key_buffer[buffer_index] = '\0'; 
        execute_command(key_buffer);
        buffer_index = 0;
        print_char('\n', 0x0F);
        clear_current_line();
        
    } else if (c == '\b') {
        if (buffer_index > 0) {
            buffer_index--;
            print_char('\b', 0x07); 
        }
    } else {
        if (buffer_index < 255) {
            key_buffer[buffer_index++] = c;
            print_char(c, 0x07);
        }
    }
}


void execute_command(char *input){
    if (input[0] != ':') {
        return; 
    }
    char *cmd_input = input + 1;

    print_char('\n',0X0F);
    for (int i = 0; i < num_commands; i++) {
        if (strcmp(cmd_input, commands[i].name) == 0) {
            commands[i].handler();
            return;
        }
    }
    print_string("Brak takiej komendy! Wpisz :help, zeby uzyskac liste komend", 0x0F);
}


//commands

void cmd_help() {
    print_string("Dostepne komendy:", 0x0F);
    for(int i=0; i<num_commands;i++) {
        print_string(commands[i].name, 0x0F);
        print_string(", ", 0x0F);
    }
}

void cmd_clear() {
    clear_screen();
}

void cmd_system_time(){
    print_time();
}
