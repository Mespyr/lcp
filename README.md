# lcp
### The Lipsem Compiler Project

This is a remake of the [Lipsem programming language](https://github.com/Mespyr/lipsem) as a compiler instead of an interpreter.
Most of the lexer uses code from the [Ach programming language](https://github.com/Mespyr/ach).
*(both of these languages were created by me)*

At this point, the language is almost completely different from Lipsem other than the labels that you can jump to.
It is still very unreadable though.

### Improvements and Changes

- [x] LCP will compile programs down to assembly and use the `fasm` assembler to make an executable. This will make the programs many times faster than the interpreter.
- [x] LCP will have actual string pointers
- [x] labels will be allowed to jump to from anywhere within a function, making control flow easier
- [x] syscalls will be implemented, making the language be able to interact with the operating system
- [x] Basic stack manipulation
- [x] Function arguments and return values
- [x] Type Checking
- [x] have more fancy type notation (using `^` to indicate pointers, making custom types possible)
- [x] add two types of integer (i8, i64) instead of just default `int` keyword. good for string as string type is a `^i8`.
- [x] Structs
	- [x] struct definition
	- [x] struct definition as variable
	- [x] setting and reading struct members
	- [x] compile structs inside of other structs and write structs into them
	- [x] passing structs into functions
	- [x] setting struct variables from other defined structs
- [x] Variables
	- [x] making struct veriables
	- [x] setting variable types to primitive types
	- [x] changing between setting variable form variable on stack and value on stack (a pointer vs the primitive type)
- [ ] allow pushing of different type integers onto the stack (ex: i8, i16, i32, i64)
	- [ ] passing those values into functions with size in mind (you can pass i8, i16, and i32 integers into functions that require i64, but you cant pass i64 into a function with i8)
	- [ ] allow type notation when pushing integers onto the stack (ex: specify that 5 be pushed as an i64 instead of an i8)
- [x] allow modifying values stored at pointers on the stack
	- [x] access members of structs pushed onto the stack
	- [x] write and read values to pointers of primitive types
- [ ] Arrays
- [ ] write code to generate a [prime spiral](https://mathimages.swarthmore.edu/index.php/Prime_spiral_(Ulam_spiral)) also known as a Ulam spiral.
