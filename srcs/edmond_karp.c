/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmond_karp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 16:27:12 by yabecret          #+#    #+#             */
/*   Updated: 2019/07/05 18:11:09 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_links		*find_hash_node(t_links *list, unsigned long hash)
{
	t_links			*new;
	t_links			*tmp;

	new = memalloc_links();
	tmp = list;
	while (tmp)
	{
		if (tmp->room && tmp->room->hash == hash)
		{
			new->room = tmp->room;
			new->next = NULL;
			return (new);
		}
		tmp = tmp->next;
	}
	return (new);
}

int			backtrack(t_lemin *lemin)
{
	unsigned long	tracker;
	t_links			*tmp;
	unsigned int	cnt;

	tracker = lemin->hashend;
	cnt = 0;
	while (1)
	{
		if (tracker == 0)
		{
			lemin->container->len = cnt;
			return (SUCCESS);
		}
		tmp = find_hash_node(lemin->list, tracker);
		addlinks(&lemin->container->path, tmp);
		tracker = lemin->container->path->room->pred;
		cnt++;
	}
	return (FAILURE);
}

void		resetvisited(t_lemin *lemin)
{
	t_links 		*tmp;

	tmp = lemin->list;
	while (tmp)
	{
		tmp->room->visited = false;
		tmp = tmp->next;
	}
}

int			ek(t_lemin *lemin)
{
	lemin->matrix = memalloc_matrix(lemin->cnt);
	lemin->weight_matrix = memalloc_matrix(lemin->cnt);
	while (bfs(lemin) != 0)
	{
		backtrack(lemin);
		resetvisited(lemin);
		if (!updatematrix(lemin))
			break ;
		//printmatrix(lemin->matrix, lemin->cnt);
		//if (!(updateweightmatrix(lemin)))
		//	ft_printf("did not work\n");
	}
	//printmatrix(lemin->weight_matrix, lemin->cnt);
	return (SUCCESS);
}












/*
int			compare_weights(t_node **room, int idx)
{
	t_node	*nxt_room;

	nxt_room = (*room)->links[idx];
	if (nxt_room->weight == 0)
		return (1);
	else if (((*room)->weight + 1 < nxt_room->weight)
			&& nxt_room->vzt == VISITED
			&& ft_strcmp((*room)->hist->next->room->name, nxt_room->name))
	{
		if (check_redundancy(*room, nxt_room))
			return (0);
		if (nxt_room->hist != NULL)
		{
			remove_path(nxt_room->hist);
			nxt_room->hist = NULL;
		}
		nxt_room->weight = (*room)->weight + 1;
		nxt_room->hist = copy_path((*room)->hist);
		add_path(nxt_room, nxt_room->hist);
		return (1);
	}
	return (0);
}

		while (nxt_room->links[++i])
		{
			if ((*room)->access == CLSD && nxt_room->hist)
				compare_weights(&nxt_room, i);
			if (reverse_flux_case(nxt_room, i) && nxt_room->links[i]->vzt == 0)
			{
				fill_vzt_path(room, nxt_room, vzt_nxt, i);
				//room = build_path(*room, idx);
				closed_access_case2(nxt_room, vzt_nxt, reinit, i);
				if ((*room)->access == OPEN)
					nxt_room->weight = (*room)->weight + 1;
				break ;
			}
		}

			if (reverse_flux_case(room, i))
				room->links[i]->weight = room->weight - 1;
			else
				room->links[i]->weight = room->weight + 1;
*/

