/*
*	This program generates instruction codes to simulate the Universal Turing Machine.
*	Input all transition functions of format "d(q(i),E) = {q(j)DC}" as "i E j D C"
*	Where i,j are state number, E is input symbol, D is direction (L/R), C is changed value of E.
*	
*	Author: Oishik Mukhopadhyay
*	Code Creator V1.0
*	02 June 2018
*/

#include <fstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

typedef class code_creator_def
{
	private:
		ofstream fout;
		char data_line[50];										// I/O buffer
		
	public:
		code_creator_def()										// Constructor
		{
			strcpy(data_line,"");
		}
		
		void init()
		{
			int n;
			system("clear");
			cout << "\nEnter number of transition functions : ";
			cin >> n;
			init_output();
			fout << n << "\n";
			if(n>0)	input(n); 									// For naughty users with 0 or negative input
		}
		
		void input(int n)
		{
			cout << "\nInput all transition functions of format \"d(q(i),E) = {q(j)DC}\" as \"i E j D C\"\n" 
				 	  << "\nEnter " << n << " transition function(s) :\n";
			int ix;
			cin.ignore();										// For input of previous integer
			for (ix = 0; ix < n; ix++)
			{
				cout << "\nDelta " << ix + 1 << " : ";
				cin.getline(data_line, 50);						// To accomodate spaces
				output(data_line);
			}
			term_output();
		}
		
		void init_output()
		{
			fout.open("code.dat",ios::out);
			if (!fout)											// Null Pointer Exception
			{
				cout << "\nError : Could not generate output file.\nTerminating process.\n";
				exit(0);
			}
		}
		
		void output(char req_str[])
		{
			fout << req_str << "\n";
		}
		
		void term_output()
		{
			fout.close();
			cout << "\nGenerated file code.dat is : \n";
			system("cat code.dat");								// Linux shell
			cout << "\nExiting.\n";
		}
		
		// Destructor defaulted, left to compiler.
		
} code_creator;

int main(int argc, char* argv[])
{
	code_creator obj;
	obj.init();
	return 0;
}
