# Communication LoRaWAN sur microcontrôleur PIC
**TFE** 2019/2020 - Renaud **ALLARD** & Nathan **HENRY**

## Pré-requis

### Partie Electronique

Pour mettre en place la partie électronique de ce projet, il est nécessaire de posséder les logiciels suivants :

- Proteus 8.7 Professionnel
- MPLAB X IDE 5.30
    - Code Configurator V3
    - LoRaWAN library for MPLAB
- MPLAB XC8 compiler 

### Partie Application

Pour la partie application, il est nécessaire de posséder un serveur sur lequel héberger le service, ainsi que les composants suivents :

- Make
- Docker
- Docker-compose

## Setup

### Partie Electronique

1. Ouvrir le fichier *<tfe proteus/TFE.pdsrj>* avec le logiciel Proteus
2. Double-Click sur le PIC
3. Bouton *Program File*
4. Sélectionner *TFE_TEMP.X/dist/default/production/blink_test.X.production.hex*
5. Lancer la simulation

### Partie Application

1. Dans le dossier *TFE_WEB*
> cp .env.dist .env
2. Remplir les variables présentes pour configurer la base de données
3. Dans le dossier *TFE_WEB/tfe*
> cp .env .env.local
4. Modifier les valeurs *APP_SECRET* et *JWT_PASSPHRASE* pour sécuriser l'application
5. Modifier la variable DATABASE_URL en fonction des données entrées à l'étape 2
6. Dans le dossier *TFE_WEB*
> make setup
7. Lorsque que c'est requis, entrer la même valeur que *JWT_PASSPHRASE* dans les prompts qui vont suivre

Le service est maintenant setup, il ne reste plus qu'à configurer nos devices LoRa.
