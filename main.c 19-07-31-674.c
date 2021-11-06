#include "get_next_line_bonus.h"
 #include "get_next_line_bonus.c"
 #include "get_next_line_utils_bonus.c"
# include <stdio.h>
 

int main ()
{
        int fd ;
       // fd = open ("./file.txt" , O_RDONLY);
       fd = open ("./gnlTester/files/41_with_nl" , O_RDONLY);
//      i = read(fd,buf,1);
//      printf("%s",buf);
	printf("%s",get_next_line(fd));
        printf("%s",get_next_line(fd));

        printf("%s",get_next_line(fd));
        printf("%s",get_next_line(fd));
         // printf("after this\n");
        printf("%s",get_next_line(fd));
        return (0);
}
