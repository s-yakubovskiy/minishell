/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agottlie <agottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 18:14:25 by agottlie          #+#    #+#             */
/*   Updated: 2019/02/02 16:11:13 by agottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*new_arr1;
	unsigned char	*new_arr2;

	new_arr1 = (unsigned char *)s1;
	new_arr2 = (unsigned char *)s2;
	while (*new_arr1 == *new_arr2 && *new_arr1 != '\0')
	{
		++new_arr1;
		++new_arr2;
	}
	return (*new_arr1 - *new_arr2);
}
