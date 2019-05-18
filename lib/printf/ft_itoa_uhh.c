/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_uhh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 10:32:26 by agottlie          #+#    #+#             */
/*   Updated: 2019/02/08 10:41:21 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_itoa_dispatcher(unsigned char n)
{
	char	*arr;

	if (n == 0)
	{
		arr = (char *)malloc(2);
		return (ft_strcpy(arr, "0"));
	}
	return (NULL);
}

static int	ft_delit(unsigned char nbr)
{
	int		i;

	i = 0;
	while (nbr > 0)
	{
		++i;
		nbr /= 10;
	}
	return (i);
}

char		*ft_itoa_uhh(unsigned char n)
{
	char	*new_arr;
	int		len;

	if (n == 0)
		return (ft_itoa_dispatcher(n));
	len = ft_delit(n);
	if ((new_arr = (char *)malloc(len + 1)) == NULL)
		return (NULL);
	new_arr[len] = '\0';
	while (n > 0)
	{
		new_arr[--len] = n % 10 + '0';
		n /= 10;
	}
	return (new_arr);
}
