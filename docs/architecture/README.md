---
description: Description des différents composants de l'application
---

# Architecture

Afin d'assurer une évolution et une maintenabilité la plus simple possible, l'application adopte une strucure modulaire qui sépare les différentes composantes en parties distinctes interargissant entre elles par un point unique.

### L'AppObject

Point nevralgique, l'**AppObject** ou **AppObj** contient les points d'accroche des moteurs, des instructions et des scenes. Il permet aussi d'accèder au informations sur la fenêtre de l'application. Instancé en singleton global, il permet d'accèder rapidement et simplement aux différentes composantes de l'application.

{% hint style="info" %}
L'AppObject est accessible depuis n'importe quel point de l'application au travers de la variable `App` :

```cpp
App->appEngine->executeScene();
```
{% endhint %}

En cas d'extension de l'application, il est de rigueur de s'assurer que la majeur partie des interactions se font bien au travers de l'**AppObj** et non entre les composants eux-même. L'idée ici est de conserver un certains cloisonnement, en accord avec l'idée de modularité mis en avant dans l'architecture.   

### Les Moteurs

Les fonctionnalités centrales de l'applications sont placés dans les moteurs \(engines\). Il existe actuellement cinq moteurs:

* Le **RessourcesEngine** - Il se charge de l'import et de l'export des différents éléments \(Assets\) nécessaire au fonctionnement de l'application. Il utilise des Importers et des Exporters pour chaque type de données a manipuler. 
* Le **RenderEngine** - Il concentre la majorité des méthodes permettant d'interargir avec OpenGL. Il permet une manipulation simplifié des buffers \(VBO & VAO\) et fournis une methode de rendu simplifé pour l'ensemble de l'application.
* L'**AppEngine** - Se charge de la manipulation des scenes en colaboration avec l'AppObject. Il prend aussi en charge les évènements claviers et souris
* L'**IndexEngine** - Gère les images \(SVG\) utilisés par l'application. Il gère l'index et sa sauvegarde.
* Le **GeneratorEngine** - Il s'occupe du chargement, de la gestion, et de fournir les Instructions utilisées pour manipuler les images. Il s'occupe aussi du chargement et la communication avec les instructions Python si celles-ci sont activées. 

### Le Core

Le core est le coeur de l'application \(!\). C'est là que ce trouve la boucle principale assurant le rendu et le rafraichissement de l'application. Le **Core** est appelé dès le lancement de l'application afin d'initialisé le **AppObject** et les moteurs. La class **Ignite**, partie intégrante du core, se charge de préparer le terrain pour la boucle.

{% hint style="info" %}
La scène de démarrage se définie au début de la methode `Core::main()`
{% endhint %}

### Les Utilitaires

Afin de rendre accessible le plus facilement certaines méthodes, sans pour autant créer de nouveaux moteurs car leur utilisation/taille ne le justifierais pas, plusieurs classes sont rangés dans le dossier **Utils/**. Le but principale de cette fragmentation est de trouver en un seul lui des méthodes utilisées à plusieurs endroits de l'application, et de décharger certaines classes afin de limiter leur poid ou complexité.

### Les Scènes

Les scènes sont l'aboutissements de tous les éléments précédents. Composées uniquement de logique pure, leur but est de donner vie à l'application grâce aux différents éléments développés précedemment.

Stockées dans le AppObj une fois instanciées, il peut y avoir plusieurs scènes à l'écran. Elles sont rafraichis à chaque tour de boucle par le Core, et peuvent répondre aux évènements utilisateurs. Toutes les scènes découlent d'une structure communes, et implémentes des méthodes supplémentaires selon leur besoin.

{% hint style="warning" %}
Toute fonction liée à la manipulation des informations au-delà d'un simple affichage à l'écran devrait être placée à l'exterieur des scènes, ceci afin de garantir une plus grande modularité et de limiter la duplication de code.
{% endhint %}

Par ailleurs, les interactions entre les scènes devrait être limitées au maximum. Si une grande quantité d'informations passe directement d'une scène à une autre \(sans passer par un moteur\) c'est qu'il y a possibilité de déplacer du code autre part. Théoriquement, une scène devrait être complètement indépendante des autres scènes.

