#include <stdio.h>
#include <fcntl.h>
#include "../get_next_line.h" 
#include "gnl_tester.h"

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

int fail_print()
{
	printf(RED "Program crashed\n" RESET);
	return(0);
}


int main (void)
{
	int testnbr;
	int linenbr;
	int fd;
	fclose(fopen("logs/error_log.txt", "w"));

	testnbr = 1;
	linenbr = 1;

	printf(BLU "\nBUFFER_SIZE = " RESET);
	printf(YEL "%d\n\n" RESET, BUFFER_SIZE);

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

	testnbr = 1;
	linenbr = 1;
	printf(BMAG "longline.txt:\n" RESET);
	fd = open("test_files/longline.txt", O_RDONLY);
	if(tester(fd, "hfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhj", testnbr, linenbr) == 1)
		return(fail_print());
	if(tester(fd, NULL, ++testnbr, ++linenbr) == 1)
		return(fail_print());
	if(tester(fd, NULL, ++testnbr, ++linenbr) == 1)
		return(fail_print());
	close(fd);
	printf("\n");

	testnbr = 1;
	linenbr = 1;
	printf(BMAG "longline_nl.txt:\n" RESET);
	fd = open("test_files/longline_nl.txt", O_RDONLY);
	if(tester(fd, "hfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhjhfisudhfkjdshfkjdshfkjhdsfkjhdskjfhdskjfndskjcdknckjwefu3hr9723yr7hkjcdsbcjbdsjcbshjbhj\n", testnbr, linenbr) == 1)
		return(fail_print());
	if(tester(fd, "\n", ++testnbr, ++linenbr) == 1)
		return(fail_print());
	if(tester(fd, NULL, ++testnbr, ++linenbr) == 1)
		return(fail_print());
	close(fd);
	printf("\n");

	testnbr = 1;
	linenbr = 1;
	printf(BMAG "multiplelines.txt:\n" RESET);
	fd = open("test_files/multiplelines.txt", O_RDONLY);
	if(tester(fd, "fkdsnckjdsnmdscmslkdmclk\n", testnbr, linenbr) == 1)
		return(fail_print());
	if(tester(fd, "jfiewjofjesofjiesfojesf\n", ++testnbr, ++linenbr) == 1)
		return(fail_print());
	if(tester(fd, "mclsmcklkdscmkdskmclmsdclkmds\n", ++testnbr, ++linenbr) == 1)
		return(fail_print());
	if(tester(fd, "kdcmslkdcmsmdslkmckdsmfkemwl\n", testnbr, linenbr) == 1)
		return(fail_print());
	if(tester(fd, "j94u23jr23nlkneflkflkmlkmm\n", ++testnbr, ++linenbr) == 1)
		return(fail_print());
	if(tester(fd, "3yrhonkjnejfjknf23kjnf3nnj\n", ++testnbr, ++linenbr) == 1)
		return(fail_print());
	if(tester(fd, NULL, ++testnbr, ++linenbr) == 1)
		return(fail_print());
	close(fd);
	printf("\n");

	testnbr = 1;
	linenbr = 1;
	printf(BMAG "nlines.txt:\n" RESET);
	fd = open("test_files/nlines.txt", O_RDONLY);
	if(tester(fd, "\n", testnbr, linenbr) == 1)
		return(fail_print());
	if(tester(fd, "\n", ++testnbr, ++linenbr) == 1)
		return(fail_print());
	if(tester(fd, "\n", ++testnbr, ++linenbr) == 1)
		return(fail_print());
	if(tester(fd, "\n", testnbr, linenbr) == 1)
		return(fail_print());
	if(tester(fd, "\n", ++testnbr, ++linenbr) == 1)
		return(fail_print());
	if(tester(fd, "\n", ++testnbr, ++linenbr) == 1)
		return(fail_print());
	if(tester(fd, NULL, ++testnbr, ++linenbr) == 1)
		return(fail_print());
	close(fd);
	printf("\n");

	testnbr = 1;
	linenbr = 1;
	printf(BMAG "nlines.txt:\n" RESET);
	fd = open("test_files/nlines.txt", O_RDONLY);
	if(tester(fd, "\n", testnbr, linenbr) == 1)
		return(fail_print());
	if(tester(fd, "\n", ++testnbr, ++linenbr) == 1)
		return(fail_print());
	if(tester(fd, "\n", ++testnbr, ++linenbr) == 1)
		return(fail_print());
	if(tester(fd, "\n", testnbr, linenbr) == 1)
		return(fail_print());
	if(tester(fd, "\n", ++testnbr, ++linenbr) == 1)
		return(fail_print());
	if(tester(fd, "\n", ++testnbr, ++linenbr) == 1)
		return(fail_print());
	if(tester(fd, NULL, ++testnbr, ++linenbr) == 1)
		return(fail_print());
	close(fd);
	printf("\n");

	// uses multiplelines.txt
	testnbr = 1;
	linenbr = 1;
	printf(BMAG "stdin\n" RESET);
	fd = STDIN_FILENO;
	if(tester(fd, "fkdsnckjdsnmdscmslkdmclk\n", testnbr, linenbr) == 1)
		return(fail_print());
	if(tester(fd, "jfiewjofjesofjiesfojesf\n", ++testnbr, ++linenbr) == 1)
		return(fail_print());
	if(tester(fd, "mclsmcklkdscmkdskmclmsdclkmds\n", ++testnbr, ++linenbr) == 1)
		return(fail_print());
	if(tester(fd, "kdcmslkdcmsmdslkmckdsmfkemwl\n", testnbr, linenbr) == 1)
		return(fail_print());
	if(tester(fd, "j94u23jr23nlkneflkflkmlkmm\n", ++testnbr, ++linenbr) == 1)
		return(fail_print());
	if(tester(fd, "3yrhonkjnejfjknf23kjnf3nnj\n", ++testnbr, ++linenbr) == 1)
		return(fail_print());
	if(tester(fd, NULL, ++testnbr, ++linenbr) == 1)
		return(fail_print());
	close(fd);
	printf("\n");

	return(1);
}
