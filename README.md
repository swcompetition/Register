# Register
Pipeline Project - Part Register

Description
-----------
Basically this is just a register part of Pipeline project.<br>
Since this project is developed in C++ and for education purpose, we simply cannot use MIPS RS/RT/RD address in X86_64 system.<br>
So we used this approach:
- Use our own memory<br>
  Actually, it will be implemented as "array" in C++
- Access RS/RT/RD memory address based on our own memory<br>
  This means we need to set some values before parsing MIPS binary-formed assembly
  
For now, this register and all pipeline-related projects will be processing R-Type assembly, called "add".<br>
after that, we will expand more type of instructions, etc.

Basic Flow
-----------
![](https://i.imgur.com/jU1CMQ1.png)
