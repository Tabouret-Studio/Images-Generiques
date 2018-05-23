---
description: Fonctionnement des scènes
---

# Les Scènes

Une scène correspond à un ensemble d'élements \(textes, images, boutons, etc.\) affichés dans la fenêtre de l'application, et avec lesquels l'utilisateur peut interargir ou non. Le but d'une scène n'est pas de faire elle-même de la manipulation de données, de lourds calculs, ou du rendu graphique; elle délègue ces taches aux moteurs et aux utilitaires. Les scènes sont donc une interface entre les fonctionnalités du programme et l'utilisateur.

Afin de pouvoir créer des interfaces complexes et modulaires, il est possible de créer et d'afficher plusieurs scène en même temps. C'est le cas pour l'interface de base de notre programme, ou les interactions sont gérés par une scène, et l'affichage de l'image par une autre.

### Manipulation des scènes

Les scènes sont stockées dans le AppObject. On ajoute une scène à la boucle de rendu via la méthode `addScene()` et on retire une scène avec `removeScene()`. Une scène présente dans la boucle rendu vois ses méthodes `execute()` et `render()` appelées à chaque tour de boucle.

On recommande de définir la méthode statique `load()` pour chaque scène, permettant d'initialiser et d'insérer une scène dans la boucle directement.

Il est possible de mettre de désactiver, mettre en pause, une scene via la methode `disable()`. On réactive une scene via la methode `enable()`. Une méthode désactivé ne sera pas exécuter ni rendu par la boucle principale.

### Création de scene

Afin de s'intégrer parfaitement à l'application, chaque scène se doit de respecter une architecture de base précise. Ceci permet de conserver un comportement indentique entre les scènes, mais offre quand même une très grande liberté dans la réalisation de ces dernières.

Une scene vierge ressemble à ceci :

```cpp
#include "libraries.hpp"
#include "Scene.hpp"
namespace Scenes
{
  class MaScene: public Scene
  {
  public:
    static void load();
    void init();
    void execute();
    void render();
    ~MaScene();
 };
}
```

Chaque scène doit être déclarée au sein du namespace `Scenes`, étendre la superclasse `Scene`. Ces deux critères sont nécessaires afin que la scène puisse être manipulée par l'application, et afin d'éciter tout risque de collision de noms.  
Enfin, la scene doit être référencée à la fin du fichier `Scenes/Scenes.hpp` pour pouvoir être utilisée.

Une scène requiert trois méthodes indispensables pour pouvoir fonctionner.

#### init\(\)

Appelée une seule fois à la création de la scene, la méthode `init()` permet à la scène de charger toutes les ressources dont elle a besoin pour fonctionner. 

#### execute\(\)

Appelée à chaque début de boucle de rendu, la méthode `execute()` à pour vocation de prendre en compte les interactions utilisateurs, et de faire évoluer son état en conséquence. 

#### render\(\)

La méthode de rendu est appelée à chaque fin de boucle. Son but n'est plus de préparer l'interface, mais de rendre ces différentes éléments sur l'écran.

#### Les événements

La superclass `Scenes` fournis des méthodes appelées uniquement dans certaines conditions. Il n'est pas obligatoire de les redéfinirs. Chaque scène les utilisent seulement si elle en a besoin. 

* `onWindowResize()` - Appelée quand la fenêtre de l'application est redimensionnée.
* D'autres a venir...

