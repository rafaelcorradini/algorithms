while(1):
	# run codes acusa erro se eu não tratar esta excessão
	try:
	    n_chambers, n_specimens = map(int, input().split())
	except EOFError:
	    quit()
	
	m = 0
	# inicaliza o vertor com zeros e tamanho 2C
	specimens = [0] * (2*n_chambers)
	inputs = input().split()
	
	for i in range(0, len(inputs)):
		specimens[i] = float(inputs[i])
		m += specimens[i]

	specimens.sort()
	imbalance = 0
	# massa média
	am = m / n_chambers

	for i in range(0, n_chambers):
		imbalance += abs((specimens[i] + specimens[(2*n_chambers-1)-i]) - am)

	print("IMBALANCE = %.5f" % imbalance)	