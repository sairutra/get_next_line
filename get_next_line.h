/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/21 23:03:23 by spenning      #+#    #+#                 */
/*   Updated: 2023/10/22 14:02:53 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// These are header guards that prevent the double definitions in the 
// source file. This prevents library dependency from double copying
// libraries. if libft is already defined if won't define it again.
// name is LIBFT_H because the name should be the full filename of the 
// header file, in all caps, with underscores for spaces and ​punctuation.

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

char *  get_next_line(int fd);

#endif