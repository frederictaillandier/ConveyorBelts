#include <term.h>
#include <unistd.h>
#include <cstdio>

#include "utils/my-getch.h"

char my_getch() {
    char buf = 0;
    struct termios shell_tmodes;
    if (tcgetattr(0, &shell_tmodes) < 0)
        perror("tcsetattr()");
    shell_tmodes.c_lflag &= ~ICANON;
    shell_tmodes.c_lflag &= ~ECHO;
    shell_tmodes.c_cc[VMIN] = 1;
    shell_tmodes.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &shell_tmodes) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror ("read()");
    shell_tmodes.c_lflag |= ICANON;
    shell_tmodes.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &shell_tmodes) < 0)
        perror ("tcsetattr ~ICANON");
    return buf;
}