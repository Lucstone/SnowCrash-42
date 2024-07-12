Il y a deux fichiers, un binaire et un fichier token qui peu être lu.
En éxécutant le binaire on s'aperçoit qu'il modifie les chaînes de caractéres envoyés en arguments.

```bash 
level09@SnowCrash:~$ ./level09 aaaaaaa
abcdefg
```
La logique est donc que chaque caractéres est additionné en fonction de sa place dans la chaîne de caractéres.

En créant un binaire qui fait l'inverse on peut donc reverse le contenu du fichier token. (fichier reverse.c)

gcc n'étant pas installé sur la VM on copie le fichier token pour le reverse.

```bash
scp -P 4242 level09@127.0.0.1:/home/user/level09/token .
```
(Sur linux il faut donner les droits de lecture du token)
```bash 
chmod 666 token
```

On l'éxécute avec le contenu du fichier token :
```bash
./reverse $(cat token)
f3iji1ju5yuevaus41q1afiuq
```

On se connecte au user **flag09** et on fait le getflag : 
```bash
flag09@SnowCrash:~$ getflag
Check flag.Here is your token : s5cAJpM8ev6XHw998pRWG728z
```

