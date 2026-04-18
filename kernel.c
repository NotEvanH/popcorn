void print(const char* string) {
    char* video = (char*) 0xB8000; // 0xB8000 = VGA text buffer

    int i = 0;
    int offset = 0;

    // VGA Text Structure: [character][colour][character][colour]
    while (string[i] != '\0') {
        video[offset] = string[i];
        video[offset + 1] = 0x07;
        i++;
        offset += 2;
    }
}

void kernel_main() {
    print("Hello World!");
}