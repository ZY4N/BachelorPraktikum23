# Code Reviews Iteration 2:
---

## Code Review Checklist - User Story: 1 - Distanzfilterung von Punktdaten
Datum: 28.11.2023</br>
Entwickler*innen: Greys Fankyeyeva</br>
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
    - Das Filtern mit einem änderbaren Filter-Prädikat wurde umgesetzt.
* Wurden die Maßnahmen für Leistung und Ressourcenverwendung korrekt umgesetzt?
    - Die Laufzeit und Speicherauslastung sind konstant.
    - Die Filter Funktionen werden mit einem Template geinlinet und arbeiten mit quadrierten Distanzen, um Wurzelberechnungen zu vermeiden.
    - Die Filter Funktionen können ohne Komplikationen von mehreren Threads gleichzeitig verwendet werden.
    - Die Filter Funktionen arbeiten auf eng-gepackten Vektoren und füllen so die Cache-Lines voll aus.
* Probleme, die im Code Review gefunden wurden: 
    - Es wurden keine Probleme im Code Review gefunden.

---

## Code Review Checklist - User Story: 2 - Geschwindigkeits-Entzerrung
Datum: 28.11.2023</br>
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
    - Die Laufzeit und Speicherauslastung sind linear Abhängig von der Anzahl an zu verarbeitenden Punkte.
    - Es wurden keine vermeidbaren Berechnungen vorgenommen.
    - Die Implementation nutzt alle zur Verfügung stehenden Threads aus, indem die zu verarbeitenden Punkte nach Aufnahmezeitpunkten
    - Der Algorithmus nutzt die selben Cache-Line optimierten Datenstrukturen wie US-0.
* Probleme, die im Code Review gefunden wurden:
    - Es wurden keine Probleme im Code Review gefunden.

---

## Code Review Checklist - User Story: 4 - Integration von 3DTK People Remover in Scan Combiner
Datum: 28.11.2023</br>
Entwickler*innen: Greys Fankyeyeva, Simon Riese</br>
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
  - [x] Werden Dateien bevor auf diese zugegriffen auf Gültigkeit überprüft?
  - [x] Werden alle Fehler durch Error Codes kommuniziert und behandelt?

### Logik:
- [ ] Gibt es offensichtliche Logikfehler?
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
    - Die Schnittstelle für weitere Ausgabemodule wurde wie besprochen implementiert und das UOS-Modul wurde in dieser Schnittstelle eingefügt.
* Wurden die Maßnahmen für Leistung und Ressourcenverwendung korrekt umgesetzt?
    - Der Schnittstelle und dem Modul werden die Punktdaten als`tcb:span` übergeben, um Kopien zu vermeiden.
    - Das UOS-Module schreibt die Punktdaten als `std::hexfloat`.
* Probleme, die im Code Review gefunden wurden:
    - Die Umrechnung von Eulerschen Winkeln in Grad wurde nicht korrekt implementiert.
    - Konsequenz: Die Berechnung wurde korrigiert, getestet und dann akzeptiert.

---

## Code Review Checklist - User Story: 5 - Entfernung dynamischer Objekte mittels 3DTK People Remover
In dieser User Story wurde kein Code geschrieben und entsprechend wurden kein Code Review druchgeführt.