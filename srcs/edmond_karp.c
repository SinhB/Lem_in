/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmond_karp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 16:27:12 by yabecret          #+#    #+#             */
/*   Updated: 2019/09/24 17:13:36 by mjouffro         ###   ########.fr       */
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
			//ft_printf("{yellow} pre-final solution : {reset}\n");
			//print(lemin->container->path);
			lemin->container->len = cnt - 1;
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
	int 		tmp;
	t_allpaths	*head;

	tmp = 1;
	lemin->matrix = memalloc_matrix(lemin->cnt);
	lemin->weight_matrix = memalloc_matrix(lemin->cnt);
	lemin->container = memalloc_allpaths();
	head = lemin->container;
	lemin->max_steps = INT_MAX;
	while (bfs(lemin) != 0 && tmp)
	{
		backtrack(lemin);
		tmp = nbr_steps(lemin, lemin->container);
		tmp ? lemin->max_steps = tmp : lemin->max_steps;
		resetvisited(lemin);
		if (!updatematrix(lemin))
			break ;
	}
	lemin->container = head;
	while (lemin->container)
	{
		if (lemin->container->len == 0)
		{
			freelinks(&lemin->container->path);
			ft_memdel((void**)(lemin->container));
			lemin->nb_paths--;
		}
		lemin->container = lemin->container->next;
	}
	lemin->container = head;

		while (lemin->container)
	{
		if (lemin->container->len == 0)
		{
			ft_printf("the container was not properly deletd biitch\n");
			lemin->nb_paths--;
		}
		lemin->container = lemin->container->next;
	}
	lemin->container = head;
	return (SUCCESS);
}