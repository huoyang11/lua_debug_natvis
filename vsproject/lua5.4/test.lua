g_test = 23

function test()
	g_test = g_test + 1
	print(g_test)
	return 1
end

local ret = test()
print(ret)