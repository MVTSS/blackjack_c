# Matis' Blackjack

Petit projet de jeu de blackjack en C jouable dans le terminal (TUI).
Fait en parallèle avec l'IA en tant qu'outil et non en tant que solution.

Ce jeu a pour ambition de pouvoir jouer à plusieurs via des sessions TMUX, puis via self-hosted server.

## Installation

### Prérequis

Prérequis : `gcc`, `make`, OpenSSL et cJSON.

Sur Ubuntu/Debian, installer les prérequis avec :

```bash
sudo apt update
sudo apt install gcc make libssl-dev libcjson-dev
```

### Utilisation 

Depuis le dossier du projet, compiler les exécutables :

```bash
make
```

Initialiser l'argent du joueur et une config clean :

```bash
./init_money
```

Lancer une partie :

```bash
./blackjack
```


### Suppressions

Pour supprimer les fichiers inutile au fonctionnement :

```bash
make cleano
```

Pour supprimer les fichiers générés :

```bash
make clean
```