/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:21:52 by yabecret          #+#    #+#             */
/*   Updated: 2019/09/23 16:19:10 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
		//print(queue);
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
