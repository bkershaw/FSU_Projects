	.text
	addu	$s1,$zero,$zero		# s1 = 0
   	addiu	$s2,$zero,10		# s2 = 10
	addiu   $s3,$zero,2		# s3 = 2
	div	$s2,$s3			# 10 / 2
	div	$s2,$s1			# 10 / 0
	addiu	$v0,$zero,5		# v0 = read value 
	addiu	$v0,$zero,10		# exit
	syscall
