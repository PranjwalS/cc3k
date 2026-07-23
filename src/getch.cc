export module getch;

import <iostream>;

// Replicating the minimal termios structure memory layout required by the Linux kernel
struct raw_termios {
    unsigned int c_iflag;     // input mode flags
    unsigned int c_oflag;     // output mode flags
    unsigned int c_cflag;     // control mode flags
    unsigned int c_lflag;     // local mode flags (This is the one we need)
    unsigned char c_line;     // line discipline
    unsigned char c_cc[32];   // control characters
    unsigned int c_ispeed;    // input speed
    unsigned int c_ospeed;    // output speed
};

// Linux kernel ioctl command numbers for terminal attributes (x86_64 specific)
#define KERNEL_TCGETS 0x5401
#define KERNEL_TCSETS 0x5402

// Bitmasks for disabling canonical mode and local echo
#define KERNEL_ICANON 0000002
#define KERNEL_ECHO   0000010

export char getch() {
    struct raw_termios oldt, newt;
    unsigned char ch = 0;
    long sys_return;

    // 1. Get terminal attributes using ioctl (sys_ioctl is call #16 on x86_64)
    // Arguments: rax=16, rdi=0 (stdin), rsi=KERNEL_TCGETS, rdx=&oldt
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

    // 2. Modify local flags to disable canonical mode and echo
    newt = oldt;
    newt.c_lflag &= ~(KERNEL_ICANON | KERNEL_ECHO);

    // 3. Set terminal attributes using ioctl (KERNEL_TCSETS)
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

    // 4. Read a single byte from stdin (sys_read is call #0)
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

    // 5. Restore original terminal settings so the terminal isn't broken on exit
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

    return ch;
}

export std::string szxcToDir(std::string c) {
    if (c == "s") {
        return "no";
    } else if (c == "z") {
        return "we";
    } else if (c == "x") {
        return "so";
    } else if (c == "c") {
        return "ea";
    } else { return ""; }
}