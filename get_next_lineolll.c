#include "get_next_line.h"

void free_memmory(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

char *allocate_memmory(size_t size)
{
	char *memmory;
	
	memmory = (char *)malloc(sizeof(char) * size );
	if(memmory == NULL)
	{
		free_memmory(&memmory);
		return (NULL);
	}
	return (memmory);
}

static char *ft_strjoin2(char *str1, char *str2)
{
	char *new_string;
	size_t total_len;
	size_t i;
	size_t j;
	
	total_len = ft_strlen(str1) + ft_strlen(str2);
	i = 0;
	j = 0;
	new_string = (char *)malloc(sizeof(char) * total_len + 1);
	if(new_string == NULL)
	{
		free_memmory(&new_string);
		return(NULL);
	}
	
	while(str1 && str1[i]) 
	{
		new_string[i++] = str1[j++];
	}
	j = 0;
	while (str2[j])
	{
		new_string[i++] = str2[j++];
	}
	new_string[i] = '\0';
	return (new_string);
}

char *get_untill_new_line(char *saved_line,char *line)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while(saved_line[j] && saved_line[j] != '\n')
	{
		line[i] = saved_line[j];
		j++;
		i++;	
	}
	if(line[i] == '\n')
		line[i] = '\n';
	line[i++] = '\0';	
	return (line);
}

unsigned int get_line_size(char *saved_line)
{
	size_t i;

	i = 0;
	while(saved_line[i] && saved_line[i] != '\n')
	{
		i++;
	}
	if(saved_line[i] == '\n')
		i++;
	return (i);
}

static char *get_save_line(char *saved_line,size_t line_len)
{
	char *new_string;
	size_t len;
	
	len = ft_strlen(saved_line + line_len);
	new_string = allocate_memmory(len + 1);
	if(!new_string)
	{
		free_memmory(&new_string);
		return(NULL);
	}
	len = 0;	
	while(saved_line[line_len])
	{
		new_string[len]=saved_line[line_len];
		len++;
		line_len++;		
	}
	new_string[len] ='\0';
	free_memmory(&saved_line);
	saved_line = new_string;
	return(saved_line);		
}

static char *get_line(char *saved_line)
{
	char *line;
	size_t j;
	
	j = 0;
	line = allocate_memmory(get_line_size(saved_line) + 1);
	if(!line)
	{
		free_memmory(&line);
		return (NULL);
	}
	line = get_untill_new_line(saved_line,line);
	saved_line = get_save_line(saved_line,get_line_size(saved_line));
	return (line);	
}

static char *get_next_line2(char *saved_line,char *buffer,int read_value,int fd)
{
	char *ptr;

	while(read_value > 0 && !ft_strchr(saved_line,'\n'))
	{	
		read_value = read(fd,buffer,BUFFER_SIZE);
		if(read_value > 0)
		{
			buffer[read_value] = '\0';
			ptr = saved_line;
			saved_line = ft_strjoin2(saved_line,buffer);
			free_memmory(&ptr);
		}
	}
	if(read_value <= 0)
	{
		if(ft_strlen(saved_line) > 0)
		{
			free_memmory(&buffer);
			return(get_line(saved_line));
		}
		free_memmory(&buffer);
		free_memmory(&saved_line);
		return (NULL);
	}
	return(get_line(saved_line));
}

char *get_next_line(int fd)
{
	static char *saved_line;
	int read_value;
	char *buffer;

	if (fd < 0 || fd >= 255|| BUFFER_SIZE <= 0)
		return (0);
	buffer = (char *) malloc(sizeof(char) * BUFFER_SIZE + 1);
	if(buffer == NULL)
	{ 
		free_memmory(&buffer);
		return (NULL);
	}
	if(saved_line == NULL || !saved_line)
	{
		saved_line = (char *)malloc(sizeof(char) * 1);
		if(saved_line == NULL)
		{
			free_memmory(&saved_line);
			return(NULL);
		}
		saved_line[0] = '\0';
	}
	read_value = 1;
	return (get_next_line2(saved_line,buffer,read_value,fd));
}
