#include "get_next_line.h"


static int check_nextline(char *rtr_buf, ssize_t buf_size)
{
    int index;

    index=0;
    while(index < buf_size || rtr_buf[index] != '\0')
    {
        if (rtr_buf[index] == '\n')
        {
            printf("found\n");
            // strjoin op static variable
            return(0);
        }
        index++;
    }
    // strjoin op static variable
    return(1);
}

static int read_buffer(int fd, char ** stat_buf)
{
	int test;
    ssize_t rtr;
	char rtr_buf[BUFFER_SIZE + 1];

    rtr = 0;
    test = 0;
    while(check_nextline(rtr_buf, rtr))
    {
        rtr = read(fd, rtr_buf, BUFFER_SIZE);
        if (rtr == -1)
            return(0);
        if (rtr < BUFFER_SIZE)
            rtr_buf[rtr] = '\0';
        else
            rtr_buf[BUFFER_SIZE] = '\0';
        test++;
    }
    printf("loop: %d\n", test);
	return(1);
}

char *  get_next_line(int fd)
{
    static char * stat_buf;

    stat_buf = NULL;
    // char * read_buf;
    // char * rtr_buf;

    // if(*stat_buf == '\0')
    // {
    read_buffer(fd, &stat_buf);
        // if (read_buf == NULL)
        //     return(NULL);
        // parse_buffer(read_buf, stat_buf, BUFFER_SIZE);
    // }
    // else
    // {
    //     parse_buffer(stat_buf, stat_buf, BUFFER_SIZE);
    // }
    return("lol");
}


int main ()
{
    unsigned int fd;

    fd = open("./test.txt", O_RDONLY);

    get_next_line(fd);

    close(fd);
}




