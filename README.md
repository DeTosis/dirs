# DIRS

This is a single header, Windows-specific library created to ease the work with directories in c.


_This library is not a production ready and has it own problems, most of wich are known by author, so use it on your own risk_ 

## How to use

1. Copy [`dirs.h`](https://github.com/DeTosis/dirs/blob/master/dirs.h) file into your project.
2.  In **one** source file define `DIRS_IMPLEMENTATION` before including it:
```c
#define DIRS_IMPLEMENTATION
#include "dirs.h"
```
3. In other files you could include it normally:
```c
#include "dirs.h"
```
4. You can also define `DIRS_STRIP_PREFIXES` so you dont need to write dirs_ prefix before each function 
```c
#define DIRS_STRIP_PREFIXES
```

You can find usage examples and explanations in [`dirs.c`](https://github.com/DeTosis/dirs/blob/master/dirs.c)


> This library folows the single-header style popularized by [stb](https://github.com/nothings/stb).

## License

Licence for this project could be viewed [here](https://github.com/DeTosis/dirs/blob/master/LICENSE).
