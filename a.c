#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main() {
    printf("%s\n",getcwd(NULL,0));
    return 0;
}
