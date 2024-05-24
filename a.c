static void official_executer(t_command *cmds, t_main *shell)
{
	int pipefd[2];
    pid_t pid_ls, pid_wc;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_ls = fork();
    if (pid_ls == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid_ls == 0) {
        // Child process: ls -la
        close(pipefd[0]); // Close unused read end of the pipe
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to the pipe write end
        close(pipefd[1]); // Close the write end of the pipe

        execve(cmds->cmd_and_path, cmds->value, shell->env_for_execve_function); // Execute ls -la
        perror("exec ls");
        exit(EXIT_FAILURE);
    }

    // Parent process
    pid_wc = fork();
    if (pid_wc == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid_wc == 0) {
        // Child process: wc -l
        close(pipefd[1]); // Close unused write end of the pipe
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to the pipe read end
        close(pipefd[0]); // Close the read end of the pipe
		cmds = cmds->next;
        execve(cmds->cmd_and_path, cmds->value, shell->env_for_execve_function); 
        perror("exec wc");
        exit(EXIT_FAILURE);
    }

    // Parent process: Wait for child processes to finish
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid_ls, NULL, 0);
    waitpid(pid_wc, NULL, 0);
}