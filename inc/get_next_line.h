/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/21 23:03:23 by spenning      #+#    #+#                 */
/*   Updated: 2024/01/21 17:51:33 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>

// This function takes a fd and returns a char * with next line from fd. If function fails it returns NULL
char	*get_next_line(int fd);
// This function reads the buffer from fd until \n is found or EOF
// and puts it in stat_buf
int		read_buffer(int fd, char **stat_buf);
// This function returns the length to the next \n or EOF
int		check_nextline(char *stat_buf);
// This function takes the string to return out of stat_buf
char	*return_str(char **stat_buf, size_t gnl);
// This function takes out the string that is going to be returned a give pointer back to memory location
// just after the return string
char	*realloc_statbuf(char	**stat_buf, size_t gnl, size_t stat_buf_len);
// This function takes s1 and s2 and joins them together.
// if join fails or if malloc fails then function returns NULL.
char	*strjoin(char const *s1, char const *s2);
// This function takes pointer char *s, and expects a null terminated string.
// then returns the length of the string.
size_t	gnl_strlen(const char *s);
// This function takes a pointer to s and creates a substring with len length starting from  
// start index. if start is longer than length of s, then function will return empty string. If the
// length is bigger than length of s starting from index start, then len will be adjusted to length of
// s starting from index start. This function returns a char * to allocated substring, 
//if allocations failed it will return NULL.
char	*gnl_substr(char const *s, unsigned int start, size_t len);
// This function copy size bytes from src to dst, function always returns the length of src. 
// Function will keep on copying until it reaches size - 1, and there are still charachters to copy
// from src. Afterwards it null terminates the result.
size_t	gnl_strlcpy(char *dst, const char *src, size_t size);
// function frees buffer given and gives ret back as return value
int		free_all(char **buffer, int ret);

#endif
