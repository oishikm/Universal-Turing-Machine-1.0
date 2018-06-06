/*
*	This program simulates the Universal Turing Machine.
*	The Universal machine takes input from Input Tape and behaves as machine [M],
*	by reading execution code data (transition functions) of [M] from code.dat file. 
*	If code.dat does not exist, the machine will halt abnormally.
*
*	After coming to a HALT, the machine will display the internal State as well as the I/O Tape.
*	
*	Author: Oishik Mukhopadhyay
*	Universal Turing Machine V1.0
*	03 - 04 June 2018
*/

#include<iostream>
#include<fstream>
#include<ctype.h>
#include<stdlib.h>

#define HALT break
#define ERRHALT exit(0)

using namespace std;

typedef struct transition_table_entry_def
{
	int i, j;												// States of q(i) -> q(j)
	char E, D, C;											// Input Symbol, Direction and Changed Symbol
	
	void set_var(char req_str[])							// Sets all variables
	{
		i = 0;
		j = 0;
		
		register int ix, flag = 0;
		/*
			Flag information :
			
			0:	Previous State
			1:	Input Symbol read from I/O Tape
			2:	Next State
			3:	Direction of movement of R/W Head	
			4:	Changed Symbol written to I/O Tape
			
		*/
		
		register char cx;
		
		char str[2];
		
		for (ix = 0; req_str[ix]!='\0'; ix++)
		{
			cx = req_str[ix];
			
			if (isdigit(cx) && (flag == 0 || flag == 2))
			{
				str[0] = cx;
				str[1] = '\0';
				if(flag == 0)	i = i*10 + atoi(str);
				if(flag == 2)	j = j*10 + atoi(str);
			}
			
			else if (cx != ' ')
			{
				if(flag == 1)		E = cx;
				else if(flag == 3)		D = cx;
				else if(flag == 4)		C = cx;
			}
			
			else if (cx == ' ') 	flag++;
		}
	}
} transition_table_entry;


typedef struct transition_table_def
{
	transition_table_entry * table;
	
	void create_table(int n)
	{
		table = (transition_table_entry *)malloc(n * sizeof(transition_table_entry));
		
		if(!table)
		{
			cout << "\nError : Failed to create Transition Table. Halting Abnormally.\n"
				 << "\nERRHALT\n";
			ERRHALT;
		}
	}
	
	void delete_table()
	{
		free(table);
	}
} transition_table;


typedef class universal_turing_machine_def
{
	private:
		int 				state;							// Internal State Governor
		char 				input_tape[100];				// I/O Tape
		char				symbol;							// Current Input Symbol
		int 				n;								// Number of transition functions
		int 				rwhead;							// Location of R/W Head
		int 				halt_state;						// Halting state (if any)
		int					init_state;						// Initial state (default 0)
		ifstream 			fin;
		transition_table	T;								// Set of transition functions
		
		int verbose;										// Flag : Linux option verbose mode '-v'
		
	public:
		universal_turing_machine_def()						// Constructor
		{
			state 			=	0;
			input_tape[0] 	= 	'\0';
			n 				= 	0;
			rwhead 			=	0;
			halt_state		=	-1;
			init_state		=	0;
		}
		
		void set_options(int n, char* option[])
		{
			// Enabling Linux Style option verbose mode '-v'
			if(n > 1 && option[1][1] == 'v') verbose = 1;
		}
		
		void init_read()
		{
			fin.open("code.dat",ios::in);
			if(!fin)
			{
				if(verbose == 1) cout << "\nError : Failed to read code.dat. Halting Abnormally.\n";
				cout << "\nERRHALT\n";
				ERRHALT;
			}
		}
		
		void read_code()
		{
			init_read();
			char buf;
			char bufline[100];
			register int ax;
			fin >> n;
			fin.ignore();									// Newline ignored
			T.create_table(n);
			for(ax = 0; ax < n && !fin.eof(); ax++)
			{
				fin.getline(bufline, 100);
				T.table[ax].set_var(bufline);
			}
			if(ax < n)
			{
				if(verbose == 1) cout << "\nError : Read insufficient data. Halting Abnormally.\n";
				cout << "\nERRHALT\n";
				ERRHALT;
			}
		}
		
		void display_code()
		{
			register int ax;
			cout << "\nRead code from code.dat is :\n";
			for (ax = 0; ax < n; ax++)
			{
				cout << "\n" << T.table[ax].i << " " << T.table[ax].E << " " << T.table[ax].j
					 << " " << T.table[ax].D << " " << T.table[ax].C;
			}
			cout << "\n";
		}
		
		void lookup(char symbol)
		{
			register int ax, flag = 0;
			for(ax = 0; ax < n; ax++)
			{
				if(T.table[ax].i == state && T.table[ax].E == symbol)
				{
					state = T.table[ax].j;
					input_tape[rwhead] = T.table[ax].C;
					if		(T.table[ax].D == 'R' || T.table[ax].D == 'r') rwhead++;
					else if	(T.table[ax].D == 'L' || T.table[ax].D == 'l') rwhead--;
					if(verbose == 1) 
						cout << "\nAt symbol " << symbol << ", State changed from " 
							 << T.table[ax].i << " to " << state << "\n";
					flag = 1;
 					break;
				}
			}
			if(flag == 0)
			{
				if(verbose == 1) cout << "\nError : Transition function not found. Halting Abnormally.\n";
				cout << "\nERRHALT\n";
				ERRHALT;
			}
		}
		
		void run()
		{
			char ch;
			cout << "\nUNIVERSAL TURING MACHINE\nBy - Oishik Mukhopadhyay"
				 << "\n\nIn case of halting problem, press Ctrl+Z or Ctrl+C\n";
			read_code();
			if(verbose == 1) display_code();
			
			cout << "\nDo you want to set a Halting State?"
				 << "\nIf not, machine will run till end of I/O tape.\n[Y/N] : ";
			cin >> ch;
			if(ch == 'y' || ch == 'Y')
			{
				cout << "\nEnter halting state number : ";
				cin >> halt_state;
			}
			
			cout << "\nDo you want to set an Initial State?"
				 << "\nIf not, machine will run from q(0).\n[Y/N] : ";
			cin >> ch;
			if(ch == 'y' || ch == 'Y')
			{
				cout << "\nEnter initial state number : ";
				cin >> init_state;
			}
			
			cout << "\nEnter I/O tape : ";
			cin >> input_tape;
			
			rwhead = 0;
			while(1)
			{
				symbol = input_tape[rwhead];

				if (state == halt_state)
				{
					if(verbose == 1) cout << "\nReached Halting State.\n";
					cout << "\nHALT\n";
					HALT;
				}

				if (symbol == '\0')
				{
					if(verbose == 1) cout << "\nReached end of I/O Tape.\n";
					cout << "\nHALT\n";
					HALT;
				}
				
				lookup(symbol);	
			}
			cout << "\nSTATE : q("<< state << ")\nI/O TAPE : " << input_tape << "\n";
		}
		
		~universal_turing_machine_def()						// Destructor
		{
			T.delete_table();
		}
		
} universal_turing_machine;


int main(int argc, char* argv[])
{
	universal_turing_machine M;
	M.set_options(argc, argv);
	M.run();
	return 0;
}
