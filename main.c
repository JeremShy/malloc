/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 15:21:54 by jcamhi            #+#    #+#             */
/*   Updated: 2016/09/07 18:07:38 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <libft.h>

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;

	char *str = ft_strdup("penis");
	char *str2 = ft_strdup("penis2");
	char *str3 = ft_strdup("peniaaaaaaaaaaaaas2");
	printf("%s - %s- %s\n", str, str2, str3);
	return (0);
}
