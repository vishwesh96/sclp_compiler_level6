
	.text 			# The .text assembler directive indicates
	.globl main		# The following is the code (as oppose to data)
main:				# .globl makes main know to the 
				# outside of the program.
# Prologue begins 
	sw $ra, 0($sp)		# Save the return address
	sw $fp, -4($sp)		# Save the frame pointer
	sub $fp, $sp, 8		# Update the frame pointer

	sub $sp, $sp, 8		# Make space for the locals
# Prologue ends

	lw $v0, 12($fp)
	lw $t0, 12($fp)
	add $t1, $v0, $t0
	move $v1, $t1
	j epilogue_main

# Epilogue Begins
epilogue_main:
	add $sp, $sp, 8
	lw $fp, -4($sp)  
	lw $ra, 0($sp)   
	jr        $31		# Jump back to the called procedure
# Epilogue Ends

