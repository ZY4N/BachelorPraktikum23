# Design Meetings Protokolle Iteration 5:
---
Datum: 12.01.2024  
Teilnehmer: Alicia Gleichmann, Greys Fankyeyeva, Leonhard Steinecke, Severin Pelikan, Simon Riese
Code Review Datum: 21.01.2024

## User Story: 16 - Export zu segmentierten Kartenformat
#### Funktionalitäten
Die Punktwolke soll für den späteren Export in Chunks aufgeteilt werden.
#### Schnittstellen
Hierfür soll eine Klasse implementiert werden, die die Punktwolke anhand ihrer Position in Chunks aufteilt. Die Chunks können dann über die "Frame Exporter" Schnittstelle getrennt voneinander in eigene Verzeichnisse geschrieben werden.
#### Erweiterbarkeit
Hier stehen die QS-Ziele Erweiterbarkeit und Effizienz im Konflikt.
Nach Absprache mit unserem Arbeitgeber sind hier keine Erweiterungen vorgesehen und es werden entsprechend keine Designs festgelegt.

#### Wie wird Leistung und Ressourcenverwendung ins Design einbezogen?
- Der Sortieralgorithmus soll einen Hybridansatz verwenden, der so viele Punkte, wie durch die maximale Speicherauslastung zugelassen, mit einem Hash basierten Bucket Sort in O(N) umsetzt und für die restlichen Punkte einen klassischen Sortieralgorithmus mit O(N·log(N)) Vergleichen einsetzt.
- Der Speicher für die Buckets, soll möglichst am Anfang allokiert werden und danach nicht mehr reallokiert werden.
- Das Aufteilen der Punkte auf Chunks sowie das Schreiben der Kartensegmente, soll alle zur Verfügung stehenden Threads effektiv nutzen können.

---

## User Story: 17 - Sammeln von Metadaten
#### Funktionalitäten
Es sollen während der Programmausführung Metadaten gesammelt werden.
#### Schnittstellen
Es wird eine Struct definiert, in dem die Metadaten eingetragen werden.
Im Metadaten-Struct sollen folgende Daten Gruppiert in Arrays enthalten sein:
Die genutzten Programmparameter (version, lidar_topic, relative_begin_time, Relative_end_time, origin_ignore_radius, max_scan_position_deviation, max_radial_distance, max_peripheral_distance), Daten zu den genutzten Rosbags (name) und Informationen zu den Scans (scan_combiner_config_index, rosbag_index, begin_index, end_index, point_count).
Dabei wird über scan_combiner_config_index und rosbag_index Einträge aus den drei Informationsgruppen einander zugordnet. 
#### Erweiterbarkeit
Es ist vorgesehen Felder im Struct hinzuzufügen zu können. Dies ist über eine übersichtlicht Struktur möglich.
#### Wie wird Leistung und Ressourcenverwendung ins Design einbezogen?
- Bei den Rosbagdaten und den Programmparametern doppeln sich Einträge in den Metadaten. Um Arbeits- und Festplattenspeicher zu sparen, soll für das Einfügen von Einträgen jeweils eine Funktion implementiert werden, die nur einzigartige Einträge zulässt.

---

## User Story:  18 - Lesen und Schreiben von Metadaten im JSON-Format
#### Funktionalitäten
Die gesamelten Metadaten sollen mit der Karte als JSON-Datei exportiert werden.
#### Schnittstellen
Hierfür wird eine "Metadaten Exporter" Schnittstelle implementiert, in der Module zur Ausgabe der Metadaten hinterlegt werden können. 
In dieser kann dann über eine Schreibefunktion und eine Lesefunktionen ein Modul ausgewählt und ausgeführt werden.
Es wird außerdem ein JSON-Modul für diese Schnittstelle erstellt, die die Metadaten im JOSN-Format ausgibt.
#### Erweiterbarkeit
Es soll möglich sein weiter Ausgabeformate hinzuzufügen. Dies wird über die "Metadaten Exporter" Schnittstelle und den Ausgabemodulen umgesetzt.
#### Wie wird Leistung und Ressourcenverwendung ins Design einbezogen?
- Für möglichst gute Leistung beim Schreiben und Lesen von JSON-Dateien, soll die auf Leistung ausgelegte Bibliothek RapidJSON verwendet werden.