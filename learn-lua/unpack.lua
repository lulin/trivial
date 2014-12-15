-- implement unpack function

_unpack = function (t,f,s,k,v)
	if (type(t) ~= "table") then return end
	if (not f) then f,s,k,v = pairs(t) end
	k,v = f(s, k)
	if (not k) then return end
	return v, _unpack(t,f,s,k,v)
end

-- test

ta = {1,2,3,f1="hello", f2="world"}
tb = {}

print("unpack(ta): ", _unpack(ta))
print("unpack(tb): ", _unpack(tb))

args = {...}

print("The arguments:")
print("  ", _unpack(args))

