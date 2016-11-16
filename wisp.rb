def nextv(i, d) 
	for j in i.downto(0)
		if d[i][0] >= d[j][1]
			return j
		end
	end

	return -1
end


def wisp(i, v, d)
	if i == -1
		return 0
	else
		nxt = nextv(i, d)
		if nxt == -1
			return [v[i], wisp(i - 1, v, d)].max
		else
			return [v[i] + wisp(nxt, v, d), wisp(i - 1, v, d)].max
		end
	end
end

v = [2, 4, 4, 7, 2, 1]
d = [[0, 2], [1, 5], [2, 6], [1, 8], [7, 9], [8, 9]]

puts wisp(d.size - 1, v, d)