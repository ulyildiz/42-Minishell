# Minishell

A bash-like interactive shell written in C, built around [GNU Readline](https://tiswww.case.edu/php/chet/readline/rltop.html). It reads a command line, tokenizes it, parses it into a pipeline of commands, expands variables, and executes it — implementing a solid subset of POSIX shell behavior from scratch, without calling `system()` or any shell-parsing library.

## Features

- **Interactive prompt** (`ft_sh: `) with line editing and history, via `readline`/`add_history`.
- **Pipelines** — any number of commands chained with `|`.
- **Redirections** — `<` (input), `>` (output, truncate), `>>` (output, append), `<<` (heredoc, with a live sub-prompt and support for variable expansion in the body).
- **Quoting** — single quotes suppress all expansion; double quotes allow `$` expansion while still protecting spaces/metacharacters.
- **Variable expansion** — `$VAR`, `$?` (last exit status), and `~` (home directory) expansion, following the same quoting rules as bash.
- **Environment management** — a real, independent environment list (not just re-exposing `environ`), correctly passed to executed programs.
- **PATH-based command resolution** with bash-accurate errors and exit codes: `command not found` (127), `Permission denied` (126), `is a directory`, `No such file or directory`.
- **Signal handling** matching interactive bash: `Ctrl-C` redraws a fresh prompt on a new line, `Ctrl-\` is ignored at the prompt, `Ctrl-D` on an empty line exits the shell; a heredoc in progress can be interrupted with `Ctrl-C`.
- **Syntax validation** before execution: unmatched quotes, a pipe with nothing before/after it, a redirection with no target, and ambiguous redirects (e.g. an unset/empty variable used as a filename) are all caught and reported without running anything.
- Uses the team's own **libft**.

### Not implemented (out of scope for this project)

This is the mandatory-only part of 42's Minishell subject — there's no bonus module in this repo. That means, unlike bash, it does **not** support:
- Logical operators `&&` / `||`
- Subshells with `(...)`
- Wildcard/glob expansion (`*`)

## Builtins

| Builtin | Behavior |
|---|---|
| `cd [dir]` | No argument → `$HOME`; `cd -` → `$OLDPWD` (printed, like bash); updates `PWD`/`OLDPWD`. |
| `pwd` | Prints the current working directory. |
| `echo [-n] [args...]` | Supports `-n` (and stacked/repeated `-n`/`-nnn` flags) to suppress the trailing newline. |
| `export [NAME[=value] ...]` | With no arguments, prints all exported variables as `declare -x NAME="value"`, sorted; with arguments, validates the identifier and sets/creates the variable. |
| `unset NAME [NAME ...]` | Removes one or more variables from the environment. |
| `env` | Prints the current environment (no flags supported). |
| `exit [n]` | Prints `exit`; with a numeric argument, exits with that code mod 256; rejects non-numeric arguments and more than one argument, matching bash's messages. |

## Build

```bash
make
```

This builds the bundled `42-libft` first, then links `minishell` against it and `libreadline`. You'll need the Readline development headers installed (e.g. `libreadline-dev` on Debian/Ubuntu, or Xcode command line tools on macOS).

```bash
make clean   # remove object files
make fclean  # remove object files, the binary, and the libft archive
make re      # fclean + make
```

## Usage

```bash
./minishell
```

```
ft_sh: export CITY=Kocaeli
ft_sh: echo "hello from $CITY" | cat -e
ft_sh: cat << EOF
> first line
> $CITY
> EOF
ft_sh: echo $?
```

Running the binary with any arguments is rejected (`Too much argument.`) — it's an interactive-only shell.

## Project structure

```
.
├── Makefile
├── 42-libft/                          # Team's own libc-replacement library
├── include/
│   ├── defines.h                       # Core types: tokens, commands, env, shell state
│   └── functions.h                     # Function prototypes
└── src/
    ├── main.c                          # Entry point, env/shell bootstrap
    ├── initialize/                      # Shell + environment initialization
    ├── shell/
    │   ├── shell.c                      # Main read-eval loop (readline + history)
    │   ├── signal/                       # SIGINT/SIGQUIT handling for prompt, exec, heredoc
    │   ├── main_structure/
    │   │   ├── lexer/                     # Command line -> token list
    │   │   ├── parser/                     # Tokens -> linked list of commands (pipeline)
    │   │   ├── expander/                    # $VAR / $? / ~ expansion, quote removal
    │   │   └── executer/                     # Forking, piping, redirections, heredocs, execve
    │   └── builtins/                       # cd, echo, env, exit, export, pwd, unset
    └── utils/                            # Syntax validation, generic helpers, cleanup/exit paths
```

## License

MIT — see [LICENSE](LICENSE).

## Contributors

- [Ulaş Berke Yıldız](https://github.com/ulyildiz)
- [Yunus Emre Saraç](https://github.com/TroubledKezoo1)
