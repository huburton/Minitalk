# Minitalk

*[English version](README.md)*

Un client envoie du texte à un serveur en n'utilisant que deux signaux UNIX, `SIGUSR1` et `SIGUSR2`.
Projet de l'école 19 (réseau 42), en C.

```text
$ ./server
PID: 2110260

$ ./client 2110260 "Bonjour 42 ! é ✓"      # dans un autre terminal
                                           # le serveur affiche : Bonjour 42 ! é ✓
```

## Fonctionnement

- Le client envoie chaque octet sous forme de 8 signaux, bit de poids fort en premier : `SIGUSR2` pour 1,
  `SIGUSR1` pour 0. Un `'\0'` final marque la fin du message.
- Le serveur reconstitue l'octet bit par bit dans son gestionnaire de signal et l'écrit dès que les 8 bits
  sont arrivés.
- **Chaque bit est acquitté.** Le serveur répond à chaque signal par un `SIGUSR1` à l'expéditeur, dont il
  lit le PID dans `siginfo_t` (`SA_SIGINFO`). Le client attend cette réponse avant d'envoyer le bit suivant :
  aucun signal ne se perd quand le serveur est occupé, sans avoir à deviner un délai.
- Le texte part en octets bruts : les caractères UTF-8 (`é`, `✓`) arrivent intacts.

## Mesure

Sur le serveur de la maison, un message de 10 000 caractères est arrivé complet en 0,31 s : environ
260 000 bits par seconde, chacun acquitté par le serveur.

## Compilation

```bash
make                         # produit ./server et ./client (avec la libft incluse)
./server                     # affiche son PID
./client <pid_du_serveur> "message"
```

`tester.sh` enchaîne des envois, jusqu'à des messages de 5 300 caractères répétés dix fois.
