# Code Reviews Iteration 3:
---

## Code Review Checklist - User Story: 0 - Einlese-Option für Rosbag-Dateien 
Datum: 16.12.2023</br>
Entwickler*innen: Leonhard Steinecke</br>
Code Buddy: Severin Pelikan
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
- [ ] Sind alle Identifier für Funktionen, Variablen und Typen aussagekräftig?
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
    - Es wurde auf Erweiterbarkeit geachtet indem alle Topics eine eigene Funktion habe, so können weitere Topics konfliktlos hinzugefügt werden (`extract_topic_1`, `extract_topic_2`, ...).
* Wurden die Maßnahmen für Leistung und Ressourcenverwendung korrekt umgesetzt?
    - Das Filtern wurde In-Place umgesetzt und somit skaliert sowohl die Laufzeit als auch die Speicherauslastung linear mit der Anzahl an geladenen Punkten, Transformationen und Geschwindigkeiten.
    - Die Implementation setzt das Laden und das Filtern der Daten ohne unnötige Operationen um.
    - Die Implementation lädt alle Daten sequentiell und nutzt dementsprechend nicht von sich aus alle zur Verfügung stehenden Threads. Jedoch bieten die Lade-Funktionen die Möglichkeit, den Zeitraum, in dem Daten verarbeitet werden, anzupassen. Diese Parameter können genutzt werden, um das Laden einzelner Zeitabschnitte unter mehreren Threads aufzuteilen. Eine performante Implementation dieser Parallelisierung bedeutet einen signifikanten Zeitaufwand und sollte erst umgesetzt werden, wenn zum einen sichergestellt ist, dass dieser Teil der Implementation nicht mehr signifikant angepasst werden muss und zum anderen, der AG der Parallelisierung die nötige Priorität zuweist. Dementsprechend ist das Parallelisieren nicht mehr Teil dieser US und sollte in Absprache mit dem AG in einer separaten US umgesetzt werden.
    - Alle Datenstrukturen für das Laden der Sensordaten bestehen aus 64-Bit Feldern (entweder double oder uint64_t) und sind eng gepackt, sodass keine Bytes für Padding verloren gehen. Damit besteht das struct für Punkte mit Zeitinformationen aus 32 Bytes e.g. (2 pro Cache Line), das für Transformationen mit Zeitinformationen aus 64 Bytes e.g. (1 pro Cache Line) und das für Geschwindigkeiten mit Zeitinformationen aus 16 Bytes e.g. (4 pro Cache Line). Folglich sind die Structs gut auf 64B Cache Line Größe optimiert.
* Probleme, die im Code Review gefunden wurden: 
    - Die Funktion-Identifier `ext_velocities` und `ext_transforms` beschreiben die Funktionsweisen der Methoden nicht eindeutig. 
    - Konsequenz: Umbenennen auf `extract_velocities` und `extract_transforms`.
    - Die Parallelisierung dieses Systems verlangt zusätzlichen Aufwand und sollte in einer separaten US umgesetzt werden.

---

## Code Review Checklist - User Story:  3 - Integration von dynamischem Logging-System
Datum: 16.12.2023</br>
Entwickler*innen: Severin Pelikan</br>
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
- [ ] Haben alle Komponenten eine ausführliche und korrekte Dokumentation?
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
    - Die Erweiterungsmöglichkeit der  für weitere Log-Level und die untetrschtützung weiter Datentypformatierungen wurde korrekt mit Structs und Templates umgesetzt.
* Wurden die Maßnahmen für Leistung und Ressourcenverwendung korrekt umgesetzt?
    - Das Loggingsystem verwendet die mit `std::atomic_flag` bereitgestllte Spinlock Implementation für niedrig latente Synchronisation.
    - Das Loggingsystem verwendet die Template Implementation von `std::ostream` für eine effiziente serialisierung der Argumente.
    - Die Log Level und Flaggen werden in 16-Bit Integern gespeichert und können mit einer einfach Zuweisung verändert werden.
* Probleme, die im Code Review gefunden wurden:
    - Es wurde die Struktur der Config nicht ausreichend dokumentiert.
    - Konsequenz: Die Dokumentation mit der Beschreibung der Bestandteilen der Config-Struct wurde erweitert.

---

## Code Review Checklist - User Story:  6 - Verringerung von Aufnahmetransformationen
Datum: 16.12.2023</br>
Entwickler*innen: Severin Pelikan</br>
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
    - N/A
* Wurden die Maßnahmen für Leistung und Ressourcenverwendung korrekt umgesetzt?
    - Die vereinten Aufnahmepositionen werden mittels eines Moving-Averages berechnet, was Zwischenspeichern vermeidet.
    - Alle (ca. 10k) Punkte, die zwischen zwei Transformationen aufgenommen wurden, werden in einem für SIMD angeordneten Block transformiert.
* Probleme, die im Code Review gefunden wurden: 
    - Es wurden keine Probleme im Code Review gefunden.

---

## Code Review Checklist - User Story:  7 - Dynamisches Anpassen von Ein- und Ausgabepfaden über CLI 
Datum: 16.12.2023</br>
Entwickler*innen: Alicia Gleichmann, Severin Pelikan</br>
Code Buddy: Simon Riese
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
    - Es wurde das "arx-System" implementiert, über das einfach neue CLI Parameter hinzugefügt werden können. Für Parameter kann ein Default-Wert und Optionalität festgelegt werden. Außerdem können im System Parser für bisher nicht unterstütze Datentypen hinzugefügt werden. So können die CLI Parameter einfach erweitert werden.
* Wurden die Maßnahmen für Leistung und Ressourcenverwendung korrekt umgesetzt?
    - N/A
* Welche Änderungen am Design wurde vorgenommen?
    - Da der Input auch aus mehreren Rosbags bestehen soll, ist der einzelner Parameter `--input` nicht ausreichend.
    - Konsequenz: Input-Pfade werden über positionale Argumente angegeben.
* Probleme, die im Code Review gefunden wurden: 
    - Es wurden keine Probleme im Code Review gefunden.
