# Design Meeting Iteration 6
Datum: 23.01.2024
Teilnehmer: Alicia Gleichmann, Greys Fankyeyeva, Leonhard Steinecke, Severin Pelikan, Simon Riese

## User Story(s):  19 - Ausarbeitung von Grundkonzepten zur Entfernung semi-dynamischer Objekte
#### Was wird implementiert?
N/A
#### Sonstiges
Hier wird kein Code geschrieben und daher ist kein Design notwendig.


## User Story(s): 20,21,22 - Erweiterung der CLI Parameter 
#### Funktionalitäten
Einige bisher im Code festgelegten Werte(Chunkgröße, maximal erlaubte Abweichung von Scanpositionen und Ausgabeformat der Metadaten) sollen dynamisch über CLI Parameter festgelegt werden.
#### Schnittstellen
Die neuen CLI Parameter werden mit dem "Arx-System" aus US-7 implementiert.
Über “--max-scan-pos-deviation“ kann die maximal erlaubte Abweichung zwischen Scanpositionen in einem Frame angepasst werden.
Über “--chunk-size" kann die Raster-Größe des Chunks (in Meter) angepasst werden.
Über “--metadata-format" kann das Ausgabeformat der Metadaten angepasst werden.
#### Erweiterbarkeit
Durch den in US 7 implementierten Argumentparser können diese Erweiterungen effektiv umgesetzt werden.
#### Wie wird Leistung und Ressourcenverwendung ins Design einbezogen?
- Da das "Arx-System" nur einmal zu Programmbeginn ausgeführt wird hat es eine vernachlässigbare Auswirkung auf Leistung, daher braucht nicht besonders auf Leistung geachtet werden.