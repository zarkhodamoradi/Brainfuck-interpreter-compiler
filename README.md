# Brainfuck Language Tools: Interpreter, Compiler, and Optimized Compiler


This repository contains a collection of tools for the Brainfuck programming language, including:

1. **Interpreter**: A Brainfuck interpreter implemented in C++.
2. **Simple Compiler**: A compiler that translates Brainfuck code into C++ code.
3. **Optimized Compiler**: An enhanced compiler that applies optimizations for common Brainfuck patterns.

---

## Features

### Interpreter
- Executes Brainfuck code directly from a file.
- Handles common syntax errors (e.g., unmatched brackets).
- Reports out-of-bounds pointer errors during execution.

### Simple Compiler
- Converts Brainfuck code into readable and executable C++ code.
- Provides basic error handling for unmatched brackets.
- Ensures pointer bounds safety in the generated code.

### Optimized Compiler
- Recognizes and optimizes common Brainfuck patterns, such as loop-based multiplications.
- Generates more efficient C++ code for improved performance.
- Reduces redundant commands by collapsing consecutive operations.

---

## Usage

### Building the Tools
Compile each tool using a C++ compiler such as `g++`:
```bash
# Compile the interpreter
$ g++ -o bf bf.cpp

# Compile the simple compiler
$ g++ -o bfc bfc.cpp

# Compile the optimized compiler
$ g++ -o bfcOpt bfcOpt.cpp
```

### Running the Interpreter
To interpret a Brainfuck program:
```bash
$ ./bf <filename>
```
- Replace `<filename>` with the path to your Brainfuck source file.
- For example if you want to run one of the examples in Example folder you can type: 
```bash
$ ./bf Example/text.bf
``` 
### Using the Simple Compiler
To compile Brainfuck code into C++:
```bash
$ ./bfc -o <output_file> <input_file>
```
- Replace `<input_file>` with the Brainfuck source file.(e.g. text.bf ) 
- Replace `<output_file>` with the desired name of the generated C++ file.(e.g. text.cpp) 

### Using the Optimized Compiler
To compile and optimize Brainfuck code:
```bash
$ ./bfcOpt -o <output_file> <input_file>
```
- Similar to the simple compiler but applies optimization techniques for better performance.

### Compiling the Generated C++ Code
After using one of the compilers, compile the generated C++ code into an executable:
```bash
$ g++ -o bf_program <output_file>
$ ./bf_program
```

---

## Examples

### Sample Brainfuck Code
Hello World:
```brainfuck
++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.
```

### Execution with the Interpreter
```bash
$ echo '++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.' > hello.bf
$ ./bf hello.bf
Hello World!
```

### Compilation with the Optimized Compiler
```bash
$ ./bfcOpt -o hello.cpp hello.bf
$ g++ -o hello hello.cpp
$ ./hello
Hello World!
```

---

## Error Handling

### Interpreter Errors
- **Pointer out of bounds**: Occurs when the pointer moves beyond the allocated tape size.
- **Syntax error**: Reports the location of unmatched brackets or invalid characters.

### Compiler Errors
- **Unmatched brackets**: Prevents compilation if brackets are not properly balanced.
- **File I/O errors**: Reports issues with reading the input file or writing the output file.

---

## Contributing
Contributions are welcome! If you have ideas for additional features or optimizations, feel free to submit a pull request or open an issue.

---

## License
This project is licensed under the MIT License. 


