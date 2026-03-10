/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstring_PTF.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:42:43 by huburton          #+#    #+#             */
/*   Updated: 2025/04/04 13:56:53 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putstring_ptf(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (ft_putstring_ptf("(null)"));
	while (str[len])
	{
		if (ft_putchar_ptf(str[len]) < 0)
			return (-1);
		len++;
	}
	return (len);
}
