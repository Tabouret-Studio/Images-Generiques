# Installation

Images-génériques prend la forme d'une application C++/OpenGL qui doit être compilé pour pouvoir être utilisé. Actuellement, l'installation fonctionne sur les systèmes UNIX \(MacOS, Linux, etc.\)

## Dépendances

Images Génériques requiert plusieurs dépendances pour pouvoir fonctionner. Celles-ci permettent de faire fonctionner des parties critiques de l'application :

* OpenGL Core \(3.3+\)
* SDL2 + SDL2\_Image
* Freetype
* GLM
* Boost
* Python

Il est possible d'installer ces dépendances manuellement, et certaines sont surement déjà installées sur votre système \(OpenGL\). Les guident suivant vous indiquent comment installer ces dépendances via **brew** sur Mac, et **Aptitude** sur Linux.

Si vous avez déjà installés ces dépendances, vous pouvez passer cette partie.

## MacOS

### OpenGL

OpenGL arrive préinstallé sur votre mac, il est possible de vérifier la version disponible via cette page du support Apple : [Mac computers that use OpenCL and OpenGL graphics](https://support.apple.com/en-us/HT202823)

Sur MacOS, l'installation des autres dépendances est simplifiée grace à l'utilisation de [**brew**](https://brew.sh), un gestionnaire de paquets.

### SDL2

```bash
$ brew install sdl2
```

### SDL2\_image

```bash
$ brew install sdl2_image
```

### Freetype

```bash
$ brew install freetype
```

### GLM

```bash
$ brew install glm
```

### Boost

```bash
$ brew install boost
```

### Python

```bash
$ brew install python
```

## LINUX

Le guide suivant est fait pour Ubuntu, mais devrait pouvoir être adapté sans soucis à d'autre distribution linux

### OpenGL

Il est possible de vérifier la version d'OpenGL disponible sur votre machine grâce à la commande suivante :

```bash
$ glxinfo | grep 'version'
```

Images Générique requiert OpenGL Core 3.3 ou plus.

Pour la suite, nous utiliserons **Aptitude** \(apt-get\) pour installer les paquets. L'utilisation d'Aptitude requiert des authorizations administrateur \(`sudo`\)

### SDL2

```bash
$ apt-get install libsdl2-dev
```

### SDL2\_image

```bash
$ apt-get install libsdl2-image-dev
```

### Freetype

```bash
$ apt-get install libfreetype6-dev
```

### GLM

```bash
$ apt-get install ibglm-dev
```

### Boost

```bash
$ apt-get install libboost-all-dev
```

### Python

```bash
$ apt-get install libpython-dev
```

## Compilation

Commencez par récupèrer la dernière version d'Image génériques et vous placer à la racine du projet:

```bash
$ git clone https://github.com/boisier/images-generiques.git
$ cd images-generiques.git/App
```

A partir de là, il ne vous reste plus qu'a compiler l'application, puis à la lancer.

```bash
$ make -j4
[...]
========================================
   ImagesGeneriques successfully compiled!
   Type "./build/ImagesGeneriques" to launch ImagesGeneriques
========================================
$ ./build/ImagesGeneriques
```

## ![](https://github.com/Boisier/Images-Generiques/tree/c2dc94668a8ba56c4144fbf8613115c7e73c9b5f/docs/assets/Capture%20d’écran%202018-05-23%20à%2013.19.42.png) {#interface}

## Résolution des problèmes

Il se peut que plusieurs problème au cours de l'installation, ou au lancement du programme. Vous trouverez ici une liste des erreurs pouvant avoir lieu

### Erreurs à la compilation

* **Header/Symbol not found** - Assurez-vous d'avoir correctement installés toutes les librairies nécessaires au programme

### Erreurs au lancement

* " **Could not find '.../indexlibrary.json' "** - Le fichier de librairie est manquant, assurez qu'il existe bien dans le dossier `App/build/indexLibrary/`. Plusieurs fichiers exemple sont données en exemple.
* " **Segmentation fault "** - Cause la plus probable, vous indiquez des images dans le fichier d'index qui ne sont cependant pas présentes. Assurez-vous que les chemin indiqués sont exacts
* **Crash à la sauvegarde :** Assurez-vous que le dossier `App/build/indexLibrary/exports/` éxiste bien.

