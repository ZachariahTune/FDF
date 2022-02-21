#include "fdf.h"

//Вывод символа
static void	ft_putchar(int c, int stdvar)
{
	write(stdvar, &c, 1);
}

//Вывод строки
void	ft_putstr(char *str)
{
	int	i;
	int	stdvar;

	stdvar = 1;
	if (str[0] == 'E' && str[1] == 'r' && str[2] == 'r'
		&& str[3] == 'o' && str[4] == 'r' && str[5] == '\n')
		stdvar = 2;
	if (str == NULL)
		str = "(null)";
	i = 0;
	while (str[i])
	{
		ft_putchar(str[i], stdvar);
		i++;
	}
}

//Вывод ошибок
void	ft_puterror(int code)
{
	if (code < 98)
		ft_putstr("Error: ");
	if (code == 1)
		ft_putstr("Neobhodimo peredat karty parametrom programmy\n");
	if (code == 2)
		ft_putstr("Programma mozhet prinimat tolko odin parametr\n");
	if (code == 3)
		ft_putstr("Ne udalos otkryt file karty\n");
	if (code == 4)
		ft_putstr("Ne udalos videlit pamyat pod kartu\n");
	if (code == 5)
		ft_putstr("Pustaya karta ili oshibka pamyati pri chtenii\n");
	if (code == 6)
		ft_putstr("Nekorrektnaya karta ili oshibka pamyati pri chtenii\n");
	if (code == 7)
		ft_putstr("Ne udalos inicializirovat MLX i videlit pamyat\n");
	if (code == 98)
		ft_putstr("Esc: Vi pokinuli programmu. Prihodite eshe!!!\n");
	if (code == 99)
		ft_putstr("Close: Vi pokinuli programmu. Prihodite eshe!!!\n");
	exit(1);
}
