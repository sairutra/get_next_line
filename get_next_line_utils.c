/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/03 10:43:41 by spenning      #+#    #+#                 */
/*   Updated: 2024/01/09 14:33:23 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	index;

	index = 0;
	if (!s)
		return (0);
	if (s[index] == '\0')
	{
		return (0);
	}
	else
	{
		while (s[index] != '\0')
		{
			index++;
		}
		return (index);
	}
}

char	*strjoin(char const *s1, char const *s2)
{
	size_t	index;
	size_t	len_s1;
	size_t	len_s2;
	char	*ns_cptr;

	if (!s1 && !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	ns_cptr = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (ns_cptr == NULL)
		return (NULL);
	index = -1;
	if (s1)
	{
		while (s1[++index])
			ns_cptr[index] = s1[index];
	}
	index = -1;
	while (s2[++index])
		ns_cptr[len_s1++] = s2[index];
	ns_cptr[len_s1] = '\0';
	return (ns_cptr);
}

int	free_all(char **buffer, int ret)
{
	free(*buffer);
	*buffer = NULL;
	return (ret);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s_cptr;
	char	*ns_cptr;
	size_t	index;

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
