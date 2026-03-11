/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:22:14 by anfouger          #+#    #+#             */
/*   Updated: 2026/03/11 15:14:16 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_key(char *str)
{
	char	*key;
	int		len;

	len = 0;
	while (str[len] != '=')
		len++;
	key = ft_strndup(str, 0, len);
	return (key);
}

// static char	*get_value(char *str)
// {
// 	char	*value;
// 	int		i;

// 	i = 0;
// 	while (str[i] != '=')
// 		i++;
// 	value = ft_strndup(str, i, ft_strlen(str));
// 	return (value);
// }

static int	verif_export(char *str)
{
	int	i;

	i = 0;
	if (str[i] >= 'A' && str[i] <= 'Z')
	{
		while (str[i] >= 'A' && str[i] <= 'Z')
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
		return (-1);
	key = get_key(argv[1]);
	if (!key)
		return (-1);
	if (!change_value(minish->envp, key, argv[1]))
		minish->envp = add_var(minish->envp, argv[1]);
	free(key);
	return (0);
}
