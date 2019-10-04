/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:10:06 by mjouffro          #+#    #+#             */
/*   Updated: 2019/10/04 12:13:00 by mjouffro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				main(void)
{
	t_lemin		lemin;

	ft_bzero(&lemin, sizeof(lemin));
	if (!(parsing(&lemin)))
	{
		ft_printf("parsing error\n");
		return (FAILURE);
	}
	ft_printf("parsing done\n");
	if (lemin.head == NULL)
		return (FAILURE);
	ek(&lemin);
	updatefinalmatrices(&lemin);
	get_final_paths(&lemin);
	solve_lemin(&lemin, 1);
	freelemin(&lemin);
	//freeallpaths(&lemin.container);
	//freeallpaths(&lemin.container1);
	return (0);
}


