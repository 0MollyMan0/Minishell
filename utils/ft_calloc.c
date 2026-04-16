/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfouger <anfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:59:37 by anfouger          #+#    #+#             */
/*   Updated: 2026/04/16 15:01:32 by anfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s2;
	size_t			i;

	i = 0;
	s2 = (unsigned char *)s;
	while (i < n)
	{
		s2[i] = c;
		i++;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*res;

	if (nmemb != 0 && nmemb * size / nmemb != size)
		return (NULL);
	if (!nmemb || !size)
		return (malloc(0));
	res = malloc(nmemb * size);
	if (res != NULL)
		ft_memset(res, 0, nmemb * size);
	return (res);
}
