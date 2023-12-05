#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


char *  get_next_line(int fd)
{
    ssize_t rtr;
    char rtr_buf[11]; 

    rtr = read(fd, rtr_buf, 9);
    rtr_buf[11] = '\0';

    printf("%ld\n", rtr);
    printf("%s\n", rtr_buf);

    return("lol");
}


int main ()
{
    unsigned int fd;

    fd = open("./lol.txt", O_RDONLY);

    get_next_line(fd);

    printf("%d\n", fd);

    close(fd);
}