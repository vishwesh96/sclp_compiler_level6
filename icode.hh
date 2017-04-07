#ifndef ICODE_HH
#define ICODE_HH

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>

#include"symbol-table.hh"

/* 
	This file defines classes for intermediate form of the code generated 
	by our compiler. It also defined classes for machine instructions.

	An intermediate code (IC) statement consists of an instruction,
	possibly two operands and a result.
*/

typedef enum 
{			/* a: assembly format; r: result; o1: opd1; o2: opd2; op: operator */
	a_op,		/* Only the operator, no operand */
	a_op_o1,	/* Only one operand, no result, eg. goto L */
	a_op_r,		/* Only the result. Operand implicit? */ 
	a_op_r_o1,	/* r <- o1 */
	a_op_o1_r,	/* r <- o1 */
	a_op_r_r_o1,	/* r <- r op o1 */
	a_op_r_o1_o2,	/* r <- o1 op o2 */ 
	a_op_o1_o2_r,	/* r <- o1 op o2 */
	a_op_o1_o2_st,	/*for conditional branch*/
	a_op_st,	/* label instr */
	a_nsy,		/* not specified yet */
	a_op_o1_o2
} Assembly_Format;

typedef enum 
{			/* i: intermediate format; r: result; o1: opd1; o2: opd2; op: operator */
	i_op,		/* Only the operator, no operand */
	i_op_o1,	/* Only one operand, no result, eg. goto L */
	i_r_op,		/* Only the result. Operand implicit? */ 
	i_op_o1_r,    
	i_op_r_o1,    
	i_r_op_o1,	/* r <- o1 */
	i_r_r_op_o1,	/* r <- r op o1 */
	i_r_o1_op_o2,	/* r <- o1 op o2 */
	i_op_o1_o2_st,	/* for conditional branch */
	i_op_st,	/* label instr */
	i_nsy,		/* not specified yet */
	i_o1_op_o2
} Icode_Format;

typedef enum 
{ 
	load, 
	imm_load,
	and_t,
	or_t,
	not_t,
	store, 
	mfc1,
	mtc1,
	mov,
	add, 
	sub,
	mult, 
	divd, 
	uminus,
	load_d, 
	imm_load_d, 
	store_d, 
	mov_d,
	add_d, 
	sub_d, 
	mult_d, 
	div_d, 
	uminus_d,
	slt,
	sle,
	sgt,
	sge,
	sne,
	seq,
	beq,
	bne,
	bgtz,
	bgez,
	bltz,
	blez,
	j,
	label,
	ret_inst,
	nop,
	la,
	imm_add,
	move_d,
	jal,
	syscall,
	seq_d,
	slt_d,
	sle_d,
	bc1t,
	bc1f
} Tgt_Op;

///////////////////////// Instruction Descriptor ///////////////////////////////////

class Instruction_Descriptor
{
	/* 
		This class stores objects representing machine instructions
		which in our case are assembly instructions supported by spim.
	*/

	Tgt_Op inst_op;
	string mnemonic;
	string ic_symbol;       /* symbol for printing in intermediate code */
	string name;
	Icode_Format ic_format; /* format for printing in intemediate code */
	Assembly_Format assem_format;

public:
	Instruction_Descriptor (Tgt_Op op, string name, string mnn, string ics, Icode_Format icf, Assembly_Format af);
	Instruction_Descriptor();
	~Instruction_Descriptor() {}

	Tgt_Op get_op();
	string get_name();
	string get_mnemonic();
	string get_ic_symbol();
	Icode_Format get_ic_format();
	Assembly_Format get_assembly_format();
 
	void print_instruction_descriptor(ostream & file_buffer);
};

///////////////////////////// Icode statement operand ///////////////////////////////////

class Ics_Opd
{	
	/* 
		Abstract base class for ic operands. From this class we 
		derive classes for three kinds of operands: memory addresses, 
		constants, and registers 
	*/

public:
	virtual Register_Descriptor * get_reg();

	/* Operands are printed differently in icode and assembly code */

	virtual void print_ics_opd(ostream & file_buffer) = 0;
	virtual void print_asm_opd(ostream & file_buffer) = 0;
};

class Mem_Addr_Opd:public Ics_Opd
{
	Symbol_Table_Entry * symbol_entry;

public:
	Mem_Addr_Opd(Symbol_Table_Entry & se);
	~Mem_Addr_Opd() {}

	void print_ics_opd(ostream & file_buffer);
	void print_asm_opd(ostream & file_buffer);

	Mem_Addr_Opd & operator= (const Mem_Addr_Opd & rhs);
};

class Register_Addr_Opd: public Ics_Opd
{
	Register_Descriptor * register_description;

public:
	Register_Addr_Opd(Register_Descriptor * rd);
	~Register_Addr_Opd() {}

	Register_Descriptor * get_reg();
	void print_ics_opd(ostream & file_buffer);
	void print_asm_opd(ostream & file_buffer);

	Register_Addr_Opd & operator=(const Register_Addr_Opd & rhs);
};

template <class T>
class Const_Opd: public Ics_Opd
{
	T num;

public:
	Const_Opd (T num);
	~Const_Opd() {}

	void print_ics_opd(ostream & file_buffer);
	void print_asm_opd(ostream & file_buffer);

	Const_Opd & operator=(const Const_Opd & rhs);
};

///////////////////////////////// Intermediate code statements //////////////////////////

class Icode_Stmt
{
	/* 
		Abstract base class for generated ic statements. From this 
		class, we derive three classes: move, compute, control_Flow.
		In this version, we need move sub class only
	*/

protected:
	Instruction_Descriptor op_desc;

public:
	Icode_Stmt() {}
	~Icode_Stmt() {}  

	Instruction_Descriptor & get_op();
	virtual Ics_Opd * get_opd1();
	virtual Ics_Opd * get_opd2();
	virtual Ics_Opd * get_result();

	virtual void set_opd1(Ics_Opd * io);
	virtual void set_opd2(Ics_Opd * io);
	virtual void set_result(Ics_Opd * io);

	virtual void print_icode(ostream & file_buffer) = 0;
	virtual void print_assembly(ostream & file_buffer) = 0;
};

class Move_IC_Stmt: public Icode_Stmt
{ 
	Ics_Opd * opd1;   
	Ics_Opd * result; 

public:
	Move_IC_Stmt(Tgt_Op inst_op, Ics_Opd * opd1, Ics_Opd * result); 
	~Move_IC_Stmt() {} 
	Move_IC_Stmt & operator=(const Move_IC_Stmt & rhs);

	Instruction_Descriptor & get_inst_op_of_ics();

	Ics_Opd * get_opd1();
	void set_opd1(Ics_Opd * io);

	Ics_Opd * get_result();
	void set_result(Ics_Opd * io);

	void print_icode(ostream & file_buffer);
	void print_assembly(ostream & file_buffer);
};


class Compute_IC_Stmt: public Icode_Stmt
{ 
	Ics_Opd * opd1;   
	Ics_Opd * opd2;   
	Ics_Opd * result; 

public:
	Compute_IC_Stmt(Tgt_Op inst_op, Ics_Opd * opd1,  Ics_Opd * opd2, Ics_Opd * result); 
	~Compute_IC_Stmt() {} 
	Compute_IC_Stmt & operator=(const Compute_IC_Stmt & rhs);

	Instruction_Descriptor & get_inst_op_of_ics();

	Ics_Opd * get_opd1();
	Ics_Opd * get_opd2();
	void set_opd1(Ics_Opd * io);
	void set_opd2(Ics_Opd * io);

	Ics_Opd * get_result();
	void set_result(Ics_Opd * io);

	void print_icode(ostream & file_buffer);
	void print_assembly(ostream & file_buffer);
};


class Control_Flow_IC_Stmt: public Icode_Stmt
{ 
	Ics_Opd * opd1;   
	Ics_Opd * opd2;   
	string label;
public:
	Control_Flow_IC_Stmt(Tgt_Op inst_op, Ics_Opd * opd1,  Ics_Opd * opd2, string l); 
	~Control_Flow_IC_Stmt() {} 
	Control_Flow_IC_Stmt & operator=(const Control_Flow_IC_Stmt & rhs);

	Instruction_Descriptor & get_inst_op_of_ics();

	Ics_Opd * get_opd1();
	Ics_Opd * get_opd2();
	string get_label();
	void set_opd1(Ics_Opd * io);
	void set_opd2(Ics_Opd * io);
	void set_label(string l);

	void print_icode(ostream & file_buffer);
	void print_assembly(ostream & file_buffer);
};

class Label_IC_Stmt: public Icode_Stmt
{
        string label;

public:
        Label_IC_Stmt(Tgt_Op inst_op, string l);
        ~Label_IC_Stmt() {}

        Label_IC_Stmt& operator=(const Label_IC_Stmt& rhs);

        Instruction_Descriptor & get_inst_op_of_ics();

        // Ics_Opd * get_opd1();
        // void set_opd1(Ics_Opd * io);

        string get_label();
        void set_label(string l);

        void print_icode(ostream & file_buffer);
        void print_assembly(ostream & file_buffer);
};

class Return_IC_Stmt: public Icode_Stmt
{
	string fname;
public:
        Return_IC_Stmt(Tgt_Op inst_op,string f);
        ~Return_IC_Stmt() {}

        Return_IC_Stmt& operator=(const Return_IC_Stmt& rhs);

        Instruction_Descriptor & get_inst_op_of_ics();

        // Ics_Opd * get_opd();
        // void set_opd(Ics_Opd * io);

        void print_icode(ostream & file_buffer);
        void print_assembly(ostream & file_buffer);
};

class Function_Call_IC_Stmt: public Icode_Stmt
{
	string fname;
public:
        Function_Call_IC_Stmt(Tgt_Op inst_op,string f);
        ~Function_Call_IC_Stmt() {}

        Function_Call_IC_Stmt& operator=(const Return_IC_Stmt& rhs);

        Instruction_Descriptor & get_inst_op_of_ics();

        // Ics_Opd * get_opd();
        // void set_opd(Ics_Opd * io);

        void print_icode(ostream & file_buffer);
        void print_assembly(ostream & file_buffer);
};

class Print_IC_Stmt : public Icode_Stmt
{
	Icode_Stmt * stmt;
	int string_key;
	Data_Type dt;

	public:	
        Print_IC_Stmt(Tgt_Op inst_op,Icode_Stmt * is, Data_Type d);
        Print_IC_Stmt(Tgt_Op inst_op, int s_key);
        ~Print_IC_Stmt() {}

        Print_IC_Stmt& operator=(const Print_IC_Stmt& rhs);

        Instruction_Descriptor & get_inst_op_of_ics();

        Icode_Stmt * get_stmt();
        void set_stmt(Icode_Stmt * io);

        int get_key();
        void set_key(int * k);

        Data_Type get_data_type();
        void set_data_type(Data_Type dt);

        void print_icode(ostream & file_buffer);
        void print_assembly(ostream & file_buffer);

};
//////////////////////// Intermediate code for Ast statements ////////////////////////

class Code_For_Ast
{
	/* 
		This class describes the code generated for a given
		AST in a sequence ast. Note that a single AST would
		in general need multiple statements to implement it.
		We also need to remember the intermediate results of
		an AST because it could be a subtree of a larger AST.
	*/

	list<Icode_Stmt *> ics_list;
	Register_Descriptor * result_register;

public:
	Code_For_Ast();
	Code_For_Ast(list<Icode_Stmt *> & ic_l, Register_Descriptor * reg);
	~Code_For_Ast() {}

	void append_ics(Icode_Stmt & ics);
	list<Icode_Stmt *> & get_icode_list();

	Register_Descriptor * get_reg();
	void set_reg(Register_Descriptor * reg);

	Code_For_Ast & operator=(const Code_For_Ast & rhs);
};

#endif
