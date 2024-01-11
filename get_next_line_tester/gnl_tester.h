#ifndef GNL_TESTER_H
# define GNL_TESTER_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>

# define MAX_ALLOCATIONS 100
# define WARN(msg, line) (printf("Warning %d: %s\n", line, msg))

/* 
Data Structure to keep track of memory allocations
*/
typedef struct {
    size_t address;
    size_t size;
    uint32_t line;
} Mem;

struct {
    Mem mem[MAX_ALLOCATIONS];
    size_t total_allocated_size;
    size_t total_free_size;
} data;


Mem *find_by_address(size_t address);
void insert(size_t address, size_t size, uint32_t line);
int erase(size_t address, uint32_t line);
void print_report();
void *_malloc(size_t size, uint32_t line);
void _free(void *ptr, uint32_t line);

#endif
