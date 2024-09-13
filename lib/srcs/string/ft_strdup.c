/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:32:40 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/11 08:38:47 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char *ft_strcpy(char *dest, const char *src)
{
    char *start = dest;
    while ((*dest++ = *src++)) ;
    return start;
}

char *ft_strdup(const char *src)
{
    char *dest;
    size_t len = ft_strlen(src);
    if (!(dest = (char *)malloc((len + 1) * sizeof(char))))
        return NULL;
    return ft_strcpy(dest, src);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char		*str_copy;
	size_t		i;

	str_copy = malloc(sizeof(*str_copy) * (n + 1));
	if (!str_copy)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && i < n)
	{
		str_copy[i] = s1[i];
		i++;
	}
	str_copy[i] = '\0';
	return (str_copy);
}
