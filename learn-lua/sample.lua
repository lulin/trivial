cmdline = {...}
nargs = #cmdline

local print_version
local _usage
local _usage_info
local _unpack

local cmd, exec, args

_usage_info = "Usage:\
  cmd args"

----

function _sequence_shift (seq)
	local new, i = {}

	for i = 2, #seq do
		new[i - 1] = seq[i]
	end
	return new
end

function _usage (self)
	print(_usage_info)
	self.list(self)
end

function print_version (self)
	print("Version: " .. self._version)
end

function _unpack (t, f, s, k, v)
	if (not f) then f, s, k = pairs(t) end
	k, v = f(s, k)
	if (not k) then return end
	return v, _unpack(t, f, s, k, v)
end

function _dump (self, method, ...)
	if (not method) then return end
	print(self[method](self, ...))
end

function _list_methods(self)
	local k, v

	print("Supported commands:")
	for k, v in pairs(self) do
		if (type(v) == "function") then print("  "..k) end
	end
end

----

sample = {
	_version = 0,

	usage = _usage,
	unpack = _unpack,
	test = _dump,
	list = _list_methods
}

----

cmd = cmdline[1]
args = _sequence_shift(cmdline)

if (not cmd) then return print_version(sample) end
if (not sample[cmd]) then sample.usage() return end

sample[cmd](sample, unpack(args))

