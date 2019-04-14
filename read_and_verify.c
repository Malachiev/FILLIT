/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_verify.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gconroy <gconroy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 19:19:16 by gconroy           #+#    #+#             */
/*   Updated: 2019/04/08 19:23:22 by gconroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int verify_links(const char *buf)
{
    int i;
    int links;

    i = 0;
    links = 0;
    while (buf[i] != '\0')
    {
        if (buf[i] == '#')
        {
            if (i && buf[i - 1] == '#')
                links++;
            if (i < 18 && buf[i + 1] == '#')
                links++;
            if (i > 4 && buf[i - 5] == '#')
                links++;
            if (i < 14 && buf[i + 5] == '#')
                links++;
            if (!links)
                return (-1);
        }
        i++;
    }
    if (links == 6 || links == 8)
        return (1);
    else
        return (-1);
}

int count_the_symbols(const char *buf)
{
    int i;
    int sharp;
    int newline;
    int point;

    i = 0;
    sharp = 0;
    point = 0;
    newline = 0;
    while (buf[i] != '\0')
    {
        if (buf[i] == '.')
            point++;
        if (buf[i] == '#')
            sharp++;
        if (buf[i] == '\n')
            newline++;
        i++;
    }
    if (point == 12 && sharp == 4 && newline == 4)
        return (1);
    else
        return (-1);
}

int verify_newline_and_count_tetro(char *buf, int *last_newline, int count_tetro)
{
    int newline;

    newline = 19;
    if (count_tetro > 26)
        return (-1);
    while (newline > 0)
    {
        if (buf[newline] != '\n')
            return (-1);
        newline -= 5; 
    }
    if (buf[20] != '\n' && buf[20] != '\0')
        return (-1);
    if (buf[20] != '\0')
        *last_newline = 1;
    else
        *last_newline = 0;
    return (1);
}

int read_and_verify(int fd, t_tetr **start)
{
    char    *buf;
    int     value;
    int     last_newline;

    buf = ft_strnew(21);
    value = 0;
    while (read(fd, buf, 21))
    {
        if (verify_newline_and_count_tetro(buf, &last_newline, value + 1) == -1)
            return (-1);
        buf[20] = '\0';
        if (count_the_symbols(buf) == -1)
            return (-1);
        if (verify_links(buf) == -1)
            return (-1);
        if (write_to_sheet(buf, start, value) == -1)
        {
            free_lst(start);
            return (-1);
        }
        ft_bzero(buf, 21);
        value++;
    }
    ft_strdel(&buf);
    if (!value || last_newline)
        return (-1);
    return (1);
}