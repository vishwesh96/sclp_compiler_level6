	.data

	.text			# The .text assembler directive indicates
	.globl main		# The following is the code (as oppose to data)
main:				# .globl makes main know to the
				# outside of the program.
# Prologue begins
	sw $ra, 0($sp)		# Save the return address
	sw $fp, -4($sp)		# Save the frame pointer
	sub $fp, $sp, 8		# Update the frame pointer
	
	sub $sp, $sp, 8		# Make space for the locals
# Prologue ends

	li.d $f2, 1.00
	s.d $f2, 0($fp)
	li $v0, 1
	sw $v0, -4($fp)
	sub $sp, $sp, 8
	jal main
	add $sp, $sp, 8
	move $v0, $v1
	li $v0, 1
	move $v1, $v0
	j epilogue_main

# Epilogue Begins
epilogue_main:
	add $sp, $sp, 8
	lw $fp, -4($sp)
	lw $ra, 0($sp)
	jr		  $31		# Jump back to the called procedure
# Epilogue Ends

