/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_tester.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mynodeus <mynodeus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:15:32 by mynodeus          #+#    #+#             */
/*   Updated: 2024/05/17 17:15:03 by mynodeus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_TESTER_H
# define GNL_TESTER_H

# include <stdio.h>
# include <fcntl.h>
# include "../inc/get_next_line.h" 

# define RED   "\x1B[31m"
# define GRN   "\x1B[1;32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define BMAG   "\x1B[1;35m"
# define CYN   "\x1B[36m"
# define BCYN   "\x1B[1;36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

int		fail_print(void);
int		tester(const int fd, char *str, int testnbr, int linenbr);
void	one_char(void);
void	empty(void);
void	longline(void);
void	longline_nl(void);
void	multiplelines(void);
void	nlines(void);
void	stdin_test(void);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

#endif