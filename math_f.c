/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 18:25:48 by lbellona          #+#    #+#             */
/*   Updated: 2019/01/05 18:41:46 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ft_sqrt(int nb)
{
	int		i;

	i = -1;
	while (++i <= nb)
	{
		if (i * i == nb)
			return (i);
		if (i * i > nb)
			return (i);
		if (i > 46430)
			break ;
	}
	return (0);
}