/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 15:03:13 by agottlie          #+#    #+#             */
/*   Updated: 2019/02/14 12:33:48 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_solver(int n)
{
	char	*arr;

	if (n == -2147483648)
	{
		arr = (char *)malloc(11);
		return (ft_strcpy(arr, "-2147483648"));
	}
	else if (n == 0)
	{
		arr = (char *)malloc(2);
		return (ft_strcpy(arr, "0"));
	}
	return (NULL);
}

static int	ft_delit(int nbr)
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

char		*ft_itoa(int n)
{
	char	*new_arr;
	int		len;

	if (n == -2147483648 || n == 0)
		return (ft_solver(n));
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
