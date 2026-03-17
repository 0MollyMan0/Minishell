/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:22:43 by anfouger          #+#    #+#             */
/*   Updated: 2026/03/17 13:18:35 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	exit_to_many_arg(char *str)
{
	printf("exit: too many arguments\n");
	return (ft_atol(str));
}

static int	exit_no_arg(t_minish *minish)
{
	int	exit_code;

	exit_code = minish->g_exit_status;
	printf("exit\n");
	free_all(minish);
	free_tab(minish->envp);
	exit(exit_code);
	return (0);
}

static int	exit_wrong_arg(t_minish *minish, char *arg)
{
	printf("exit: %s: numeric argument required\n", arg);
	free_all(minish);
	free_tab(minish->envp);
	exit(2);
	return (0);
}

static int	is_code_exit(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_minish *minish, char **argv)
{
	long	arg;

	if (!argv[1])
		return (exit_no_arg(minish));
	if (!is_code_exit(argv[1]) || !verif_max_long(argv[1]))
		return (exit_wrong_arg(minish, argv[1]));
	if (argv[2])
		return (exit_to_many_arg(argv[1]));
	if (is_code_exit(argv[1]) && verif_max_long(argv[1]))
	{
		printf("exit\n");
		arg = ft_atol(argv[1]);
		free_all(minish);
		free_tab(minish->envp);
		exit((unsigned char)arg);
	}
	return (0);
}
