export module getch;

import <iostream>;

struct raw_termios {
    unsigned int c_iflag;
    unsigned int c_oflag;
    unsigned int c_cflag;
    unsigned int c_lflag;
    unsigned char c_line;
    unsigned char c_cc[32];
    unsigned int c_ispeed;
    unsigned int c_ospeed;
};

#define KERNEL_TCGETS 0x5401
#define KERNEL_TCSETS 0x5402

#define KERNEL_ICANON 0000002
#define KERNEL_ECHO   0000010

export int getch() {
    struct raw_termios oldt, newt;
    unsigned char ch = 0;
    long sys_return;

    __asm__ volatile (
        "movq $16, %%rax\n\t"
        "movq $0, %%rdi\n\t"
        "movq %0, %%rsi\n\t"
        "leaq %1, %%rdx\n\t"
        "syscall\n\t"
        :
        : "i"(KERNEL_TCGETS), "m"(oldt)
        : "rax", "rdi", "rsi", "rdx", "rcx", "r11", "memory"
    );

    newt = oldt;
    newt.c_lflag &= ~(KERNEL_ICANON | KERNEL_ECHO);

    __asm__ volatile (
        "movq $16, %%rax\n\t"
        "movq $0, %%rdi\n\t"
        "movq %0, %%rsi\n\t"
        "leaq %1, %%rdx\n\t"
        "syscall\n\t"
        :
        : "i"(KERNEL_TCSETS), "m"(newt)
        : "rax", "rdi", "rsi", "rdx", "rcx", "r11", "memory"
    );

    __asm__ volatile (
        "movq $0, %%rax\n\t"
        "movq $0, %%rdi\n\t"
        "leaq %1, %%rsi\n\t"
        "movq $1, %%rdx\n\t"
        "syscall\n\t"
        : "=a"(sys_return)
        : "m"(ch)
        : "rcx", "r11", "memory"
    );

    __asm__ volatile (
        "movq $16, %%rax\n\t"
        "movq $0, %%rdi\n\t"
        "movq %0, %%rsi\n\t"
        "leaq %1, %%rdx\n\t"
        "syscall\n\t"
        :
        : "i"(KERNEL_TCSETS), "m"(oldt)
        : "rax", "rdi", "rsi", "rdx", "rcx", "r11", "memory"
    );

    return (sys_return == 1) ? static_cast<int>(ch) : -1;
}