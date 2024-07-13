Aucun fichier caché n'est présent, aucun mail, aucun binaire..
On en conclus qu'il faut donc chercher dans le binaire de la commande getflag.

Après décompilation on remarque que tout les mots de passe y sont stockés et notamment celui de notre flag14.

C'est une fôret de if/else sans précédent mais facilement contournable en modifiant la valeur de 2 variable pour atteindre le print du flag14 : 

Process : 
```bash
gdb getflag
```
Il faut mettre les 2 breakpoint sur les variables à modifier:
```bash
b *0x0804898e
b *0x08048b0a
```
On lance le programme pour s'arréter sur les breakpoints
```bash
(gdb) run
Starting program: /bin/getflag 

Breakpoint 1, 0x0804898e in main ()
```
On modifie la valeur qui doit devenir supérieur a 0 pour éxécuter la condition que l'on souhaite :
```bash 
set $eax=1
```
On continue :
```bash
continue
```
On modifie la valeur du 2e breakpoint:
```bash
set $eax=0xbc6
```
Pour on continue l'éxécution pour obtenir le flag :
```bash
(gdb) c
Continuing.
Check flag.Here is your token : 7QiHafiNa3HVozsaXkawuYrTstxbpABHD8CPnHJ
```

Il ne nous reste plus qu'à nous connecter au flag14 :
```bash
level14@SnowCrash:/bin$ su flag14
Password: 
Congratulation. Type getflag to get the key and send it to me the owner of this livecd :)
```

