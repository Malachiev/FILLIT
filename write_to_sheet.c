/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_sheet.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gconroy <gconroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 18:36:57 by gconroy           #+#    #+#             */
/*   Updated: 2019/04/08 19:56:09 by gconroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_tetr	*create_elem(char *buf)
{
	t_tetr	*tmp;
	int		i;
	int		j;
	int		k;

	if (!(tmp = (t_tetr *)ft_memalloc(sizeof(t_tetr))))
		return (0);
	if (!(tmp->tetri = (char **)ft_memalloc(sizeof(char *) * 4)))
		return (0);
	i = -1;
	while (++i < 4)
		if (!(tmp->tetri[i] = ft_strnew(4)))
			return (0);
	k = 0;
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			tmp->tetri[i][j] = buf[k++];
		k++;
	}
	return (tmp);
}

int next_sheet(char *buf, t_tetr *start, int value)
{
    t_tetr  *tail;

    while (start->next)
    {
        start = start->next;
    }
    if (!(tail = create_elem(buf)))
        return (0);
    tail->value = 'A' + value;
    tail->next = NULL;
    start->next = tail;
    return (1);
}

int  first_sheet(char *buf, t_tetr **start)
{
    t_tetr  *tmp;

    if (!(tmp = create_elem(buf)))
        return (0);
    tmp->value = 'A';
    tmp->next = NULL;
    *start = tmp;
    return (1);
}

int write_to_sheet(char *buf, t_tetr **start, int value)
{
    if (!value)
    {
        if (!first_sheet(buf, start))
            return (-1);
    }
    else
    {
        if (!next_sheet(buf, *start, value))
            return (-1);
    }
    return (1);
}