
	.text 			# The .text assembler directive indicates
	.globl main		# The following is the code (as oppose to data)
main:				# .globl makes main know to the 
				# outside of the program.
# Prologue begins 
	sw $ra, 0($sp)		# Save the return address
	sw $fp, -4($sp)		# Save the frame pointer
	sub $fp, $sp, 8		# Update the frame pointer

	sub $sp, $sp, 24		# Make space for the locals
# Prologue ends

	li.d $f2, 1.00
	s.d $f2, 0($fp)
	li.d $f2, 2.00
	s.d $f2, -8($fp)
	l.d $f2, 0($fp)
	l.d $f4, -8($fp)
	li $v0, 0
	c.le.d $f2, $f4
	bc1f label0
	li $v0, 1

label0:    	
	sltu $v0, $v0, 1
	l.d $f2, 0($fp)
	l.d $f4, -8($fp)
	li $t0, 0
	c.le.d $f2, $f4
	bc1f label1
	li $t0, 1

label1:    	
	and $t1, $v0, $t0
	l.d $f2, 0($fp)
	l.d $f4, -8($fp)
	li $v0, 0
	c.le.d $f2, $f4
	bc1f label2
	li $v0, 1

label2:    	
	sltu $v0, $v0, 1
	or $t0, $t1, $v0
	beq $t0, $zero, label3 
	li.d $f2, 1.00
	s.d $f2, 0($fp)
	j label4

label3:    	

label4:    	
	j epilogue_main

# Epilogue Begins
epilogue_main:
	add $sp, $sp, 24
	lw $fp, -4($sp)  
	lw $ra, 0($sp)   
	jr        $31		# Jump back to the called procedure
# Epilogue Ends

