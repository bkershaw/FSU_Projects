		.text
		j L1
L1:			addiu	$v0,$zero,5		# ready syscall for reading int
		syscall						# read int into $v0
		sw 		$v0,x($gp)			# store int into .word labelled x
		addiu	$v0,$zero,5		# ready syscall for reading int
		syscall						# read int into $v0
		sw 		$v0,y($gp)			# store int into .word labelled y
		lw		$t0,x($gp)			# $t0 now contain x
		lw		$t1,y($gp)			# $t1 now contain y
		addu	$a0,$t0,$t1		# $t2 = x + y
		addiu	$v0,$zero,1		# syscall value for print int
		syscall						# print x + y
		subu	$a0,$t0,$t1		# $a0 = x - y
		syscall						# print x - y
		and		$a0,$t0,$t1		# $a0 = x & y
		syscall						# print x & y
		or		$a0,$t0,$t1		# $a0 = x | y
		syscall						# print x | y
		mult	$t0,$t1			# $lo = x * y
		mflo	$a0					# $a0 = $lo,getting ready to print
		syscall						# print x * y
		div		$t0,$t1			# now $lo = x / y,$hi = x % y
		mflo	$a0
		syscall						# print x / y
		mfhi	$a0
		syscall						# print x % y
		slt		$a0,$t0,$t1		# if x < y,$a0 = 1,else $a0 = 0
		syscall						# print value of $a0
		addiu 	$t2,$zero,1		# $t2 = 1
		addiu 	$t3,$zero,1		# $t3 = 1
try:		beq		$t3,$zero,exit	# go to exit routine $t3 = 0
		addu	$t3,$zero,$zero	# $a0 = 0
		bne		$t3,$t2,try		# go back to try now that $t3 = 0
exit:		addiu 	$v0,$zero,10		# ready syscall for exit routine
		syscall						# exit
		.data
x:			.word 0						# x reference 1st int
y:			.word 0						# y reference 2nd int
