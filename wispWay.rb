def wispWay(h, l)
	m = Array.new
	c = Array.new
	m[0] = 0
	m[1] = 0
	for i in 2..(h.size-1)
	  a = h[i] + m[i - 2]
	  b = l[i] + m[i - 1]
	  if a > b 
		  m[i] = a
		  c[i-2] = 'h'
		else
		  m[i] = b
		  c[i-1] = 'l'
		end
	end

	puts c
	return m[i]
end

h = [0, 0, 2, 10, 1 ,3]
l = [0, 0, 3, 5, 1 ,5]

puts wispWay(h, l)
