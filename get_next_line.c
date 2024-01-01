#include "get_next_line.h"
#include <string.h>

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
	if(ns_vptr == NULL)
		return (NULL);
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


int check_nextline(char *stat_buf)
{
    int index;
    index=0;
    while(stat_buf[index] != '\0')
    {
		// printf("check_nl: %c\n", stat_buf[index]);
        if (stat_buf[index] == '\n')
        {
            return(index);
        }
    	index++;
    }
    return(index);
}

char * realloc_statbuf(char **stat_buf, size_t gnl, size_t stat_buf_len)
{
	char * temp;

	temp = *stat_buf;
	*stat_buf = ft_substr(*stat_buf, gnl + 1, stat_buf_len - gnl);
	if(temp)
	{
		free(temp);
		temp = NULL;
	}	
	return(*stat_buf);
}

int read_buffer(int fd, char** stat_buf)
{
    static ssize_t rtr;
	char *read_buf;
	char * temp;

	read_buf = malloc((BUFFER_SIZE + 1));
	if(read_buf == NULL)
		return (0);

    rtr = -1;
    while(rtr != 0)
    {
		rtr = read(fd, read_buf, BUFFER_SIZE);
        if (rtr == -1)
		{
		    free(read_buf);
			read_buf = NULL;
			return(0);
		}
		if (rtr < BUFFER_SIZE)
            read_buf[rtr] = '\0';
        else
            read_buf[BUFFER_SIZE] = '\0';
		// printf("read buffer stat_buf: %s\n", *stat_buf);
		if(!*stat_buf && rtr == 0)
		{
			free(read_buf);
			read_buf = NULL;
			return(0);
		}
		if(!*stat_buf)
			*stat_buf = ft_strdup("");
		temp = *stat_buf;
		*stat_buf = strjoin(*stat_buf, read_buf);
		free(temp);
		temp = NULL;
		if(check_nextline(read_buf) < BUFFER_SIZE)
		{
			free(read_buf);
			read_buf = NULL;
			return(1);
		}
    }
	free(read_buf);
	read_buf = NULL;
	return(1);
}

char * return_str(char **stat_buf, size_t gnl)
{
	char * ret;
	size_t 	strlcpy_int;
	if(gnl == 0 && !*stat_buf)
		return(NULL);
	if(gnl == 1)
		gnl += 1;
	else
		gnl += 2;
	ret = malloc(gnl);
	if(ret == NULL)
		return(NULL);
	strlcpy_int = ft_strlcpy(ret, *stat_buf, gnl);
	if(strlcpy_int == 0)
	{
		free(ret);
		ret = NULL;
		return(NULL);
	}
	return(ret);
}

char *  get_next_line(int fd)
{
    static char 	*stat_buf;
	char 			*ret;
	size_t			gnl;
	size_t			stat_buf_len;

	if(BUFFER_SIZE == 0)
		return(NULL);
	if(read_buffer(fd, &stat_buf) == 0)
	{
		if(stat_buf)
		{
			free(stat_buf);
			stat_buf = NULL;
		}
		return(NULL);
	}
	stat_buf_len = ft_strlen(stat_buf);
	gnl = check_nextline(stat_buf);
	// printf("stat_buf_len= %ld\ngnl= %ld\n", stat_buf_len, gnl);
	// printf("stat_buf= %s\n", stat_buf);
	ret = return_str(&stat_buf, gnl);
	// printf("ret= %d\n", ret[0]);
	if(gnl < stat_buf_len && ret != NULL)
		realloc_statbuf(&stat_buf, gnl, stat_buf_len);
	if(gnl == stat_buf_len)
	{	
		// printf("stat_buf: %s\n", stat_buf);
		if(stat_buf)
		{
			free(stat_buf);
			stat_buf = NULL;
		}
		// printf("stat_buf: %s\n", stat_buf);
	}
	return(ret);
}


// int main ()
// {
//     unsigned int fd;
// 	char *test;
//     fd = open("./test.txt", O_RDWR);

// 	test = get_next_line(fd);
// 	printf("return: \n%s\n", test);
// 	free(test); 
// 	// test = get_next_line(fd);
// 	// printf("return: \n%s\n", test);
// 	// free(test);

//     // close(fd);

// 	// fd = open("./test.txt", O_RDWR);

// 	test = get_next_line(fd);
// 	printf("return: \n%s\n", test);
// 	free(test); 
// 	test = get_next_line(fd);
// 	printf("return: \n%s\n", test);
// 	free(test); 
// 	test = get_next_line(fd);
// 	printf("return: \n%s\n", test);
// 	free(test); 
// 	test = get_next_line(fd);
// 	printf("return: \n%s\n", test);
// 	free(test); 
	
// 	// test = get_next_line(fd);
// 	// printf("return: \n%s\n", test);
// 	// free(test);

//     close(fd); 
// }




