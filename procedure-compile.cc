#include "common-classes.hh"
#include "error-display.hh"
#include "user-options.hh"
#include "icode.hh"
#include "reg-alloc.hh"
#include "symbol-table.hh"
#include "ast.hh"
#include "procedure.hh"
#include "program.hh"


void Procedure::compile()
{
	sequence_ast->compile();
}
void Procedure::print_icode(ostream & file_buffer)
{
	
}
void Procedure::print_assembly(ostream & file_buffer)
{

}
void Procedure::print_prologue(ostream & file_buffer)
{

}
void Procedure::print_epilogue(ostream & file_buffer)
{

}