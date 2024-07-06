# Interactive C Shell

This project is an implementation of an interactive shell in C, developed as part of an Operating System course. The shell supports various commands and functionalities typical of Unix-like shells.

## Features Implemented

### Basic System Calls

1. **Display Requirement**
   - Displays a shell prompt `<Username@SystemName:~>` showing the current directory.

2. **warp**
   - Changes the current directory.
   - Supports symbols like `~`, `.`, `..`, and `-`.
   - Handles both absolute and relative paths.

3. **peek**
   - Lists files and directories in a specified directory.
   - Supports flags `-a` (all files) and `-l` (detailed info).
   - Handles symbols like `~`, `.`, `..`, and `-`.

4. **pastevents**
   - Stores and retrieves the 15 most recent commands.
   - Supports executing past commands by index.

5. **System commands**
   - Executes other system commands (e.g., `emacs`, `gedit`) in foreground and background processes.

6. **proclore**
   - Displays information about processes spawned by the shell.

7. **seek**
   - Searches for files/directories in a target directory.
   - Supports flags `-d`, `-f`, and `-e`.

8. **I/O Redirection**
   - Supports redirection operators `>`, `>>`, and `<`.

9. **Pipes**
   - Supports piping multiple commands together.

10. **activities**
    - Lists processes spawned by the shell.

11. **Signals**
    - Sends signals to processes (`ping` command).
    - Handles Ctrl-C, Ctrl-D, and Ctrl-Z signals.

12. **fg and bg**
    - Brings background processes to foreground (`fg`).
    - Resumes stopped background processes (`bg`).

13. **Neonate**
    - Prints the PID of the most recently created process at intervals until 'x' is pressed.

### Networking

14. **iMan**
    - Fetches man pages from http://man.he.net/ using sockets.
    - Displays basic command information.

## Usage

### Compilation
Compile the shell using the provided Makefile.


### Commands
Use the implemented commands as described in the specifications document.

## Additional Notes

- The shell handles both interactive and batch modes.
- Error handling is implemented for various scenarios (e.g., file not found, permission denied).
- Memory management practices are followed to prevent memory leaks.

## Credits
This project was developed as part of the Operating System course.

