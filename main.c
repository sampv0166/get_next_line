#include "get_next_line.h"
 #include "get_next_line.c"
 #include "get_next_line_utils.c"

int main ()
{
        int fd ;
        fd = open ("./gnlTester/files/42_no_nl" , O_RDONLY);
//      i = read(fd,buf,1);
//      printf("%s",buf);
	printf("%s",get_next_line(fd));
        printf("%s",get_next_line(fd));

          printf("%s",get_next_line(fd));
       // printf("%s",get_next_line(fd));

        return (0);
}
