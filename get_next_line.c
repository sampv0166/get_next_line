# include "get_next_line.h"
#include <string.h>

size_t *get_temp_line(size_t fd)
{	
	size_t i;
	char *temp_line;
	
	temp_line = malloc(sizeof(char) * 1);

	while(*t && i != 0) 
	{
		i = read(fd,temp_line,1);
	}
	return (i);
}

char *get_next_line(int fd)
{	
	size_t i;
	size_t j;
	char *current_line;

	static char *buffer;

	i = get_temp_line(fd);
	printf("%lu\n" ,i);
	current_line = malloc(sizeof(char) * i + 1);
	j = read(fd,current_line,i);
	printf("%c" ,*buffer);

	return (buffer);
}

int main ()
{
	int fd ;
	size_t i;
	char buf[1];

	fd = open ("./file.txt" , O_RDONLY); 
//	i = read(fd,buf,1);
//	printf("%s",buf);	
	get_next_line(fd);
	//printf("%s",get_next_line(fd));	
	return (0);
}

