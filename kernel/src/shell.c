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

shell_settings settings;

void handle_keyboard_input(char c) {
    if (c == '\n') {
        key_buffer[buffer_index] = '\0'; 
        execute_command(key_buffer);
        buffer_index = 0;
        print_char('\n', settings.main_bg_fg);
        clear_current_line(settings.main_bg_fg);
        
    } else if (c == '\b') {
        if (buffer_index > 0) {
            buffer_index--;
            print_char('\b', settings.main_bg_fg); 
        }
    } else {
        if (buffer_index < 255) {
            key_buffer[buffer_index++] = c;
            print_char(c, settings.user_bg_fg);
        }
    }
}


void execute_command(char *input){
    if (input[0] != ':') {
        return; 
    }
    char *cmd_input = input + 1;

    print_char('\n',settings.main_bg_fg);
    for (int i = 0; i < num_commands; i++) {
        if (strcmp(cmd_input, commands[i].name) == 0) {
            commands[i].handler();
            return;
        }
    }
    print_string("Brak takiej komendy! Wpisz :help, zeby uzyskac liste komend", settings.system_bg_fg);
}


//commands

void cmd_help() {
    print_string("Dostepne komendy:", settings.system_bg_fg);
    for(int i=0; i<num_commands;i++) {
        print_string(commands[i].name, settings.system_bg_fg);
        print_string(", ", settings.system_bg_fg);
    }
    
}

void cmd_clear() {
    clear_screen(settings.main_bg_fg);
}

void cmd_system_time(){
    print_time(settings.system_bg_fg);
}

void init_shell() {
    settings.user_bg_fg = 0x0F;
    settings.system_bg_fg = 0x03;
    settings.main_bg_fg = 0x0F;

    clear_screen(settings.main_bg_fg);
}

