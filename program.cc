#include "common-classes.hh"
#include "error-display.hh"
#include "user-options.hh"
#include "icode.hh"
#include "reg-alloc.hh"
#include "symbol-table.hh"
#include "ast.hh"
#include "procedure.hh"
#include "program.hh"

using namespace std;

Program program_object;

Program::Program()
{
	//TODO6
}

Program::~Program()
{
	//TODO6
}

void Program::add_procedure(Procedure * proc, int line)
{
	//TODO6
	
}

void Program::print_sym()
{
	//TODO6
	global_symbol_table.print();
	procedure->print_sym();
}

void Program::print()
{

	//TODO6
	procedure->print();
}

void Program::global_list_in_proc_check()
{

	//TODO6
}

void Program::set_global_table(Symbol_Table & new_global_table)
{
	global_symbol_table = new_global_table;
}

bool Program::variable_in_symbol_list_check(string variable)
{
	return global_symbol_table.variable_in_symbol_list_check(variable);
}

bool Program::variable_proc_name_check(string symbol)
{
	return (procedure->get_proc_name()==symbol);
}	

Symbol_Table_Entry & Program::get_symbol_table_entry(string variable)
{
	return global_symbol_table.get_symbol_table_entry(variable)
}

void Program::compile()
{
	procedure->compile();
}

void Program::delete_all()
{
	delete(procedure);
	global_symbol_table.~Symbol_Table();
}

bool Program::variable_in_proc_map_check(string variable)
{
	
}