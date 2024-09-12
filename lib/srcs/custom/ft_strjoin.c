/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:27:53 by nkanaan           #+#    #+#             */
/*   Updated: 2024/07/29 13:56:18 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdarg.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	char	*res;

	len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s1 && *s1)
		res[i++] = *s1++;
	while (s2 && *s2)
		res[i++] = *s2++;
	res[i] = '\0';
	return (res);
}

static size_t total_length(int count, va_list args) {
    size_t len = 0;
    for (int i = 0; i < count; i++) {
        const char *str = va_arg(args, const char *);
        if (str)
            len += strlen(str);
    }
    return len;
}

char *ft_strjoin_n(int count, ...) {
    if (count <= 0)
        return NULL;
    
    va_list args;
    va_start(args, count);

    size_t len = total_length(count, args);
    va_end(args);

    char *result = (char *)malloc(len + 1);
    if (!result)
        return NULL;

    va_start(args, count);
    char *ptr = result;
    for (int i = 0; i < count; i++) {
        const char *str = va_arg(args, const char *);
        if (str) {
            while (*str) {
                *ptr++ = *str++;
            }
        }
    }
    va_end(args);

    *ptr = '\0';

    return result;
}
