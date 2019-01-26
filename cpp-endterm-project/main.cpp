
#include "xo/xo-events.h"
#include <stdio.h>
#define PORT 54000

int main(int argc, char const *argv[])
{
    printf("Starting Engin on port %d...", PORT);
    XOEvents::startEngin(PORT);
    return 0;
}
