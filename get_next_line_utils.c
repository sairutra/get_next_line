#include "get_next_line.h"

static int alloc_stat(size_t index, size_t len, char *stat_buff, char *buff, unsigned int SIZE)
{
	int stat_index;

	stat_buff = malloc(SIZE);
	if (stat_buff == NULL)
		return(0);
	while (index < len)
	{
		stat_buff[stat_index] = buff[index];
		stat_index;
		index++;
	}
	stat_buff[stat_index] = '\0';
	return (1);
}

static size_t lenstr(char * buff)
{	
	size_t len;

	len = 0;
	while (buff[len] != '\0')
	{
		len++;
	}
	return(len);
}

static char * memmove(char *rtr, int end, char *stat_buf)
{
	int index;

	index = 0;
	while (index < end)
	{
		rtr[index] = stat_buf[index];
		index++;
	}
	rtr[index + 1] = '\0';
	return(rtr);
}

char * parse_buffer(char * buff, char * stat_buff, unsigned int SIZE)
{
	int index;
	char *rtr;
	size_t len;

	index = 0;
	len = lenstr(buff);
	while(buff[index] != '\0')
	{
		if(buff[index] == '\n')
		{
			rtr = malloc(index + 1);
			if(rtr == NULL)
				return(NULL);
			rtr = memmove(rtr, index, buff);
			if(alloc_stat(index, len, stat_buff, buff, SIZE) == 0)
				return(0);
			return(rtr);
		}
		index++;
	}
	rtr = malloc(index + 1);
	if(rtr == NULL)
		return(NULL);
	rtr = memmove(rtr, index, buff);
	if(alloc_stat(index, len, stat_buff, buff, SIZE) == 0)
		return(0);
	return(rtr);
}

static char * read_buffer( int fd)
{
	ssize_t rtr;
	char *rtr_buf;
    rtr_buf = malloc(BUFFER_SIZE + 1);
    if (rtr_buf == NULL)
        return(NULL);
    rtr = read(fd, rtr_buf, BUFFER_SIZE);
    if (rtr == -1)
        return(NULL);
    if (rtr < BUFFER_SIZE)
		rtr_buf[rtr] = '\0';
	else
		rtr_buf[BUFFER_SIZE] = '\0';
	return(rtr_buf);
}
