/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:40:35 by dioferre          #+#    #+#             */
/*   Updated: 2024/10/22 14:47:00 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	kill_program(t_root *root)
{
	// Properly free everything else
	free (root);
	exit (-1);
}

/* Checks if a string has ONLY digits,
returns 0 if not, 1 if yes */
int	digit_check(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!(str[i] >= '0' && str[i] <= '9'))
			return(0);
	return (1);
}
