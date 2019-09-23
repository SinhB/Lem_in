/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 16:26:52 by mjouffro          #+#    #+#             */
/*   Updated: 2019/09/23 19:27:44 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			find_nb_paths(t_lemin *lemin)
{
	int 		ret;
	int 		cnt;

	cnt = 0;
	ret = 0;
	while (cnt < lemin->cnt)
	{
		if (lemin->matrix[cnt][lemin->sink->index] == 1)
			ret++;
		cnt++;
	}
	return (ret);
}

t_links		*find_index_node(t_links *list, int index)
{
	t_links			*new;
	t_links			*tmp;

	new = memalloc_links();
	tmp = list;
	while (tmp)
	{
		if (tmp->room && tmp->room->index == index)
		{
			new->room = tmp->room;
			new->next = NULL;
			return (new);
		}
		tmp = tmp->next;
	}
	return (new);
}

int			get_matrix_path(t_lemin *lemin, t_links *tmp)
{
	int				current;
	int				len;
	int				i;

	len = 0;
	current = lemin->sink->index;
	while (current != lemin->head->index)
	{
		i = 0;
		while (i < lemin->cnt && lemin->matrix[i][current] != 1)
			i++;
		if (i == lemin->cnt)
			return (0);
		tmp = find_index_node(lemin->list, i);
		addlinks(&lemin->container1->path, tmp);
		lemin->matrix[i][current] = 0;
		current = i;
		len++;
	}
	return (len);
}

t_allpaths *sort_paths(t_allpaths *container)
{
	t_allpaths *swap;
	t_allpaths *swap2;
	t_allpaths *pred;
	t_allpaths *head;

	head = container;
	pred = head;
	while (container->next)
	{
//		ft_printf("pred | %d |\n", pred->len);
//		ft_printf("%d | %d\n", container->len, container->next->len);
		if (container->len > container->next->len)
		{
			swap = container;
//			ft_printf("swap len is : %d\n", swap->len);
//			ft_printf("Before container len is : %d\n", container->len);
			container = container->next;
			pred->next = container;
			swap2 = container->next;
			swap->next = swap2;
//			ft_printf("After  container len is : %d\n", container->len);
			container->next = swap;
			if (swap == head)
				head = container;
			swap = NULL;
//			ft_printf("Container next len is : %d\n", container->next->len);
			container = head;
			pred = head;
//			ft_printf("{red}BACK{reset}\n");
		}
		else
		{
//			ft_printf("NEXT\n");
			if (container != head)
				pred = pred->next;
			container = container->next;
		}
	}
	container = head;
	while (container)
	{
		ft_printf("---path len is %d\n", container->len);
		container = container->next;
	}
	container = head;
	return (container);
}

void		get_final_paths(t_lemin *lemin)
{
	t_links 	*tmp;
	t_allpaths	*tmp2;
	t_allpaths	*head;
	int 		length;
	int			i;
	
	lemin->nb_paths = find_nb_paths(lemin);
	tmp = memalloc_links();
	lemin->container1 = memalloc_allpaths();
	head = lemin->container1;
	i = 0;
	while (i < lemin->nb_paths)
	{
		tmp->room = lemin->sink;
		addlinks(&lemin->container1->path, tmp);
		length = get_matrix_path(lemin, tmp);
		if (length == lemin->cnt)
			ft_printf("length == lemin->cnt!\n");
		lemin->container1->len = length;
		if (i != lemin->nb_paths - 1)
		{
			tmp2 = memalloc_allpaths();
			lemin->container1->next = tmp2;
			lemin->container1 = tmp2;
		}
		i++;
	}
	lemin->container1 = sort_paths(lemin->container1);
	lemin->container1 = head;
	max_stepsek(lemin, head);
	ft_printf("{yellow} max_steps : %d\n", lemin->max_steps);
	ft_printf("{yellow} max_steps1 : %d\n", lemin->max_steps1);
	ft_printf("nb paths is %d\n", lemin->nb_paths);
}
