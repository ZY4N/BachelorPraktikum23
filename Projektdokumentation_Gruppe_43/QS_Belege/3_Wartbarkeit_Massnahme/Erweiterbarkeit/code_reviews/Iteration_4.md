## User Story:  8 - Entfernen von Nick- und Schwankbewegungen aus Scans 
Datum: 08.01.2024
Entwickler*innen: Severin Pelikan
Code Buddy: Leonhard Steinecke
#### Ergebnis des Reviews: 
* Wurden die Maßnahmen für Erweiterbarkeit korrekt umgesetzt?
    - N/A
* Wurden die Maßnahmen für Leistung und Ressourcenverwendung korrekt umgesetzt ?
    - Die IMU Daten werden in 32 Byte großen Quaternions geladen, um Cache-Line Auslastung zu maximieren.
    - Die eigentliche Korrektur wurde nicht implentiert und kann dementsprechend nicht evaluiert werden.
* Probleme, die im Code Review gefunden wurden: 
    - Beim Testen ist aufgefallen, dass die bereitgestellten IMU-Sensordaten fehlerhaft sind, darum wurde die User Story nicht ins entgültige System übernommen. 
  
## User Story:  9 - Integration von Removert in Scan Combiner 
Datum: 08.01.2024
Entwickler*innen: Simon Riese
Code Buddy: Greys Fankyeyeva
#### Ergebnis des Reviews: 
* Wurden die Maßnahmen für Erweiterbarkeit korrekt umgesetzt?
    - Es wurde die in US 4 erstellte Ausgabeschnittstelle genutzt, um das System zu erweitern.
* Wurden die Maßnahmen für Leistung und Ressourcenverwendung korrekt umgesetzt?
    - Der Schnittstelle und dem Modul werden die Punktdaten als`tcb:span` übergeben, um Kopien zu vermeiden.
    - Die Punktdaten werden von dem Modul in Binär gespeichert
* Probleme, die im Code Review gefunden wurden: 
    - Es wurden keine Probleme im Code Review gefunden.

## User Story: 12,13,14,15 - Erweiterung der CLI Parameter
Datum: 08.01.2024
Entwickler*innen: Alicia Gleichmann
Code Buddy: Severin Pelikan
#### Ergebnis des Reviews: 
* Wurden die Maßnahmen für Erweiterbarkeit korrekt umgesetzt?
    - Durch den in US 7 implementierten "Arx-System" konnten diese Erweiterungen effektiv umgesetzt werden.
* Wurden die Maßnahmen für Leistung und Ressourcenverwendung korrekt umgesetzt?
    - N/A
* Probleme, die im Code Review gefunden wurden: 
    - Es wurden keine Probleme im Code Review gefunden.