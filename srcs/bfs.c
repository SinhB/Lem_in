/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabecret <yabecret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:21:52 by yabecret          #+#    #+#             */
/*   Updated: 2019/07/05 21:22:16 by yabecret         ###   ########.fr       */
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
