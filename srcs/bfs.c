/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:21:52 by yabecret          #+#    #+#             */
/*   Updated: 2019/09/26 11:46:32 by mjouffro         ###   ########.fr       */
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
	enqueue(&queue, new);
	queue->room->visited = true;
	while (queue != NULL)
	{
		enqueue_adjacent(lemin, &queue, queue->room);
		todelete = queue;
		queue = queue->next;
		//print(queue);
		if (queue)
			cnt++;
		free(todelete); //remove first node from the queue
	}
	if (lemin->container && lemin->container->len != 0)
	{
		lemin->container->next = memalloc_allpaths();
		lemin->container = lemin->container->next;
	}
	return (cnt);
}
