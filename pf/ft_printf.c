#include <stdarg.h>
#include <unistd.h>

typedef struct s_pf
{
    char *src;
    int rtn;
    int wid;
    int prc;
    char type;

}   t_pf;

int ft_strlen(char *str)
{
	int len;

	len = 0;
	if (!str)
		return 0;	
	while (*str++)
		len++;
	return (len);
}

int	ft_nbrlen_base(long nbr, int base) 
{
	int len;

	len = 0;
	if (nbr < 0)
		nbr *= -1;
	if (nbr >= base)
		len += ft_nbrlen_base(nbr / base, base);
	len++;
	return len;
}

int	ft_putnbr_base(long nbr, int base)
{
	int len;

	len = 0;
	if (nbr < 0)
		nbr *= -1;
	if (nbr > base)
	{
		len += ft_putnbr_base(nbr / base, base);
		len += ft_putnbr_base(nbr % base, base);
	}
	else 
	{
		if (base == 10)
			write(1, &"0123456789"[nbr], 1);
		else if (base == 16)
			write(1, &"0123456789abcdef"[nbr], 1);
		len++;
	}
	return (len);	
}

void	print_format(t_pf *pf, va_list ap)
{
	int i;

	if (pf->type == 's')
	{
		char *str;
		int str_len;

		i = 0;
		str = va_arg(ap, char *);
		if (!str)              //프엪의 ... 으로 들어온 char * 포인터의 값이 
			str = "(null)";   //NULL이라면 "(null)"을 출력해야 한다
		str_len = ft_strlen(str);

		if (pf->prc == -1 || pf->prc > str_len)
			pf->prc = str_len;
		while (i++ < pf->wid - pf->prc)
			pf->rtn += write(1, " ", 1);
		i = 0;
		while (i++ < pf->prc)
			pf->rtn += write(1, str++, 1);
	}
	else if (pf->type == 'd' || pf->type == 'x')
	{
		int nbr_len;
		long nbr;         // int 또는 unsigned int가 올거라서 long으로 받음

		nbr = 0; // nbr unused 방지
		if (pf->type == 'd')
		{
			nbr = va_arg(ap, int);
			// unsigned int 자료의 경우 long으로 꺼내도 문제가 없지만
			// int 자료의 경우 MAX_INT + 1, MIN_INT 값울 꺼낼 때 
			// long으로 꺼냈을 때와, int로 꺼냈을 때와 부호값이 다르다
			// 그래서 va_arg(ap, long) 으로 통합을 못한다 
			nbr_len = ft_nbrlen_base(nbr, 10);  // 만약 -42일 때, 길이는 2다 ('-'포함 안함)
		}
		else if (pf->type == 'x')
		{
			nbr = va_arg(ap, unsigned int);  
			nbr_len = ft_nbrlen_base(nbr, 16);
			/*  만약 printf("%x, %x, %x", 42, 0x2a, 052) <= 모두 10진수로 42
	  			이렇게 10,16,8 진수로 들어와도 unsigned int 사이즈로 꺼내어 지고
	 			nbr에 long로 타입 캐스팅 되어 저장된다 */
		}

		//예외 처리 e.g. => printf("[%3.0]", 0);  => [   ]
		if (nbr == 0 && pf->prc == 0)
		{
			i = 0;
			while (i++ < pf->wid)
				pf->rtn += write(1, " ", 1);
			return ;
		}

		// 정밀도가 없거나 숫자길이보다 작으면 그냥 숫자 길이 그대로 출력한다
		if (pf->prc == -1 || pf->prc < nbr_len)
			pf->prc = nbr_len;

		// '-'가 너비 1자리를 차지할 것이기 때문에
		if (nbr < 0)
			pf->wid--;
		
		// 너비 ' ' 출력
		i = 0;
		while (i++ < pf->wid - pf->prc)
			pf->rtn += write(1, " ", 1);

		// 음수일 때 '-' 출력
		if (nbr < 0)
			pf->rtn += write(1, "-", 1);

		// 정밀도 '0' 츨력
		i = 0;
		while (i++ < pf->prc - nbr_len)
			pf->rtn += write(1, "0", 1);

		// 여기서 부터 이제 putnbr()로 출력
		if (pf->type == 'd')
			pf->rtn += ft_putnbr_base(nbr, 10);
		else if (pf->type == 'x')
			pf->rtn += ft_putnbr_base(nbr, 16);
	}
}

void	init_flags(t_pf *pf)
{
	pf->wid = 0;
	pf->prc = -1;
	pf->type = '\0';
}

void	inti_pf(t_pf *pf)
{
	pf->rtn = 0;
	pf->src = NULL;
	init_flags(pf);
}

void	check_flags(t_pf *pf)
{
	char *s;
	
	s = pf->src;
	// 너비 체크
	s++;
	while (*s >= '0' && *s <= '9')
		pf->wid = pf->wid * 10 + (*s++ - '0');
		//printf("wid : %d\n", pf->wid);

	// precision check
	if (*s == '.')
	{
		pf->prc = 0;
		s++;
		while (*s >= '0' && *s <= '9')
			pf->prc = pf->prc * 10 + (*s++ - '0');
	}
		//printf("prc : %d\n", pf->prc);

	// tyep check
	if (*s == 's' || *s == 'd' || *s == 'x')
		pf->type  = *s++;
		//printf("type : %c\n", pf->type);
	pf->src = s;
}

void parse_str(t_pf *pf, va_list ap)
{
	while (*pf->src)
	{
		if (*pf->src == '%')
		{
			check_flags(pf);
			print_format(pf, ap);
			init_flags(pf);
		}
		else
		{
			write(1, pf->src++, 1);
			pf->rtn++;
		}
	}
}

int ft_printf(char *src, ...)
{
	t_pf	pf;
	va_list	ap;

	inti_pf(&pf); // pf->rtn 값이 ft_printf가 끝나도 main안에서 계속 살아있어서 값을 초기화해줌
	va_start(ap, src);
	pf.src = src;
	parse_str(&pf, ap);
	va_end(ap);
	return pf.rtn;
}