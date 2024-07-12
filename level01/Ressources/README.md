Le fichier dans /etc nommée passwd
Copie du fichier pour le décoder via l'outil john 
```bash
scp -P 4242 level01@localhost:/etc/passwd .
```
Pour afficher le flag il faut executer john :
```bash
./john --show passwd
```
```bash
flag01:abcdefg:3001:3001::/home/flag/flag01:/bin/bash
```
Après s'être connecté a flag01 avec **abcdefg** on éxécute la commande getflag
```bash
getflag
Check flag.Here is your token : f2av5il02puano7naaf6adaaf
```