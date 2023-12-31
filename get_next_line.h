/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mynodeus <mynodeus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 23:03:23 by spenning          #+#    #+#             */
/*   Updated: 2023/12/30 23:49:24 by mynodeus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// These are header guards that prevent the double definitions in the 
// source file. This prevents library dependency from double copying
// libraries. if libft is already defined if won't define it again.
// name is LIBFT_H because the name should be the full filename of the 
// header file, in all caps, with underscores for spaces and ​punctuation.


#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
    #define BUFFER_SIZE 10
// #elif BUFFER_SIZE == 1000000
//     #undef BUFFER_SIZE
//     #define BUFFER_SIZE 999998
#endif

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


char *  get_next_line(int fd);
int read_buffer(int fd, char** stat_buf);
int check_nextline(char *stat_buf);
char	*strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
// static char * memmove(char *rtr);
// static int read_stat(char *stat_buf);
// char * parse_buffer(char * buff, char * stat_buff, unsigned int SIZE);
// size_t lenstr(char * buff);
// void alloc_stat(size_t index, size_t len, char *stat_buff, char *buff, unsigned int SIZE);



#endif