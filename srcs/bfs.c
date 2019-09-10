/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:21:52 by yabecret          #+#    #+#             */
/*   Updated: 2019/09/10 16:56:24 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			len_max(t_lemin *lemin, t_allpaths *head)
{
	unsigned int	len_max;
	unsigned int	cnt;
	t_allpaths		*tmp;

	cnt = 0;
	tmp = head;
	len_max = tmp->len;
	while (tmp)
	{
		ft_printf("tmp len is %d\n", tmp->len);
		len_max = len_max < tmp->len ? tmp->len : len_max;
		cnt++;
		tmp = tmp->next;
	}
	lemin->nb_paths = cnt;
	ft_printf("cnt is %d\n", cnt);
	return (len_max);
}

unsigned int			get_total(t_lemin *lemin, t_allpaths *head)
{
	unsigned int	total;
	unsigned int	max_steps;
	unsigned int	max_len;
	t_allpaths		*tmp;

	tmp = head;
	max_len = len_max(lemin, tmp);
	ft_printf("max_len is %d\n", max_len);
	total = 0;
	max_steps = lemin->max_steps;
	while (tmp)
	{
		tmp->max_steps = ((max_len + 1) - tmp->len);
		total += tmp->max_steps;
		tmp = tmp->next;
	}
	ft_printf("total is %d\n", total);
	return (total);
}

unsigned int			nbr_steps(t_lemin *lemin, t_allpaths *head)
{
	unsigned int	max_steps;
	unsigned int	max = 0;
	unsigned int	total;
	unsigned int	remainder;
	unsigned int	reste;
	t_allpaths		*tmp;

	max_steps = lemin->max_steps;
	tmp = head;
	total = get_total(lemin, tmp);
	if (total > lemin->nb_ants)
		return (0);
	ft_printf("nb paths = %d\n", lemin->nb_paths);
	remainder = (lemin->nb_ants - total) / lemin->nb_paths;
	ft_printf("remainder = %d\n", remainder);
	reste = lemin->nb_ants - (remainder * lemin->nb_paths + total);
	ft_printf("reste = %d\n", reste);
	while (tmp)
	{
		//ft_printf("AVANT tmp->max_steps is : %d\n", tmp->max_steps);
		tmp->max_steps += (remainder + tmp->len + (reste ? 1 : 0) - 1);
		//ft_printf("APRES tmp->max_steps is : %d\n", tmp->max_steps);
		if (max < tmp->max_steps)
			max = tmp->max_steps;
		tmp = tmp->next;
		if (reste > 0)
			reste--;
	}
	max_steps = max;
	ft_printf("{green}max_steps is : %d{reset}\n", max_steps);
	if (max_steps > lemin->max_steps)
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
	//new->room = lemin->sink;
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
		print(queue);
		if (queue)
			cnt++;
		free(todelete); //remove first node from the queue
	}
	//ft_printf("{red}QUEUE EMPTY{reset}\n");
	//printall(lemin->list);
	if (lemin->container && lemin->container->len != 0)
	{
		lemin->container->next = memalloc_allpaths();
		lemin->container = lemin->container->next;
	}
	return (cnt);
}
