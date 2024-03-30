# Code Reviews Iteration 5:
---

## Code Review Checklist - User Story: 16 - Export zu segmentierten Kartenformat
Datum: 21.01.2024</br>
Entwickler*innen: Severin Pelikan, Alicia Gleichmann</br>
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
- [ ] Wurde notwendig komplexer Code oder nicht offensichtliche Entscheidungen ausreichend kommentiert?

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
    - Der hybride Sortieralgorithmus wurde mit einer einfachen räumlichen Hash Funktion umgesetzt und erfüllt alle Vorgaben.
    - Die initiale Größe der Buckets wird auf Basis der Programm-Parameter angepasst, um eine gute Balance zwischen Speicherauslastung und Laufzeit zu finden.
    - Der Speicher bleibt grundsätzlich allokiert, kann aber zu einem geringen Grad wachsen oder schrumpfen, um sich der Last anzupassen.
    - Die Implementation nutzt alle zur Verfügung stehenden Threads effektiv aus.
    - Alle verwendeten Arrays von Datenstrukturen sind eng gepackt und werden sequentiell gelesen und geschrieben um Cache Misses zu verringern.
* Probleme, die im Code Review gefunden wurden:
    - Kommentare für komplexe Codeabschnitte waren nicht ausführlich genug. 
    - Konsequenz: Die Kommentare wurde im Review angepasst und dann akzeptiert.

---

## Code Review Checklist - User Story: 17 - Sammeln von Metadaten
Datum: 21.01.2024</br>
Entwickler*innen: Leonhard Steinecke</br>
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
    - Es wurde eine übersichtliche Struktur im Struct genutzt, daher ist es einfach weitere Felder hinzuzufügen. 
* Wurden die Maßnahmen für Leistung und Ressourcenverwendung korrekt umgesetzt?
    - Die Eintragefunktionen wurde umgesetzt und diese erlauben nur einzigartige Einträge.
* Probleme, die im Code Review gefunden wurden: 
    - Es wurden keine Probleme im Code Review gefunden.