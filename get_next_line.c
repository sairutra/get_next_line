#include "get_next_line.h"


char *  get_next_line(int fd)
{
    static char *stat_buf; 
    char * read_buf;
    char * rtr_buf;

    if(*stat_buf == '\0')
    {
        read_buf = read_buffer(BUFFER_SIZE, fd);
        if (read_buf == NULL)
            return(NULL);
        parse_buffer(read_buf, stat_buf, BUFFER_SIZE);
    }
    else
    {
        parse_buffer(stat_buf, stat_buf, BUFFER_SIZE);
    }
    return("lol");
}


int main ()
{
    unsigned int fd;

    fd = open("./test.txt", O_RDONLY);

    get_next_line(fd);

    printf("%d\n", fd);

    close(fd);
}




