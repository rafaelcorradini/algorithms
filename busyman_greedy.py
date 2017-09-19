t = int(input())

for i in range(0, t):
	n = int(input())
	# inicializa a lista de dicionarios
	acts = list( {} for i in range(0, n) )
	for j in range(0, n):
		acts[j]['start'], acts[j]['end'] = map(int, input().split())

	# ordena a lista pelo inicio da tarefa
	acts.sort(key=lambda x: x['start'], reverse=False)
	res = 0
	end = 0
	for a in acts:
		if(a['end'] < end):
			end = a['end']
		elif(a['start'] >= end):
			end = a['end']
			res += 1

	print(res)		