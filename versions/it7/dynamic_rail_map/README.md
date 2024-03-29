# Dynamic Rail Map

[![Wiki](https://img.shields.io/badge/-Wiki-8A2BE2)](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/home)
[![Pipeline](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/badges/main/pipeline.svg)](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/pipelines?page=1&scope=all&ref=main)

### Beschreibung:

Das Ziel des Dynamic Railmap Projekts ist es, automatisiert eine 3D-Karte aus den Sensordaten mehrerer Fahrten der
InnoTram zu erstellen. Die Basis bilden dabei die LiDAR-Daten. Im Zuge dieser Kartierung sollen alle dynamischen und
semi-dynamischen Objekte entfernt werden. Außerdem soll die Karte für eine effiziente Handhabung in Chunks (Raster)
aufgeteilt sein.

1. **Scan Combination:**

In der ersten Stufe werden die LiDAR-Daten mehrerer Fahrten präzise ausgerichtet und anhand zusätzlicher Sensordaten in
Chunks unterteilt, was die Grundlage für die 3D-Karte bildet.

2. **Dynamic Object Removal (work in progress):**

Im nächsten Schritt müssen alle dynamischen Objekte entfernt werden. Als dynamisches Objekt zählt alles, was sich
während der Aufnahme bewegt, zum Beispiel fahrende Autos oder Fußgänger, die über den Luisenplatz laufen.

3. **Semi-Dynamic Object Removal (work in progress):**

Bei dieser Stufe sollen auch alle semi-dynamischen Objekte entfernt werden. Dabei handelt es sich um Objekte, die in den
Aufnahmen oft an denselben Stellen stehen, aber nicht verlässlicher Bestandteil der statischen Umgebung sind. Beispiele
dafür sind Autos, die an roten Ampeln halten, Personen, die an Haltestellen warten oder auch die Stände des
Weihnachtsmarkts.

## Wiki:

[Übersicht](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/Home)

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
- [Dynamic Object Removal](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/dynamic_object_removal)
    - [People Remover](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/dynamic_object_removal/people_remover)
    - [Removert](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/dynamic_object_removal/removert)
- [Semi-Dynamic Object Removal](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/semi_dynamic_object_removal/semi_dynamic_object_removal)
- [Code Guidelines](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/code_guidelines)
    - [C API](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/code_guidelines/c_api)
    - [Compilation](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/code_guidelines/compilation)
    - [Documentation](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/code_guidelines/documentation)
    - [Modern C++](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/code_guidelines/modern_cpp)
    - [Style Guidelines](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/code_guidelines/style_guidelines)

[All Pages](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/pages)

## Aktueller Stand:

Die erste Stufe, der `scan_combiner`, ist abgeschlossen.

Bei dem Entfernen dynamischer Objekte wurden einige externe Projekte evaluiert und testweise in das System integriert.
Allerdings waren die Ergebnisse dieser Implementationen nicht zufriedenstellend.\
Mehr dazu im [Wiki](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/dynamic_object_removal).

Für das Entfernen semi-dynamischer Objekte wurden einige Grundkonzepte erarbeitet.\
Mehr dazu
im [Wiki](https://git.rwth-aachen.de/fzd/maas/dynamic_rail_map/-/wikis/semi_dynamic_object_removal/semi_dynamic_object_removal).

## Autoren:

Alicia Gleichmann,
Greys Fankyeyeva,
Leonhard Steinecke,
Severin Pelikan,
Simon Riese

Unter der Leitung von Alexander Kroth.