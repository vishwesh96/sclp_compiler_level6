#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>

using namespace std;

#include "common-classes.hh"
#include "error-display.hh"
#include "icode.hh"
#include "reg-alloc.hh"
#include "symbol-table.hh"
#include "ast.hh"
#include "program.hh"

/****************************** Class Ics_Opd *****************************/

Register_Descriptor * Ics_Opd::get_reg()
{
	//DONE
	CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, "Error!! Control should not reach here")
}

/****************************** Class Mem_Addr_Opd *****************************/

Mem_Addr_Opd::Mem_Addr_Opd(Symbol_Table_Entry & se) 
{
	//DONE
	symbol_entry = &se;
}

Mem_Addr_Opd & Mem_Addr_Opd::operator=(const Mem_Addr_Opd & rhs)
{
	//DONE	
	Mem_Addr_Opd *m = new Mem_Addr_Opd(*(rhs.symbol_entry));
	return *m;
}

void Mem_Addr_Opd::print_ics_opd(ostream & file_buffer) 
{
	//DONE
	file_buffer << symbol_entry->get_variable_name();

}

void Mem_Addr_Opd::print_asm_opd(ostream & file_buffer) 
{
	Table_Scope symbol_scope = symbol_entry->get_symbol_scope();

	CHECK_INVARIANT(((symbol_scope == local) || (symbol_scope == global) || (symbol_scope == formal)), 
			"Wrong scope value");

	if (symbol_scope == local)
	{
		int offset = symbol_entry->get_start_offset();
		file_buffer << offset << "($sp)";
	}
	if (symbol_scope == formal)
	{
		int offset = symbol_entry->get_start_offset();
		file_buffer << offset << "($fp)";
	}
	else
		file_buffer << symbol_entry->get_variable_name();
}

/****************************** Class Register_Addr_Opd *****************************/

Register_Addr_Opd::Register_Addr_Opd(Register_Descriptor * reg) 
{
	//DONE
	register_description = reg;
}

Register_Descriptor * Register_Addr_Opd::get_reg()    
{ 
	//DONE 
	return register_description;
}

Register_Addr_Opd& Register_Addr_Opd::operator=(const Register_Addr_Opd& rhs)
{
	//DONE
	Register_Addr_Opd *r = new Register_Addr_Opd(rhs.register_description);
	return *r;
}

void Register_Addr_Opd::print_ics_opd(ostream & file_buffer) 
{
	//DONE
	file_buffer << register_description->get_name();
}

void Register_Addr_Opd::print_asm_opd(ostream & file_buffer) 
{
	//TODO
	file_buffer << "$" << register_description->get_name();
}

/****************************** Class Const_Opd *****************************/

template <class DATA_TYPE>
Const_Opd<DATA_TYPE>::Const_Opd(DATA_TYPE n) 
{
	//DONE
	num = n;
}

template <class DATA_TYPE>
Const_Opd<DATA_TYPE> & Const_Opd<DATA_TYPE>::operator=(const Const_Opd<DATA_TYPE> & rhs)
{
	//DONE
	Const_Opd<DATA_TYPE> *c = new Const_Opd<DATA_TYPE>(rhs.num);
	return *c;
}

template <class DATA_TYPE>
void Const_Opd<DATA_TYPE>::print_ics_opd(ostream & file_buffer) 
{
	//DONE
	file_buffer<<num;
}

template <class DATA_TYPE>
void Const_Opd<DATA_TYPE>::print_asm_opd(ostream & file_buffer) 
{
	//DONE
	file_buffer<<num;
}

/****************************** Class Icode_Stmt *****************************/

Instruction_Descriptor & Icode_Stmt::get_op()
{ 
	return op_desc; 
}

Ics_Opd * Icode_Stmt::get_opd1()
{
	CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, "virtual method get_Opd1 not implemented");
}

Ics_Opd * Icode_Stmt::get_opd2()
{
	CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, "virtual method get_Opd2 not implemented");
}

Ics_Opd * Icode_Stmt::get_result()
{
	CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, "virtual method get_Result not implemented");
}

void Icode_Stmt::set_opd1(Ics_Opd * ics_opd)
{
	CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, "virtual method set_Opd1 not implemented");
}

void Icode_Stmt::set_opd2(Ics_Opd * ics_opd)
{
	CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, "virtual method set_Opd2 not implemented");
}

void Icode_Stmt::set_result(Ics_Opd * ics_opd)
{
	CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, "virtual methos set_Result not implemented");
}

/*************************** Class Move_IC_Stmt *****************************/

Move_IC_Stmt::Move_IC_Stmt(Tgt_Op op, Ics_Opd * o1, Ics_Opd * res)
{
	CHECK_INVARIANT((machine_desc_object.spim_instruction_table[op] != NULL),
			"Instruction description in spim table cannot be null");

	op_desc = *(machine_desc_object.spim_instruction_table[op]);
	opd1 = o1;   
	result = res; 
}

Ics_Opd * Move_IC_Stmt::get_opd1()          { return opd1; }
Ics_Opd * Move_IC_Stmt::get_result()        { return result; }

void Move_IC_Stmt::set_opd1(Ics_Opd * io)   { opd1 = io; }
void Move_IC_Stmt::set_result(Ics_Opd * io) { result = io; }

Move_IC_Stmt& Move_IC_Stmt::operator=(const Move_IC_Stmt& rhs)
{
	op_desc = rhs.op_desc;
	opd1 = rhs.opd1;
	result = rhs.result; 

	return *this;
}

void Move_IC_Stmt::print_icode(ostream & file_buffer)
{
	CHECK_INVARIANT (opd1, "Opd1 cannot be NULL for a move IC Stmt");
	CHECK_INVARIANT (result, "Result cannot be NULL for a move IC Stmt");

	string operation_name = op_desc.get_name();

	Icode_Format ic_format = op_desc.get_ic_format();

	switch (ic_format)
	{
	case i_r_op_o1: 
			file_buffer << "\t" << operation_name << ":    \t";
			result->print_ics_opd(file_buffer);
			file_buffer << " <- ";
			opd1->print_ics_opd(file_buffer);
			file_buffer << "\n";

			break; 

	default: CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, 
				"Intermediate code format not supported");
		break;
	}
}

void Move_IC_Stmt::print_assembly(ostream & file_buffer)
{
	CHECK_INVARIANT (opd1, "Opd1 cannot be NULL for a move IC Stmt");
	CHECK_INVARIANT (result, "Result cannot be NULL for a move IC Stmt");
	string op_name = op_desc.get_mnemonic();
	Assembly_Format assem_format = op_desc.get_assembly_format();
	switch (assem_format)
	{
	case a_op_r_o1: 
			file_buffer << "\t" << op_name << " ";
			result->print_asm_opd(file_buffer);
			file_buffer << ", ";
			opd1->print_asm_opd(file_buffer);
			file_buffer << "\n";

			break; 

	case a_op_o1_r: 
			file_buffer << "\t" << op_name << " ";
			opd1->print_asm_opd(file_buffer);
			file_buffer << ", ";
			result->print_asm_opd(file_buffer);
			file_buffer << "\n";

			break; 

	default: CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, "Intermediate code format not supported");
		break;
	}
}


Compute_IC_Stmt::Compute_IC_Stmt(Tgt_Op op, Ics_Opd * o1, Ics_Opd * o2, Ics_Opd * res)
{
	CHECK_INVARIANT((machine_desc_object.spim_instruction_table[op] != NULL),
			"Instruction description in spim table cannot be null");

	op_desc = *(machine_desc_object.spim_instruction_table[op]);
	opd1 = o1;
	opd2 = o2;   
	result = res; 
}


Ics_Opd * Compute_IC_Stmt::get_opd1()          { return opd1; }
Ics_Opd * Compute_IC_Stmt::get_opd2()          { return opd2; }
Ics_Opd * Compute_IC_Stmt::get_result()        { return result; }

void Compute_IC_Stmt::set_opd1(Ics_Opd * io)   { opd1 = io; }
void Compute_IC_Stmt::set_opd2(Ics_Opd * io)   { opd2 = io; }
void Compute_IC_Stmt::set_result(Ics_Opd * io) { result = io; }

Compute_IC_Stmt& Compute_IC_Stmt::operator=(const Compute_IC_Stmt& rhs)
{
	op_desc = rhs.op_desc;
	opd1 = rhs.opd1;
	opd2 = rhs.opd2;
	result = rhs.result; 

	return *this;
}


void Compute_IC_Stmt::print_icode(ostream & file_buffer)
{
	CHECK_INVARIANT (result, "Result cannot be NULL for a compute IC Stmt");

	string operation_name = op_desc.get_name();
	Icode_Format ic_format = op_desc.get_ic_format();

	switch (ic_format)
	{
	case i_r_o1_op_o2: 
			file_buffer << "\t" << operation_name << ":    \t";
			result->print_ics_opd(file_buffer);
			file_buffer << " <- ";
			opd1->print_ics_opd(file_buffer);
			file_buffer << " , ";
			opd2->print_ics_opd(file_buffer);
			file_buffer << "\n";

			break; 

	case i_op_o1_r:
	case i_op_r_o1:    
	case i_r_op_o1:
			file_buffer << "\t" << operation_name << ":    \t";
			result->print_ics_opd(file_buffer);
			file_buffer << " <- ";
			opd1->print_ics_opd(file_buffer);
			file_buffer << "\n";

			break; 

	

	default: CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, 
				"Intermediate code format not supported");
		break;
	}
}

void Compute_IC_Stmt::print_assembly(ostream & file_buffer)
{
	CHECK_INVARIANT (opd1, "Opd1 cannot be NULL for a Compute IC Stmt");
	CHECK_INVARIANT (result, "Result cannot be NULL for a move IC Stmt");
	string op_name = op_desc.get_mnemonic();

	Assembly_Format assem_format = op_desc.get_assembly_format();
	switch (assem_format)
	{
	case a_op_r_o1: 
			file_buffer << "\t" << op_name << " ";
			result->print_asm_opd(file_buffer);
			file_buffer << ", ";
			opd1->print_asm_opd(file_buffer);
			file_buffer << "\n";

			break; 

	case a_op_o1_r: 
			file_buffer << "\t" << op_name << " ";
			opd1->print_asm_opd(file_buffer);
			file_buffer << ", ";
			result->print_asm_opd(file_buffer);
			file_buffer << "\n";

			break;

	case a_op_r_o1_o2:
			file_buffer << "\t" << op_name << " ";
			result->print_asm_opd(file_buffer);
			file_buffer << ", ";
			opd1->print_asm_opd(file_buffer);
			file_buffer << ", ";
			opd2->print_asm_opd(file_buffer);
			file_buffer << "\n";
			break;

	case a_op_o1_o2_r:
			file_buffer << "\t" << op_name << " ";
			opd1->print_asm_opd(file_buffer);
			file_buffer << ", ";
			opd2->print_asm_opd(file_buffer);
			file_buffer << ", ";
			result->print_asm_opd(file_buffer);
			file_buffer << "\n";
			break;


	default: CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, "Intermediate code format not supported");
		break;
	}
}



Control_Flow_IC_Stmt::Control_Flow_IC_Stmt(Tgt_Op op, Ics_Opd * o1, Ics_Opd * o2, string label)
{
	CHECK_INVARIANT((machine_desc_object.spim_instruction_table[op] != NULL),
			"Instruction description in spim table cannot be null");

	op_desc = *(machine_desc_object.spim_instruction_table[op]);
	opd1 = o1;
	opd2 = o2;
	this->label = label;
}

Ics_Opd * Control_Flow_IC_Stmt::get_opd1()          { return opd1; }
Ics_Opd * Control_Flow_IC_Stmt::get_opd2()          { return opd2; }
string Control_Flow_IC_Stmt::get_label()        { return label; }

void Control_Flow_IC_Stmt::set_opd1(Ics_Opd * io)   { opd1 = io; }
void Control_Flow_IC_Stmt::set_opd2(Ics_Opd * io)   { opd2 = io; }
void Control_Flow_IC_Stmt::set_label(string label) { this->label = label; }


Control_Flow_IC_Stmt& Control_Flow_IC_Stmt::operator=(const Control_Flow_IC_Stmt& rhs)
{
	*this = rhs;
	return *this;
}



void Control_Flow_IC_Stmt::print_icode(ostream & file_buffer)
{
	CHECK_INVARIANT (!label.empty(), "label cannot be NULL for a control IC Stmt");

	string operation_name = op_desc.get_name();

	Icode_Format ic_format = op_desc.get_ic_format();
	switch (ic_format)
	{
		case i_op_o1_o2_st:
			file_buffer << "\t" << operation_name << ":    \t";
			opd1->print_ics_opd(file_buffer);
			file_buffer << " , ";
			opd2->print_ics_opd(file_buffer);
			file_buffer << " : goto " + label;
			file_buffer << "\n";
			break;
		case i_op_st :
			file_buffer << "\tgoto " + label;
			file_buffer <<"\n";
			break;
		default: 
			CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH,"Intermediate code format not supported");
			break;
	}
}

void Control_Flow_IC_Stmt::print_assembly(ostream & file_buffer)
{
	CHECK_INVARIANT (!label.empty(), "label cannot be NULL for a control IC Stmt");

	string op_name = op_desc.get_mnemonic();
	Assembly_Format assem_format = op_desc.get_assembly_format();

	switch (assem_format)
	{
		case a_op_o1_o2_st:			
			file_buffer << "\t" << op_name << " ";
			opd1->print_asm_opd(file_buffer);
			file_buffer << ", ";
			opd2->print_asm_opd(file_buffer);
			file_buffer << ", " + label + " ";
			file_buffer << "\n";
			break;
		case a_op_st:
				file_buffer << "\tj " + label;
				file_buffer <<"\n";
				break;
		default:
			CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH,"Intermediate code format not supported");
			break;
	}
}

Label_IC_Stmt::Label_IC_Stmt(Tgt_Op op, string l)
{

	CHECK_INVARIANT((machine_desc_object.spim_instruction_table[op] != NULL),
			"Instruction description in spim table cannot be null");
	op_desc = *(machine_desc_object.spim_instruction_table[op]);
	this->label = l;
}

Label_IC_Stmt& Label_IC_Stmt::operator=(const Label_IC_Stmt& rhs)
{
	*this = rhs;
	return *this;
}

string Label_IC_Stmt::get_label()        { return label; }

void Label_IC_Stmt::set_label(string label) { this->label = label; }


void Label_IC_Stmt::print_icode(ostream & file_buffer)
{
	CHECK_INVARIANT (!label.empty(), "label cannot be NULL for a label IC Stmt");

	// string operation_name = op_desc.get_name();
	Icode_Format ic_format = op_desc.get_ic_format();
	switch (ic_format)
	{
		case i_op_st:
			file_buffer <<"\n" + label + ":    \t";
			file_buffer << "\n";
			break;

		default: 
			CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH,"Intermediate code format not supported");
			break;
	}
}

void Label_IC_Stmt::print_assembly(ostream & file_buffer)
{
	CHECK_INVARIANT (!label.empty(), "label cannot be NULL for a label IC Stmt");

	// string op_name = op_desc.get_mnemonic();
	Assembly_Format assem_format = op_desc.get_assembly_format();

	switch (assem_format)
	{
		case a_op_st:
			file_buffer <<"\n" + label + ":    \t";
			file_buffer << "\n";
			break;

		default: 
			CHECK_INVARIANT(CONTROL_SHOULD_NOT_REACH, "Intermediate code format not supported");
			break;
	}
}



/******************************* Class Code_For_Ast ****************************/

Code_For_Ast::Code_For_Ast()
{
	//DONE
	result_register = NULL; // Check once
	// ics_list = NULL;

}

Code_For_Ast::Code_For_Ast(list<Icode_Stmt *> & ic_l, Register_Descriptor * reg)
{
	//DONE
	ics_list = ic_l;
	result_register = reg;
}

void Code_For_Ast::append_ics(Icode_Stmt & ic_stmt)
{
	//DONE
	ics_list.push_back(&ic_stmt);
}

list<Icode_Stmt *> & Code_For_Ast::get_icode_list()  
{ 
	//DONE 
	return ics_list;
}

Register_Descriptor * Code_For_Ast::get_reg()
{
	//DONE
	return result_register;
}

void Code_For_Ast::set_reg(Register_Descriptor * reg)
{
	//DONE
	result_register = reg;
}

Code_For_Ast& Code_For_Ast::operator=(const Code_For_Ast& rhs)
{
	//DONE
	ics_list = rhs.ics_list;
	result_register = rhs.result_register;
	return *this;
}

/************************ class Instruction_Descriptor ********************************/

Tgt_Op Instruction_Descriptor::get_op()                   	{ return inst_op; }
string Instruction_Descriptor::get_name()                       { return name; }
string Instruction_Descriptor::get_mnemonic()                   { return mnemonic; }
string Instruction_Descriptor::get_ic_symbol()                  { return ic_symbol; }
Icode_Format Instruction_Descriptor::get_ic_format()            { return ic_format; }
Assembly_Format Instruction_Descriptor::get_assembly_format()   { return assem_format; }

Instruction_Descriptor::Instruction_Descriptor (Tgt_Op op, string temp_name, string temp_mnemonic, 
						string ic_sym, Icode_Format ic_form, Assembly_Format as_form)
{
	inst_op = op;
	name = temp_name; 
	mnemonic = temp_mnemonic;
	ic_symbol = ic_sym;
	ic_format = ic_form;
	assem_format = as_form;
}

Instruction_Descriptor::Instruction_Descriptor()
{
	inst_op = nop;
	name = "";
	mnemonic = "";
	ic_symbol = "";
	ic_format = i_nsy;
	assem_format = a_nsy;
}

template class Const_Opd<int>;
template class Const_Opd<double>;


Return_IC_Stmt::Return_IC_Stmt(Tgt_Op op,string f)
{
	CHECK_INVARIANT((machine_desc_object.spim_instruction_table[op] != NULL),
			"Instruction description in spim table cannot be null");
	op_desc = *(machine_desc_object.spim_instruction_table[op]);
	fname = f;
}

Return_IC_Stmt& Return_IC_Stmt::operator=(const Return_IC_Stmt& rhs)
{

}

Instruction_Descriptor & Return_IC_Stmt::get_inst_op_of_ics()
{
	
}

void Return_IC_Stmt::print_icode(ostream & file_buffer)
{
	file_buffer<<"return";
}

void Return_IC_Stmt::print_assembly(ostream & file_buffer)
{
	file_buffer<<"\t"<<"j "<<"epilogue_"<<fname<<endl;
}

Function_Call_IC_Stmt::Function_Call_IC_Stmt(Tgt_Op op,string f)
{
	CHECK_INVARIANT((machine_desc_object.spim_instruction_table[op] != NULL),
			"Instruction description in spim table cannot be null");
	op_desc = *(machine_desc_object.spim_instruction_table[op]);
	fname = f;

}
void Function_Call_IC_Stmt::print_icode(ostream & file_buffer)
{
	file_buffer<<"\t"<<"call "<<fname<<endl;
}

void Function_Call_IC_Stmt::print_assembly(ostream & file_buffer)
{
	file_buffer<<"\t"<<"jal "<<fname<<endl;
}