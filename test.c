<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

# define C_NC		"\033[0m"
# define C_BLOCK	"\033[30m"
# define C_RED		"\033[31m"
# define C_GREEN	"\033[32m"
# define C_YELLOW	"\033[33m"
# define C_BLUE		"\033[34m"
# define C_PURPLE	"\033[35m"
# define C_AQUA		"\033[36m"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
static void	clear_screen(void)
{
	static const char	*CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";

	ft_putstr_fd(CLEAR_SCREEN_ANSI, 1);
}


/**
 * tester exception: heredoc, echo $?, cd
 */
int	main(void)
{
clear_screen();
	ft_putstr_fd("\033[31m*************************\n", 2);
	ft_putstr_fd("******* echo test *******\n", 2);
	ft_putstr_fd("*************************\033[0m\n", 2);
	ft_putstr_fd("\033[33mecho tester\n\033[0m", 2);
	system("echo tester");
	ft_putstr_fd("\033[33mecho $? (on success)\n\033[0m", 2);
	system("echo $?");
	ft_putstr_fd("\033[33mecho '$HOME'\n\033[0m", 2);
	system("echo '$HOME'");
	ft_putstr_fd("\033[33mecho \"$HOME\"\n\033[0m", 2);
	system("echo \"$HOME\"");
getchar();
	// =====================================================================

clear_screen();

	ft_putstr_fd("\033[33mecho \"\'$HOME\'\"\n\033[0m", 2);
	system("echo \"\'$HOME\'\"");
	ft_putstr_fd("\033[33mecho \'\"$HOME\"\'\n\033[0m", 2);
	system("echo \'\"$HOME\"\'");

	ft_putstr_fd("\033[33mecho $\n\033[0m", 2);
	system("echo $");
	ft_putstr_fd("\033[33mecho $??\n\033[0m", 2);
	system("echo $??");
	ft_putstr_fd("\033[33mecho $USER?\n\033[0m", 2);
	system("echo $USER?");
	ft_putstr_fd("\033[33mecho $USER$\n\033[0m", 2);
	system("echo $USER$");
	ft_putstr_fd("\033[33mecho $abc$\n\033[0m", 2);
	system("echo $abc$");
	ft_putstr_fd("\033[33mecho $$\n\033[0m", 2);
	system("echo $$");

getchar();
	// =====================================================================

clear_screen();
	ft_putstr_fd("\033[31m*********************************\n", 2);
	ft_putstr_fd("******* syntax error test *******\n", 2);
	ft_putstr_fd("*********************************\033[0m\n", 2);
	ft_putstr_fd("\033[33mecho echo hi;\n\033[0m", 2);
	system("echo hi;");
	ft_putstr_fd("\033[33mecho echo hi\\\n\033[0m", 2);
	system("echo hi\\");
	ft_putstr_fd("\033[33mecho echo '$HOME';\n\033[0m", 2);
	system("echo '$HOME';");
	ft_putstr_fd("\033[33mecho echo \"$HOME\";\n\033[0m", 2);
	system("echo \"$HOME\";");

getchar();
	// =====================================================================

clear_screen();
	ft_putstr_fd("\033[31m*************************************\n", 2);
	ft_putstr_fd("******* redirect + pipe test *******\n", 2);
	ft_putstr_fd("*************************************\033[0m\n", 2);
	ft_putstr_fd("\033[33m< infile cat \n\033[0m", 2);
	system("< infile cat ");
	ft_putstr_fd("\033[33m< infile cat README.md\n\033[0m", 2);
	system("< infile cat README.md");
getchar();
clear_screen();
	ft_putstr_fd("\033[33m< infile cat README.md Makefile\n\033[0m", 2);
	system("< infile cat README.md Makefile");
getchar();
clear_screen();
	ft_putstr_fd("\033[33m< infile cat | grep i\n\033[0m", 2);
	system("< infile cat | grep i");
	ft_putstr_fd("\033[33m< infile cat | grep i | wc\n\033[0m", 2);
	system("< infile cat | grep i | wc");
	ft_putstr_fd("\033[33m< infile cat | grep i | wc\n\033[0m", 2);
	system("< infile cat | grep i | wc");

	// =====================================================================

	ft_putstr_fd("\033[33m< infile cat | grep i | wc | wc -l\n\033[0m", 2);
	system("< infile cat | grep i | wc | wc -l");

	ft_putstr_fd("\033[33m< infile cat | grep i | wc | wc -l | wc\n\033[0m", 2);
	system("< infile cat | grep i | wc | wc -l | wc");

	ft_putstr_fd("\033[33m< infile cat | grep i | wc | wc -l | wc > outfile\n\033[0m", 2);
	system("< infile cat | grep i | wc | wc -l | wc > outfile");
	ft_putstr_fd("\033[33mcat outfile\n\033[0m", 2);
	system("cat outfile");

getchar();

	// =====================================================================

clear_screen();
	ft_putstr_fd("\033[31m*************************************\n", 2);
	ft_putstr_fd("******* pwd + cd test *******\n", 2);
	ft_putstr_fd("*************************************\033[0m\n", 2);
	ft_putstr_fd("\033[33mpwd\n\033[0m", 2);
	system("pwd");
	ft_putstr_fd("\033[33mcd and pwd\n\033[0m", 2);
	system("cd && pwd");

	// =====================================================================

	ft_putstr_fd("\033[31m*************************************\n", 2);
	ft_putstr_fd("******* env and export and unset test *******\n", 2);
	ft_putstr_fd("*************************************\033[0m\n", 2);
	ft_putstr_fd("\033[33menv\n\033[0m", 2);
	system("env");
getchar();
clear_screen();
	ft_putstr_fd("\033[33mexport\n\033[0m", 2);
	system("export");
getchar();
clear_screen();
	ft_putstr_fd("\033[33mexport a=a and export\n\033[0m", 2);
	system("export a=a && export");
getchar();
clear_screen();
	ft_putstr_fd("\033[33mexport b=bbb c=ccc d=ddd and export\n\033[0m", 2);
	system("export b=bbb c=ccc d=ddd && export");
getchar();

	// =====================================================================

clear_screen();

	ft_putstr_fd("\033[33mexport a=aa and export and unset a and export\n\033[0m", 2);
	system("export a=aa && export && echo && unset a && export");
getchar();
clear_screen();
	ft_putstr_fd("\033[33mexport a=aa b=bb c=cc and export and unset a b c and export\n\033[0m", 2);
	system("export a=aa b=bb c=cc && export && echo && unset a b c && export");


	// =====================================================================


	// =====================================================================


	return (0);
}
=======
int	main()
{
	while (1)
		;
	return (0);
}
>>>>>>> junho3
