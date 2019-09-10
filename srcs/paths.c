/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 16:26:52 by mjouffro          #+#    #+#             */
/*   Updated: 2019/09/10 16:35:34 by mjouffro         ###   ########.fr       */
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
	return (container);
}

int			len_max2(t_lemin *lemin, t_allpaths *head, int index)
{
	unsigned int	len_max;
	unsigned int	cnt;
	t_allpaths		*tmp;
	int i = 0;

	cnt = 0;
	tmp = head;
	len_max = tmp->len;
	while (i < index)
	{
		ft_printf("tmp len is %d\n", tmp->len);
		len_max = len_max < tmp->len ? tmp->len : len_max;
		cnt++;
		tmp = tmp->next;
		i++;
	}
	lemin->nb_paths = cnt;
	ft_printf("cnt is %d\n", cnt);
	return (len_max);
}

unsigned int			get_total2(t_lemin *lemin, t_allpaths *head, int index)
{
	unsigned int	total;
	unsigned int	max_steps;
	unsigned int	max_len;
	t_allpaths		*tmp;
	int i = 0;

	tmp = head;
	max_len = len_max2(lemin, tmp, index);
	ft_printf("max_len is %d\n", max_len);
	total = 0;
	max_steps = lemin->max_steps;
	while (i < index)
	{
		tmp->max_steps = ((max_len + 1) - tmp->len);
		total += tmp->max_steps;
		tmp = tmp->next;
		i++;
	}
	ft_printf("total is %d\n", total);
	return (total);
}

unsigned int			nbr_steps2(t_lemin *lemin, t_allpaths *head, int index)
{
	unsigned int	max_steps;
	unsigned int	max = 0;
	unsigned int	total;
	unsigned int	remainder;
	unsigned int	reste;
	int i = 0;
	t_allpaths		*tmp;

	max_steps = lemin->max_steps;
	tmp = head;
	total = get_total2(lemin, tmp, index);
	if (total > lemin->nb_ants)
		return (0);
	ft_printf("nb paths = %d\n", lemin->nb_paths);
	remainder = (lemin->nb_ants - total) / lemin->nb_paths;
	ft_printf("remainder = %d\n", remainder);
	reste = lemin->nb_ants - (remainder * lemin->nb_paths + total);
	ft_printf("reste = %d\n", reste);
	while (i < index)
	{
		ft_printf("AVANT tmp->max_steps is : %d\n", tmp->max_steps);
		tmp->max_steps += (remainder + tmp->len + (reste ? 1 : 0) - 1);
		ft_printf("APRES tmp->max_steps is : %d\n", tmp->max_steps);
		if (max < tmp->max_steps)
			max = tmp->max_steps;
		tmp = tmp->next;
		i++;
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

int			max_steps2(t_lemin *lemin, t_allpaths *head)
{
	int			i;
	int			max = lemin->nb_paths;

	i = 1;
	ft_printf("max : %d\n", max);
	lemin->max_steps = INT_MAX;
	while (i < (max + 1))
	{
		ft_printf("{red}PRINT %d{reset}\n", i);
		if (!nbr_steps2(lemin, head, i))
			return (0);
		i++;
	}
	return (1);
}

void		get_final_paths(t_lemin *lemin)
{
	t_links 	*tmp;
	t_allpaths	*tmp2;
	t_allpaths	*head;
	int 		length;
	int			i;
//	int			nb_steps;

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
		//ft_printf("{yellow} final solution : {reset}\n");
		//print(lemin->container1->path);
		//ft_printf("path len is : %d\n", lemin->container1->len);
//		printmatrix(lemin->matrix, lemin->cnt);
		if (i != lemin->nb_paths - 1)
		{
			tmp2 = memalloc_allpaths();
			lemin->container1->next = tmp2;
			lemin->container1 = tmp2;
		}
		i++;
	}
	lemin->container1 = head;
	while (lemin->container1)
	{
		//ft_printf("{yellow} final solution : {reset}\n");
		ft_printf("the paths is : \n\n\n");
		print(lemin->container1->path);
		printall(lemin->container1->path);
		//ft_printf("path len is : %d\n", lemin->container1->len);
		lemin->container1 = lemin->container1->next;
	}
	//ft_printf("{red} AFTER SORT : {reset}\n");
	/*lemin->container1 = sort_paths(lemin->container1);
	head = lemin->container1;
	while (lemin->container1)
	{
		//ft_printf("{yellow} final solution : {reset}\n");
		ft_printf("the paths is : \n\n\n");
		print(lemin->container1->path);
		printall(lemin->container1->path);
		//ft_printf("path len is : %d\n", lemin->container1->len);
		lemin->container1 = lemin->container1->next;
	}
	lemin->container1 = head;
	max_steps2(lemin, head);
	//	nb_steps = nbr_steps(lemin, head);
	//	ft_printf("FINAL nbr_steps is %d\n", nb_steps);*/
}
