cmdline = {...}
nargs = #cmdline

local _pVersion
local _usage
local _usage_info
local _unpack

local cmd, exec, args

_usage_info = [[
Usage:
  cmd args]]

sample = {
	_version = 0
}

----

function _sequenceDup (seq)
	return {unpack(seq)}
end

function _sequenceShift (seq)
	seq[1] = nil
	return _sequenceDup(seq)
end

function _usage ()
	print(_usage_info)
end

function _pVersion (self)
	print("Version: " .. self._version)
end

function _unpack (t, f, s, k, v)
	if (not f) then f, s, k = pairs(t) end
	k, v = f(s, k)
	if (not k) then return end
	return v, _unpack(t, f, s, k, v)
end

function _selfMethod (self, cmd)
	return function (...)
		return self[cmd](self, ...)
	end
end

----

-- sample.usage()
sample.usage = _usage

-- sample.unpack(self)
-- sample:unpack()
sample.unpack = _unpack

----

cmd = cmdline[1]
args = _sequenceShift(cmdline)

if (not cmd) then return _pVersion(sample) end
if (not sample[cmd]) then sample.usage() end

exec = _selfMethod(sample, cmd)
exec(unpack(args))

