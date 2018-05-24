---
description: Explications des choix de développement
---

# Philosophie

Afin de mieux comprendre la manière avec laquelle l'application a été développée, il est intéressant de prendre connaissance des informations suivantes :

### Modularité et échanges d'informations

Afin d'assurer la plus grande modularité possible, et de simplifer au maximum de futures évolutions impliquant des changements majeurs, il a été décider de limiter les échanges d'informations entre les classes à des échanges verticaux. Une classe reçoit et transmet des informations avec son entité parent, mais pas avec ses entités soeurs. Les moteurs communiquent entre eux au travers du AppObject. Les scenes ne sont pas supposées communiquer entre elles. Seuls les utilitaires échappent à cette logique, de part leur propre nature de servir un peu partout.

### Gestion des inclusions

Afin d'éviter toute inclusion cyclique, et d'assurer une consistence des inclusions plusieurs rêgles ont été mises en place.

L'ensemble des définitions de bas niveau, tels que l'inclusion des libraries externes et la définition des types, est concentré dans le fichier `libraries.hpp` . Ce fichier se doit d'être inclus dans chaque header `hpp` ou il convient, il ne doit jamais être inclus dans un fichier `cpp`.

Les inclusions de haut niveau, internes à l'application, se font en deux étapes:

* **Dans les headers** `hpp` - Utilisation au maximum de _Forward declarations_, ceci afin d'empecher tout risque d'inclusions cycliques. Si une _Forward declarations_ n'est pas possible, et seulement dans ce cas, on peut inclure directement le header nécessaire. Les inclusion de la librairie standard se font aussi dans les headers.
* **Dans les unité de compilation** **`cpp`** - Inclusion des headers nécessaires non-inclus dans le header correspondant. Un header inclus dans une unité de compilation n'entrera pas en conflit avec des inclusion dans d'autres unités.

### Dénominations

Le nommage des différentes entités de l'application est très classique : 

* **Variables** `lowerCamelCase`
* **Classes** `UpperCamelCase`

Unique exception à la rêgle : la variable `App`, point d'accroche du AppObject.

Toutes les entités sont en anglais, et possède des noms explicites, exception faite des itérateurs et variables de boucle \(`i`, `j`, etc.\). L'intérêt est de comprendre directement ce que contient la varible de part son nom.

Les variables membres privés des classes commencent par `m_`, ceci afin de bien les différencier des variables locales.

### Commentaires

> On dit qu'une applicaiton correctement codées'auto-documente, et ne nécessite pas de commentaires. Ce n'est pas le cas ici, tout comme partout ailleurs.

Toujours dans l'optique d'avoir une application facilement maintenable, le code de celle-ci est fortemment commenté, et suit une structure précise.

Les headers sont la partie la plus documenté du code. Chaque méthode est décrite, ainsi que ses paramètres et son éventuelle valeur de retour. Le but ici est, pour quelqu'un qui cherche juste à utiliser une des méthodes de la classe, de ne pas avoir à ouvrir le cpp, toutes les informations nécessaires à l'utilisation de la classe doivent se trouver dans le header.

Dans les unités de compilation, les commentaires sont plus éparses. Ils ne servent qu'a indiquer des informations susceptible de ne pas être claires pour une personne découvrant le code pour la première fois. La quantité de commentaire est ici réduite au minimum par l'utilisation de noms de variables et de méthodes clairs et explicites.

