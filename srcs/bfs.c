/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:21:52 by yabecret          #+#    #+#             */
/*   Updated: 2019/09/04 14:29:58 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			len_max(t_lemin *lemin)
{
	unsigned int	len_max;
	unsigned int	cnt;
	t_allpaths		*tmp;

	cnt = 0;
	tmp = lemin->container;
	ft_printf("tmp len is %d\n", tmp->len);
	len_max = tmp->len;
	while (tmp)
	{
		len_max = tmp->len;
		cnt++;
		tmp = tmp->next;
		ft_printf("cnt is %d\n", cnt);
	}
	lemin->nb_paths = cnt;
	return (len_max);
}

unsigned int			get_total(t_lemin *lemin)
{
	unsigned int	total;
	unsigned int	max_steps;
	unsigned int	max_len;
	t_allpaths		*tmp;

	max_len = len_max(lemin);
	total = 0;
	max_steps = lemin->max_steps;
	tmp = lemin->container;
	while (tmp)
	{
		tmp->max_steps = ((max_len + 1) - tmp->len);
		total += tmp->max_steps;
		tmp = tmp->next;
	}
	ft_printf("total is %d\n", total);
	return (total);
}

unsigned int			nbr_steps(t_lemin *lemin)
{
	unsigned int	max_steps;
	unsigned int	total;
	unsigned int	remainder;
	unsigned int	reste;
	t_allpaths		*tmp;

	tmp = lemin->container;
	total = get_total(lemin);
	ft_printf("nb paths = %d\n", lemin->nb_paths);
	remainder = lemin->nb_ants - total / lemin->nb_paths;
	reste = lemin->nb_ants - (remainder * lemin->nb_paths);
	tmp = lemin->container;
	while (tmp)
	{
		tmp->max_steps += (remainder + tmp->len + (reste - 1));
		ft_printf("tmp->max_steps is : %d\n", tmp->max_steps);
		if (max_steps > tmp->max_steps)
			max_steps = tmp->max_steps;
		tmp = tmp->next;
		reste--;
	}
	if (max_steps == lemin->max_steps)
		return (0);
	else
		return (max_steps);
}

int			bfs(t_lemin *lemin)
{
	t_links 		*queue;
	t_links			*new;
	t_links 		*todelete;
	int				cnt;

	cnt = 0;
	queue = NULL;
	todelete = NULL;
	new = memalloc_links();
	new->room = lemin->head;
	enqueue(&queue, new);
	queue->room->visited = true;
	while (queue != NULL)
	{
		// compare weights
		// add weight + 1 to next room
//		ft_printf("{red}QUEUE:{reset}\n");
//		print(queue);
		enqueue_adjacent(lemin, &queue, queue->room); //add all adjacent into the queue
		todelete = queue;
		queue = queue->next;
		if (queue)
			cnt++;
		free(todelete); //remove first node from the queue
	}
	//ft_printf("{red}QUEUE EMPTY{reset}\n");
	//printall(lemin->list);
	lemin->container = memalloc_allpaths();
	return (cnt);
}

