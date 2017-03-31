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

}

Program::~Program()
{

}

void Program::set_procedure(Procedure * proc, int line)
{

}

void Program::print_sym()
{

}

void Program::print()
{

}

void Program::global_list_in_proc_check()
{

}

void Program::set_global_table(Symbol_Table & new_global_table)
{

}

bool Program::variable_in_symbol_list_check(string variable)
{

}

bool Program::variable_proc_name_check(string symbol)
{

}

Symbol_Table_Entry & Program::get_symbol_table_entry(string variable)
{

}

void Program::compile()
{

}

void Program::delete_all()
{

}

bool Program::variable_in_proc_map_check(string variable)
{

}