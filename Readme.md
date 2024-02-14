# CS2002 W05 Practical (ttable)
## Building ttable
To build the ttable executable run the following from the project root:
```shell
make ttable
```
*__Note:__ The Makefile is relatively symlinked into `src` for compatibility with stacscheck.  
While possible, it is not recommended to build ttable from inside `src` manually*

The executable can then be launched by:
```shell
./ttable <var_count> '<formula in RPN>'
```
## Building memory tests
If you wish to replicate the memory tests from the report run:
```shell
make run_tests
./run_tests
```
*__Note:__ The compiler will generate warnings for using scanf("%c") with no arguments to pause the program, those can be safely ignored*

## Cleaning the project
To remove all compiled files run:
```shell
make clean
```