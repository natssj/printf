/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-dieg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 17:10:24 by nde-dieg          #+#    #+#             */
/*   Updated: 2026/06/25 17:10:25 by nde-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdint.h>

int		ft_printf(char const *format, ...);
int		print_char(char c);
int		print_string(char *str);
int		print_pointer(void *ptr);
int		print_number(int nbr);
int		ft_intlen(int nbr);
int		ft_unsignedintlen(unsigned int nbr);
int		print_unsigned(unsigned int nbr);
int		print_hexalower(unsigned int nbr);
int		print_hexaupper(unsigned int nbr);
char	ft_hexalowercase(unsigned int nbr);
char	ft_hexauppercase(unsigned int nbr);
int		print_hexapointer(unsigned long nbr);

#endif
