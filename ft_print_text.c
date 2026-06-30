/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_text.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-dieg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 13:23:27 by nde-dieg          #+#    #+#             */
/*   Updated: 2026/06/30 13:23:28 by nde-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	print_char(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	print_string(char *str)
{
	if (!str)
		return (ft_putstr_fd("(null)", 1), 6);
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}
