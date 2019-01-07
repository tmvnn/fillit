/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 20:10:35 by lbellona          #+#    #+#             */
/*   Updated: 2019/01/07 22:02:33 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_tetlst		*ft_create_elem(char letter)
{
	t_tetlst	*newlist;

	if ((newlist = (t_tetlst*)malloc(sizeof(t_tetlst))))
	{
		newlist->next = NULL;
		newlist->letter = letter;
	}
	return (newlist);
}

void			ft_list_push_back(t_tetlst **begin_list, t_tetlst *cur_tet)
{
	t_tetlst	*tmpptr;

	if (*begin_list == NULL)
		*begin_list = cur_tet;
	else
	{
		tmpptr = *begin_list;
		while (tmpptr->next)
			tmpptr = tmpptr->next;
		tmpptr->next = cur_tet;
	}
}

int				create_tetr(t_tetlst **tets, char *buff, char letter)
{
	int			m_iter;
	int			j;
	t_point		delt;
	t_tetlst	*cur_tet;

	j = -1;
	m_iter = 0;
	ALCN_CHECK((cur_tet = ft_create_elem(letter)));
	while (*buff)
	{
		if (*buff == '#')
		{
			if (!++j)
			{
				delt.x = m_iter % TET_SIZE;
				delt.y = m_iter / TET_SIZE;
			}
			cur_tet->x[j] = m_iter % TET_SIZE - delt.x;
			cur_tet->y[j] = m_iter / TET_SIZE - delt.y;
		}
		m_iter = *buff++ == '\n' ? m_iter : m_iter + 1;
	}
	ft_list_push_back(tets, cur_tet);
	return (1);
}

t_tetlst		*read_2_lst(int fd, int *tet_num)
{
	t_tetlst	*tets;
	char		buff[BUFF_SIZE + 1];
	int			size;
	int			i;

	i = 0;
	tets = NULL;
	while ((size = read(fd, buff, BUFF_SIZE)))
	{
		buff[size] = '\0';
		if (!(input_is_valid()))
			return ((t_tetlst *)pr_error());
		ALCN_CHECK((create_tetr(&tets, buff, (i + 65))));
		*tet_num = ++i;
	}
	close(fd);
	return (tets);
}

int				main(int argc, char **argv)
{
	int			fd;
	int			tet_num;
	t_tetlst	*tets;

	if (argc != 2)
		ft_putstr("usage: binary_file tetraminos_file\n");
	else
	{
		if ((fd = open(argv[1], O_RDONLY)) < 0)
			return ((int)pr_error());
		if ((tets = read_2_lst(fd, &tet_num)))
		{
			if (tets_is_valid(tet_num))
				solve_map(tets, tet_num);
		}
	}
	return (0);
}
