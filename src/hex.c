/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 16:56:12 by jslave            #+#    #+#             */
/*   Updated: 2020/01/12 16:56:14 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void        transform_hex_format(t_pf *pf)
{
    int i;
    int len;
    char *temp;

    i = 0;
    len = ft_strlen(pf->filling);
    while (pf->filling[i] == ' ')
        i++;
    if (pf->precision == -5 && pf->width && pf->zero_filling && pf->filling[0] == '0' && pf->filling[1] == '0')
        pf->filling[1] = 'x';
    else if (i <= 1 && pf->filling[len -1] != ' ')
        pf->filling = ft_strjoinfree_s2("0x", &pf->filling[i]);///FREEEE
    else if (i <= 1 && pf->filling[len -1] == ' ')
    {
        temp = ft_strnew(len);
        ft_memset(temp, ' ', ft_strlen(temp));
        ft_memcpy(temp,"0x", 2);
        if (pf->filling[len -2] == ' ')
        {
            ft_memcpy(&temp[2], pf->filling, len);
            ft_memcpy(pf->filling, temp, len);
            free(temp);/////////FREEE
        }
        else
        {
            ft_memcpy(&temp[2], pf->filling, len -1);
            free(pf->filling);
            pf->filling = temp;////FREEEE
        }
    }
    else if(i >=2)
    {
        pf->filling[i -2] = '0';
        pf->filling[i-1] = 'x';
    }
    else if ((pf->filling[0] == '0' && pf->filling[1] == '0') || (pf->zero_filling == 0 && pf->width && pf->precision == -5))
        pf->filling[1] = 'x';
}

void        print_int_hex(t_pf *pf)
{
    unsigned long long int num;

    num = ft_atoi_long_long_uns(pf->filling);

    if (pf->precision == -5 && pf->width == 0 && pf->align_left == 0 &&
        (pf->need_sign == 1))
        pf->filling = ft_strjoinfree_s2("+", pf->filling);////FREEEEE
    if (pf->precision != -5)
        handle_int_precision(pf);
    if (pf->width != 0 && pf->precision == -5)
        handle_int_width(pf);
    else if (pf->width != 0 && pf->precision != -5)
        handle_int_width_and_precision(pf);
    if (pf->need_spase == 1)
        handle_int_space(pf);
    if (pf->need_format == 1 && ft_atoi_base(pf->filling, 16) != 0)
        transform_hex_format(pf);
    if (pf->type == 'X')
        upper_symb(pf->filling);
    ft_putstr(pf->filling);
    pf->printed+=ft_strlen(pf->filling);

}
