/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 10:16:10 by agottlie          #+#    #+#             */
/*   Updated: 2019/01/29 12:24:33 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_itoa_dispatcher(long n)
{
	char	*arr;

	if (n == MIN(long))
	{
		arr = (char *)malloc(21);
		return (ft_strcpy(arr, "-9223372036854775808"));
	}
	else if (n == 0)
	{
		arr = (char *)malloc(2);
		return (ft_strcpy(arr, "0"));
	}
	return (NULL);
}

static int	ft_delit(long nbr)
{
	int		i;

	i = 0;
	if (nbr == 0)
		return (1);
	else if (nbr < 0)
	{
		++i;
		nbr *= -1;
	}
	while (nbr > 0)
	{
		++i;
		nbr /= 10;
	}
	return (i);
}

char		*ft_itoa_ll(long n)
{
	char	*new_arr;
	int		len;

	if (n == MIN(long) || n == 0)
		return (ft_itoa_dispatcher(n));
	len = ft_delit(n);
	if ((new_arr = (char *)malloc(len + 1)) == NULL)
		return (NULL);
	new_arr[len] = '\0';
	if (n < 0)
	{
		new_arr[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		new_arr[--len] = n % 10 + '0';
		n /= 10;
	}
	return (new_arr);
}
