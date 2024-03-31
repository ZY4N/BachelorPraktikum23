# Code Reviews Iteration 6:
---

## Code Review Checklist - User Story: 10 - Entfernung dynamischer Objekte mittels Removert 
In dieser User Story wurde kein Code geschrieben und entsprechend wurden kein Code Review druchgeführt.

---

## Code Review Checklist - User Story: 18 - Lesen und Schreiben von Metadaten im JSON-Format
Datum: 05.02.2024</br>
Entwickler*innen: Simon Riese</br>
Code Buddy: Leonhard Steinecke
### Struktur:
  - [x] Wurden die Akzeptanzkriterien der User Story erfüllt?
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
    - Es wurde eine Schnittstelle implementiert über die in Zukunft weitere Module für die Ausgabe von Metadaten hinzugefügt werden können.
* Wurden die Maßnahmen für Leistung und Ressourcenverwendung korrekt umgesetzt?
    - Die Bibliothek "RapidJSON" wurde erfolgreich zum Lesen und Schreiben der JSON-Dateien eingesetzt.
* Probleme, die im Code Review gefunden wurden: 
    - Es wurden keine Probleme im Code Review gefunden.

---

## Code Review Checklist - User Story: 19 - Ausarbeitung von Grundkonzepten zur Enfernung semi-dynamischer Objekte
In dieser User Story wurde kein Code geschrieben und entsprechend wurden kein Code Review druchgeführt.

---

## Code Review Checklist - User Story: 20,21,22 - Erweiterung der CLI Parameter
Datum: 05.02.2024</br>
Entwickler*innen: Alicia Gleichmann</br>
Code Buddy: Severin Pelikan
### User Story 20
### Struktur:
  - [x] Wurden die Akzeptanzkriterien der User Story erfüllt?
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

### User Story 21:
### Struktur:
  - [x] Wurden die Akzeptanzkriterien der User Story erfüllt?
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

### User Story 22:
### Struktur:
  - [x] Wurden die Akzeptanzkriterien der User Story erfüllt?
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
     - Durch den in US 7 implementierten "Arx-System" konnten diese Erweiterungen effektiv umgesetzt werden.
* Wurden die Maßnahmen für Leistung und Ressourcenverwendung korrekt umgesetzt?
    - N/A
* Probleme, die im Code Review gefunden wurden: 
    - Es wurden keine Probleme im Code Review gefunden.