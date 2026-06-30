/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-dieg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 14:33:47 by nde-dieg          #+#    #+#             */
/*   Updated: 2026/06/30 14:33:48 by nde-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

char	ft_hexalowercase(unsigned int nbr)
{
	char	*lower;

	lower = "0123456789abcdef";
	return (lower[nbr]);
}

char	ft_hexauppercase(unsigned int nbr)
{
	char	*upper;

	upper = "0123456789ABCDEF";
	return (upper[nbr]);
}

int	print_hexapointer(unsigned long nbr)
{
	char	word;
	int		len;

	len = 0;
	if (nbr >= 16)
		len = len + print_hexapointer(nbr / 16);
	word = ft_hexalowercase(nbr % 16);
	write(1, &word, 1);
	len++;
	return (len);
}
