/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-dieg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 13:30:01 by nde-dieg          #+#    #+#             */
/*   Updated: 2026/06/30 13:30:02 by nde-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	print_number(int nbr)
{
	ft_putnbr_fd(nbr, 1);
	return (ft_intlen(nbr));
}

int	print_unsigned(unsigned int nbr)
{
	char	c;
	int		len;

	len = ft_unsignedintlen(nbr);
	if (nbr >= 10)
		print_unsigned(nbr / 10);
	c = (nbr % 10) + '0';
	write(1, &c, 1);
	return (len);
}

int	print_hexalower(unsigned int nbr)
{
	char	word;
	int		len;

	len = 0;
	if (nbr >= 16)
		len = len + print_hexalower(nbr / 16);
	word = ft_hexalowercase(nbr % 16);
	write(1, &word, 1);
	len++;
	return (len);
}

int	print_hexaupper(unsigned int nbr)
{
	char	word;
	int		len;

	len = 0;
	if (nbr >= 16)
		len = len + print_hexaupper(nbr / 16);
	word = ft_hexauppercase(nbr % 16);
	write(1, &word, 1);
	len++;
	return (len);
}
