#include "lem_in.h"

int		start_end(char *line)
{
	if (ft_strcmp("##start", line) == 0)
		return (S_START);
	else if (ft_strcmp("##end", line) == 0)
		return (S_END);
	return (FAILURE);
}

int		gnl_exit(char *line)
{
	ft_strdel(&line);
	return (0);
}

/*void	add_line_and_delete(t_lemin *lemin, char *line)
{
	add_line_to_str(lemin, line);
	ft_strdel(&line);
}*/

int		parsing(t_lemin *lemin)
{
	char		*line;

	line = NULL;
	while (get_next_line(FD, &line) == 1)
	{
		if (is_command(line))
		{
			lemin->state |= start_end(line);
			add_line_to_str(lemin, line);
			ft_strdel(&line);
			//add_line_and_delete(lemin, line);
		}
		else if (is_comment(line))
		{
			add_line_to_str(lemin, line);
			ft_strdel(&line);
			//add_line_and_delete(lemin, line);
		}
		else if (ft_str_is_digit(line) && !lemin->nb_ants)
		{
			lemin->nb_ants = ft_atoi(line);
			add_line_to_str(lemin, line);
		}
		else if (ft_strchr(line, '-') && (lemin->state & S_ROOMS))
		{
			if (rooms_errors(lemin) && !(lemin->state & S_LINKS))
				exit_with_message_room(line);
			if (!get_link(lemin, &lemin->list, line))
				exit_with_message_links(line);
		}
		else if (!(lemin->state & S_LINKS) && is_room(line) 
			&& (lemin->nb_ants))
		{
			if (!get_room(lemin, &lemin->list, line))
				exit_with_message_room(line);
		}
		/*else
		{
			ft_printf("did not go in any parsing condition\n");
			return (gnl_exit(line));
		}*/
		ft_strdel(&line);
	}
	return (1);
}

