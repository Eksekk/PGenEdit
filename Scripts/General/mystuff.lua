function reloadM()
	M = dofile"C:\\Users\\Eksekk\\Documents\\GitHub\\MMStuff\\EksekkStuff.lua"
end
json = require"json"
reloadM()
if not M.dll then
	M.loadDll()
end

