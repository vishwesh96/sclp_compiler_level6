#include "common-classes.hh"
#include "error-display.hh"
#include "user-options.hh"
#include "icode.hh"
#include "reg-alloc.hh"
#include "symbol-table.hh"
#include "ast.hh"
#include "procedure.hh"
#include "program.hh"

void Program::compile()
{

  	for(auto it = proc_map.begin();it!=proc_map.end();it++)
	{
		it->second->compile();
	}
	print_icode();
	print_assembly();

}

void Program::print_icode()
{
	command_options.create_ic_buffer();
  	for(auto it = proc_map.begin();it!=proc_map.end();it++)
	{
		it->second->print_icode(command_options.get_ic_buffer());
	}
}
void Program::print_assembly()
{

	command_options.create_output_buffer();
	std::ostream & file_buffer = command_options.get_output_buffer();
	file_buffer<<"	.data"<<endl;
	for(auto it = global_symbol_table.get_table().begin();it!=global_symbol_table.get_table().end();it++){
		file_buffer<<(*it)->get_variable_name()<<":	.word 0"<<endl;
	}
  	for(auto it = proc_map.begin();it!=proc_map.end();it++)
	{
		it->second->print_assembly(file_buffer);
	}	
}
