/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:22:14 by anfouger          #+#    #+#             */
/*   Updated: 2026/03/17 09:40:58 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_key(char *str)
{
	char	*key;
	int		len;

	len = 0;
	while (str[len] != '=')
		len++;
	key = ft_strndup(str, 0, len);
	return (key);
}

static int	verif_export(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '_'
		|| (str[i] >= 'A' && str[i] <= 'Z')
		|| (str[i] >= 'a' && str[i] <= 'z'))
	{
		while (str[i] == '_'
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= '0' && str[i] <= '9'))
			i++;
		if (str[i] != '=')
			return (0);
		if (!str[++i])
			return (0);
		return (1);
	}
	return (0);
}

int	builtin_export(t_minish *minish, char **argv)
{
	char	*key;

	if (!verif_export(argv[1]))
		return (1);
	key = get_key(argv[1]);
	if (!key)
		return (1);
	if (!change_value(minish->envp, key, argv[1]))
		minish->envp = add_var(minish->envp, argv[1]);
	free(key);
	return (0);
}
