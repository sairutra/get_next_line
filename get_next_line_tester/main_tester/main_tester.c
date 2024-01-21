#include <stdio.h>
#include <fcntl.h>
#include "../../get_next_line.h"

int main(void)
{
	char * test;
	int fd;
	int index;

	fd = open("main_text.txt", O_RDONLY);

	index = 0;
	test = get_next_line(fd);
	printf("String returned:\n");
	printf("%s\n", test);
	printf("Ascii returned:\n");
	while (test[index] != '\0')
		printf("%i\n", test[index++]);
	index = 0;
	free(test);

	close(fd);
	return(0);
}
