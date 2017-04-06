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

Procedure::Procedure(Data_Type proc_return_type, string proc_name, int line)
{
	this.return_type = proc_return_type;
	this.name = proc_name;
	this.lineno = line

}

Procedure::~Procedure()
{

}

void Procedure::check_formal_table(Symbol_Table & table)
{
	return;	
}

void Procedure::set_formal_list(Symbol_Table & new_list)
{
	formal_symbol_table = new_list;
	formal_symbol_table.set_table_scope(formal);
	// formal_symbol_table.se

}

bool variable_in_formal_list_check(string variable)
{
	return formal_symbol_table.variable_in_formal_list_check(variable);
}

string Procedure::get_proc_name()
{
	return name;
}


void Procedure::set_sequence_ast(Sequence_Ast & sa)
{
	sequence_ast = &sa;
}

void Procedure::set_local_list(Symbol_Table & new_list)
{
	local_symbol_table = new_list;
	local_symbol_table.set_table_scope(local);
}

Data_Type Procedure::get_return_type()
{
	return return_type;
}


Symbol_Table_Entry & Procedure::get_symbol_table_entry(string variable_name)
{
	if(local_symbol_table.variable_in_symbol_list_check(variable_name))	{
		return local_symbol_table.get_symbol_table_entry(variable_name);
	}
	if(formal_symbol_table.variable_in_formal_list_check(variable_name))	{
		return formal_symbol_table.get_symbol_table_entry(variable_name);
	}

}

void Procedure::print(ostream & file_buffer)
{
	sequence_ast->print(file_buffer);
}

void Procedure::print_sym(ostream & file_buffer)
{
	local_symbol_table.print(file_buffer);
}


bool Procedure::variable_in_symbol_list_check(string variable)
{
	return local_symbol_table.variable_in_symbol_list_check(variable);
}

