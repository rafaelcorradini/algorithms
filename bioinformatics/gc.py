from Bio import SeqIO
import matplotlib.pyplot as plt

def GC_content(seq, window=100): 
	"""Calculates GC content G+C for multiple windows along the sequence. 

	Returns a list of ratios (floats), controlled by the length of the sequence 
	and the size of the window. 

	Returns 0 for windows without any G/C by handling zero division errors. 
 
	""" 
	values = [] 
	for i in range(0, len(seq), window): 
	    s = seq[i: i + window] 
	    gc = sum(s.count(x) for x in ['G', 'C', 'g', 'c', 'S', 's'])
	    try:
	    	content = gc * 100.0 / len(s)
	    except ZeroDivisionError: 
	    	content = 0.0
	    values.append(content)
	return values 

def print_freq(seq):
	print("G: "+str(seq.count('G')), "C: "+str(seq.count('C')), "T: "+str(seq.count('T')), "A: "+str(seq.count('A')))
	print("P(G): "+str(seq.count('G')/len(seq)), "P(C): "+str(seq.count('C')/len(seq)), "P(T): "+str(seq.count('T')/len(seq)), "P(A): "+str(seq.count('A')/len(seq)))

seq_lambda = []
for gen in SeqIO.parse("lambda.fasta", "fasta"):
	seq_lambda = gen.seq

plt.plot(GC_content(seq_lambda, 100))
plt.title('Bacteriophage lambda GC content')
plt.xlabel('Window(size = 100)')
plt.ylabel('Frequency(%)')
plt.show()

plt.plot(GC_content(seq_lambda, 350))
plt.title('Bacteriophage lambda GC content')
plt.xlabel('Window(size = 350)')
plt.ylabel('Frequency(%)')
plt.show()

plt.plot(GC_content(seq_lambda, 500))
plt.title('Bacteriophage lambda GC content')
plt.xlabel('Window(size = 500)')
plt.ylabel('Frequency(%)')
plt.show()	
    

seq_man = []
for gen in SeqIO.parse("man.fasta", "fasta"):
    seq_man = gen.seq   

seq_chimp = []
for gen in SeqIO.parse("chimp.fasta", "fasta"):
    seq_chimp = gen.seq     

plt.plot(GC_content(seq_man, 100), label='Man')
plt.plot(GC_content(seq_chimp, 100), label='Chimp')
plt.legend(loc='upper center', shadow=True)
plt.title('Man and chimpanzee GC contents comparison')
plt.xlabel('Window(size = 100)')
plt.ylabel('Frequency(%)')
plt.show()

plt.plot(GC_content(seq_man, 350), label='Man')
plt.plot(GC_content(seq_chimp, 350), label='Chimp')
plt.legend(loc='upper center', shadow=True)
plt.title('Man and chimpanzee GC contents comparison')
plt.xlabel('Window(size = 350)')
plt.ylabel('Frequency(%)')
plt.show()

plt.plot(GC_content(seq_man, 500), label='Man')
plt.plot(GC_content(seq_chimp, 500), label='Chimp')
plt.legend(loc='upper center', shadow=True)
plt.title('Man and chimpanzee GC contents comparison')
plt.xlabel('Window(size = 500)')
plt.ylabel('Frequency(%)')	
plt.show()  

print("\nMan:")
print_freq(seq_man)
print("\nChimp")
print_freq(seq_chimp)