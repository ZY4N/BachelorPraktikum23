# Code Reviews Iteration 7:

## Code Review Checklist - User Story: 23 - PCD Converter
Datum: 20.02.2024</br>
Entwickler*innen: Greys Fankyeyeva</br>
Code Buddy: Alicia Gleichmann
### Struktur:
  - [x] Wurden die Akzeptanzkriterien der User Story(s) erfüllt?
  - [x] Wurden die Entscheidungen des Design Meetings eingehalten?
  - [x] Wurden die Maßnahmen für Erweiterbarkeit korrekt umgesetzt?
  - [x] Wurden Code- und Style Richtlinien eingehalten?
  - [x] Wurden Linter und Code Formatter für alle veränderten Dateien angewendet?
  - [x] Werden alle Code- und Testabschnitte benutzt und kompiliert?
  - [x] Wurde Code, wenn sinnvoll, durch externe wiederverwendbare Komponenten oder Funktionen aus Bibliotheken ersetzt?
  - [x] Wurde sich wiederholende Code, wenn sinnvoll, in Hilfsfunktionen ausgelagert?
  - [x] Wurden „magic numbers“ vermieden?
  - [x] Gibt es keine Codeabschnitte, die unnötig komplex sind?
  - [x] Werden Typen korrekt gecastet und sind keine redundanten Variablen vorhanden?
  - [ ] Werden Dateien bevor auf diese zugegriffen auf Gültigkeit überprüft?
  - [x] Werden alle Fehler durch Error Codes kommuniziert und behandelt?

### Logik:
- [x] Gibt es offensichtliche Logikfehler?
- [x] Wurden alle Randfälle abgedeckt?
- [x] Wurden alle Schleifen korrekt konstruiert, iterieren diese nur über die notwendigen Elemente und terminieren diese?
- [x] Kann Code, wenn möglich außerhalb von Schleifen ausgeführt?
- [x] Wurden alle Logikverzweigungen inhaltlich korrekt erstellt?
- [x] Wurden, wenn möglich, die Anweisungen außerhalb der Schleife platziert?

### Lesbarkeit und Verständlichkeit:
- [x] Sind alle Identifier für Funktionen, Variablen und Typen aussagekräftig?
- [x] Haben alle Komponenten eine ausführliche und korrekte Dokumentation?
- [x] Sind die Kommentare und Dokumentation einheitlich mit dem Code (Namen etc.)?
- [x] Wurde notwendig komplexer Code oder nicht offensichtliche Entscheidungen ausreichend kommentiert?

### Leistung und Ressourcenverwendung:
- [x] Wurden die festgelegten Algorithmen und Datenstrukturen korrekt implementiert?
- [x] Wurden die vorgegebenen Implementationsdetails umgesetzt?
- [x] Lastet die Implementation die Hardware effektiv aus?

### Testabdeckung
- [x] Wurden ausführliche Tests für alle neuen Features geschrieben und laufen alle Tests erfolgreich durch?
- [x] Wurden alle Randfälle getestet?
- [x] Kompiliert das Programm in der Pipeline?
#### Ergebnis des Reviews: 
* Wurden die Maßnahmen für Erweiterbarkeit korrekt umgesetzt?
    - Es wurde die Bibliothek "PCL" genutzt, um das Schreiben zu implementieren. Somit kann der Konverter um andere PCD-Varianten erweitert werden. 
* Wurden die Maßnahmen für Leistung und Ressourcenverwendung korrekt umgesetzt?
    - TODO
* Probleme, die im Code Review gefunden wurden: 
    - Es wurde nicht überprüft, ob Dateien im Eingabepfad liegen. Dies wurde im Review behoben und dann akzeptiert.


## Code Review Checklist - User Story: 24 - Programm parallelisieren
Datum: 20.02.2024</br>
Entwickler*innen: Severin Pelikan</br>
Code Buddy: Greys Fankyeyeva
### Struktur:
  - [x] Wurden die Akzeptanzkriterien der User Story(s) erfüllt?
  - [x] Wurden die Entscheidungen des Design Meetings eingehalten?
  - [x] Wurden die Maßnahmen für Erweiterbarkeit korrekt umgesetzt?
  - [x] Wurden Code- und Style Richtlinien eingehalten?
  - [x] Wurden Linter und Code Formatter für alle veränderten Dateien angewendet?
  - [x] Werden alle Code- und Testabschnitte benutzt und kompiliert?
  - [x] Wurde Code, wenn sinnvoll, durch externe wiederverwendbare Komponenten oder Funktionen aus Bibliotheken ersetzt?
  - [x] Wurde sich wiederholende Code, wenn sinnvoll, in Hilfsfunktionen ausgelagert?
  - [x] Wurden „magic numbers“ vermieden?
  - [x] Gibt es keine Codeabschnitte, die unnötig komplex sind?
  - [x] Werden Typen korrekt gecastet und sind keine redundanten Variablen vorhanden?
  - [x] Werden Dateien bevor auf diese zugegriffen auf Gültigkeit überprüft?
  - [x] Werden alle Fehler durch Error Codes kommuniziert und behandelt?

### Logik:
- [x] Gibt es offensichtliche Logikfehler?
- [ ] Wurden alle Randfälle abgedeckt?
- [x] Wurden alle Schleifen korrekt konstruiert, iterieren diese nur über die notwendigen Elemente und terminieren diese?
- [x] Kann Code, wenn möglich außerhalb von Schleifen ausgeführt?
- [x] Wurden alle Logikverzweigungen inhaltlich korrekt erstellt?
- [x] Wurden, wenn möglich, die Anweisungen außerhalb der Schleife platziert?

### Lesbarkeit und Verständlichkeit:
- [x] Sind alle Identifier für Funktionen, Variablen und Typen aussagekräftig?
- [x] Haben alle Komponenten eine ausführliche und korrekte Dokumentation?
- [x] Sind die Kommentare und Dokumentation einheitlich mit dem Code (Namen etc.)?
- [x] Wurde notwendig komplexer Code oder nicht offensichtliche Entscheidungen ausreichend kommentiert?

### Leistung und Ressourcenverwendung:
- [x] Wurden die festgelegten Algorithmen und Datenstrukturen korrekt implementiert?
- [x] Wurden die vorgegebenen Implementationsdetails umgesetzt?
- [x] Lastet die Implementation die Hardware effektiv aus?

### Testabdeckung
- [x] Wurden ausführliche Tests für alle neuen Features geschrieben und laufen alle Tests erfolgreich durch?
- [x] Wurden alle Randfälle getestet?
- [x] Kompiliert das Programm in der Pipeline?
#### Ergebnis des Reviews: 
* Wurden die Maßnahmen für Erweiterbarkeit korrekt umgesetzt?
    - Da wir schon vorher auf die Erweiterung mit Unterstüzung für Multithreading geachtet habne konnte dies gut umgesetzt werden.
* Wurden die Maßnahmen für Leistung und Ressourcenverwendung korrekt umgesetzt?
    - Die Implementation nutzt separate Threads pro Rosbag-Topic sowie mehrere Verarbeitungs-Threads um die Daten zu verarbeiten.
    - Die Anzahl der Threads wrd mittels prozentualen Anteilen effektiv zwischen den Rosbag-Topics aufgeteilt.
    - Die Implementation nutzt `std::mutex` und `std::condition_variable` um die Synchronisation möglichst ressourcenschonend umzusetzen.
    - Die von einem Thread geladenen Punkte werden mittels eines Multipliers unter mehreren Verarbeitungsthreads aufgeteilt, um das Kombinieren der Punkt-Buffer vermeiden zu können.
* Probleme, die im Code Review gefunden wurden: 
    - Bei einer geringen Thread-Zahl wurden für einen Programmteil keine Threads zugewiesen. 
    - Konsequenz: Es wurde eine minimal Anzahl an Threads pro Programmteil gesetzt.

## Code Review Checklist - User Story: 25 - Unterstützung weiterer LiDAR-Sensoren
Datum: 20.02.2024
Entwickler*innen: Simon Riese, Severin Pelikan
Code Buddy: Greys Fankyeyeva
### Struktur:
  - [x] Wurden die Akzeptanzkriterien der User Story(s) erfüllt?
  - [x] Wurden die Entscheidungen des Design Meetings eingehalten?
  - [x] Wurden die Maßnahmen für Erweiterbarkeit korrekt umgesetzt?
  - [x] Wurden Code- und Style Richtlinien eingehalten?
  - [x] Wurden Linter und Code Formatter für alle veränderten Dateien angewendet?
  - [x] Werden alle Code- und Testabschnitte benutzt und kompiliert?
  - [x] Wurde Code, wenn sinnvoll, durch externe wiederverwendbare Komponenten oder Funktionen aus Bibliotheken ersetzt?
  - [x] Wurde sich wiederholende Code, wenn sinnvoll, in Hilfsfunktionen ausgelagert?
  - [x] Wurden „magic numbers“ vermieden?
  - [x] Gibt es keine Codeabschnitte, die unnötig komplex sind?
  - [x] Werden Typen korrekt gecastet und sind keine redundanten Variablen vorhanden?
  - [x] Werden Dateien bevor auf diese zugegriffen auf Gültigkeit überprüft?
  - [x] Werden alle Fehler durch Error Codes kommuniziert und behandelt?

### Logik:
- [x] Gibt es offensichtliche Logikfehler?
- [x] Wurden alle Randfälle abgedeckt?
- [x] Wurden alle Schleifen korrekt konstruiert, iterieren diese nur über die notwendigen Elemente und terminieren diese?
- [x] Kann Code, wenn möglich außerhalb von Schleifen ausgeführt?
- [x] Wurden alle Logikverzweigungen inhaltlich korrekt erstellt?
- [x] Wurden, wenn möglich, die Anweisungen außerhalb der Schleife platziert?

### Lesbarkeit und Verständlichkeit:
- [x] Sind alle Identifier für Funktionen, Variablen und Typen aussagekräftig?
- [x] Haben alle Komponenten eine ausführliche und korrekte Dokumentation?
- [x] Sind die Kommentare und Dokumentation einheitlich mit dem Code (Namen etc.)?
- [x] Wurde notwendig komplexer Code oder nicht offensichtliche Entscheidungen ausreichend kommentiert?

### Leistung und Ressourcenverwendung:
- [x] Wurden die festgelegten Algorithmen und Datenstrukturen korrekt implementiert?
- [x] Wurden die vorgegebenen Implementationsdetails umgesetzt?
- [x] Lastet die Implementation die Hardware effektiv aus?

### Testabdeckung
- [x] Wurden ausführliche Tests für alle neuen Features geschrieben und laufen alle Tests erfolgreich durch?
- [x] Wurden alle Randfälle getestet?
- [x] Kompiliert das Programm in der Pipeline?
#### Ergebnis des Reviews: 
* Wurden die Maßnahmen für Erweiterbarkeit korrekt umgesetzt?
    - Durch die Erstellung dieser Schnittstelle für Parser von LiDAR-Sensoren kann man nun das Programm einfach um weitere LiDAR-Sensoren erweitern.
* Wurden die Maßnahmen für Leistung und Ressourcenverwendung korrekt umgesetzt?
    - TODO
* Probleme, die im Code Review gefunden wurden: 
    - Es wurden keine Probleme im Code Review gefunden.

## Code Review Checklist - User Story: 26 - Erweiterung der Metadaten um Sensortypen und Rosbag-Topic
Datum: 20.02.2024
Entwickler*innen: Simon Riese 
Code Buddy: Leonhard Steinecke
### Struktur:
  - [x] Wurden die Akzeptanzkriterien der User Story(s) erfüllt?
  - [x] Wurden die Entscheidungen des Design Meetings eingehalten?
  - [x] Wurden die Maßnahmen für Erweiterbarkeit korrekt umgesetzt?
  - [x] Wurden Code- und Style Richtlinien eingehalten?
  - [x] Wurden Linter und Code Formatter für alle veränderten Dateien angewendet?
  - [x] Werden alle Code- und Testabschnitte benutzt und kompiliert?
  - [x] Wurde Code, wenn sinnvoll, durch externe wiederverwendbare Komponenten oder Funktionen aus Bibliotheken ersetzt?
  - [x] Wurde sich wiederholende Code, wenn sinnvoll, in Hilfsfunktionen ausgelagert?
  - [x] Wurden „magic numbers“ vermieden?
  - [x] Gibt es keine Codeabschnitte, die unnötig komplex sind?
  - [x] Werden Typen korrekt gecastet und sind keine redundanten Variablen vorhanden?
  - [x] Werden Dateien bevor auf diese zugegriffen auf Gültigkeit überprüft?
  - [x] Werden alle Fehler durch Error Codes kommuniziert und behandelt?

### Logik:
- [x] Gibt es offensichtliche Logikfehler?
- [x] Wurden alle Randfälle abgedeckt?
- [x] Wurden alle Schleifen korrekt konstruiert, iterieren diese nur über die notwendigen Elemente und terminieren diese?
- [x] Kann Code, wenn möglich außerhalb von Schleifen ausgeführt?
- [x] Wurden alle Logikverzweigungen inhaltlich korrekt erstellt?
- [x] Wurden, wenn möglich, die Anweisungen außerhalb der Schleife platziert?

### Lesbarkeit und Verständlichkeit:
- [x] Sind alle Identifier für Funktionen, Variablen und Typen aussagekräftig?
- [x] Haben alle Komponenten eine ausführliche und korrekte Dokumentation?
- [x] Sind die Kommentare und Dokumentation einheitlich mit dem Code (Namen etc.)?
- [x] Wurde notwendig komplexer Code oder nicht offensichtliche Entscheidungen ausreichend kommentiert?

### Leistung und Ressourcenverwendung:
- [x] Wurden die festgelegten Algorithmen und Datenstrukturen korrekt implementiert?
- [x] Wurden die vorgegebenen Implementationsdetails umgesetzt?
- [x] Lastet die Implementation die Hardware effektiv aus?

### Testabdeckung
- [x] Wurden ausführliche Tests für alle neuen Features geschrieben und laufen alle Tests erfolgreich durch?
- [x] Wurden alle Randfälle getestet?
- [x] Kompiliert das Programm in der Pipeline?
#### Ergebnis des Reviews: 
* Wurden die Maßnahmen für Erweiterbarkeit korrekt umgesetzt?
    - Es wurde auf Erweiterbarkeit bei der Erstellung der Metadaten und der Metadatenausgabe geachtet, somit ließen sich die Erweiterungen gut einsetzten.
* Wurden die Maßnahmen für Leistung und Ressourcenverwendung korrekt umgesetzt?
    - N/A
* Probleme, die im Code Review gefunden wurden: 
    - Es wurden keine Probleme im Code Review gefunden.

## Code Review Checklist - User Story: 27 - Erstellung von Testdatensätzen 
In dieser User Story wurde kein Code geschrieben und entsprechend wurden kein Code Review druchgeführt.

## Code Review Checklist - User Story: 28,29,30 - Erweiterung der CLI-Parameter 
Datum: 20.02.2024</br>
Entwickler*innen: Alicia Gleichmann</br>
Code Buddy: Severin Pelikan
#### Ergebnis des Reviews: 
* Wurden die Maßnahmen für Erweiterbarkeit korrekt umgesetzt?
     - Durch den in US 7 implementierten "Arx-System" konnten diese Erweiterungen effektiv umgesetzt werden.
* Wurden die Maßnahmen für Leistung und Ressourcenverwendung korrekt umgesetzt?
    - N/A
* Probleme, die im Code Review gefunden wurden: 
    - Es wurden keine Probleme im Code Review gefunden.