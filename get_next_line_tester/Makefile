include ../sources.mk

CC = cc

CFLAGS = -Wall -Werror -Wextra

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=logs/valgrind-out.txt 

LIB = mallocinterpose

LIBSO = lib$(LIB).so

NORMINETTE = norminette_tester/norminette.c

TEST_1 = output/test1.out
TEST_2 = output/test2.out
TEST_3 = output/test3.out
TEST_4 = output/test4.out

.SILENT:

all: output logs welcome norminette tests 

exe_without_welcome: output logs norminette tests

exe_welcome_lite: output logs welcome_lite norminette tests

welcome_lite:
	$(CC) $(CFLAGS) gnl_tester_welcome_lite.c -o welcome_lite && ./welcome_lite && rm welcome_lite
welcome: 
	$(CC) $(CFLAGS) gnl_tester_welcome.c -o welcome && ./welcome && rm welcome

tests:
	$(CC) $(CFLAGS) gnl_tester.c ../get_next_line.c ../get_next_line_utils.c -D BUFFER_SIZE=1 -o $(TEST_1)
	-$(VALGRIND) ./$(TEST_1) < test_files/multiplelines.txt
	$(CC) $(CFLAGS) gnl_tester.c ../get_next_line.c ../get_next_line_utils.c -D BUFFER_SIZE=42 -o $(TEST_2) 
	-$(VALGRIND) ./$(TEST_2) < test_files/multiplelines.txt
	$(CC) $(CFLAGS) gnl_tester.c ../get_next_line.c ../get_next_line_utils.c -D BUFFER_SIZE=1000 -o $(TEST_3) 
	-$(VALGRIND) ./$(TEST_3) < test_files/multiplelines.txt
	$(CC) $(CFLAGS) gnl_tester.c ../get_next_line.c ../get_next_line_utils.c -D BUFFER_SIZE=100000 -o $(TEST_4) 
	-$(VALGRIND) ./$(TEST_4) < test_files/multiplelines.txt

norminette: 
	cc -Wall -Werror -Wextra $(NORMINETTE) && ./a.out $(SOURCES)
	rm a.out

output: 
	mkdir output
logs:
	mkdir logs

clean_logs:
	-rm -rf logs

clean_output:
	-rm -rf output

clean: clean_logs clean_output

re: clean all
