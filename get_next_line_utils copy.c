#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	char	*ptr;

	printf("firs :%s\nsecond:%s\n" , s1,s2);
	if (!s1 && !s2)
		return (NULL);
	newstr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (newstr == NULL)
		return (NULL);
	ptr = newstr;
	while (*s1)
	{
		*newstr = *s1;
		s1++;
		newstr++;
	}

	printf("joined_line:%s" , newstr);
	while (*s2)
	{
		*newstr = *s2;
		s2++;
		newstr++;
	}
	*newstr = '\0';
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s != NULL && s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	size_t i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == (char)c)
			return ((char *)str + i);
		i++;
	}
	if (c == '\0')
		return ((char *)str + i);
	return (0);
	
}
