# Simulateur B4SKET-GAME 2022

## Présentation du protocole implanté dans le simulateur ESP'ACE

Ce document présente rapidement le fonctionnement du simulateur ainsi que le protocole implémenté. Le protocole complet est disponible dans Google Drive. Actuellement, la version du protocole est la **0.2** (09 juin 2022).

## Configuration du simulateur

Valeur par défaut :

```cpp
#define NB_PANIERS              7
```

## Fonctionnement

- Trame de début de partie :

```
$basket;STT;5;\r
$basket;ACK;5;\r
```

`5` : nombre de paniers

- Trames de détection :

```
$basket;P;2;R;\r
$basket;P;5;J;\r
$basket;P;0;R;\r
$basket;P;1;J;\r
$basket;P;5;R;\r
```

- Trame de fin de partie :

```
$basket;STP;\r
$basket;ACK;\r
```

## platform.ini

```ini
[env:lolin32]
platform = espressif32
board = lolin32
framework = arduino
lib_deps =
  thingpulse/ESP8266 and ESP32 OLED driver for SSD1306 displays @ ^4.2.0
upload_port = /dev/ttyUSB0
upload_speed = 115200
monitor_port = /dev/ttyUSB0
monitor_speed = 115200
```

## Auteur

- Thierry Vaira <<tvaira@free.fr>>
