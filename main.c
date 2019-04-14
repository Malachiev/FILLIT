/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gconroy <gconroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 16:39:17 by gconroy           #+#    #+#             */
/*   Updated: 2019/04/08 21:41:18 by gconroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		ft_er(void)
{
	write(1, "error\n", 6);
}

static int	check_sol2(t_tetr *tmp, t_tetr *tetr, int x, int y)
{
	int		i;
	int		j;

	while (tmp->value != tetr->value)
	{
		i = -1;
		while (++i < 4)
		{
			j = -1;
			while (++j < 4)
				if (tmp->tetri[i][j] == '#')
				{
					if ((tmp->x + i == (tetr->x + x)) &&
						(tmp->y + j == (tetr->y + y)))
						return (0);
				}
		}
		tmp = tmp->next;
	}
	return (1);
}

static int	check_sol(t_tetr *start, t_tetr *tetr, int size)
{
	int		x;
	int		y;

	x = -1;
	while (++x < 4)
	{
		y = -1;
		while (++y < 4)
			if (tetr->tetri[x][y] == '#')
			{
				if ((x + tetr->x) >= size || (y + tetr->y) >= size ||
					(x + tetr->x) < 0 || (y + tetr->y) < 0)
					return (0);
				if (!check_sol2(start, tetr, x, y))
					return (0);
			}
	}
	return (1);
}

static int	brutforce(t_tetr *start, t_tetr *tetr, int size)
{
	int		x;
	int		y;

	x = -4;
	while (++x < size)
	{
		y = -4;
		while (++y < size)
		{
			tetr->x = x;
			tetr->y = y;
			if (check_sol(start, tetr, size))
			{
				if (!(tetr->next))
					return (1);
				if (brutforce(start, tetr->next, size))
					return (1);
			}
		}
	}
	return (0);
}

void	free_lst(t_tetr **start)
{
	int		i;
	t_tetr	*tmp;

	while (*start)
	{
		i = -1;
		while (++i < 4)
			ft_strdel(&(*start)->tetri[i]);
		ft_memdel((void **)&((*start)->tetri));
		tmp = (*start)->next;
		ft_memdel((void **)(start));
		*start = tmp;
	}
}

int	main(int argc, char **argv)
{
	t_tetr 	*start;
	int		check;
	int		size;

	start = NULL;
	if (argc == 2)
	{
		if (open_file(argv[1], &start) == -1)
		{
			free_lst(&start);
			ft_er();
			return (0);
		}
		size = 1;
		check = 0;
		while(!check)
			check = brutforce(start, start, ++size);
		if (!(print_sol(start, size)))
			free_lst(&start);
		free_lst(&start);
		return (1);
	}
	ft_er();
	return (0);
}
