Au login nous voyons un binaire level13 que nous décidons de decomplier avec `ghidra` pour voir le code source.

```c
void main(void)

{
  __uid_t _Var1;
  undefined4 uVar2;
  
  _Var1 = getuid();
  if (_Var1 != 0x1092) {
    _Var1 = getuid();
    printf("UID %d started us but we we expect %d\n",_Var1,0x1092);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  uVar2 = ft_des("boe]!ai0FB@.:|L6l@A?>qJ}I");
  printf("your token is %s\n",uVar2);
  return;
}
```
Nous voyons que le binaire attend un uid de 0x1092 pour afficher le token.

lorsque nous affichgons notre uid avec la commande `id` nous obtenons `uid=2013(level13) gid=2013(level13) groups=2013(level13)` alors que nous voulons `uid=0x1092`qui vaut `uid=4242(level13) gid=4242(level13) groups=4242(level13)`.

les differentes manieres de changer d'uid dans le shell sont: des commandes utilisant sudo, su, setuid. et nous n'avons pas les droits pour utiliser ces commandes.

On decide d'utiliser `gdb` pour changer l'uid de notre processus.

avec la commande disassemble main de gdb nous obtenons l'adresse de la comparaison qui pose probleme `break 0x0804859a`.

nous effectuons un break point a cette adresse et nous changeons la valeur de l'uid avec la commande `set $eax=0x1092` puis nous continuons l'execution du programme avec la commande `continue`.

```bash
(gdb) break *0x0804859a
Breakpoint 2 at 0x804859a
(gdb) run
Starting program: /home/user/level13/level13

Breakpoint 2, 0x0804859a in main ()
(gdb) set $eax = 0x1092
(gdb) continue
Continuing.
your token is 2A31L79asukciNyi8uppkEuSx
[Inferior 1 (process 16671) exited with code 050]
(gdb)
```
Nous obtenons le token `2A31L79asukciNyi8uppkEuSx` qui nous permet de valider le niveau.
