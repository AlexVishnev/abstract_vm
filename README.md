# abstract_vm

AbstractVM is a machine that uses a stack to compute simple arithmetic expressions.
These arithmetic expressions are provided to the machine as basic assembly programs.


# COMMANDS

• Comments: Comments start with a ’;’ and finish with a newline. A comment can
  be either at the start of a line, or after an instruction.
  
• `push v` : Pushes the value "v" at the top of the stack. Value form:
  
    - int8(n)   : Creates an 8-bit integer with value n;

    - int16(n)  : Creates a 16-bit integer with value n;

    - int32(n)  : Creates a 32-bit integer with value n;

    - float(n)  : Creates a float with value n;

    - double(n) : Creates a double with value n;.

• `pop` : Unstacks the value from the top of the stack. If the stack is empty, the
          program execution must stop with an error.

• `dump`: Displays each value of the stack, from the most recent one to the oldest
          one WITHOUT CHANGING the stack. Each value is separated from the next one
          by a newline.

• `assert v`: Asserts that the value at the top of the stack is equal to the one passed
              as parameter for this instruction. If it is not the case, the program execution must
              stop with an error. The value v has the same form that those passed as parameters
              to the instruction push.

• `add`: Unstacks the first two values on the stack, adds them together and stacks the
        result. If the number of values on the stack is strictly inferior to 2, the program
        execution must stop with an error.

• `sub`:  Unstacks the first two values on the stack, subtracts them, then stacks the
          result. If the number of values on the stack is strictly inferior to 2, the program
          execution must stop with an error.

• `mul`:  Unstacks the first two values on the stack, multiplies them, then stacks the
          result. If the number of values on the stack is strictly inferior to 2, the program
          execution must stop with an error
