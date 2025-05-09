/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_more_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:58:12 by aharder           #+#    #+#             */
/*   Updated: 2025/05/09 14:59:03 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	customstrlen2(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *dest, char *src)
{
	char	*joinedstring;
	int		i;
	int		j;
	int		lenstrs;

	i = 0;
	lenstrs = customstrlen2(dest) + customstrlen2(src);
	joinedstring = (char *)malloc(lenstrs * sizeof(char) + 1);
	if (joinedstring == NULL)
		return (NULL);
	while (dest[i] != '\0')
	{
		joinedstring[i] = dest[i];
		i++;
	}
	j = 0;
	while (src[j] != '\0')
	{
		joinedstring[i + j] = src[j];
		j++;
	}
	joinedstring[i + j] = '\0';
	return (joinedstring);
}

char	*ft_strdup(char *src)
{
	char	*dest;
	int		sizestr;
	int		i;

	sizestr = ft_strlen(src);
	dest = malloc((sizestr + 1) * sizeof(*dest));
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
