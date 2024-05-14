# Calculator Verison 1.1

### About the project in general and futur plans

The future idea is to implement alsow integrating technics.

---

### Features

Operations:

- multiplication

- division

- addition

- substraction

Locic:

- Pointoperation before Lineoperations


Note:
Not included are negativ numbers.

---

### How to use

Once you can execute the programm, a title *MATHPROGRAM* should appear on the command line. Then you can give instructions. Type help to get a list of every command and discription. You alsow can find it here in the manual. Currently every input and output is in the command line.

### Send a Calculation

Type: *run:* into the command line and then in the new line the operation, for example *1+1*.

```run:```
```1+1```

After that you should get *RESULT* and on a new line: *2.000000*.

### Exit the programm

Type in the commandline *exit* to exit the programm.

### Math Input

The input can't be bigger than 50 caracters. The calculation can include integers and floats and all operations listed above. The order does not matter the programm will process the points bevore line operations.
```1.1+2*5 = 11.1```

There is alsow the posibility to handel the order by the usere itself. Then every step mus be didictet in the calculation. The program first calculas the inner brackets and then goes from the inside to the outside. For example:

```((1+1)*2)```

This would result in 4. It is alsow posible to set just spesific parts in brakets

```(1+1)*5```

this would result in 10.

---

### All Instruction

| Instruction | Description |
| ------------|-------------|
| help        | prints all avaliable command|
| exit        | exit the program|
| run:        | the next line will be executed as a calculation|
| runTests    | runs all tests to check if the programm is correctly working|
| runexeTest  | runs a calculation test to check if the calculationpart is working|

---

### About the structur and the project

The Project includs two parts. The one part is the string libary and the other one the calculator. The calculator will be split in multiple parts later but for now it is more comfortable to have everything in one file.

The program works everytime with strings. Because the stringlibrary is working on the heap, the work with the stringlibary does not make it very efficient. But this is not the target of the project to make it very efficient. That would something be for the numerical integration but this is futur stuff.

Why always strings?
I beleve that strings are easier when it comes to the mor complicated stuff. The normal way how one would do it today would be to translate the stirng into objects and then build a reverse tree to solve the math problem. But especialy when it comes to calculating with variales I thinks it will be much more difficult to handel all this stuff, especialy when the tree changes because of mathematical optimisations. But I don't know if it is realy easier. A first aproach with creating the problem in objects, can be found on my [Github](https://github.com/laurin-hefti/test-ef5/blob/main/Calcpy). 