/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouffro <mjouffro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:10:06 by mjouffro          #+#    #+#             */
/*   Updated: 2019/09/11 10:49:14 by yabecret         ###   ########.fr       */
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
	ek(&lemin);
	updatefinalmatrices(&lemin);
	//printmatrix(lemin.weight_matrix, lemin.cnt);
//	freeallpaths(&lemin.container);
	get_final_paths(&lemin);
	//printmatrix(lemin.matrix, lemin.cnt);
///	ft_printf("%s\n", lemin.map);
///	sharing_ants(&lemin);
//	solve_lemin(&lemin, 1);
//	freelemin(&lemin);
	return (0);
}
