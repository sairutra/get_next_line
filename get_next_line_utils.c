#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	index;

	index = 0;
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

	if (s1 && s2)
	{
		len_s1 = ft_strlen(s1);
		len_s2 = ft_strlen(s2);
		ns_cptr = (char*)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
		if (ns_cptr == NULL)
			return (NULL);
		index = -1;
		while (s1[++index])
			ns_cptr[index] = s1[index];
		index = -1;
		while (s2[++index])
		{
			ns_cptr[len_s1] = s2[index];
			len_s1++;
		}
		ns_cptr[len_s1] = '\0';
		return (ns_cptr);
	}
	return(NULL);
}