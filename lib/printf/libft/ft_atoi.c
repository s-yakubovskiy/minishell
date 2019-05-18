/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 11:06:22 by agottlie          #+#    #+#             */
/*   Updated: 2018/12/06 08:51:08 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	int					i;
	unsigned long long	res;
	int					sign;

	i = 0;
	res = 0;
	sign = 1;
	if (*str == '\0')
		return (0);
	while (str[i] == ' ' || str[i] == '\v' || str[i] == '\n' || \
		str[i] == '\f' || str[i] == '\t' || str[i] == '\r')
		++i;
	(str[i] == '-') ? sign *= -1 : sign;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + str[i] - 48;
		++i;
	}
	if (res > 9223372036854775807)
	{
		return (sign < 0) ? 0 : -1;
	}
	return ((int)res * sign);
}
