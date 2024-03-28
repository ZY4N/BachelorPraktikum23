# Scan Combiner

[![Scan Combiner Wiki](https://img.shields.io/badge/-Wiki-8A2BE2)](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/scan_combiner)
[![Version](https://img.shields.io/badge/Version-1.0.0-blue)](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/tree/main/scan_combiner)
[![Pipeline](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/badges/main/pipeline.svg)](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/pipelines?page=1&scope=all&ref=main)

### Beschreibung:

Der Scan Combiner erstellt aus den Aufnahmen mehrerer InnoTram Fahrten eine kontinuierliche Karte auf Basis der
LiDAR-Daten. Diese werden dann in Chunks in einem auswählbaren Format und mit zusätzlichen Metadaten gespeichert.
Genauere Informationen befinden sich
im [Wiki](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/scan_combiner).

### Features-Übersicht:

- Einlesen von einem oder mehreren Rosbags
- Einlesen von mehreren LiDAR-Sensortypen möglich
- Filterung der Punkte nach Entfernung zum LiDAR-Sensor
- Herausfiltern von invaliden Daten
- Multithreading mit einstellbarer Threadanzahl
- Nutzung der Positionsdaten und Interpolation zwischen diesen, um eine möglichst genaue Karte zu erhalten
- Reframing, um die Anzahl an Positionsdaten zu verringern.
- Aufteilung in Chunks mit einstellbarer Größe um den Ursprung
- Export in verschiedenen Datenformaten

## Quickstart:

Schnellstart unseres Programms für Ungeduldige. \
**Wichtig:** Stellen in Befehlen, die in spitzen Klammern stehen <...>,  müssen durch die jeweils beschriebene Information ersetzt werden.

### Installation:

Für das Compilen dieser Software müssen die Developer-Tools von ROS1 sowie Git installiert sein. \
Anleitung für die Installation von ROS1:noetic (getestete Version) findet
ihr [hier](https://wiki.ros.org/noetic/Installation/Ubuntu) \
Wie Git installiert wird, ist  [hier](https://git-scm.com/book/de/v2/Erste-Schritte-Git-installieren) beschrieben. \
Für das Compilen wird mindestens gcc-10 benötigt.

Zuerst müssen Schritt zwei und drei nach [dieser](https://wiki.ros.org/ROS/Tutorials/InstallingandConfiguringROSEnvironment) Anleitung ausgeführt werden.
Danach müssen im Terminal folgende Befehle nacheinander ausgeführt werden:

```bash
sudo apt-get install -y libeigen3-dev
git clone --recurse-submodules https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map.git
mkdir dynamic_rail_map/scan_combiner/.build
cd dynamic_rail_map/scan_combiner/.build 
cmake .. 
cmake --build . --target install --config Debug
```

Die ausführbare Datei befindet sich dann im `.build` Ordner. \
Sollten die Library Eigen3 bereits installiert sein, 
kann der erste Befehl übersprungen werden. Wenn das repo bereits geclonet wurde, kann der zweite Befehl
ebenfalls übersprungen werden.

### Ausführung:

Im `.build`-Ordner folgende Befehle ausführen:

```bash
./scan_combiner -o <Pfad zum Ausgabeordner> <Pfad zu Eingabe rosbags>
```

Genauere Informationen zu Einstellmöglichkeiten und Parametern finden sich in unserem [Wiki](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/scan_combiner/parameters).

## Beispiel:

![Beispiel 1](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/scan_combiner/scan_combiner_chunks.png)

Zeigt die vier 30m x 30m Chunks um das Ludwigsmonument.

## Wiki Scan Combiner:

Enthält alle wichtigen Informationen zum Benutzten, Verstehen und Erweitern des Scan Combiners:

- [Scan Combiner](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/scan_combiner)
    - [CLI Parameter](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/scan_combiner/parameters)
    - [Funktionsweise](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/scan_combiner/funktionsweise)
    - [Metadaten](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/scan_combiner/metadata)
    - [Ausgabeformate](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/scan_combiner/output_formats)
    - [Module](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/scan_combiner/module)
        - [LiDAR Sensoren](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/scan_combiner/add_new_lidar_sensor)
        - [Frame Formate](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/scan_combiner/add_new_frame_format)
        - [Metadaten Formate](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/scan_combiner/add_new_metadata_format)
    - [CI/CD-Pipeline](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/scan_combiner/ci_pipeline)
    - [Port ROS2](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/scan_combiner/port_ros_2)

## Dependencies:

- [ROS1 noetic](https://wiki.ros.org/noetic)
- [Eigen3](https://eigen.tuxfamily.org/)
- [rapidjson](https://github.com/Tencent/rapidjson)
- [tcbrindle/span](https://github.com/tcbrindle/span)

## Autoren:

Alicia Gleichmann,
Greys Fankyeyeva,
Leonhard Steinecke,
Severin Pelikan,
Simon Riese

Unter der Leitung von Alexander Kroth.
