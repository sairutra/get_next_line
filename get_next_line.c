/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mynodeus <mynodeus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 23:44:00 by mynodeus          #+#    #+#             */
/*   Updated: 2024/01/06 14:27:45 by mynodeus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int check_nextline(char *stat_buf)
{
    int index;
    index=0;
    while(stat_buf[index] != '\0')
    {
        if (stat_buf[index] == '\n')
        {
			index++;
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
	*stat_buf = ft_substr(*stat_buf, gnl, stat_buf_len - gnl);
	if(*stat_buf == NULL)
	{
		free(temp);
		return(NULL);
	}
	if(temp)
	{
		free(temp);
		temp = NULL;
	}
	return(*stat_buf);
}

int read_buffer(int fd, char** stat_buf)
{
    ssize_t rtr;
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
			return(free_all(&read_buf, 0));
        read_buf[rtr] = '\0';
		temp = *stat_buf;
		*stat_buf = strjoin(*stat_buf, read_buf);
		free_all(&temp, 1);
		if(*stat_buf == NULL)
			return(free_all(&read_buf, 0));
		if(check_nextline(read_buf) < BUFFER_SIZE || read_buf[BUFFER_SIZE - 1] == '\n')
			return(free_all(&read_buf, 1));
    }
	return(free_all(&read_buf, 1));
}

char * return_str(char **stat_buf, size_t gnl)
{
	char * ret;
	size_t 	strlcpy_int;

	if(gnl == 0 && !*stat_buf)
		return(NULL);
	gnl += 1;
	ret = malloc(gnl);
	if(ret == NULL)
	{
		free_all(stat_buf, 1);
		free_all(&ret, 1);
		return(NULL);
	}
	strlcpy_int = ft_strlcpy(ret, *stat_buf, gnl);
	if(strlcpy_int == 0)
	{
		free_all(stat_buf, 1);
		free_all(&ret, 1);
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
			free_all(&stat_buf, 1);
		return(0);
	}
	stat_buf_len = ft_strlen(stat_buf);
	gnl = check_nextline(stat_buf);
	ret = return_str(&stat_buf, gnl);
	if(gnl < stat_buf_len && ret != NULL)
		realloc_statbuf(&stat_buf, gnl, stat_buf_len);
	if(stat_buf == NULL && ret)
	{
		free_all(&ret, 1);
		return(NULL);
	}
	if(stat_buf && gnl == stat_buf_len)
		free_all(&stat_buf, 1);
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
	
// 	char c;
// 	read(fd, &c, 1);
// 	printf("ret: %c\n", c);

// 	test = get_next_line(fd);
// 	printf("return: \n%s\n", test);
// 	free(test);
// 	// test = get_next_line(fd);
// 	// printf("return: \n%s\n", test);
// 	// free(test);
// 	// test = get_next_line(fd);
// 	// printf("return: \n%s\n", test);
// 	// free(test);
// 	// test = get_next_line(fd);
// 	// printf("return: \n%s\n", test);
// 	// free(test);

// 	// test = get_next_line(fd);
// 	// printf("return: \n%s\n", test);
// 	// free(test);

//     close(fd);
// }




