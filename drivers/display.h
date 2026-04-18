#ifndef DISPLAY_H
#define DISPLAY_H

const int MAX_HEIGHT = 80;
const int MAX_WIDTH = 25;

int get_row_from_offset(int offset) {
    return offset / (2 * MAX_HEIGHT);
}

int get_offset(int col, int row) {
    return 2 * (row * MAX_HEIGHT + col);
}

int move_offset_to_new_line(int offset) {
    return get_offset(0, get_row_from_offset(offset) + 1);
}

void set_char_at_location(char character, int offset) {
    char* video = (char*) 0xB8000; // 0xB8000 = VGA text buffer

    video[offset] = character;
    video[offset + 1] = 0x07;
}

void clear_screen() {
    for (int i = 0; i < MAX_HEIGHT * MAX_WIDTH * 2; i++) {
        set_char_at_location(' ', i * 2);
    }
}

void print(const char* string) {
    int i = 0;
    int offset = 0;

    // VGA Text Structure: [character][colour][character][colour]
    while (string[i] != '\0') {
        char character = string[i];
        if (character == '\n') {
            offset = move_offset_to_new_line(offset);
        } else {
            set_char_at_location(character, offset);
            offset += 2;
        }

        i++;
    }
}

#endif