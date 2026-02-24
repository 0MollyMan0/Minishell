/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_case.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 09:41:16 by anfouger          #+#    #+#             */
/*   Updated: 2026/02/24 10:30:12 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	var_case(char *str, char **new_str, int	*i, int	*i_new)
{
	char	*var;
	int		i_var;

	i_var = 0;
	var = get_var(str, *(&i));
	if (!var)
		*new_str = NULL;
	while (var && var[i_var])
	{
		*new_str = ft_realloc(*new_str, 1);
		if (!*new_str)
			return ;
		*new_str[*i_new] = var[i_var];
		*i_new += 1;
		i_var++;
	}
}
