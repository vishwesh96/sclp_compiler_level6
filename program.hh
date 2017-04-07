#ifndef PROGRAM_HH
#define PROGRAM_HH

#include <string>

#define GLOB_SPACE "   "

using namespace std;

class Program;

extern Program program_object;

class Program
{
	Symbol_Table global_symbol_table;
	map<string, Procedure*> proc_map;

public:
	Program();
	~Program();
	void delete_all();


	void insert_procedure(Procedure * proc, int line);
	Procedure * get_procedure(string proc_name);
	void set_global_table(Symbol_Table & new_global_table);

	Symbol_Table_Entry & get_symbol_table_entry(string variable);

	void print_sym();
	void print();

	
	bool variable_in_symbol_list_check(string variable);
	void global_list_in_proc_check();
	bool variable_in_proc_map_check(string variable);

	// compile
	void compile();
	void print_assembly();
	void print_icode();
};

#endif
