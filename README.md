# Minishell

A minimal UNIX-like shell that replicates core behaviors of `bash` for learning purposes (processes, pipes, redirections, env, and signals).

## Features
- Interactive prompt, command history (if enabled in your project)
- Execute binaries via absolute/relative path and via `PATH`
- Builtins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Pipes: `cmd1 | cmd2 | cmd3`
- Redirections: `<`, `>`, `>>`
- Heredoc: `<<` (with proper signal behavior)
- Quote handling (`'...'` and `"..."`) and environment expansion (`$VAR`, `$?`)
- Signal handling similar to `bash` (Ctrl-C interrupts, Ctrl-\ behavior, Ctrl-D EOF)

## Getting Started
### Requirements
- `make`
- A C compiler (e.g., `cc`/`clang`/`gcc`)
- Unix-like OS (Linux/macOS)

### Build
```sh
make
```

### Run
```sh
./minishell
```

### Clean
```sh
make clean      # remove objects
make fclean     # remove objects + binary
make re         # full rebuild
```

## Usage
Minishell accepts commands similarly to `bash`:
```sh
minishell$ echo "hello world"
minishell$ ls -la | grep minishell > out.txt
minishell$ cat < out.txt
minishell$ export NAME=world
```

### Builtins (quick notes)
- `cd [dir]` changes directory (supports relative/absolute paths)
- `export KEY=VALUE` sets env vars, `unset KEY` removes them
- `exit [status]` exits the shell with an optional status code

## Project Notes / Behavior
- Exit status follows standard conventions (`$?` is last command status).
- Error messages aim to match `bash` style where applicable.
- Some advanced `bash` features may be intentionally out of scope (`&&/||`, wildcards ).

## Development
Suggested targets/checks:
- Run with `valgrind` (Linux) or `leaks` (macOS) to verify no leaks.
- Add tests for: quotes, expansion edge-cases, heredoc, invalid syntax, and signals.

## Credits
Built as part of the 42 curriculum Minishell project.

