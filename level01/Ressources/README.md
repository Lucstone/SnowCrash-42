Le dossier est vide, en cherchant dans les répertoires on trouve un fichier dans /etc nommée passwd
```bash
cat /etc/passwd
flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash
```

Le mot de passe ne fonctionne pas il semble encodé.

Copie du fichier pour le décoder via l'outil john 
```bash
scp -P 4242 level01@localhost:/etc/passwd .
```

Pour afficher le flag il faut executer john :
```bash
./john --show passwd
flag01:abcdefg:3001:3001::/home/flag/flag01:/bin/bash
```

Après s'être connecté a flag01 avec **abcdefg** on éxécute la commande getflag

```bash
getflag
Check flag.Here is your token : f2av5il02puano7naaf6adaaf
```