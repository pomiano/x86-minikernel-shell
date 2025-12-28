#include "../include/shell.h"
#include "../include/drivers/screen.h"
#include "../include/lib/string.h"

static char key_buffer[256];
static int buffer_index = 0;

static shell_command_t commands[] = {
    {"help",   cmd_help},
    {"clear",  cmd_clear},
    {"system-time", cmd_system_time},
    {"set", cmd_set},
    {"colors", cmd_colors}
};

static const int num_commands = sizeof(commands) / sizeof(shell_command_t);

shell_settings settings;
command_history_t history;

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
    } else if(c == KEY_DOWN){
        if(history.view_index < history.count){
            history.view_index++;
            if(history.view_index == history.count){
                clear_current_line(settings.main_bg_fg);
                key_buffer[0] = '\0';
                buffer_index = 0;
            }else {
                load_history_to_buffer();
            }
        }

    } else if(c == KEY_UP) {
        if(history.view_index>0){
            history.view_index--;
            load_history_to_buffer();

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
    char*arg;

    history_add(cmd_input);

    for(int i = 0; cmd_input[i]!='\0'; i++) {
        if(cmd_input[i]==' '){
            cmd_input[i] = '\0';
            arg = &cmd_input[i+1];
            break;
        }
    }
    print_char('\n',settings.main_bg_fg);
    for (int i = 0; i < num_commands; i++) {
        if (strcmp(cmd_input, commands[i].name) == 0) {
            commands[i].handler(arg);
            return;
        }
    }
    print_string("Brak takiej komendy! Wpisz :help, zeby uzyskac liste komend", settings.error_bg_fg);
}

void init_shell() {
    settings.user_bg_fg = 0x0F;
    settings.system_bg_fg = 0x03;
    settings.error_bg_fg = 0x0C;   
    settings.success_bg_fg = 0x0A;
    settings.main_bg_fg = 0x0F;

    history.view_index=0;
    history.count=0;

    clear_screen(settings.main_bg_fg);
}


//commands

void cmd_help(char *args) {
    print_string("Dostepne komendy:", settings.system_bg_fg);
    for(int i=0; i<num_commands;i++) {
        print_string(commands[i].name, settings.system_bg_fg);
        print_string(", ", settings.system_bg_fg);
    }
    
}

void cmd_clear(char *args) {
    clear_screen(settings.main_bg_fg);
}

void cmd_system_time(char *args){
    print_time(settings.system_bg_fg);
}


//TODO
void cmd_set(char * args) {
    if (args == 0 || args[0] == '\0') {
        print_string("Ta funckja wymaga argumentow! Wpisz ':set -h', zeby dowiedziec sie wiecej", settings.error_bg_fg);
        return;
    }

    char *target = args;
    char *type = 0;
    char *val_str = 0;

    for (int i = 0; target[i]; i++) {
        if (target[i] == ' ') {
            target[i] = '\0';
            type = &target[i + 1];
            break;
        }
    }
    if(strcmp(target, "-h")==0){
        print_string("Uzycie: :set [system/user] [fg/bg] [wartosc]\n", settings.system_bg_fg);
        print_string("Opcje: fg (czcionka), bg (tlo)\n", settings.system_bg_fg);
        print_string("Format: liczba 0-15 lub hex (np. 0x0A)\n", settings.system_bg_fg);
        print_string("Dostepne kolory mozesz zobaczyc po uzyciu ':colors'", settings.system_bg_fg);
        return;
    }

    if (type) {
        for (int i = 0; type[i]; i++) {
            if (type[i] == ' ') {
                type[i] = '\0';
                val_str = &type[i + 1];
                break;
            }
        }
    }

    if (!val_str) {
        print_string("Blad: Za malo argumentow! Wpisz ':set -h', zeby dowiedziec sie wiecej", settings.error_bg_fg);
        return;
    }

    uint8_t val;
    if (val_str[0] == '0' && val_str[1] == 'x') {
        val = (uint8_t)str_to_hex(val_str);
    } else {
        val = (uint8_t)atoi(val_str);      
    }

    if (strcmp(target, "system") == 0){
        if(strcmp(type, "fg")==0){
            set_system_fg(val);
        } else if(strcmp(type, "bg")==0) {
            set_system_bg(val);
        } else {
            print_string("Bledna komenda! Wpisz ':set -h', zeby dowiedziec sie wiecej", settings.error_bg_fg);
            return;
        }
    } else if( strcmp(target, "user") == 0){
        if(strcmp(type, "fg")==0){
            set_user_fg(val);
        } else if(strcmp(type, "bg")==0) {
            set_user_bg(val);
        } else {
            print_string("Bledna komenda! Wpisz ':set -h', zeby dowiedziec sie wiecej", settings.error_bg_fg);
            return;
        }
    } else{
        print_string("Bledna komenda! Wpisz ':set -h', zeby dowiedziec sie wiecej", settings.error_bg_fg);
        return;
    }
    print_string("Ustawienia zaktualizowane!", settings.success_bg_fg);
}

void cmd_colors() {
    print_string("Dostepne kolory:\n", settings.system_bg_fg);
    char *hex_chars = "0123456789ABCDEF";
    char buff[2];
    buff[1] = '\0';

    for (int i = 0; i < 16; i++) {
        buff[0] = hex_chars[i];
        
        print_string(buff, i); 
        print_string(" ", settings.system_bg_fg);
    }
    print_string("\n", settings.system_bg_fg);
}

// funkcje pomocnicze

void set_system_bg(uint8_t bg_color) {
    uint8_t current_fg = settings.system_bg_fg & 0x0F; 
    settings.system_bg_fg = (bg_color << 4) | current_fg;
}

void set_system_fg(uint8_t fg_color) {
    uint8_t current_bg = settings.system_bg_fg & 0xF0; 
    settings.system_bg_fg = current_bg | (fg_color & 0x0F);
}

void set_user_bg(uint8_t bg_color) {
    uint8_t current_fg = settings.user_bg_fg & 0x0F;
    settings.user_bg_fg = (bg_color << 4) | current_fg;
}

void set_user_fg(uint8_t fg_color) {
    uint8_t current_bg = settings.user_bg_fg & 0xF0;
    settings.user_bg_fg = current_bg | (fg_color & 0x0F);
}

void set_main_bg(uint8_t bg_color) {
    uint8_t current_fg = settings.main_bg_fg & 0x0F;
    settings.main_bg_fg = (bg_color << 4) | current_fg;
}


void history_add(char * command) {
    if(command[0]=='\0')
        return;

    if(history.count >= HISTORY_SIZE){
        for(int i=0;i<HISTORY_SIZE-1;i++) {
            strcpy(history.lines[i],history.lines[i+1]);
        }
    } else  
        history.count++;

    strcpy(history.lines[history.count-1], command);

    history.view_index = history.count;
}

void load_history_to_buffer() {
    clear_current_line(settings.main_bg_fg);
    char *command = history.lines[history.view_index];
    key_buffer[0] = ':';
    strcpy(key_buffer + 1, command);
    buffer_index = strlen(command) + 1;

    print_string(key_buffer, settings.user_bg_fg);
}