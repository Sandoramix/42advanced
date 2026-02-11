# NM

The nm command is a versatile tool used primarily by developers and system programmers to inspect the symbol table of object files.

It is particularly useful when debugging or trying to understand the inner workings of compiled programs.
The nm command reveals valuable information about the symbols—such as functions and variables—contained in object files, libraries, and executable files.

## Requirements

Base requirements: create the `nm` executable that works as the original.

Work with ELF binaries, handle **x86_32**, **x86_64**, **object files** and _shared\_libraries_ (**\*.so**)

### Mandatory

The program doesn't have to handle the options.

### Bonus

The program has to manage the following options:

|option|extended|description|
|---|---|---|
|`-a`|_(`--debug-syms`)_|Display debugger-only symbols|
|`-g`|_(`--extern-only`)_|Display only external symbols|
|`-u`|_(`--undefined-only`)_|Display only undefined symbols|
|`-r`|_(`--reverse-sort`)_|Reverse the sense of the sort|
|`-p`|_(`--no-sort`)_|Do not sort the symbols|
