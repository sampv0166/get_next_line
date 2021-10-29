#include "get_next_line.h"
#include "get_next_line.c"
#include "get_next_line_utils.c"

int main ()
{
        int fd ;
        fd = open ("./gnlTester/files/nl" , O_RDONLY);
//      i = read(fd,buf,1);
//      printf("%s",buf);
        get_next_line(fd);	
        get_next_line(fd);
	//printf("%s",get_next(fd));
        return (0);
}	char buffer[BUFFER_SIZE + 1];
