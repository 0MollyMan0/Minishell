/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:22:14 by anfouger          #+#    #+#             */
/*   Updated: 2026/03/23 15:57:12 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_key(char *str)
{
	char	*key;
	int		len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	key = ft_strndup(str, 0, len);
	return (key);
}

// static int	verif_export(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (str[i] == '_'
// 		|| (str[i] >= 'A' && str[i] <= 'Z')
// 		|| (str[i] >= 'a' && str[i] <= 'z'))
// 	{
// 		while (str[i] == '_'
// 			|| (str[i] >= 'A' && str[i] <= 'Z')
// 			|| (str[i] >= 'a' && str[i] <= 'z')
// 			|| (str[i] >= '0' && str[i] <= '9'))
// 			i++;
// 		if (str[i] != '=')
// 			return (0);
// 		if (!str[++i])
// 			return (0);
// 		return (1);
// 	}
// 	return (0);
// }

static int	verif_export(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '_'
		|| (str[i] >= 'A' && str[i] <= 'Z')
		|| (str[i] >= 'a' && str[i] <= 'z'))
	{
		while (str[i] == '_'  || str[i] != '='
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= '0' && str[i] <= '9'))
		{
			if (str[i + 1] == '\0')
				return (1);
			i++;		
		}
		return (0);
	}
	return (0);
}

static int	export_no_args(t_minish *minish)
{
	int	i;

	i = 0;
	while (minish->envp[i])
	{
		printf("declare -x %s\n", minish->envp[i]);
		i++;
	}
	return (0);
}

static int	export_invalid_id(char *argv)
{
	write(2, "export: ", 8);
	write(2, &argv, ft_strlen(argv));
	write(2, " not a valid identifier\n", 24);
	return (1);	
}

int	builtin_export(t_minish *minish, char **argv)
{
	char	*key;
	int		i;
	int		res;

	i = 0;
	res = 0;
	if (!argv[i])
		res = export_no_args(minish);
	while (argv[i])
	{
		if (!verif_export(argv[i]))
		{
			res = export_invalid_id(argv[i]);
			continue ;
		}
		key = get_key(argv[i]);
		if (!key)
			res = 1;
		if (!change_value(minish->envp, key, argv[i]))
			minish->envp = add_var(minish->envp, argv[i]);
		free(key);
		i++;
	}
	return (res);
}
