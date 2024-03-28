# Code Review Checklist

## Struktur:
  - [ ] Wurden die Akzeptanzkriterien der User Story(s) erfüllt?
  - [ ] Wurden die Entscheidungen des Design Meetings eingehalten?
  - [ ] Wurden die Maßnahmen für Erweiterbarkeit korrekt umgesetzt?
  - [ ] Wurden Code- und Style Richtlinien eingehalten?
  - [ ] Wurden Linter und Code Formatter für alle veränderten Dateien angewendet?
  - [ ] Werden alle Code- und Testabschnitte benutzt und kompiliert?
  - [ ] Wurde Code, wenn sinnvoll, durch externe wiederverwendbare Komponenten oder Funktionen aus Bibliotheken ersetzt?
  - [ ] Wurde sich wiederholende Code, wenn sinnvoll, in Hilfsfunktionen ausgelagert?
  - [ ] Wurden „magic numbers“ vermieden?
  - [ ] Gibt es keine Codeabschnitte, die unnötig komplex sind?
  - [ ] Werden Typen korrekt gecastet und sind keine redundanten Variablen vorhanden?
  - [ ] Werden Dateien bevor auf diese zugegriffen auf Gültigkeit überprüft?
  - [ ] Werden alle Fehler durch Error Codes kommuniziert und behandelt?

## Logik:
- [ ] Gibt es offensichtliche Logikfehler?
- [ ] Wurden alle Randfälle abgedeckt?
- [ ] Wurden alle Schleifen korrekt konstruiert, iterieren diese nur über die notwendigen Elemente und terminieren diese?
- [ ] Kann Code, wenn möglich außerhalb von Schleifen ausgeführt?
- [ ] Wurden alle Logikverzweigungen inhaltlich korrekt erstellt?
- [ ] Wurden, wenn möglich, die Anweisungen außerhalb der Schleife platziert?

## Lesbarkeit und Verständlichkeit:
- [ ] Sind alle Identifier für Funktionen, Variablen und Typen aussagekräftig?
- [ ] Haben alle Komponenten eine ausführliche und korrekte Dokumentation?
- [ ] Sind die Kommentare und Dokumentation einheitlich mit dem Code (Namen etc.)?
- [ ] Wurde notwendig komplexer Code oder nicht offensichtliche Entscheidungen ausreichend kommentiert?

## Leistung und Ressourcenverwendung:
- [ ] Wurden die festgelegten Algorithmen und Datenstrukturen korrekt implementiert?
- [ ] Wurden die vorgegebenen Implementationsdetails umgesetzt?
- [ ] Lastet die Implementation die Hardware effektiv aus?

## Testabdeckung
- [ ] Wurden ausführliche Tests für alle neuen Features geschrieben und laufen alle Tests erfolgreich durch?
- [ ] Wurden alle Randfälle getestet?
- [ ] Kompiliert das Programm in der Pipeline?
