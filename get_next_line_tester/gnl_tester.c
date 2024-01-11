#include <stdio.h>
#include <fcntl.h>
#include "gnl_tester.h"
#include "../get_next_line.h" 

#define RED   "\x1B[31m"
#define GRN   "\x1B[1;32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define BMAG   "\x1B[1;35m"
#define CYN   "\x1B[36m"
#define BCYN   "\x1B[1;36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"


static size_t	test_strlen(const char *s)
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

static int	test_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;
	size_t	s1_len;
	size_t	s2_len;
	int		returnval;

	index = 0;
	returnval = 0;
	s1_len = test_strlen(s1);
	s2_len = test_strlen(s2);
	while (index < n && (index < s1_len || index < s2_len))
	{
		if ((unsigned char)s1[index] != (unsigned char)s2[index])
			return ((unsigned char)s1[index] - (unsigned char)s2[index]);
		index++;
	}
	return (returnval);
}


int tester (const int fd, char *str, int testnbr, int linenbr)
{
	int 	rtr;
	char 	*gnl;
	int		error_index;
	FILE 	*errorLog;

	error_index = 0; 
	rtr = 0;
	gnl = get_next_line(fd);
	if(str && gnl)
	{
		if(test_strlen(gnl) > test_strlen(str))
			rtr += test_strncmp(str, gnl, test_strlen(gnl));
		else
			rtr += test_strncmp(str, gnl, test_strlen(str));
	}
	if (rtr != 0 || (gnl && !str) || (!gnl && str))
	{
		errorLog = fopen("logs/error_log.txt", "a");

		if (errorLog == NULL)
    	{
			free(gnl);
        	printf("Error opening the file");
        	return 1;
    	}
		printf(RED "%d " RESET, testnbr);
		printf(RED "FAIL " RESET);
		printf(RED "Check error_log.txt\n" RESET);
		fprintf(errorLog, "----------------\n");
		fprintf(errorLog, "Test number %d\n", testnbr);
		fprintf(errorLog, "Line %d\n", linenbr);
		if(str)
		{
			while (str[error_index] != '\0')
				fprintf(errorLog, "expected output: %d\n", str[error_index++]);
		}
		error_index = 0;
		fprintf(errorLog, "expected output: %s\n", str);
		if(gnl)
		{
			while (gnl[error_index]!= '\0')
				fprintf(errorLog, "gnl output: %d\n", gnl[error_index++]);
		}
		fprintf(errorLog, "gnl output: %s\n", gnl);
		fprintf(errorLog, "strncmp difference: %d\n", rtr);
		fclose(errorLog);
		free(gnl);
		return(0);
	}
	printf(GRN "%d OK " RESET, testnbr );
	free(gnl);
	return(0);
}


void welcome_screen()
{
	printf(CYN "<==================================================================================>\n" RESET);
	printf(CYN "||                                                                                ||\n" RESET);
	printf(CYN "||    ||      |      ||  ||||||  ||     |||||   ||||||    |||| |||||   ||||||     ||\n" RESET);
	printf(CYN "||    ||     |||     ||  ||      ||    ||      ||    ||  ||   ||   ||  ||         ||\n" RESET);
	printf(CYN "||    ||    || ||    ||  ||||||  ||    ||      ||    ||  ||   ||   ||  ||||||     ||\n" RESET);
	printf(CYN "||     ||  ||   ||  ||   ||      ||    ||      ||    ||  ||   ||   ||  ||         ||\n" RESET);
	printf(CYN "||      ||||     ||||    ||||||  |||||  |||||   ||||||   ||   ||   ||  ||||||     ||\n" RESET);
	printf(CYN "||                                                                                ||\n" RESET);
	printf(CYN "<==================================================================================>\n" RESET);
	printf(CYN "+                                                                                  +\n" RESET);
	printf(CYN "+                             " RESET);
	printf(YEL "get_next_line" RESET);
	printf(CYN " tester" RESET);
	printf(CYN "                                 +\n" RESET);
	printf(CYN "+                                  by spenning                                     +\n" RESET);
	printf(CYN "+                                                                                  +\n" RESET);
	printf(CYN "<==================================================================================>\n" RESET);
}

int fail_print()
{
	printf(RED "Program crashed\n" RESET);
	return(0);
}

// redefine allocator functions
# define malloc(size) _malloc(size, __LINE__)
# define free(ptr) _free(ptr, __LINE__)


int main (void)
{
	int testnbr;
	int linenbr;
	int fd;
	fclose(fopen("logs/error_log.txt", "w"));
	welcome_screen();

	testnbr = 1;
	linenbr = 1;
	printf(BMAG "1char.txt:\n" RESET);
	fd = open("test_files/1char.txt", O_RDONLY);
	if(tester(fd, "1\n", testnbr, linenbr) == 1)
		return(fail_print());
	if(tester(fd, "1\n", ++testnbr, ++linenbr) == 1)
		return(fail_print());
	if(tester(fd, "1", ++testnbr, ++linenbr) == 1)
		return(fail_print());
	close(fd);
	printf("\n");
	
	testnbr = 1;
	linenbr = 1;
	printf(BMAG "empty.txt:\n" RESET);
	fd = open("test_files/empty.txt", O_RDONLY);
	if(tester(fd, NULL, testnbr, linenbr) == 1)
		return(fail_print());
	if(tester(fd, NULL, ++testnbr, ++linenbr) == 1)
		return(fail_print());
	if(tester(fd, NULL, ++testnbr, ++linenbr) == 1)
		return(fail_print());
	close(fd);
	printf("\n");

	print_report();

	return(1);
}
