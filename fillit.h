/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gconroy <gconroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 19:15:42 by gconroy           #+#    #+#             */
/*   Updated: 2019/04/08 21:16:40 by gconroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "libft.h"
# include <stdio.h>

typedef struct		s_tetr
{
	char			**tetri;
	char			value;
	int				x;
	int				y;
	struct s_tetr	*next;
}					t_tetr;

void	ft_er(void);
void	free_map(char ***map, int size);
void	free_lst(t_tetr **start);
int 	next_sheet(char *buf, t_tetr *start, int value);
int  	first_sheet(char *buf, t_tetr **start);
int		open_file(const char *filename, t_tetr **start);
int     read_and_verify(int fd, t_tetr **start);
int     verify_links(const char *tetro_str);
int     count_the_symbols(const char *tetro_str);
int     verify_newline_and_count_tetro(char *tetro_str, int *last_newline, int count_tetro);
int     write_to_sheet(char *buf, t_tetr **start, int value);
int		print_sol(t_tetr *tmp, int size);
t_tetr	*create_elem(char *buf);

#endif
