/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 23:44:00 by mynodeus      #+#    #+#                 */
/*   Updated: 2024/01/09 14:42:23 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_nextline(char	*stat_buf)
{
	int	index;

	index = 0;
	while (stat_buf[index] != '\0')
	{
		if (stat_buf[index] == '\n')
		{
			index++;
			return (index);
		}
		index++;
	}
	return (index);
}

char	*realloc_statbuf(char	**stat_buf, size_t gnl, size_t stat_buf_len)
{
	char	*temp;

	temp = *stat_buf;
	*stat_buf = ft_substr(*stat_buf, gnl, stat_buf_len - gnl);
	if (*stat_buf == NULL)
	{
		free(temp);
		return (NULL);
	}
	if (temp)
	{
		free(temp);
		temp = NULL;
	}
	return (*stat_buf);
}

int	read_buffer(int fd, char **stat_buf)
{
	ssize_t	rtr;
	char	*buf;
	char	*temp;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (0);
	rtr = -1;
	while (rtr != 0)
	{
		rtr = read(fd, buf, BUFFER_SIZE);
		if (rtr == -1)
			return (free_all(&buf, 0));
		buf[rtr] = '\0';
		temp = *stat_buf;
		*stat_buf = strjoin(*stat_buf, buf);
		free_all(&temp, 1);
		if (*stat_buf == NULL)
			return (free_all(&buf, 0));
		if (check_nextline(buf) < BUFFER_SIZE || buf[BUFFER_SIZE - 1] == '\n')
			return (free_all(&buf, 1));
	}
	return (free_all(&buf, 1));
}

char	*return_str(char **stat_buf, size_t gnl)
{
	char	*ret;
	size_t	strlcpy_int;

	if (gnl == 0 && !*stat_buf)
		return (NULL);
	gnl += 1;
	ret = malloc(sizeof(char) * gnl);
	if (ret == NULL)
	{
		free_all(stat_buf, 1);
		free_all(&ret, 1);
		return (NULL);
	}
	strlcpy_int = ft_strlcpy(ret, *stat_buf, gnl);
	if (strlcpy_int == 0)
	{
		free_all(stat_buf, 1);
		free_all(&ret, 1);
		return (NULL);
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	static char		*stat_buf;
	char			*ret;
	size_t			gnl;
	size_t			stat_buf_len;

	if (read_buffer(fd, &stat_buf) == 0 || BUFFER_SIZE == 0)
	{
		if (stat_buf)
			free_all(&stat_buf, 1);
		return (NULL);
	}
	stat_buf_len = ft_strlen(stat_buf);
	gnl = check_nextline(stat_buf);
	ret = return_str(&stat_buf, gnl);
	if (gnl < stat_buf_len && ret != NULL)
		realloc_statbuf(&stat_buf, gnl, stat_buf_len);
	if (stat_buf == NULL && ret)
	{
		free_all(&ret, 1);
		return (NULL);
	}
	if (stat_buf && gnl == stat_buf_len)
		free_all(&stat_buf, 1);
	return (ret);
}
