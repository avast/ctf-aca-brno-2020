#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int check = 0x00000000;
    char buffer[10];

    printf("   IN: ");
    fgets(buffer, 15, stdin);
    printf("  OUT: %s\n", buffer);
    
    if(check == 0x1337beef)
    {
        setuid(geteuid());
        system("vim");
    }
    else printf("CHECK: %08x != 1337beef\n", check);
}
