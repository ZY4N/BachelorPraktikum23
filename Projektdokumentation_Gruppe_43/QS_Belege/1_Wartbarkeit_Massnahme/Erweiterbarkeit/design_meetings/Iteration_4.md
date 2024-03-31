# Design Meetings Protokolle Iteration 4:
---
Datum: 20.12.2023  
Teilnehmer: Alicia Gleichmann, Greys Fankyeyeva, Severin Pelikan, Simon Riese
Code Review Datum: 08.01.2024

## User Story: 8 - Entfernen von Nick- und Schwankbewegungen aus Scans
#### Funktionalitäten
Die Positition der Punkte in der Punktwolke sollen anhand der von der Bahn über die IMU aufgenommenen Nick- und Schwankbewegungen korrigiert werden.
#### Schnittstellen
Es wird eine Funktion implementiert, die durch die Aufnahme- und Geschwindigkeitsdaten den Fehler durch Nick- und Schwankbewegungen approximiert. Diese korrigiert dann anhand der Approximation für jeden Punkt die Position.
#### Erweiterbarkeit
Hier stehen die QS-Ziele Erweiterbarkeit und Effizienz im Konflikt.
Nach Absprache mit unserem Arbeitgeber sind hier keine Erweiterungen vorgesehen und es werden entsprechend keine Designs festgelegt.
#### Wie wird Leistung und Ressourcenverwendung ins Design einbezogen?
- Die IMU Rotations Daten sollen eng gepackten Structs geladen werden.
- Das Korrigieren der Sensorrotation soll keinen zusätzlichen Heap-Speicher nutzen.

---

## User Story: 9 - Integration von Removert in Scan Combiner 
#### Funktionalitäten
Die verarbeiten Punkte sollen mit ihren Aufnahmeposition als Karte im KITTI-Format ausgegeben werden.
#### Schnittstellen
Es wird ein KITTI-Modul für die "Frame Exporter" Schnittstelle aus US-4 erstellt, die die Karte im KITTI-Format ausgibt.
#### Erweiterbarkeit
Die Implementation wird mit der in US-4 erstellten Schnittstelle als Modul hinzugefügt und profitiert damit von dem Fokus auf Erweiterbarkeit.
#### Wie wird Leistung und Ressourcenverwendung ins Design einbezogen?
- Die Schreibfunktion des Moduls und der Schnittstelle sollen Daten über eine `tcb::span` (C++ 17 Implementation von `std::span`) erhalten, um unnötiges Kopieren von Daten zu vermeiden.
- Die Punktdaten der Punktwolke des KITTI-Formats werden in Binär geschrieben, so wird weniger Festplattenspeicher verbraucht.

---

## User Story: 10 - Entfernung dynamischer Objekte mittels Removert
#### Funktionalitäten
N/A
#### Sonstiges
Hier wird kein Code geschrieben und daher ist kein Design notwendig.

---

## User Story: 11 - Docker Integration für Zielsystem
#### Funktionalitäten
N/A
#### Sonstiges
Hier wird kein Code geschrieben und daher ist kein Design notwendig.

---

## User Story: 12, 13, 14, 15 - Erweiterung der CLI Parameter
#### Funktionalitäten
Einige bisher im Code festgelegten Werte(Ausgabeformat der Frames, zu bearbeitenden Zeitabschnitt und Distanzfilterparamter) sollen dynamisch über CLI Parameter festgelegt werden.
#### Schnittstellen
Die neuen CLI Parameter werden mit dem "Arx-System" aus US-7 implementiert.
Mit diesem System wird ein Parameter hinzugefügt, über welchen das Ausgabeformat der Frames festgelegt wird (UOS oder KITTI).
Es werden zwei Parameter hinzugefügt, über welche das Log-Level des Loggers und ob diese Farbig ausgegeben werden festgelegt wird.
Es wird ein Parameter hinzugefügt, über welchen die Zeitlänge festgelegt wird, die gleichzeitig bearbeitet wird.
Es werden zwei Parameter hinzugefügt, über welche die maximale radiale und die maximale periphere Distanz von Punkten zum LiDAR-Sensor festgelegt werden. 
#### Erweiterbarkeit
Durch den in US 7 implementierten Argumentparser können diese Erweiterungen effektiv umgesetzt werden.
#### Wie wird Leistung und Ressourcenverwendung ins Design einbezogen?
- Da das "Arx-System" nur einmal zu Programmbeginn ausgeführt wird hat es eine vernachlässigbare Auswirkung auf Leistung, daher braucht nicht besonders auf Leistung geachtet werden.