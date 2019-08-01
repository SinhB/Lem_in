/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 12:59:29 by mjouffro          #+#    #+#             */
/*   Updated: 2019/07/04 15:08:26 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		display_ants(t_allpaths	*paths, int left)
{
	t_links	*tmp;

	tmp = paths->path;
	while (tmp)
	{
		if (tmp->room->antid && left == 0)
		{
			ft_printf("L%u-%s", tmp->room->antid, tmp->room->name);
			left = 1;
		}
		else if (tmp->room->antid && left == 1)
			ft_printf(" L%u-%s", tmp->room->antid, tmp->room->name);
		tmp = tmp->next;
	}
	return (left);
}