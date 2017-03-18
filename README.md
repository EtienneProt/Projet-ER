# Code pour le SPI en ER :

## Test du SPI : 

### Schéma de cablage : 

On prend deux arduino uno et on relit :
- les deux broches 13 (signal d'horloge)
- les deux broches 12 (Signal MISO : Master INPUT SLave OUTPUT)
- les deux broches 11 (signal MOSI : Master OUTPUT Slave INPUT)
- les deux broches 10 (signal de selection de l'esclave)

Pour le test on branche une led avec en série un résistance de 220 Ohms afin de vérifier le fonctionnement de la liaison SPI, ensuite on peut, si on veut, rajouter un oscilloscope sur différentes broches de l'arduino afin de voir les signaux. 
Personnelement j'ai un oscilloscope à une voie donc je l'ai mis au bornes de la led afin de voir le changement de tension à ses bornes. 

### Code pour l'arduino Master :

```C
```
