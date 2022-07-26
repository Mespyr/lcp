#include "include/compiler.h"

void compile_to_asm(Program program, std::string output_filename)
{
	static_assert(OP_COUNT == 54, "unhandled op types in compile_to_asm()");

	File outfile(output_filename, FILE_WRITE);

	// boilerplate
	outfile.writeln("format ELF64 executable 3");
	outfile.writeln("segment readable executable");
	outfile.writeln("entry start");

	outfile.writeln("dump:");
	outfile.writeln("\tmov r9, -3689348814741910323");
	outfile.writeln("\tsub rsp, 40");
	outfile.writeln("\tmov BYTE [rsp+31], 10");
	outfile.writeln("\tlea rcx, [rsp+30]");
	outfile.writeln(".L2:");
	outfile.writeln("\tmov rax, rdi");
	outfile.writeln("\tlea r8, [rsp+32]");
	outfile.writeln("\tmul r9");
	outfile.writeln("\tmov rax, rdi");
	outfile.writeln("\tsub r8, rcx");
	outfile.writeln("\tshr rdx, 3");
	outfile.writeln("\tlea rsi, [rdx+rdx*4]");
	outfile.writeln("\tadd rsi, rsi");
	outfile.writeln("\tsub rax, rsi");
	outfile.writeln("\tadd eax, 48");
	outfile.writeln("\tmov BYTE [rcx], al");
	outfile.writeln("\tmov rax, rdi");
	outfile.writeln("\tmov rdi, rdx");
	outfile.writeln("\tmov rdx, rcx");
	outfile.writeln("\tsub rcx, 1");
	outfile.writeln("\tcmp rax, 9");
	outfile.writeln("\tja .L2");
	outfile.writeln("\tlea rax, [rsp+32]");
	outfile.writeln("\tmov edi, 1");
	outfile.writeln("\tsub rdx, rax");
	outfile.writeln("\txor eax, eax");
	outfile.writeln("\tlea rsi, [rsp+32+rdx]");
	outfile.writeln("\tmov rdx, r8");
	outfile.writeln("\tmov rax, 1");
	outfile.writeln("\tsyscall");
	outfile.writeln("\tadd rsp, 40");
	outfile.writeln("\tret");

	std::vector<std::string> strings;

	// compile functions
    for (auto fn_key = program.functions.begin(); fn_key != program.functions.end(); fn_key++)
    {
		// setup function
        Function function = fn_key->second;
		outfile.writeln("; function " + fn_key->first);
		outfile.writeln("func_addr_" + std::to_string(function.addr) + ":");
		outfile.writeln("\tsub rsp, " + std::to_string(function.memory_capacity));
		outfile.writeln("\tmov [ret_stack_rsp], rsp");
		outfile.writeln("\tmov rsp, rax");

		// compile ops
		for (Op op : function.ops)
		{
			// debugging
			if (op.type == OP_DUMP)
			{
				outfile.writeln("\t; OP_DUMP");
				outfile.writeln("\tpop rdi");
				outfile.writeln("\tcall dump");
			}
			
			// arithmetics
			else if (op.type == OP_PLUS)
			{
				outfile.writeln("\t; OP_PLUS");
				outfile.writeln("\tpop rax");
				outfile.writeln("\tpop rbx");
				outfile.writeln("\tadd rbx, rax");
				outfile.writeln("\tpush rbx");
			} 
			else if (op.type == OP_MINUS)
			{
				outfile.writeln("\t; OP_MINUS");
				outfile.writeln("\tpop rax");
				outfile.writeln("\tpop rbx");
				outfile.writeln("\tsub rbx, rax");
				outfile.writeln("\tpush rbx");
			}
			else if (op.type == OP_MUL)
			{
				outfile.writeln("\t; OP_MUL");
				outfile.writeln("\tpop rax");
				outfile.writeln("\tpop rbx");
				outfile.writeln("\tmul rbx");
				outfile.writeln("\tpush rax");
			}
			else if (op.type == OP_DIV)
			{
				outfile.writeln("\t; OP_DIV");
				outfile.writeln("\txor rdx, rdx");
				outfile.writeln("\tpop rbx");
				outfile.writeln("\tpop rax");
				outfile.writeln("\tdiv rbx");
				outfile.writeln("\tpush rax");
				outfile.writeln("\tpush rdx");
			}
		
			// comparisons
			else if (op.type == OP_EQUAL)
			{
				outfile.writeln("\t; OP_EQUAL");
				outfile.writeln("\tmov rcx, 0");
				outfile.writeln("\tmov rdx, 1");
				outfile.writeln("\tpop rax");
				outfile.writeln("\tpop rbx");
				outfile.writeln("\tcmp rax, rbx");
				outfile.writeln("\tcmove rcx, rdx");
				outfile.writeln("\tpush rcx");
			}
			else if (op.type == OP_GREATER)
			{
				outfile.writeln("\t; OP_GREATER");
				outfile.writeln("\tmov rcx, 0");
				outfile.writeln("\tmov rdx, 1");
				outfile.writeln("\tpop rbx");
				outfile.writeln("\tpop rax");
				outfile.writeln("\tcmp rax, rbx");
				outfile.writeln("\tcmovg rcx, rdx");
				outfile.writeln("\tpush rcx");
			}
			else if (op.type == OP_LESS)
			{
				outfile.writeln("\t; OP_LESS");
				outfile.writeln("\tmov rcx, 0");
				outfile.writeln("\tmov rdx, 1");
				outfile.writeln("\tpop rbx");
				outfile.writeln("\tpop rax");
				outfile.writeln("\tcmp rax, rbx");
				outfile.writeln("\tcmovl rcx, rdx");
				outfile.writeln("\tpush rcx");
			}
			else if (op.type == OP_GREATER_EQ)
			{
				outfile.writeln("\t; OP_GREATER_EQ");
				outfile.writeln("\tmov rcx, 0");
				outfile.writeln("\tmov rdx, 1");
				outfile.writeln("\tpop rbx");
				outfile.writeln("\tpop rax");
				outfile.writeln("\tcmp rax, rbx");
				outfile.writeln("\tcmovge rcx, rdx");
				outfile.writeln("\tpush rcx");
			}
			else if (op.type == OP_LESS_EQ)
			{
				outfile.writeln("\t; OP_LESS_EQ");
				outfile.writeln("\tmov rcx, 0");
				outfile.writeln("\tmov rdx, 1");
				outfile.writeln("\tpop rbx");
				outfile.writeln("\tpop rax");
				outfile.writeln("\tcmp rax, rbx");
				outfile.writeln("\tcmovle rcx, rdx");
				outfile.writeln("\tpush rcx");
			}
			else if (op.type == OP_NOT_EQ)
			{
				outfile.writeln("\t; OP_NOT_EQ");
				outfile.writeln("\tmov rcx, 0");
				outfile.writeln("\tmov rdx, 1");
				outfile.writeln("\tpop rbx");
				outfile.writeln("\tpop rax");
				outfile.writeln("\tcmp rax, rbx");
				outfile.writeln("\tcmovne rcx, rdx");
				outfile.writeln("\tpush rcx");
			}
			else if (op.type == OP_NOT)
			{
				outfile.writeln("\t; OP_NOT");
				outfile.writeln("\tpop rax");
				outfile.writeln("\tnot rax");
				outfile.writeln("\tpush rax");
			}
			else if (op.type == OP_AND)
			{
				outfile.writeln("\t; OP_AND");
				outfile.writeln("\tpop rax");
				outfile.writeln("\tpop rbx");
				outfile.writeln("\tand rbx, rax");
				outfile.writeln("\tpush rbx");
			}
			else if (op.type == OP_OR)
			{
				outfile.writeln("\t; OP_OR");
				outfile.writeln("\tpop rax");
				outfile.writeln("\tpop rbx");
				outfile.writeln("\tor rbx, rax");
				outfile.writeln("\tpush rbx");
			}

			// stack manipulation
			else if (op.type == OP_POP)
			{
				outfile.writeln("\t; OP_POP");
				outfile.writeln("\tpop rax");
			}
			else if (op.type == OP_DUP)
			{
				outfile.writeln("\t; OP_DUP");
				outfile.writeln("\tpop rax");
				outfile.writeln("\tpush rax");
				outfile.writeln("\tpush rax");
			}
			else if (op.type == OP_SWP)
			{
				outfile.writeln("\t; OP_SWP");
				outfile.writeln("\tpop rax");
				outfile.writeln("\tpop rbx");
				outfile.writeln("\tpush rax");
				outfile.writeln("\tpush rbx");
			}
			else if (op.type == OP_ROT)
			{
				outfile.writeln("\t; OP_ROT");
				outfile.writeln("\tpop rax");
				outfile.writeln("\tpop rbx");
				outfile.writeln("\tpop rcx");
				outfile.writeln("\tpush rbx");
				outfile.writeln("\tpush rax");
				outfile.writeln("\tpush rcx");
			}
			else if (op.type == OP_OVER)
			{
				outfile.writeln("\t; OP_OVER");
				outfile.writeln("\tpop rax");
				outfile.writeln("\tpop rbx");
				outfile.writeln("\tpush rbx");
				outfile.writeln("\tpush rax");
				outfile.writeln("\tpush rbx");
			}

			// variables
			else if (op.type == OP_SET_VAR)
			{
				static_assert(MODE_COUNT == 3, "unhandled OpCodeModes in compile_to_asm()");
				outfile.writeln("\t; OP_SET_VAR " + op.str_operand + " offset:" + std::to_string(op.int_operand) + " size:" + std::to_string(op.int_operand_2));
				if (op.is_prim_type_mode())
				{
					outfile.writeln("\tpop rbx");
					outfile.writeln("\tmov rax, [ret_stack_rsp]");
					outfile.writeln("\tadd rax, " + std::to_string(op.int_operand));

					if (op.mode == MODE_8BIT)
						outfile.writeln("\tmov [rax], bl");
					else if (op.mode == MODE_64BIT)
						outfile.writeln("\tmov [rax], rbx");
				}
				else if (op.mode == MODE_STRUCT)
				{
					outfile.writeln("\tpop rbx");
					// get pointer to struct
					outfile.writeln("\tmov rax, [ret_stack_rsp]");
					outfile.writeln("\tadd rax, " + std::to_string(op.int_operand));
					outfile.writeln("\tmov rcx, [rbx]");
					outfile.writeln("\tmov [rax], rcx");
					for (int i = 8; i < op.int_operand_2; i+=8)
					{
						outfile.writeln("\tadd rax, 8");
						outfile.writeln("\tadd rbx, 8");
						outfile.writeln("\tmov rcx, [rbx]");
						outfile.writeln("\tmov [rax], rcx");
					}
				}
			}
			else if (op.type == OP_SET_VAR_FROM_OTHER_PTR)
			{
				static_assert(MODE_COUNT == 3, "unhandled OpCodeModes in compile_to_asm()");
				// rbx is the pointer we are setting the variable to
				// rax is the pointer to the variable
				outfile.writeln("\t; OP_SET_VAR_FROM_OTHER_PTR " + op.str_operand + " offset:" + std::to_string(op.int_operand) + " size:" + std::to_string(op.int_operand_2));
				outfile.writeln("\tpop rbx");
				outfile.writeln("\tmov rax, [ret_stack_rsp]");
				outfile.writeln("\tadd rax, " + std::to_string(op.int_operand));
				if (op.mode == MODE_8BIT)
				{
					outfile.writeln("\tmov cl, [rbx]");
					outfile.writeln("\tmov [rax], cl");
				}
				else if (op.mode == MODE_64BIT)
				{
					outfile.writeln("\tmov rcx, [rbx]");
					outfile.writeln("\tmov [rax], rcx");
				}
			}
			else if (op.type == OP_SET_VAR_STRUCT_MEMBER)
			{
				static_assert(MODE_COUNT == 3, "unhandled OpCodeModes in compile_to_asm()");
				outfile.writeln("\t; OP_SET_VAR_STRUCT_MEMBER " + op.str_operand + " offset:" + std::to_string(op.int_operand) + " size:" + std::to_string(op.int_operand_2));
				outfile.writeln("\tpop rbx");
				outfile.writeln("\tmov rax, [ret_stack_rsp]");
				outfile.writeln("\tadd rax, " + std::to_string(op.int_operand));
				if (op.mode == MODE_8BIT)
					outfile.writeln("\tmov [rax], bl");
				else if (op.mode == MODE_64BIT)
					outfile.writeln("\tmov [rax], rbx");
				else if (op.mode == MODE_STRUCT)
				{
					outfile.writeln("\tmov rcx, [rbx]");
					outfile.writeln("\tmov [rax], rcx");
					for (int i = 8; i < op.int_operand_2; i+=8)
					{
						outfile.writeln("\tadd rax, 8");
						outfile.writeln("\tadd rbx, 8");
						outfile.writeln("\tmov rcx, [rbx]");
						outfile.writeln("\tmov [rax], rcx");
					}
				}
			}
			else if (op.type == OP_READ_VAR)
			{
				static_assert(MODE_COUNT == 3, "unhandled OpCodeModes in compile_to_asm()");
				outfile.writeln("\t; OP_READ_VAR " + op.str_operand + " offset:" + std::to_string(op.int_operand));
				outfile.writeln("\tmov rax, [ret_stack_rsp]");
				outfile.writeln("\tadd rax, " + std::to_string(op.int_operand));
				outfile.writeln("\txor rbx, rbx");
				if (op.mode == MODE_8BIT)
					outfile.writeln("\tmov bl, [rax]");
				else if (op.mode == MODE_64BIT)
					outfile.writeln("\tmov rbx, [rax]");
				outfile.writeln("\tpush rbx");
			}
			else if (op.type == OP_READ_VAR_STRUCT_MEMBER)
			{
				static_assert(MODE_COUNT == 3, "unhandled OpCodeModes in compile_to_asm()");
				outfile.writeln("\t; OP_READ_VAR_STRUCT_MEMBER " + op.str_operand + " offset:" + std::to_string(op.int_operand) + " size:" + std::to_string(op.int_operand_2));
				outfile.writeln("\tmov rax, [ret_stack_rsp]");
				outfile.writeln("\tadd rax, " + std::to_string(op.int_operand));
				if (op.mode == MODE_STRUCT)
					outfile.writeln("\tpush rax");
				else
				{
					outfile.writeln("\txor rbx, rbx");
					if (op.mode == MODE_8BIT)
						outfile.writeln("\tmov bl, [rax]");
					else if (op.mode == MODE_64BIT)
						outfile.writeln("\tmov rbx, [rax]");
					outfile.writeln("\tpush rbx");
				}
			}
			else if (op.type == OP_PUSH_VAR)
			{
				outfile.writeln("\t; OP_PUSH_VAR " + op.str_operand + " offset:" + std::to_string(op.int_operand));
				outfile.writeln("\tmov rax, [ret_stack_rsp]");
				outfile.writeln("\tadd rax, " + std::to_string(op.int_operand));
				outfile.writeln("\tpush rax");
			}
			// variable pointers
			else if (op.type == OP_SET_PTR)
			{
				static_assert(MODE_COUNT == 3, "unhandled OpCodeModes in compile_to_asm()");
				outfile.writeln("\t; OP_SET_PTR " + op.str_operand + " size:" + std::to_string(op.int_operand));
				outfile.writeln("\tpop rax");
				outfile.writeln("\tpop rbx");
				if (op.is_prim_type_mode())
				{
					if (op.mode == MODE_8BIT)
						outfile.writeln("\tmov [rax], bl");
					else if (op.mode == MODE_64BIT)
						outfile.writeln("\tmov [rax], rbx");
				}
				else if (op.mode == MODE_STRUCT)
				{
					// get pointer to struct
					outfile.writeln("\tmov rcx, [rbx]");
					outfile.writeln("\tmov [rax], rcx");
					for (int i = 8; i < op.int_operand; i+=8)
					{
						outfile.writeln("\tadd rax, 8");
						outfile.writeln("\tadd rbx, 8");
						outfile.writeln("\tmov rcx, [rbx]");
						outfile.writeln("\tmov [rax], rcx");
					}
				}
			}
			else if (op.type == OP_SET_PTR_FROM_OTHER_PTR)
			{
				static_assert(MODE_COUNT == 3, "unhandled OpCodeModes in compile_to_asm()");
				// rax is the pointer to the variable
				// rbx is the pointer we are setting the ptr to
				outfile.writeln("\t; OP_SET_PTR_FROM_OTHER_PTR " + op.str_operand + " size:" + std::to_string(op.int_operand));
				outfile.writeln("\tpop rax");
				outfile.writeln("\tpop rbx");
				if (op.mode == MODE_8BIT)
				{
					outfile.writeln("\tmov cl, [rbx]");
					outfile.writeln("\tmov [rax], cl");
				}
				else if (op.mode == MODE_64BIT)
				{
					outfile.writeln("\tmov rcx, [rbx]");
					outfile.writeln("\tmov [rax], rcx");
				}
			}
			else if (op.type == OP_SET_PTR_STRUCT_MEMBER)
			{
				static_assert(MODE_COUNT == 3, "unhandled OpCodeModes in compile_to_asm()");
				outfile.writeln("\t; OP_SET_PTR_STRUCT_MEMBER " + op.str_operand + " relative-offset:" + std::to_string(op.int_operand) + " size:" + std::to_string(op.int_operand_2));
				outfile.writeln("\tpop rax");
				outfile.writeln("\tadd rax, " + std::to_string(op.int_operand));
				outfile.writeln("\tpop rbx");
				if (op.mode == MODE_8BIT)
					outfile.writeln("\tmov [rax], bl");
				else if (op.mode == MODE_64BIT)
					outfile.writeln("\tmov [rax], rbx");
				else if (op.mode == MODE_STRUCT)
				{
					outfile.writeln("\tmov rcx, [rbx]");
					outfile.writeln("\tmov [rax], rcx");
					for (int i = 8; i < op.int_operand_2; i+=8)
					{
						outfile.writeln("\tadd rax, 8");
						outfile.writeln("\tadd rbx, 8");
						outfile.writeln("\tmov rcx, [rbx]");
						outfile.writeln("\tmov [rax], rcx");
					}
				}
			}
			else if (op.type == OP_READ_PTR)
			{
				static_assert(MODE_COUNT == 3, "unhandled OpCodeModes in compile_to_asm()");
				outfile.writeln("\t; OP_READ_PTR");
				outfile.writeln("\tpop rax");
				outfile.writeln("\txor rbx, rbx");
				if (op.mode == MODE_8BIT)
					outfile.writeln("\tmov bl, [rax]");
				else if (op.mode == MODE_64BIT)
					outfile.writeln("\tmov rbx, [rax]");
				outfile.writeln("\tpush rbx");
			}
			else if (op.type == OP_READ_PTR_STRUCT_MEMBER)
			{
				static_assert(MODE_COUNT == 3, "unhandled OpCodeModes in compile_to_asm()");
				outfile.writeln("\t; OP_READ_PTR_STRUCT_MEMBER relative-offset:" + std::to_string(op.int_operand) + " size:" + std::to_string(op.int_operand_2));
				outfile.writeln("\tpop rax");
				outfile.writeln("\tadd rax, " + std::to_string(op.int_operand));
				if (op.mode == MODE_STRUCT)
					outfile.writeln("\tpush rax");
				else
				{
					outfile.writeln("\txor rbx, rbx");
					if (op.mode == MODE_8BIT)
						outfile.writeln("\tmov bl, [rax]");
					else if (op.mode == MODE_64BIT)
						outfile.writeln("\tmov rbx, [rax]");
					outfile.writeln("\tpush rbx");
				}
			}

			// syscalls
			else if (op.type == OP_SYSCALL0)
			{
				outfile.writeln("\t; OP_SYSCALL0");
				outfile.writeln("\tpop rax");
				outfile.writeln("\tsyscall");
				outfile.writeln("\tpush rax");
			}
			else if (op.type == OP_SYSCALL1)
			{
				outfile.writeln("\t; OP_SYSCALL1");
				outfile.writeln("\tpop rax");
				outfile.writeln("\tpop rdi");
				outfile.writeln("\tsyscall");
				outfile.writeln("\tpush rax");
			}
			else if (op.type == OP_SYSCALL2)
			{
				outfile.writeln("\t; OP_SYSCALL2");
				outfile.writeln("\tpop rax");
				outfile.writeln("\tpop rdi");
				outfile.writeln("\tpop rsi");
				outfile.writeln("\tsyscall");
				outfile.writeln("\tpush rax");
			}
			else if (op.type == OP_SYSCALL3)
			{
				outfile.writeln("\t; OP_SYSCALL3");
				outfile.writeln("\tpop rax");
				outfile.writeln("\tpop rdi");
				outfile.writeln("\tpop rsi");
				outfile.writeln("\tpop rdx");
				outfile.writeln("\tsyscall");
				outfile.writeln("\tpush rax");
			}
			else if (op.type == OP_SYSCALL4)
			{
				outfile.writeln("\t; OP_SYSCALL4");
				outfile.writeln("\tpop rax");
				outfile.writeln("\tpop rdi");
				outfile.writeln("\tpop rsi");
				outfile.writeln("\tpop rdx");
				outfile.writeln("\tpop r10");
				outfile.writeln("\tsyscall");
				outfile.writeln("\tpush rax");
			}
			else if (op.type == OP_SYSCALL5)
			{
				outfile.writeln("\t; OP_SYSCALL5");
				outfile.writeln("\tpop rax");
				outfile.writeln("\tpop rdi");
				outfile.writeln("\tpop rsi");
				outfile.writeln("\tpop rdx");
				outfile.writeln("\tpop r10");
				outfile.writeln("\tpop r8");
				outfile.writeln("\tsyscall");
				outfile.writeln("\tpush rax");
			}
			else if (op.type == OP_SYSCALL6)
			{
				outfile.writeln("\t; OP_SYSCALL6");
				outfile.writeln("\tpop rax");
				outfile.writeln("\tpop rdi");
				outfile.writeln("\tpop rsi");
				outfile.writeln("\tpop rdx");
				outfile.writeln("\tpop r10");
				outfile.writeln("\tpop r8");
				outfile.writeln("\tpop r9");
				outfile.writeln("\tsyscall");
				outfile.writeln("\tpush rax");
			}

			// labels
			else if (op.type == OP_LABEL)
			{
				outfile.writeln("\t; OP_LABEL " + op.str_operand + " index:" + std::to_string(op.int_operand));
				// addr_(function_addr)_(index_in_code):
				outfile.writeln("\taddr_" + std::to_string(function.addr) + "_" + std::to_string(op.int_operand) + ":");
			}
			else if (op.type == OP_LABEL_END)
			{
				outfile.writeln("\t; OP_LABEL_END " + op.str_operand + " index:" + std::to_string(op.int_operand));
				outfile.writeln("\taddr_" + std::to_string(function.addr) + "_" + std::to_string(op.int_operand) + ":");
			}
			else if (op.type == OP_JMP)
			{
				outfile.writeln("\t; OP_JMP " + op.str_operand + " index:" + std::to_string(op.int_operand));
				outfile.writeln("\tjmp addr_" + std::to_string(function.addr) + "_" + std::to_string(op.int_operand));
			}
			else if (op.type == OP_CJMPT)
			{
				outfile.writeln("\t; OP_CJMPT " + op.str_operand + " index:" + std::to_string(op.int_operand));
				outfile.writeln("\tpop rax");
				outfile.writeln("\ttest rax, rax");
				outfile.writeln("\tjnz addr_" + std::to_string(function.addr) + "_" + std::to_string(op.int_operand));
			}
			else if (op.type == OP_CJMPF)
			{
				outfile.writeln("\t; OP_CJMPF " + op.str_operand + " index:" + std::to_string(op.int_operand));
				outfile.writeln("\tpop rax");
				outfile.writeln("\ttest rax, rax");
				outfile.writeln("\tjz addr_" + std::to_string(function.addr) + "_" + std::to_string(op.int_operand));
			}
			else if (op.type == OP_JMPE)
			{
				outfile.writeln("\t; OP_JMPE " + op.str_operand + " index:" + std::to_string(op.int_operand));
				outfile.writeln("\tjmp addr_" + std::to_string(function.addr) + "_" + std::to_string(op.int_operand));
			}
			else if (op.type == OP_CJMPET)
			{
				outfile.writeln("\t; OP_CJMPET " + op.str_operand + " index:" + std::to_string(op.int_operand));
				outfile.writeln("\tpop rax");
				outfile.writeln("\ttest rax, rax");
				outfile.writeln("\tjnz addr_" + std::to_string(function.addr) + "_" + std::to_string(op.int_operand));
			}
			else if (op.type == OP_CJMPEF)
			{
				outfile.writeln("\t; OP_CJMPEF " + op.str_operand + " index:" + std::to_string(op.int_operand));
				outfile.writeln("\tpop rax");
				outfile.writeln("\ttest rax, rax");
				outfile.writeln("\tjz addr_" + std::to_string(function.addr) + "_" + std::to_string(op.int_operand));
			}

			// other
			else if (op.type == OP_PUSH_INT)
			{
                outfile.writeln("\t; OP_PUSH_INT " + std::to_string(op.int_operand));
				outfile.writeln("\tmov rax, " + std::to_string(op.int_operand));
				outfile.writeln("\tpush rax");
			}
			else if (op.type == OP_PUSH_STR)
			{
				strings.push_back(op.str_operand);
				outfile.writeln("\t; OP_PUSH_STR size:" + std::to_string(op.str_operand.length()));
				outfile.writeln("\tmov rax, " + std::to_string(op.str_operand.length()));
				outfile.writeln("\tpush rax");
				outfile.writeln("\tpush str_" + std::to_string(strings.size()-1));
			}
			else if (op.type == OP_FUNCTION_CALL)
            {
                outfile.writeln("\t; OP_FUNCTION_CALL " + op.str_operand);
                outfile.writeln("\tmov rax, rsp");
                outfile.writeln("\tmov rsp, [ret_stack_rsp]");
                outfile.writeln("\tcall func_addr_" + std::to_string(program.functions.at(op.str_operand).addr));
                outfile.writeln("\tmov [ret_stack_rsp], rsp");
                outfile.writeln("\tmov rsp, rax");
            }
		}

		// end function
		outfile.writeln("\t; return");
		outfile.writeln("\tmov rax, rsp");
		outfile.writeln("\tmov rsp, [ret_stack_rsp]");
		outfile.writeln("\tadd rsp, " + std::to_string(function.memory_capacity));
		outfile.writeln("\tret");
	}

	// entry code
	outfile.writeln("start:");
	outfile.writeln("\tmov rax, ret_stack_end");
	outfile.writeln("\tmov [ret_stack_rsp], rax");
	outfile.writeln("\tcall func_addr_" + std::to_string(program.functions.at("main").addr));
	outfile.writeln("\tmov rax, 60");
	outfile.writeln("\tmov rdi, 0");
	outfile.writeln("\tsyscall");

	// data
	outfile.writeln("segment readable writable");

	// strings
	for (long unsigned int i = 0; i < strings.size(); i++)
	{
		std::string str = strings.at(i);
		std::stringstream ss;
		if (str.size() == 0)
			ss << "0x0";
		else
		{
			for (long unsigned int a = 0; a < str.size() - 1; a++)
				ss << "0x" << std::hex << (int) str.at(a) << ",";
			ss << "0x" << std::hex << (int) str.back();
		}
		outfile.writeln("str_" + std::to_string(i) + ": db " + ss.str());
	}

	outfile.writeln("ret_stack_rsp: rq 1");
	outfile.writeln("ret_stack: rb 4096");
	outfile.writeln("ret_stack_end:");
}
