Project Author:		Oishik Mukhopadhyay

Project Date:		02 June 2018

Project Name:		Universal Turing Machine
			          
	Version: 1.0
					
INTRODUCTION:
------------

This project is to simulate a Universal Turing Machine as dreamt and designed by Sir Alan Turing.
A Universal Turing Machine takes input and produces output on an Input/Output Tape. This tape is ideally infinite.
The machine takes two inputs:

1. Code 'M' representing any Turing Machine [M] (i.e. State Transition Functions).

2. The input 'E' to drive the Machine [M].

After coming to a HALT, the machine will display the internal state as well as the I/O Tape.

USER INSTRUCTIONS:
-----------------

1. 	After cloning or downloading this repo, open up a terminal and use the command:
		`$ chmod +x auto_compile.sh`.
	This grants executable permission to compilation shell script.

2.	Compile both .cpp files easily using the *auto_compile.sh* script:
		`$ ./auto_compile.sh`,
	or, compile them yourself using g++ or a similar C++ compiler. The files are [*code_creator.cpp*](code_creator.cpp) and [*universal_turing_machine.cpp*](universal_turing_machine.cpp)

3.	Create the *code.dat* file using:
		`$ ./code_creator`,
	or using the executable filename you used manually. The Universal Turing Machine reads its State Transition Table from this file. NOTE: If you do not know clearly what a Universal Turing Machine is, [check this](https://en.wikipedia.org/wiki/Universal_Turing_machine).

4.	Run the Turing Machine using:
		`$ ./utm`,
	or using the executable filename you used manually.

5.	You can run the Turing Machine in Verbose mode as well to get Error Messages and State Transitions:
		`$ ./utm -v`

6.	You can use the shell scripts *autorun.sh* and *autorun_verbose.sh* to run the program in non-verbose and verbose modes respectively. Remember, using these scripts will make you create the *code.dat* file each time.
	
7.	To not create the *code.dat* file every time, use the shell scripts *run_utm.sh* and *run_utm_verbose.sh* to run the program in non-verbose and verbose modes respectively. 
