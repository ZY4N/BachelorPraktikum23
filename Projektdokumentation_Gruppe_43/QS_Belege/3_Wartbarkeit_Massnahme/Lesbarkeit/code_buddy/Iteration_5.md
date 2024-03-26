# Statusmeeting Protokolle Iteration 5
---

## Statusmeeting 1 zu User Story 10. Entfernung dynamischer Objekte mittels Removert
- Datum: 16.01.2024 12:30 Uhr - 13:00 Uhr
- Entwickler\*innen: Severin Pelikan, Greys Fankyeyeva
- Code Buddy: Simon Riese
- Kontext:
	- -
- Beispiel:
	- -
- Diagnose:
	- -
- Aktion:
	- -
- Sonstiges: 
	- Fragmente sind immer noch da, allerdings weniger
	- Verschiedene Kombinationen der Parameter bereits ausprobiert
- Nächstes Meeting am: 20.01.2024 um 12:30 Uhr

---

## Checkliste 1 zu User Storie 16. Export zu segmentierten Karten Format 
### C API
- [x] Keine manuelle Heapallokation benutzt
- [x] Keine C-Arrays, sondern C++-Arrays zur Stack Allokation benutzt
- [x] Keine Strings als null-terminierende char Pointer umgesetzt
- [x] Casting nur durch Casting Operationen durchgeführt
- [x] Keine Funktionen von cstdlib, sondern von STL Funktionen verwendet
- [x] Keine raw Pointer, sondern Referenzen benutzen
- [x] Logische Operatoren nur in der ausgeschriebenen Bezeichnung benutzt
- [x] Keine Macros, sondern Templates und andere moderne Compile-time Konstruktionen verwendet

### Kompilieren
- [x] nur CMake 3.16 verwendet
- [x] kein Undefined Behavior vorhanden
- [x] Alle Warnungen werden als Error behandelt
- [x] Build -0fast ist aktiviert und funktioniert

### Dokumentation
- ##### Kommentare in Funktionen sind: 
	- [x] in englischer Spreche 
	- [x] als ganze Sätze umgesetzt
	- [x] mit korrekter Grammatik und Rechtschreibung geschrieben
	- [x] nur als inline Kommentare (// statt /* ... \*/) umgesetzt
- ##### Dokumentationen von Funktionen 
	- [x] sind in englischer Sprache
	- [x] sind als ganze Sätze umgesetzt
	- [x] sind mit korrekter Grammatik und Rechtschreibung geschrieben
	- [x] Kurze und präzise Beschreibung der Funktionalität nach `@brief` 
	- [x] \[optional] Detailliertere Beschreibung, in der die Funktionsschritte durchgegangen und wichtige Implementationsdetails erklärt werden
	- [x] \[optional] Folge von Extrainformationen, wie die Funktion benutzt werden sollte nach `@note` 
	- [x] Folge der Parameter, in denen in einem kurzem Satz die Bedeutung des Parameters im Kontext der Funktion erklärt wird nach `@tparam` und `@param` geschrieben
	- [x] \[falls die Funktion einen Rückgabewert hat] Bedeutung des Rückgabewerts wird im Kontext der Funktion nach `@return` beschrieben 
	- [x] Die Reihenfolge der Dokumentation ist: `@brief`, \[optional] detailliertere Beschreibung, \[optional] `@note`, `@tparam` und `@param`, \[falls die Funktion einen Rückgabewert hat] `@return`
	- [x] Alle Blöcke in der Dokumentation sind durch genau eine Leerzeile getrennt
	- [x] Die Dokumentation ist in einem Kommentarblock (/* ... \*/)
	- [x] Wenn C++ Typen referenziert werden, wird der Name monospaced nach `@c` geschrieben
- ##### Dokumentation von Klassen, Strukturen, Enumerations, Namespaces etc.
	- [x] sind in englischer Sprache
	- [x] sind als ganze Sätze umgesetzt
	- [x] sind mit korrekter Grammatik und Rechtschreibung geschrieben
	- [x] Kurze und präzise Beschreibung der Funktionalität nach `@brief` 
	- [x] \[optional] Detailliertere Beschreibung, in der die Funktionalitätsschritte durchgegangen und wichtige Implementation Details erklärt werden
	- [x] \[optional] Folge von Extrainformationen, wie die Funktion benutzt werden sollte nach `@note` 
	- [x] Die Reihenfolge der Dokumentation ist: `@brief`, \[optional] detailliertere Beschreibung, \[optional] `@note`
	- [x] Alle Blöcke in der Dokumentation sind durch genau eine Leerzeile getrennt
	- [x] Die Dokumentation ist in einem Kommentarblock (/* ... \*/)
	- [x] Wenn C++ Typen referenziert werden, wird der Name monospaced nach `@c` geschrieben

### Modernes C++
- [x] `auto` benutzt bei Speicherung oder Referenz eines Rückgabewerts
- [x] `auto` benutzt bei Variablendeklarationen
- [x] In Schleifen nur Iterationen über Mengen genutzt
- [x] Wenn existent STL Implementation verwändet
- [x] Lambda statt benannter Funktion in STL API's verwendet
- [x] Lambda statt Code Duplikation benutzt
- [x] Variablen, wenn möglich konstant durch `const` gemacht
- [x] Ausdrücke, wenn möglich konstant durch `constexpr` gemacht

### Style Guidelines
- [x] Alle Identifiers außer Template Parameter sind in snake_case geschrieben
- [x] Alle Template Parameter sind in PascalCase geschrieben
- [x] Alle Identifiers sind passend gewählt
- [x] Es wurde `#pragma once` anstatt explizit eingebundenen Guards verwendet
- [x] In den includes wurde `<>` für Standard Bibliothek und `""` für den Rest verwendet 
- [x] `using namespace` wurde nur in kleinen Namespaces, über die die volle Kontrolle bestand, verwendet
- [x] Am Ende jeder Datei ist eine Leerzeile

### Code Formatter und Linter
- [x] Code Formatter ist korrekt am Code angewendet worden
- [x] Linter ist korrekt am Code angewendet worden


## Statusmeeting 1 zu User Story 16. Export zu segmentierten Karten Format 
- Datum: 15.01.2024 15:30 Uhr - 16:15 Uhr
- Entwickler\*innen: Severin Pelikan, Alicia Gleichmann
- Code Buddy: Greys Fankyeyeva
- Kontext:
	- -
- Beispiel:
	- -
- Diagnose:
	- -
- Aktion:
	- -
- Sonstiges:
	- Aufteilung in Buckets großteils abgeschlossen
	- Fehlt Buckets zu Output
	- Keine Probleme in der Dokumentation und auch keine verbotenen Operationen verwendet
- Nächstes Meeting am: 19.01.2024 um 14:00 Uhr

---

## Statusmeeting 1 zu User Story 17. Sammeln von Metadaten 
- Datum: 15.01.2024 15:30 Uhr - 15:40 Uhr
- Entwickler\*innen: Leonhard Steinecke
- Code Buddy: Simon Riese
- Kontext:
	- -
- Beispiel:
	- -
- Diagnose:
	- -
- Aktion:
	- -
- Sonstiges:
	- bisher kein Implementationsfortschritt
- Nächstes Meeting am: 19.01.2024 um 18:00 Uhr

---

## Checkliste 1 zu User Storie 18. Lesen und Schreiben von Metadaten im JSON-Format
### C API
- [x] Keine manuelle Heapallokation benutzt
- [x] Keine C-Arrays, sondern C++-Arrays zur Stack Allokation benutzt
- [x] Keine Strings als null-terminierende char Pointer umgesetzt
- [x] Casting nur durch Casting Operationen durchgeführt
- [x] Keine Funktionen von cstdlib, sondern von STL Funktionen verwendet
- [x] Keine raw Pointer, sondern Referenzen benutzen
- [x] Logische Operatoren nur in der ausgeschriebenen Bezeichnung benutzt
- [x] Keine Macros, sondern Templates und andere moderne Compile-time Konstruktionen verwendet

### Kompilieren
- [x] nur CMake 3.16 verwendet
- [x] kein Undefined Behavior vorhanden
- [x] Alle Warnungen werden als Error behandelt
- [x] Build -0fast ist aktiviert und funktioniert

### Dokumentation
- ##### Kommentare in Funktionen sind: 
	- [x] in englischer Spreche 
	- [x] als ganze Sätze umgesetzt
	- [x] mit korrekter Grammatik und Rechtschreibung geschrieben
	- [x] nur als inline Kommentare (// statt /* ... \*/) umgesetzt
- ##### Dokumentationen von Funktionen 
	- [x] sind in englischer Sprache
	- [x] sind als ganze Sätze umgesetzt
	- [x] sind mit korrekter Grammatik und Rechtschreibung geschrieben
	- [x] Kurze und präzise Beschreibung der Funktionalität nach `@brief` 
	- [x] \[optional] Detailliertere Beschreibung, in der die Funktionsschritte durchgegangen und wichtige Implementationsdetails erklärt werden
	- [x] \[optional] Folge von Extrainformationen, wie die Funktion benutzt werden sollte nach `@note` 
	- [x] Folge der Parameter, in denen in einem kurzem Satz die Bedeutung des Parameters im Kontext der Funktion erklärt wird nach `@tparam` und `@param` geschrieben
	- [x] \[falls die Funktion einen Rückgabewert hat] Bedeutung des Rückgabewerts wird im Kontext der Funktion nach `@return` beschrieben 
	- [x] Die Reihenfolge der Dokumentation ist: `@brief`, \[optional] detailliertere Beschreibung, \[optional] `@note`, `@tparam` und `@param`, \[falls die Funktion einen Rückgabewert hat] `@return`
	- [x] Alle Blöcke in der Dokumentation sind durch genau eine Leerzeile getrennt
	- [x] Die Dokumentation ist in einem Kommentarblock (/* ... \*/)
	- [x] Wenn C++ Typen referenziert werden, wird der Name monospaced nach `@c` geschrieben
- ##### Dokumentation von Klassen, Strukturen, Enumerations, Namespaces etc.
	- [x] sind in englischer Sprache
	- [x] sind als ganze Sätze umgesetzt
	- [x] sind mit korrekter Grammatik und Rechtschreibung geschrieben
	- [x] Kurze und präzise Beschreibung der Funktionalität nach `@brief` 
	- [x] \[optional] Detailliertere Beschreibung, in der die Funktionalitätsschritte durchgegangen und wichtige Implementation Details erklärt werden
	- [x] \[optional] Folge von Extrainformationen, wie die Funktion benutzt werden sollte nach `@note` 
	- [x] Die Reihenfolge der Dokumentation ist: `@brief`, \[optional] detailliertere Beschreibung, \[optional] `@note`
	- [x] Alle Blöcke in der Dokumentation sind durch genau eine Leerzeile getrennt
	- [x] Die Dokumentation ist in einem Kommentarblock (/* ... \*/)
	- [x] Wenn C++ Typen referenziert werden, wird der Name monospaced nach `@c` geschrieben

### Modernes C++
- [x] `auto` benutzt bei Speicherung oder Referenz eines Rückgabewerts
- [x] `auto` benutzt bei Variablendeklarationen
- [x] In Schleifen nur Iterationen über Mengen genutzt
- [x] Wenn existent STL Implementation verwändet
- [x] Lambda statt benannter Funktion in STL API's verwendet
- [x] Lambda statt Code Duplikation benutzt
- [ ] Variablen, wenn möglich konstant durch `const` gemacht
- [x] Ausdrücke, wenn möglich konstant durch `constexpr` gemacht

### Style Guidelines
- [x] Alle Identifiers außer Template Parameter sind in snake_case geschrieben
- [x] Alle Template Parameter sind in PascalCase geschrieben
- [x] Alle Identifiers sind passend gewählt
- [x] Es wurde `#pragma once` anstatt explizit eingebundenen Guards verwendet
- [x] In den includes wurde `<>` für Standard Bibliothek und `""` für den Rest verwendet 
- [x] `using namespace` wurde nur in kleinen Namespaces, über die die volle Kontrolle bestand, verwendet
- [x] Am Ende jeder Datei ist eine Leerzeile

### Code Formatter und Linter
- [x] Code Formatter ist korrekt am Code angewendet worden
- [x] Linter ist korrekt am Code angewendet worden


## Statusmeeting 1 zu User Story 18. Lesen und Schreiben von Metadaten im JSON-Format
- Datum: 15.01.2024 16:15 Uhr - 17:00 Uhr
- Entwickler\*innen: Simon Riese
- Code Buddy: Leonhard Steinecke
- Kontext: 
	- Variablen nicht konstant gesetzt
- Beispiel: 
	- frame_exporter.hpp (und frame_exporter.cpp gleiche Variable) directory
- Diagnose: 
	- Schlechtere Performance durch nicht konstante Variablen 
- Aktion:
	- const einfügen
- Sonstiges:
	- Code durchgesprochen
	- Dokumentation, die schon da ist, hat alle Punkte der Checkliste abgehakt
	- Code außer diesem Fehler gut
	- Zusammen gleich behoben
- Nächstes Meeting am: 19.01.2024 um 16:00 Uhr

---

## Statusmeeting 2 zu User Story 10. Entfernung dynamischer Objekte mittels Removert
- Datum: 20.01.2024 12:30 Uhr - 14:00 Uhr
- Entwickler\*innen: Severin Pelikan, Greys Fankyeyeva
- Code Buddy: Simon Riese
- [x] alle besprochenen Änderungen wurden umgesetzt 
- Kontext:
	- -
- Beispiel:
	- -
- Diagnose:
	- -
- Aktion:
	- -
- Sonstiges:
	- Fragmente mit unterschiedlichen Kombinationen der Parameter unterschiedlich stark, allerdings immer noch da
	- In der Dokumentation des KIT wird beschrieben, dass ein zu großer Datensatz potenziell Probleme macht -> Test mit kleineren Datensätzen durch segmentierte Karte
		- Übernahme in nächste Iteration


Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: 
	- User Story wurde in die nächste Iteration übernommen. Änderungen werden bis zum nächsten Code Buddy Meeting umgesetzt.

---

## Checkliste 2 zu User Storie 16. Export zu segmentierten Karten Format 
### C API
- [x] Keine manuelle Heapallokation benutzt
- [x] Keine C-Arrays, sondern C++-Arrays zur Stack Allokation benutzt
- [ ] Keine Strings als null-terminierende char Pointer umgesetzt
- [x] Casting nur durch Casting Operationen durchgeführt
- [x] Keine Funktionen von cstdlib, sondern von STL Funktionen verwendet
- [x] Keine raw Pointer, sondern Referenzen benutzen
- [x] Logische Operatoren nur in der ausgeschriebenen Bezeichnung benutzt
- [x] Keine Macros, sondern Templates und andere moderne Compile-time Konstruktionen verwendet

### Kompilieren
- [x] nur CMake 3.16 verwendet
- [x] kein Undefined Behavior vorhanden
- [x] Alle Warnungen werden als Error behandelt
- [x] Build -0fast ist aktiviert und funktioniert

### Dokumentation
- ##### Kommentare in Funktionen sind: 
	- [x] in englischer Spreche 
	- [x] als ganze Sätze umgesetzt
	- [x] mit korrekter Grammatik und Rechtschreibung geschrieben
	- [x] nur als inline Kommentare (// statt /* ... \*/) umgesetzt
- ##### Dokumentationen von Funktionen 
	- [x] sind in englischer Sprache
	- [x] sind als ganze Sätze umgesetzt
	- [x] sind mit korrekter Grammatik und Rechtschreibung geschrieben
	- [x] Kurze und präzise Beschreibung der Funktionalität nach `@brief` 
	- [x] \[optional] Detailliertere Beschreibung, in der die Funktionsschritte durchgegangen und wichtige Implementationsdetails erklärt werden
	- [x] \[optional] Folge von Extrainformationen, wie die Funktion benutzt werden sollte nach `@note` 
	- [x] Folge der Parameter, in denen in einem kurzem Satz die Bedeutung des Parameters im Kontext der Funktion erklärt wird nach `@tparam` und `@param` geschrieben
	- [x] \[falls die Funktion einen Rückgabewert hat] Bedeutung des Rückgabewerts wird im Kontext der Funktion nach `@return` beschrieben 
	- [x] Die Reihenfolge der Dokumentation ist: `@brief`, \[optional] detailliertere Beschreibung, \[optional] `@note`, `@tparam` und `@param`, \[falls die Funktion einen Rückgabewert hat] `@return`
	- [x] Alle Blöcke in der Dokumentation sind durch genau eine Leerzeile getrennt
	- [x] Die Dokumentation ist in einem Kommentarblock (/* ... \*/)
	- [x] Wenn C++ Typen referenziert werden, wird der Name monospaced nach `@c` geschrieben
- ##### Dokumentation von Klassen, Strukturen, Enumerations, Namespaces etc.
	- [x] sind in englischer Sprache
	- [x] sind als ganze Sätze umgesetzt
	- [x] sind mit korrekter Grammatik und Rechtschreibung geschrieben
	- [x] Kurze und präzise Beschreibung der Funktionalität nach `@brief` 
	- [x] \[optional] Detailliertere Beschreibung, in der die Funktionalitätsschritte durchgegangen und wichtige Implementation Details erklärt werden
	- [x] \[optional] Folge von Extrainformationen, wie die Funktion benutzt werden sollte nach `@note` 
	- [x] Die Reihenfolge der Dokumentation ist: `@brief`, \[optional] detailliertere Beschreibung, \[optional] `@note`
	- [x] Alle Blöcke in der Dokumentation sind durch genau eine Leerzeile getrennt
	- [x] Die Dokumentation ist in einem Kommentarblock (/* ... \*/)
	- [x] Wenn C++ Typen referenziert werden, wird der Name monospaced nach `@c` geschrieben

### Modernes C++
- [x] `auto` benutzt bei Speicherung oder Referenz eines Rückgabewerts
- [x] `auto` benutzt bei Variablendeklarationen
- [x] In Schleifen nur Iterationen über Mengen genutzt
- [x] Wenn existent STL Implementation verwändet
- [x] Lambda statt benannter Funktion in STL API's verwendet
- [x] Lambda statt Code Duplikation benutzt
- [x] Variablen, wenn möglich konstant durch `const` gemacht
- [x] Ausdrücke, wenn möglich konstant durch `constexpr` gemacht

### Style Guidelines
- [x] Alle Identifiers außer Template Parameter sind in snake_case geschrieben
- [x] Alle Template Parameter sind in PascalCase geschrieben
- [x] Alle Identifiers sind passend gewählt
- [x] Es wurde `#pragma once` anstatt explizit eingebundenen Guards verwendet
- [x] In den includes wurde `<>` für Standard Bibliothek und `""` für den Rest verwendet 
- [x] `using namespace` wurde nur in kleinen Namespaces, über die die volle Kontrolle bestand, verwendet
- [x] Am Ende jeder Datei ist eine Leerzeile

### Code Formatter und Linter
- [x] Code Formatter ist korrekt am Code angewendet worden
- [x] Linter ist korrekt am Code angewendet worden


## Statusmeeting 2 zu User Story 16. Export zu segmentierten Karten Format 
- Datum: 19.01.2024 14:00 Uhr - 15:00 Uhr
- Entwickler\*innen: Severin Pelikan, Alicia Gleichmann
- Code Buddy: Greys Fankyeyeva
- [x] alle besprochenen Änderungen wurden umgesetzt
- Kontext:
	- String als Char-Array
- Beispiel:
	- Name der Frames in Chunks
- Diagnose:
	- Nicht gut, da bei Unvorsichtigkeit Stack Overflow möglich
- Aktion:
	- String als std::string oder std::stringview
- Sonstiges: 
	- String direkt zu std::stringview geändert
	- Alles andere ist korrekt, alle Punkte der Checkliste abgehakt


Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: 19.1.2024

---

## Checkliste 2 zu User Storie 17. Sammeln von Metadaten 
### C API
- [x] Keine manuelle Heapallokation benutzt
- [x] Keine C-Arrays, sondern C++-Arrays zur Stack Allokation benutzt
- [x] Keine Strings als null-terminierende char Pointer umgesetzt
- [x] Casting nur durch Casting Operationen durchgeführt
- [x] Keine Funktionen von cstdlib, sondern von STL Funktionen verwendet
- [x] Keine raw Pointer, sondern Referenzen benutzen
- [x] Logische Operatoren nur in der ausgeschriebenen Bezeichnung benutzt
- [x] Keine Macros, sondern Templates und andere moderne Compile-time Konstruktionen verwendet

### Kompilieren
- [x] nur CMake 3.16 verwendet
- [x] kein Undefined Behavior vorhanden
- [x] Alle Warnungen werden als Error behandelt
- [x] Build -0fast ist aktiviert und funktioniert

### Dokumentation
- ##### Kommentare in Funktionen sind: 
	- [x] in englischer Spreche 
	- [x] als ganze Sätze umgesetzt
	- [x] mit korrekter Grammatik und Rechtschreibung geschrieben
	- [x] nur als inline Kommentare (// statt /* ... \*/) umgesetzt
- ##### Dokumentationen von Funktionen 
	- [x] sind in englischer Sprache
	- [x] sind als ganze Sätze umgesetzt
	- [x] sind mit korrekter Grammatik und Rechtschreibung geschrieben
	- [x] Kurze und präzise Beschreibung der Funktionalität nach `@brief` 
	- [x] \[optional] Detailliertere Beschreibung, in der die Funktionsschritte durchgegangen und wichtige Implementationsdetails erklärt werden
	- [x] \[optional] Folge von Extrainformationen, wie die Funktion benutzt werden sollte nach `@note` 
	- [x] Folge der Parameter, in denen in einem kurzem Satz die Bedeutung des Parameters im Kontext der Funktion erklärt wird nach `@tparam` und `@param` geschrieben
	- [x] \[falls die Funktion einen Rückgabewert hat] Bedeutung des Rückgabewerts wird im Kontext der Funktion nach `@return` beschrieben 
	- [x] Die Reihenfolge der Dokumentation ist: `@brief`, \[optional] detailliertere Beschreibung, \[optional] `@note`, `@tparam` und `@param`, \[falls die Funktion einen Rückgabewert hat] `@return`
	- [x] Alle Blöcke in der Dokumentation sind durch genau eine Leerzeile getrennt
	- [x] Die Dokumentation ist in einem Kommentarblock (/* ... \*/)
	- [x] Wenn C++ Typen referenziert werden, wird der Name monospaced nach `@c` geschrieben
- ##### Dokumentation von Klassen, Strukturen, Enumerations, Namespaces etc.
	- [x] sind in englischer Sprache
	- [x] sind als ganze Sätze umgesetzt
	- [x] sind mit korrekter Grammatik und Rechtschreibung geschrieben
	- [x] Kurze und präzise Beschreibung der Funktionalität nach `@brief` 
	- [x] \[optional] Detailliertere Beschreibung, in der die Funktionalitätsschritte durchgegangen und wichtige Implementation Details erklärt werden
	- [x] \[optional] Folge von Extrainformationen, wie die Funktion benutzt werden sollte nach `@note` 
	- [x] Die Reihenfolge der Dokumentation ist: `@brief`, \[optional] detailliertere Beschreibung, \[optional] `@note`
	- [x] Alle Blöcke in der Dokumentation sind durch genau eine Leerzeile getrennt
	- [x] Die Dokumentation ist in einem Kommentarblock (/* ... \*/)
	- [x] Wenn C++ Typen referenziert werden, wird der Name monospaced nach `@c` geschrieben

### Modernes C++
- [x] `auto` benutzt bei Speicherung oder Referenz eines Rückgabewerts
- [x] `auto` benutzt bei Variablendeklarationen
- [x] In Schleifen nur Iterationen über Mengen genutzt
- [x] Wenn existent STL Implementation verwändet
- [x] Lambda statt benannter Funktion in STL API's verwendet
- [x] Lambda statt Code Duplikation benutzt
- [x] Variablen, wenn möglich konstant durch `const` gemacht
- [x] Ausdrücke, wenn möglich konstant durch `constexpr` gemacht

### Style Guidelines
- [x] Alle Identifiers außer Template Parameter sind in snake_case geschrieben
- [x] Alle Template Parameter sind in PascalCase geschrieben
- [x] Alle Identifiers sind passend gewählt
- [x] Es wurde `#pragma once` anstatt explizit eingebundenen Guards verwendet
- [x] In den includes wurde `<>` für Standard Bibliothek und `""` für den Rest verwendet 
- [x] `using namespace` wurde nur in kleinen Namespaces, über die die volle Kontrolle bestand, verwendet
- [x] Am Ende jeder Datei ist eine Leerzeile

### Code Formatter und Linter
- [x] Code Formatter ist korrekt am Code angewendet worden
- [x] Linter ist korrekt am Code angewendet worden


## Statusmeeting 2 zu User Story 17. Sammeln von Metadaten 
- Datum: 19.01.2024 18:00 Uhr - 18:30 Uhr
- Entwickler\*innen: Leonhard Steinecke
- Code Buddy: Simon Riese
- [x] alle besprochenen Änderungen wurden umgesetzt
- Kontext:
	- -
- Beispiel:
	- -
- Diagnose:
	- -
- Aktion:
	- -
- Sonstiges: 
	- Keine Fehler im Code oder der Dokumentation, die die Lesbarkeit beeinträchtigen
	- Tests gehen durch


Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: -

---

## Checkliste 2 zu User Storie 18. Lesen und Schreiben von Metadaten im JSON-Format
### C API
- [x] Keine manuelle Heapallokation benutzt
- [x] Keine C-Arrays, sondern C++-Arrays zur Stack Allokation benutzt
- [x] Keine Strings als null-terminierende char Pointer umgesetzt
- [x] Casting nur durch Casting Operationen durchgeführt
- [x] Keine Funktionen von cstdlib, sondern von STL Funktionen verwendet
- [x] Keine raw Pointer, sondern Referenzen benutzen
- [x] Logische Operatoren nur in der ausgeschriebenen Bezeichnung benutzt
- [x] Keine Macros, sondern Templates und andere moderne Compile-time Konstruktionen verwendet

### Kompilieren
- [x] nur CMake 3.16 verwendet
- [x] kein Undefined Behavior vorhanden
- [x] Alle Warnungen werden als Error behandelt
- [x] Build -0fast ist aktiviert und funktioniert

### Dokumentation
- ##### Kommentare in Funktionen sind: 
	- [x] in englischer Spreche 
	- [x] als ganze Sätze umgesetzt
	- [x] mit korrekter Grammatik und Rechtschreibung geschrieben
	- [x] nur als inline Kommentare (// statt /* ... \*/) umgesetzt
- ##### Dokumentationen von Funktionen 
	- [x] sind in englischer Sprache
	- [x] sind als ganze Sätze umgesetzt
	- [x] sind mit korrekter Grammatik und Rechtschreibung geschrieben
	- [x] Kurze und präzise Beschreibung der Funktionalität nach `@brief` 
	- [x] \[optional] Detailliertere Beschreibung, in der die Funktionsschritte durchgegangen und wichtige Implementationsdetails erklärt werden
	- [x] \[optional] Folge von Extrainformationen, wie die Funktion benutzt werden sollte nach `@note` 
	- [x] Folge der Parameter, in denen in einem kurzem Satz die Bedeutung des Parameters im Kontext der Funktion erklärt wird nach `@tparam` und `@param` geschrieben
	- [x] \[falls die Funktion einen Rückgabewert hat] Bedeutung des Rückgabewerts wird im Kontext der Funktion nach `@return` beschrieben 
	- [x] Die Reihenfolge der Dokumentation ist: `@brief`, \[optional] detailliertere Beschreibung, \[optional] `@note`, `@tparam` und `@param`, \[falls die Funktion einen Rückgabewert hat] `@return`
	- [x] Alle Blöcke in der Dokumentation sind durch genau eine Leerzeile getrennt
	- [x] Die Dokumentation ist in einem Kommentarblock (/* ... \*/)
	- [x] Wenn C++ Typen referenziert werden, wird der Name monospaced nach `@c` geschrieben
- ##### Dokumentation von Klassen, Strukturen, Enumerations, Namespaces etc.
	- [x] sind in englischer Sprache
	- [x] sind als ganze Sätze umgesetzt
	- [x] sind mit korrekter Grammatik und Rechtschreibung geschrieben
	- [x] Kurze und präzise Beschreibung der Funktionalität nach `@brief` 
	- [x] \[optional] Detailliertere Beschreibung, in der die Funktionalitätsschritte durchgegangen und wichtige Implementation Details erklärt werden
	- [x] \[optional] Folge von Extrainformationen, wie die Funktion benutzt werden sollte nach `@note` 
	- [x] Die Reihenfolge der Dokumentation ist: `@brief`, \[optional] detailliertere Beschreibung, \[optional] `@note`
	- [x] Alle Blöcke in der Dokumentation sind durch genau eine Leerzeile getrennt
	- [x] Die Dokumentation ist in einem Kommentarblock (/* ... \*/)
	- [x] Wenn C++ Typen referenziert werden, wird der Name monospaced nach `@c` geschrieben

### Modernes C++
- [x] `auto` benutzt bei Speicherung oder Referenz eines Rückgabewerts
- [x] `auto` benutzt bei Variablendeklarationen
- [x] In Schleifen nur Iterationen über Mengen genutzt
- [x] Wenn existent STL Implementation verwändet
- [x] Lambda statt benannter Funktion in STL API's verwendet
- [x] Lambda statt Code Duplikation benutzt
- [x] Variablen, wenn möglich konstant durch `const` gemacht
- [x] Ausdrücke, wenn möglich konstant durch `constexpr` gemacht

### Style Guidelines
- [x] Alle Identifiers außer Template Parameter sind in snake_case geschrieben
- [x] Alle Template Parameter sind in PascalCase geschrieben
- [x] Alle Identifiers sind passend gewählt
- [x] Es wurde `#pragma once` anstatt explizit eingebundenen Guards verwendet
- [x] In den includes wurde `<>` für Standard Bibliothek und `""` für den Rest verwendet 
- [x] `using namespace` wurde nur in kleinen Namespaces, über die die volle Kontrolle bestand, verwendet
- [x] Am Ende jeder Datei ist eine Leerzeile

### Code Formatter und Linter
- [x] Code Formatter ist korrekt am Code angewendet worden
- [x] Linter ist korrekt am Code angewendet worden


## Statusmeeting 2 zu User Story 18. Lesen und Schreiben von Metadaten im JSON-Format
- Datum: 19.01.2024 16:00 Uhr - 16:30 Uhr
- Entwickler\*innen: Simon Riese
- Code Buddy: Leonhard Steinecke
- [x] alle besprochenen Änderungen wurden umgesetzt 
- Kontext:
	- -
- Beispiel:
	- -
- Diagnose:
	- -
- Aktion:
	- -
- Sonstiges:
	- Keine Fehler in der Dokumentation
	- Da Implementation noch nicht vollständig Übernahme in die nächste Iteration


Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: 
	- User Story wurde in die nächste Iteration übernommen. Änderungen werden bis zum nächsten Code Buddy Meeting umgesetzt. 