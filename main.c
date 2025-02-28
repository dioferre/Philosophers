/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:52:20 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/27 14:33:25 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_root	*root;

	root = malloc(sizeof(t_root));
	if (check_parsing(root, argc, argv) == -1);
		return(free(root), -1); //TO DO: Clean up
	setup_root(&root, argc, argv);

}
