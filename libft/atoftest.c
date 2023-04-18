#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include "libft.h"

int main ()
{
	printf("%f\n",    atof("3.14325235"));
	printf("%f\n", ft_atof("3.14325235"));
	printf("%f\n",    atof("0.314325235"));
	printf("%f\n", ft_atof("0.314325235"));
	printf("%f\n",    atof("3.14325235e4"));
	printf("%f\n", ft_atof("3.14325235e4"));
	printf("%f\n",    atof("3.14325235E4"));
	printf("%f\n", ft_atof("3.14325235E4"));
	printf("%f\n",    atof("3.14325235e-3"));
	printf("%f\n", ft_atof("3.14325235e-3"));
	printf("%f\n",    atof("-3.14325235"));
	printf("%f\n", ft_atof("-3.14325235"));
	printf("%f\n",    atof("+3.14325235"));
	printf("%f\n", ft_atof("+3.14325235"));
	printf("%f\n",    atof("- 3.14325235"));
	printf("%f\n", ft_atof("- 3.14325235"));
	printf("%f\n",    atof("+ 3.14325235"));
	printf("%f\n", ft_atof("+ 3.14325235"));
	printf("%f\n",    atof("   3.14325235"));
	printf("%f\n", ft_atof("   3.14325235"));
	printf("%f\n",    atof("a   3.14325235"));
	printf("%f\n", ft_atof("a   3.14325235"));
	printf("%f\n",    atof("  a3.14325235"));
	printf("%f\n", ft_atof("  a3.14325235"));
	printf("%f\n",    atof("31432"));
	printf("%f\n", ft_atof("31432"));
	printf("%f\n",    atof(".31432"));
	printf("%f\n", ft_atof(".31432"));
	printf("%f\n",    atof("31432."));
	printf("%f\n", ft_atof("31432."));
	printf("%f\n",    atof("31432kkk"));
	printf("%f\n", ft_atof("31432kkk"));
	printf("%f\n",    atof("31432e-3"));
	printf("%f\n", ft_atof("31432e-3"));

	printf("%f\n",    atof("1e22"));
	printf("%f\n", ft_atof("1e22"));
	printf("%f\n",    atof("1e23"));
	printf("%f\n", ft_atof("1e23"));

	printf("%e\n",    atof("1e-20"));
	printf("%e\n", ft_atof("1e-20"));
	printf("%.40f\n",    atof("1e-20"));
	printf("%.40f\n", ft_atof("1e-20"));

	printf("%.400f\n",    atof("1e-323"));
	printf("%.400f\n", ft_atof("1e-323"));

	printf("%f\n",    atof("-"));
	printf("%f\n", ft_atof("-"));
	printf("%f\n",    atof("."));
	printf("%f\n", ft_atof("."));
	printf("%f\n",    atof("+"));
	printf("%f\n", ft_atof("+"));
	printf("%f\n",    atof("-."));
	printf("%f\n", ft_atof("-."));

	printf("%f\n",    atof("a"));
	printf("%f\n", ft_atof("a"));

	printf("%f\n",    atof("3.33a"));
	printf("%f\n", ft_atof("3.33a"));

	printf("\n");

	printf("%d\n", ft_isfloatstr("-"));
	printf("%d\n", ft_isfloatstr("+"));
	printf("%d\n", ft_isfloatstr("."));
	printf("%d\n", ft_isfloatstr("e"));
	printf("%d\n", ft_isfloatstr("E"));
	printf("%d\n", ft_isfloatstr("E-3"));
	printf("%d\n", ft_isfloatstr("a"));
	printf("\n");
	printf("%d\n", ft_isfloatstr("3.33333"));
	printf("%d\n", ft_isfloatstr("-3.33332"));
	printf("%d\n", ft_isfloatstr(".5235"));
	printf("%d\n", ft_isfloatstr("4.5e-4"));
	printf("%d\n", ft_isfloatstr("4E4"));	

	return (0);
}