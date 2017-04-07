
	.data
i:	.word 0
size:	.word 0
prev:	.word 0
number:	.word 0

	.text 			# The .text assembler directive indicates
	.globl fibonacci		# The following is the code (as oppose to data)
fibonacci:				# .globl makes main know to the 
				# outside of the program.
# Prologue begins 
	sw $ra, 0($sp)		# Save the return address
	sw $fp, -4($sp)		# Save the frame pointer
	sub $fp, $sp, 8		# Update the frame pointer

	sub $sp, $sp, 12		# Make space for the locals
# Prologue ends

	lw $v0, i
	lw $t0, size
	seq $t1, $v0, $t0
	beq $t1, $zero, label0 
	j label1

label0:    	
	lw $v0, 12($fp)
	lw $t0, 16($fp)
	add $t2, $v0, $t0
	sw $t2, 0($fp)
	lw $v0, 16($fp)
	sw $v0, 12($fp)
	lw $v0, 0($fp)
	sw $v0, 16($fp)
	lw $v0, i
	li $t0, 1
	add $t2, $v0, $t0
	sw $t2, i
	lw $v0, 16($fp)
	sw $v0, 0($sp)
	lw $v0, 12($fp)
	sw $v0, -4($sp)
	sub $sp, $sp, 8
	jal fibonacci
	add $sp, $sp, 8
	move $v0, $v1

label1:    	
	li $v0, 0
	move $v1, $v0
	j epilogue_fibonacci

# Epilogue Begins
epilogue_fibonacci:
	add $sp, $sp, 12
	lw $fp, -4($sp)  
	lw $ra, 0($sp)   
	jr        $31		# Jump back to the called procedure
# Epilogue Ends


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

	li $v0, 0
	sw $v0, prev
	li $v0, 1
	sw $v0, number
	li $v0, 20
	sw $v0, size
	li $v0, 1
	sw $v0, i
	lw $v0, number
	sw $v0, 0($sp)
	lw $v0, prev
	sw $v0, -4($sp)
	sub $sp, $sp, 8
	jal fibonacci
	add $sp, $sp, 8
	move $v0, $v1
	j epilogue_main

# Epilogue Begins
epilogue_main:
	add $sp, $sp, 8
	lw $fp, -4($sp)  
	lw $ra, 0($sp)   
	jr        $31		# Jump back to the called procedure
# Epilogue Ends

