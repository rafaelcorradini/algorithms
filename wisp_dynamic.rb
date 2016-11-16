def nextv(i, d) 
	for j in i.downto(0)
		if d[i][0] >= d[j][1]
			return j
		end
	end

	return -1
end


def wisp(v, d)
	m = Array.new
	m[0] = v[0]
	for i in 1..(v.size-1)
		nxt = nextv(i, d)
		if nxt == -1
			m[i] = [v[i], m[i - 1]].max
		else
			m[i] = [v[i] + m[nxt], m[i - 1]].max
		end
		
	end
	
	return m[i]
end

v = [2, 4, 4, 7, 2, 1]
d = [[0, 2], [1, 5], [2, 6], [1, 8], [7, 9], [8, 9]]

puts wisp(v, d)