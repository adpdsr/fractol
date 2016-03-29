/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 14:13:55 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/03/16 11:58:16 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freetab(char **tab)
{
	int i;
	int len;

	if (tab)
	{
		if (*tab)
		{
			i = -1;
			len = ft_tablen(tab);
			while (++i < len)
				ft_strdel(&tab[i]);
		}
		free(tab);
		tab = NULL;
	}
}
