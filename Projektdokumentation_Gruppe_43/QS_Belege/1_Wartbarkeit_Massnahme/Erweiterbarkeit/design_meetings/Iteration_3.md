# Design Meetings Protokolle Iteration 3:
---
Datum: 30.11.2023  
Teilnehmer: Alicia Gleichmann, Greys Fankyeyeva, Leonhard Steinecke, Severin Pelikan, Simon Riese
Code Review Datum: 16.12.2023

## User Story: 6 - Verringerung von Aufnahmetransformationen
#### Funktionalitäten
Die Anzahl der zu speichernden Aufnahmetransformationen soll reduziert werde, indem mehrere ähnliche Aufnahmetransformationen zu einer zusammengefasst werden.
#### Schnittstellen
Hierfür wird eine Funktion implementiert die die Aufnahme- und Geschwindigkeitsdaten erhält und über Interpolation die Aufnahmeposition für jeden Punkt aproximiert und die Punkte anhand dessen zu einem Frame zu ordnet.
#### Erweiterbarkeit
Hier stehen die QS-Ziele Erweiterbarkeit und Effizienz im Konflikt.
Nach Absprache mit unserem Arbeitgeber sind hier keine Erweiterungen vorgesehen und es werden entsprechend keine Designs festgelegt.
#### Wie wird Leistung und Ressourcenverwendung ins Design einbezogen?
- Die Implementation darf die Aufnahmepositionen nicht im Heap zwischenspeichern, sondern muss eine In-Place Lösung finden.
- Das Transformieren der Punkte zu den vereinten Aufnahmepositionen soll in größeren Blöcken geschehen, um Cache Lokalität und SIMD ausnutzen zu können.

---

## User Story: 7 - Dynamisches Anpassen von Ein- und Ausgabepfaden über CLI
#### Funktionalitäten
Die Inputpfade und der Outputpfad sollen dynamisch über CLI-Parameter eingestellt werden können.
Es soll möglich sein, einfach für neue CLI-Parametern das Hinzufügen, Definieren und Parsen zu implementieren.
#### Schnittstellen
Es wird das "Arx-System" hinzugefügt über das die Flaggen, der gewollte Datentyp und der Standardwert für neue CLI-Paramerter einfach definiert werden kann.
Es können außerdem in dem System weitere Parser für bisher nicht unterstütze Datentypen hinzugefügt werden und das System gibt entsprechende Fehlermeldung aus, falls notwendige Parameter fehlen.
Mit diesem System werden zwei Parameter, über welche die Positionen der zu bearbeitenden Daten und der Ausgabeort der bearbeiteten Daten festgelegt werden müssen, hinzugefügt. 
#### Erweiterbarkeit
Es soll möglich sein das Programm einfach um weitere CLI-Parametern zu ergänzen.
Durch die implementierung des obengenannten Systems, wird dies umgesetzt.
#### Wie wird Leistung und Ressourcenverwendung ins Design einbezogen?
- Da das "Arx-System" nur einmal zu Programmbeginn ausgeführt wird hat es eine vernachlässigbare Auswirkung auf Leistung, daher braucht nicht besonders auf Leistung geachtet werden.
 
