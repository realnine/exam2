#include <unistd.h> //write
#include <stdarg.h> // va_list

typedef struct s_pf
{
	char *str;
	int rtn;
	int wid;
	int prc;
	char type;
}	t_pf;

void init_flags(t_pf *pf)
{
	pf->wid = 0;
	pf->prc = -1;
	pf->type = '\0';
}

int ft_nbrlen_base(long nbr, int base)
{
	int len;

	len = 0;
	if (nbr < 0)
		nbr *= -1;
	if (nbr >= base)
		len += ft_nbrlen_base(nbr / base, base);
	len++;
	return (len);
}

int ft_putnbr_base(long nbr, int base)
{
	int len;

	len = 0;
	if (nbr < 0)
		nbr *= -1;
	if (nbr >= base)
	{
		len += ft_putnbr_base(nbr / base, base);
		len += ft_putnbr_base(nbr % base, base);
	}
	else
	{
		if (base == 10)
			write(1, &"0123456789"[nbr], 1);
		if (base == 16)
			write(1, &"0123456789abcdef"[nbr], 1);
		len++;
	}
	return len; 
}

// - - - - - - - - - - - - - - - - - - - - -
void	check_flags(t_pf *pf)
{
	char *s;

	s = pf->str + 1;
	while (*s >= '0' && *s <= '9')
		pf->wid = (10 * pf->wid) + (*s++ - '0');

	if (*s == '.')
	{
		pf->prc = 0;
		s++;
		while (*s >= '0' && *s <= '9')
			pf->prc = (10 * pf->prc) + (*s++ - '0');
	}
	
	if (*s == 's' || *s == 'd' || *s == 'x')
		pf->type = *s++;
	pf->str = s;
}

void	print_format(t_pf *pf, va_list ap)
{
	if (pf->type == 's')
	{
		char *s;
		int s_len;

		s = va_arg(ap, char *);
		if (!s)
			s = "(null)";

		s_len = 0;
		while (s[s_len])
			s_len++;

		if (pf->prc == -1 || pf->prc > s_len)
			pf->prc = s_len;

		while (pf->wid-- > pf->prc)
			pf->rtn += write(1, " ", 1);

		while (pf->prc-- > 0)
			pf->rtn += write(1, s++, 1);
	}
	else if (pf->type == 'd' || pf->type == 'x')
	{
		int n_len = 0;
		long nbr = 0;

		if (pf->type == 'd')
		{
			nbr = va_arg(ap, int);
			n_len = ft_nbrlen_base(nbr, 10);
		}
		else if(pf->type == 'x')
		{
			nbr = va_arg(ap, unsigned int);
			n_len = ft_nbrlen_base(nbr, 16);
		}
		
		if (nbr == 0 && pf->prc == 0)
		{
			while (pf->wid-- > pf->prc)
				pf->rtn += write(1, " ", 1);
			return ;
		}

		if (pf->prc < n_len)
			pf->prc = n_len;
		
		if (nbr < 0)
			pf->wid--;

		while (pf->wid-- > pf->prc)
			pf->rtn += write(1, " ", 1);

		if (nbr < 0)
			pf->rtn += write(1, "-", 1);

		while (pf->prc-- > n_len)
			pf->rtn += write(1, "0", 1);
		
		if (pf->type == 'd')
			pf->rtn += ft_putnbr_base(nbr, 10);
		else if (pf->type == 'x')
			pf->rtn += ft_putnbr_base(nbr, 16);
	}
}

void	parse_str(t_pf *pf, va_list ap)
{
	while (*pf->str)
	{
		if (*pf->str == '%')
		{
			init_flags(pf);
			check_flags(pf);
			print_format(pf, ap);
			init_flags(pf);
		}
		else
			pf->rtn += write(1, &*pf->str++, 1);
	}

}

int	ft_printf(char *str, ...)
{
	t_pf pf;
	va_list ap;

	va_start(ap, str);
	pf.rtn = 0;
	pf.str = str;
	parse_str(&pf, ap);
	va_end(ap);
	return (pf.rtn);
}