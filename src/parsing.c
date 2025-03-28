/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:04:22 by dioferre          #+#    #+#             */
/*   Updated: 2025/03/28 15:24:48 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	count;

	count = 0;
	while (count < n && (s1[count] != '\0' || s2[count] != '\0'))
	{
		if (s1[count] != s2[count])
			return ((unsigned char)(s1[count]) - (unsigned char)(s2[count]));
		count++;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_parsing(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (-1);
	while (++i < argc)
	{
		if (!argv[i] || !argv[i][0])
			return (-2);
		else if(!digit_check(argv[i]))
			return (-3);
		else if (ft_strlen(argv[i]) > 10
				|| ((ft_strlen(argv[i]) == 10) && (ft_strncmp(argv[i], "2147483647", 10) > 0)))
			return (-4);
	}
	return (0);
}
