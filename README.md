# 📞 Minitalk

**Minitalk** est un projet de l'école 42 visant à développer un programme d'échange de données (client / serveur) en utilisant les signaux UNIX.

## 📝 Description

Le but du projet est de créer un client et un serveur qui communiquent.
Le serveur, lancé en premier, doit afficher son PID. Le client prend en paramètre ce PID ainsi que la chaîne de caractères à envoyer. La chaîne est transmise de manière asynchrone au serveur qui se charge de l'afficher.

La communication s'effectue **exclusivement** via les signaux UNIX `SIGUSR1` et `SIGUSR2`.

## 🛠️ Compilation

Un `Makefile` est présent à la racine du projet. Voici les règles disponibles :

```bash
# Compile les exécutables client et server
make

# Supprime les fichiers objets (.o)
make clean

# Supprime les fichiers objets et les exécutables
make fclean

# Recompile le projet depuis le début
make re
```

## 🚀 Utilisation

**1. Lancer le serveur**

Dans un premier terminal, exécutez le serveur :
```bash
./server
```
*Le serveur affichera alors son PID (ex: `PID: 12345`) et attendra la réception de signaux.*

**2. Lancer le client**

Dans un second terminal, utilisez le client en passant le PID du serveur puis le message à envoyer :
```bash
./client <PID> "Le message à envoyer"
```

**Exemple :**
```bash
./client 12345 "Bonjour 42 !"
```

## ⚙️ Fonctionnement ("Sous le capot")

- Le **client** traduit chaque caractère du message en binaire (sur 8 bits).
- Il envoie un par un ces bits au serveur :
  - Le bit `0` est transmis par le signal `SIGUSR1`.
  - Le bit `1` est transmis par le signal `SIGUSR2`.
- Le **serveur** reçoit les signaux de façon asynchrone, reconstitue l'octet bit par bit, et affiche le caractère correspondant dès qu'il est complet.
- Ce projet tire notamment parti de votre propre bibliothèque `libft` (incluant `ft_printf`).

## 🧪 Tests

Un script `tester.sh` est disponible dans le dépôt pour potentiellement automatiser ou tester le comportement de l'envoi de messages.
