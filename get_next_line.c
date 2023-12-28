#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	char	*s_cptr;
	size_t	s_len;
	void	*ns_vptr;
	char	*ns_cptr;
	size_t	index;

	s_cptr = (char *)s;
	s_len = ft_strlen(s_cptr);
	ns_vptr = malloc(s_len + 1);
	ns_cptr = (char *)ns_vptr;
	if (!ns_cptr)
		return (NULL);
	index = 0;
	while (s_cptr[index] != '\0')
	{
		ns_cptr[index] = s_cptr[index];
		index++;
	}
	ns_cptr[index] = '\0';
	return (ns_cptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s_cptr;
	char	*ns_cptr;
	size_t	index;

	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	ns_cptr = (char *)malloc(len + 1);
	if (ns_cptr == NULL)
		return (NULL);
	s_cptr = (char *)s;
	index = 0;
	while (index < len && s_cptr[start] != '\0')
	{
		ns_cptr[index] = s_cptr[start];
		start++;
		index++;
	}
	ns_cptr[index] = '\0';
	return (ns_cptr);
}



void	ft_bzero(void *s, size_t n)
{
	long unsigned int	index;
	char				*cptr;

	index = 0;
	cptr = (char *)s;
	while (index < n)
	{
		cptr[index] = '\0';
		index++;
	}
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t		srclen;
	size_t		index;

	srclen = ft_strlen(src);
	index = 0;
	if (size > 0)
	{
		while (index < (size -1) && src[index])
		{
			dst[index] = src[index];
			index ++;
		}
		dst[index] = '\0';
	}
	return (srclen);
}

int check_nextline(char *rtr_buf, ssize_t buf_size)
{
    int index;
    index=0;
    while(index < buf_size || rtr_buf[index] != '\0')
    {
		printf("%c\n", rtr_buf[index]);
        if (rtr_buf[index] == '\n')
        {
            // printf("found\n");
            return(index);
        }
		if(rtr_buf[index] == '\0')
			return(-1);
        index++;
    }
    return(-1);
}

int read_buffer(int fd, char **stat_buf)
{
	// int test;
    ssize_t rtr;
	char rtr_buf[BUFFER_SIZE + 1];
	char *temp;

    rtr = 1;
    // test = 0;
    while((check_nextline(rtr_buf, rtr) == -1) && (rtr != 0))
    {
		rtr = read(fd, rtr_buf, BUFFER_SIZE);
		printf("%ld\n",rtr);
        if (rtr == -1)
            return(0);
        if (rtr < BUFFER_SIZE)
            rtr_buf[rtr] = '\0';
        else
            rtr_buf[BUFFER_SIZE] = '\0';
		temp = *stat_buf;
        *stat_buf = strjoin(*stat_buf, rtr_buf);
		free(temp);
		printf("read_buffer statbuf: %s\n", *stat_buf);
		if (rtr == 0)
			return (0);
        // test++;
    }
    // printf("loop: %d\n", test);
	return(1);
}

char *  get_next_line(int fd)
{
    static char 	*stat_buf;
    char 			*ret_str;
	char 			*temp;
	size_t			cnl;

	if(fd == 0 || BUFFER_SIZE == 0)
		return(NULL);
    if(!stat_buf)
		stat_buf = ft_strdup("");
	// printf("start statbuf: %s\n", stat_buf);
	if (read_buffer(fd, &stat_buf) == 0)	
		return(NULL);
	// printf("%s", stat_buf);
	cnl = check_nextline(stat_buf, BUFFER_SIZE) + 1;
    printf("cnl: %ld\n", cnl);
    ret_str = malloc(cnl + 1);
    if(ret_str == NULL)
        return(NULL);
    ft_strlcpy(ret_str, stat_buf, cnl + 1);
	temp = stat_buf;
	printf("%ld\n%ld\n", cnl, ft_strlen(stat_buf));
	stat_buf = ft_substr(stat_buf, cnl, cnl);
	free(temp);
	// ft_bzero(stat_buf, cnl);
    // printf("stat_buf pre cnl: %s\n", stat_buf);
	// stat_buf += cnl;
    // printf("stat_buf aft cnl: %s\n", stat_buf);
    printf("stat_buf: %s\n", stat_buf);
    printf("ret_str: %s\n", ret_str);
    return(ret_str);
}


int main ()
{
    unsigned int fd;
	char *test;
    fd = open("./test.txt", O_RDONLY);

	test = get_next_line(fd);
	printf("%s", test);
	test = get_next_line(fd);
	printf("%s", test);
	free(test); 

    close(fd);
}




