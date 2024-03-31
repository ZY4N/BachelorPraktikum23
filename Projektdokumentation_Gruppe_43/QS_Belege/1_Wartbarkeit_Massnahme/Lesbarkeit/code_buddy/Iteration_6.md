# Statusmeeting Protokolle Iteration 6
---

## Statusmeeting 1 zu User Story 10. Entfernung dynamischer Objekte mittels Removert
- Datum: 27.01.2024
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
	- auch mit kleineren Datensätzen bleiben Fragmente erhalten
	- Unterschiedliche Gewichtungen der Parameter getestet keine anderen Ergebnisse
	- Demonstration der Fragmente
	- kein weiteres Statusmeeting notwendig

- Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: 
	- kein Abschluss der User Story und keine Änderungen, da die User Story nicht übernommen wird.

---

## Checkliste 1 zu User Story 18. Lesen und Schreiben von Metadaten im JSON-Format
### C API
- [x] Keine manuelle Heapallokation benutzt
- [x] Keine C-Arrays, sondern C++-Arrays zur Stack Allokation benutzt
- [x] Keine Strings als null-terminierende char Pointer umgesetzt
- [x] Casting nur durch Casting Operationen durchgeführt
- [x] Keine Funktionen von cstdlib, sondern von STL Funktionen verwendet
- [x] Keine raw Pointer, sondern Referenzen benutzen
- [ ] Logische Operatoren nur in der ausgeschriebenen Bezeichnung benutzt
- [x] Keine Macros, sondern Templates und andere moderne Compile-time Konstruktionen verwendet

### Kompilieren
- [x] nur CMake 3.16 verwendet
- [x] kein Undefined Behavior vorhanden
- [x] Alle Warnungen werden als Error behandelt
- [x] Build -0fast ist aktiviert und funktioniert

### Dokumentation
- ##### Kommentare in Funktionen sind: 
	- [x] in englischer Sprache 
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
- [x] clang-format ist korrekt am Code angewendet worden

- [x] clang-tidy ist korrekt in die IDE integriert und wirft keine Errors


## Statusmeeting 1 zu User Story 18. Lesen und Schreiben von Metadaten im JSON-Format
- Datum: 27.01.2024
- Entwickler\*innen: Simon Riese
- Code Buddy: Leonhard Steinecke
- Kontext:
	- && statt and 
- Beispiel:
	- metadata_jason.hpp
- Diagnose:
	- schlechter verständlich
- Aktion:
	- && austauschen zu and
- Sonstiges:
	- Der Rest ist bisher gut 
	- && im Meeting ersetzt
- Nächstes Meeting am: 04.02.2024 um 15:00 Uhr

---

## Checkliste 1 zu User Story 19. Ausarbeitung von Grundkonzepten zur Enfernung semi-dynamischer Objekte 
- [x] keine Rechtschreibfehler
- [x] keine Grammatikfehler
- [x] Text ist gut strukturiert  
- [x] Text ist in nachvollziehbare Sinnabschnitte unterteilt
- [x] \[optional] Wenn sinnvoll, wurden Bilder oder Code-Beispiele integriert
- [x] Text hat keine inhaltlichen Fehler
- [x] Es wurden keine langen und verschachtelte, sondern kurze und prägnante Sätze gebildet.
- [x] \[optional] wenn sinnvoll Links integriert
- [x] \[optional] wenn vorhanden Links richtig verlinkt
- [x] \[optional] wenn sinnvoll Übersichtsseiten integriert


## Statusmeeting 1 zu User Story 19. Ausarbeitung von Grundkonzepten zur Enfernung semi-dynamischer Objekte 
- Datum: 28.01.2024
- Entwickler\*innen: Simon Riese, Leonhard Steinecke
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
	- Möglichkeiten scheinen nicht so gut
		- schwer umsetzbar, Umfang eines eigenen Projekts
	- Alle Möglichkeiten kurz durchgesprochen
	- Dokumentation sieht gut aus
- Nächstes Meeting am: 04.02.2024 um 12:30 Uhr

---

## Checkliste 1 zu User Story 22. Dynamisches Anpassen des Metadatenausgabeformats über CLI
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
	- [x] in englischer Sprache 
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
	- [ ] sind mit korrekter Grammatik und Rechtschreibung geschrieben
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
- [x] clang-format ist korrekt am Code angewendet worden

- [x] clang-tidy ist korrekt in die IDE integriert und wirft keine Errors


## Statusmeeting 1 zu User Story 20. Dynamisches Anpassen der maximalen Aufnahmepositionsabweichung innerhalb eines Frames über CLI, 21. Dynamisches Anpassen der Zellengröße über CLI und 22. Dynamisches Anpassen des Metadatenausgabeformats über CLI
- Datum: 27.01.2024
- Entwickler\*innen: Alicia Gleichmann
- Code Buddy: Severin Pelikan
- Kontext:
	- Rechtschreibfehler
- Beispiel:
	- trancoding
- Diagnose:
	- -
- Aktion:
	- transcoding ...
- Sonstiges:
	- US 22 ist, abgesehen von dem Rechtschreibfehler, lesbar und abgeschlossen
		- Direkt korrigiert
	- US 20 und 21 sind noch nicht angefangen
- Nächstes Meeting am: 04.02.2024 um 15:00 Uhr

---

## Checkliste 2 zu User Story 18. Lesen und Schreiben von Metadaten im JSON-Format
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
	- [x] in englischer Sprache 
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
- [x] clang-format ist korrekt am Code angewendet worden

- [x] clang-tidy ist korrekt in die IDE integriert und wirft keine Errors


## Statusmeeting 2 zu User Story 18. Lesen und Schreiben von Metadaten im JSON-Format
- Datum: 04.02.2024
- Entwickler\*innen: Simon Riese
- Code Buddy:  Leonhard Steinecke
- [x] alle besprochenen Änderungen wurden umgesetzt 
- Kontext
	-
- Beispiel:
	- -
- Diagnose:
	- -
- Aktion:
	- -
- Sonstiges:
	- Alles Lesbar
	- Code durchgesprochen
	- keine weiteren Anmerkungen


Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: -

---

## Checkliste 2 zu User Story 19. Ausarbeitung von Grundkonzepten zur Enfernung semi-dynamischer Objekte 
- [x] keine Rechtschreibfehler
- [x] keine Grammatikfehler
- [x] Text ist gut strukturiert  
- [x] Text ist in nachvollziehbare Sinnabschnitte unterteilt
- [x] \[optional] Wenn sinnvoll, wurden Bilder oder Code-Beispiele integriert
- [x] Text hat keine inhaltlichen Fehler
- [x] Es wurden keine langen und verschachtelte, sondern kurze und prägnante Sätze gebildet.
- [x] \[optional] wenn sinnvoll Links integriert
- [x] \[optional] wenn vorhanden Links richtig verlinkt
- [x] \[optional] wenn sinnvoll Übersichtsseiten integriert


## Statusmeeting 2 zu User Story 19. Ausarbeitung von Grundkonzepten zur Enfernung semi-dynamischer Objekte 
- Datum: 04.02.2024
- Entwickler\*innen: Simon Riese, Leonhard Steinecke
- Code Buddy: Greys Fankyeyeva
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
	- Dokumentation ist gut strukturiert und fehlerfrei
	- Umfang der Umsetzung aller Alternativen ist sehr hoch 


Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: -

---


## Checkliste 1 zu User Story 20. Dynamisches Anpassen der maximalen Aufnahmepositionsabweichung innerhalb eines Frames über CLI
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
	- [x] in englischer Sprache 
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
- [x] clang-format ist korrekt am Code angewendet worden

- [x] clang-tidy ist korrekt in die IDE integriert und wirft keine Errors


## Checkliste 1 zu User Story 21. Dynamisches Anpassen der Zellengröße über CLI
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
	- [x] in englischer Sprache 
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
- [x] clang-format ist korrekt am Code angewendet worden

- [x] clang-tidy ist korrekt in die IDE integriert und wirft keine Errors


## Checkliste 2 zu User Story 22. Dynamisches Anpassen des Metadatenausgabeformats über CLI
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
	- [x] in englischer Sprache 
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
- [x] clang-format ist korrekt am Code angewendet worden

- [x] clang-tidy ist korrekt in die IDE integriert und wirft keine Errors


## Statusmeeting 2 zu User Story 20. Dynamisches Anpassen der maximalen Aufnahmepositionsabweichung innerhalb eines Frames über CLI, 21. Dynamisches Anpassen der Zellengröße über CLI und 22. Dynamisches Anpassen des Metadatenausgabeformats über CLI
- Datum: 04.02.2024
- Entwickler\*innen: Alicia Gleichmann
- Code Buddy: Severin Pelikan
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
	- Rechtschreibfehler aus US 22 wurde behoben und US 20 und 21 hatten keine Fehler
	- Code noch mal ganz kurz durchgesprochen


Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: -