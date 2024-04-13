#ifndef FUNCTIONS_H
#define FUNCTIONS_H

# include "defines.h"

//init
int 	initialize(t_main *shell, char **env);
char	**get_cmd(t_main *shell, char **env);


#endif