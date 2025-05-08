/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:37:49 by mfahmi            #+#    #+#             */
/*   Updated: 2024/10/28 10:44:53 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void f(unsigned int index, char *c) {
    if (*c >= 'a' && *c <= 'z') {
        *c -= 32;
    }
}*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*int main ()
{
	char str[] = "the best school ever";
	ft_striteri(str, f);
	printf("%s",str);
}*/
