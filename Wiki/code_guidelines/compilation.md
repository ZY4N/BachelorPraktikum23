# Compilation
## CMake
- For this project `CMake 3.16` is the chosen build system 
## Undefined behavior
- Undefined Behavior is not allowed.
## Compiler flags
- All warnings need to be activated and treated as errors
	- `-Wall -Wextra -pedantic -Werror` 
- For production builds `-Ofast` has to be enabled and has to work flawlessly