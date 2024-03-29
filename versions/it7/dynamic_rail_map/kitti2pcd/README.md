# kitti2pcd

[![Version](https://img.shields.io/badge/Version-0.1.0-blue)](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/tree/main/kitti2pcd)
[![Pipeline](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/badges/main/pipeline.svg)](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/pipelines?page=1&scope=all&ref=main)

### Beschreibung:

Das kitti2pcd Programm konvertiert die Frames einer oder mehrerer Chunks aus dem Kitti-Format zu PCL-Dateien und fasst
diese pro Chunk in eine `combined.pcl`-Datei zusammen.

## Quickstart:

Schnellstart unseres Programms für Ungeduldige. \
**Wichtig:** Stellen in Befehlen, die in spitzen Klammern stehen <...>,  müssen durch die jeweils beschriebene Information ersetzt werden.

### Installation:

Für das Compilen dieser Software nach dieser Anleitung muss Git installiert sein. \
Wie Git installiert wird, ist  [hier](https://git-scm.com/book/de/v2/Erste-Schritte-Git-installieren) beschrieben. \
Für das Compilen wird mindestens gcc-10 benötigt.

```bash
sudo apt-get install -y libeigen3-dev libpcl-dev
git clone --recurse-submodules https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map.git
mkdir dynamic_rail_map/kitti2pcd/.build
cd dynamic_rail_map/kitti2pcd/.build 
cmake .. 
cmake --build . --target install --config Debug
```

Die ausführbare Datei befindet sich dann im `.build` Ordner. \
Sollten die Libraries Eigen3 und PCL bereits installiert sein, 
kann der erste Befehl übersprungen werden. Wenn das repo bereits geclonet wurde, kann der zweite Befehl
ebenfalls übersprungen werden.

### Ausführung:

Im `.build`-Ordner ausführen.

##### Einzelne Chunks zu einer PCL-Datei konvertieren:

```bash
./kitti2pcd <Pfade zu Chunkordnern> -o <Pfad zu einem Outputordner>  
```

##### Einen oder mehrere Ordner voller Chunks zu einer PCL-Datei konvertieren:

```bash
./kitti2pcd -r <Pfade zu Mapordnern> -o <Pfad zu einem Outputordner>  
```

Genauere Informationen zu Einstellmöglichkeiten und Parametern können mithilfe des Arguments `--help` abgerufen werden.

![Bild von Help](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/kitty2pcl/help.png)

## Dependencies:

- [PCL >=1.10.0](https://pointclouds.org/)
- [Eigen3](https://eigen.tuxfamily.org/)

## Autoren:

Alicia Gleichmann,
Greys Fankyeyeva,
Leonhard Steinecke,
Severin Pelikan,
Simon Riese

Unter der Leitung von Alexander Kroth.
