/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 10:58:18 by yabecret          #+#    #+#             */
/*   Updated: 2019/09/25 17:47:10 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	addflow(int **matrix, int x, int y)
{
	matrix[x][y] += 1;
}

int		find_no_end_list(t_lemin *lemin)
{
	t_links		*tmp;

	tmp = lemin->list;
	//ft_printf("{blue}end index : %d\n{reset}", lemin->sink->index);
	while (tmp)
	{
		if (tmp->room && tmp->room->hash == lemin->sink->pred)
		{
			if (lemin->matrix[tmp->room->index][lemin->sink->index] == 1)
				return (FAILURE);
			else
				return (SUCCESS);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}


int		updatematrix(t_lemin *lemin)
{
	t_links *head;
	t_links *children;

	head = lemin->container->path;
	if (!find_no_end_list(lemin))
		return (FAILURE);
	while (head)
	{
		if (head->next)
		{
			children = head->next;
			addflow(lemin->matrix, head->room->index, children->room->index);
		}
		head = head->next;
	}
	return (SUCCESS);
}

int		updatefinalmatrices(t_lemin *lemin)
{
	int 		i;
	int 		j;

	i = 0;
	while (i < lemin->cnt)
	{
		j = 0;
		while (j < lemin->cnt)
		{
			if (lemin->matrix[i][j] == 1 && lemin->matrix[j][i] == 1)
			{
				lemin->matrix[i][j] = 0;
				lemin->matrix[j][i] = 0;
				if (lemin->matrix[i][j] == 0)
					lemin->weight_matrix[i][j] = 0;
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}