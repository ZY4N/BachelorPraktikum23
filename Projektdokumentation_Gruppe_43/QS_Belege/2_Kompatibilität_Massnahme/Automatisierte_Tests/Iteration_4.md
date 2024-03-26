# Testdurchläufe:

## Entfernen von Nick- und Schwankbewegungen aus Scans (ID: 8)
#### Push am 28.12.2023 um 22:18 Uhr
![](imu_p1.png)
- Gepusht von: Severin Pelikan
- Ergebnis: Fehler beim Kompilieren
- Konsequenzen: Implementation noch nicht vollständig. Entwicklung muss fortgesetzt werden.
#### Push am 06.01.2024 um 00:41 Uhr
![](imu_p2.png)
![](imu_t2.png)
- Gepusht von: Severin Pelikan
- Ergebnis: Erfolgreich
- Konsequenzen:  QS-Maßnahme gilt als bestanden



---

## Integration von Removert in Scan Combiner (ID: 9)
#### Push am 28.12.2023 um 18:23 Uhr
![](kitti_p1.png)
- Gepusht von: Simon Riese
- Ergebnis: Fehler beim Kompilieren
- Konsequenzen: Implementation noch nicht vollständig. Entwicklung muss fortgesetzt werden.
#### Push am 05.01.2024 um 14:00 Uhr
![](kitti_p2.png)
![](kitti_t2.png)
- Gepusht von: Simon Riese
- Ergebnis: Erfolgreich
- Konsequenzen:  QS-Maßnahme gilt als bestanden

---

## Entfernung dynamischer Objekte mittels Removert (ID: 10)
#### Userstory Enthält keinen Code darum gibt es keine Durchführung der Pipeline

---

## Docker Integration für Zielsystem  (ID: 11)

#### Push am 23.12.2023 um 22:14 Uhr
![](docker_integration_p1.png)
- Gepusht von: Leonhard Steinecke
- Ergebnis: Fehler beim Kompilieren
- Konsequenzen: CMakeLists.txt müssen überarbeitet werden, sodass es auf der Zielhardware (repräsentiert durch das Dockerimage) läuft.
#### Push am 23.12.2023 um 22:44 Uhr
![](docker_integration_p2.png)
- Gepusht von: Leonhard Steinecke
- Ergebnis: Fehler bei den Tests
- Konsequenzen: Fehler im Script der Pipeline. Tests wurden nicht korrekt aufgerufen. Script muss entsprechend angepasst werden. 
#### Push am 23.12.2023 um 23:06 Uhr
![](docker_integration_p3.png)
![](docker_integration_t3.png)
- Gepusht von: Leonhard Steinecke
- Ergebnis: Erfolgreich
- Konsequenzen: QS-Maßnahme gilt als bestanden
#### Push am 04.01.2024 um 13:41 Uhr
![](docker_integration_p4.png)
![](docker_integration_t4.png)
- Gepusht von: Leonhard Steinecke
- Ergebnis: Erfolgreich
- Konsequenzen: QS-Maßnahme gilt als bestanden

---

## Dynamisches Anpassen des Ausgabeformats über CLI  (ID: 12)
#### Push am 27.12.2023 um 14:12 Uhr
![](cli_output_p1.png)
![](cli_output_t1.png)
- Gepusht von: Alicia Gleichmann
- Ergebnis: Erfolgreich
- Konsequenzen: QS-Maßnahme gilt als bestanden
#### Push am 03.01.2024 um 16:25 Uhr
![](cli_output_p2.png)
![](cli_output_t2.png)
- Gepusht von: Alicia Gleichmann
- Ergebnis: Erfolgreich
- Konsequenzen: QS-Maßnahme gilt als bestanden

---

## Dynamisches Anpassen der Loggerkonfiguration über CLI  (ID: 13)
#### Push am 04.01.2024 um 20:44 Uhr
![](cli_log_p1.png)
![](cli_log_t1.png)
- Gepusht von: Alicia Gleichmann
- Ergebnis: Erfolgreich
- Konsequenzen: QS-Maßnahme gilt als bestanden


---

## Anpassung der Arbeitsspeicherauslastung über CLI (ID: 14)
#### Push am 28.12.2023 um 10:17 Uhr
![](cli_memory_utilization_p1.png)
- Gepusht von: Alicia Gleichmann
- Ergebnis: Fehler beim Kompilieren
- Konsequenzen: Implementation noch nicht vollständig. Entwicklung muss fortgesetzt werden.
#### Push am 06.01.2024 um 12:11 Uhr
![](cli_memory_utilization_p2.png)
![](cli_memory_utilization_t2.png)
- Gepusht von: Alicia Gleichmann
- Ergebnis: Fehler bei Chrono Test
- Konsequenzen: Fehler beim Parsen von Chrono-Literalen. Muss vor Abnahme der User Story behoben werden.
#### Push am 06.01.2024 um 17:27 Uhr
![](cli_memory_utilization_p3.png)
![](cli_memory_utilization_t3.png)
- Gepusht von: Alicia Gleichmann
- Ergebnis: Erfolgreich
- Konsequenzen: QS-Maßnahme gilt als bestanden


---

## Dynamisches Anpassen der maximalen radialen und peripheren Distanzen über CLI (ID: 15)
#### Push am 05.01.2024 um 11:02 Uhr
![](cli_filter_p1.png)
![](cli_filter_t1.png)
- Gepusht von: Alicia Gleichmann
- Ergebnis: Erfolgreich
- Konsequenzen: QS-Maßnahme gilt als bestanden

---

