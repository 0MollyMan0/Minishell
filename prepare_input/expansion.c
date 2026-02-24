/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 12:40:40 by anfouger          #+#    #+#             */
/*   Updated: 2026/02/24 08:06:59 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_expandable(char c)
{
	if (c == '_'
		|| c == '?'
		|| (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

static char *create_new_arg(char *str)
{
	int	i;
	int i_new;
	char *new_str;
	
	i = 0;
	i_new = 0;
	new_str = malloc(sizeof(char) * 1);
	new_str[0] = '\0';
	while (str[i])
	{
		if (str[i] == '$' && is_expandable(str[i]))
		{
			do_expansion();
		}
		else
		{
			new_str = ft_realloc(new_str, 1);
			new_str[i_new] = str[i];
			i_new++;
			i++;
		}
	}
	free(str);
	return (new_str);
}

t_cmd	*expansion(t_cmd *cmds)
{
	t_cmd	*p_cmds;
	int		i;

	p_cmds = cmds;
	while (p_cmds)
	{
		i = 0;
		while (p_cmds->argv[i])
		{
			if (p_cmds->argv[i][0] != '\'')
				p_cmds->argv[i] = create_new_arg(p_cmds->argv[i]);
			i++;
		}
		p_cmds = p_cmds->next;
	}
	return (cmds);
}
