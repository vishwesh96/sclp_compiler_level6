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
std::map<int, string> string_map;

Program::Program()
{
	//TODO6
}

Program::~Program()
{
	//TODO6
}

void Program::delete_all()
{
	for(map<string, Procedure*>::iterator it = proc_map.begin();it!=proc_map.end();it++){
		delete it->second;
	}
	proc_map.clear();
}

void Program::insert_procedure(Procedure * proc, int line)
{
	//TODO6
	if(proc!=NULL)
	{
		string proc_name = proc->get_proc_name();
		// CHECK_INPUT_AND_ABORT((proc_map.find(proc_name) == proc_map.end()),"Overloading..Procedure already declared",line); // This ideally should not happen
		proc_map[proc_name] = proc;
	}
}

void Program::set_global_table(Symbol_Table & new_global_table)
{
	global_symbol_table = new_global_table;
	global_symbol_table.set_table_scope(global);
}


Symbol_Table_Entry & Program::get_symbol_table_entry(string variable)
{
	return global_symbol_table.get_symbol_table_entry(variable);
}

void Program::print_sym()
{
	//TODO6
	// global_symbol_table.print();
	command_options.create_output_buffer();
  	for(auto it = proc_map.begin();it!=proc_map.end();it++)
	{
		it->second->print(command_options.get_output_buffer());
		cout<<endl;
	}

}

void Program::print()
{

	//TODO6
	// check at last
	command_options.create_ast_buffer();
  	for(auto it = proc_map.begin();it!=proc_map.end();it++)
	{

		it->second->print(command_options.get_ast_buffer());
		
	}

	// fb.close();
}

Procedure * Program::get_procedure(string proc_name)
{
	return proc_map[proc_name];
}


bool Program::variable_in_symbol_list_check(string variable)
{
	return global_symbol_table.variable_in_symbol_list_check(variable);
}

void Program::global_list_in_proc_check()
{
	// check later
	return;
}


bool Program::variable_in_proc_map_check(string variable)
{
	return (proc_map.find(variable) != proc_map.end());
}

