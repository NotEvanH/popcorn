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

void print(const char* string) {
    char* video = (char*) 0xB8000; // 0xB8000 = VGA text buffer

    int i = 0;
    int offset = 0;

    // VGA Text Structure: [character][colour][character][colour]
    while (string[i] != '\0') {
        char character = string[i];
        if (character == '\n') {
            offset = move_offset_to_new_line(offset);
        } else {
            video[offset] = character;
            video[offset + 1] = 0x07;
            offset += 2;
        }

        i++;
    }
}

void kernel_main() {
    print("Hello,\nWorld!");
}