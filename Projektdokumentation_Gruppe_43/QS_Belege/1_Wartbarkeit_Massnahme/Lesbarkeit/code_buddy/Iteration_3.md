# Statusmeeting Protokolle Iteration 3
---

## Checkliste 1 zu User Story 0. Einlese-Option für Rosbag-Dateien
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


## Statusmeeting 1 zu User Story 0. Einlese-Option für Rosbag-Dateien
- Datum: 07.12.2023
- Entwickler\*innen: Leonhard Steinecke
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
	- Tests laufen durch, Vorzeichenfehler
	- Rest des Codes hat sich nicht mehr verändert
	- Dementsprechend keine Weiteren Statusmeetings von Nöten

---

## Checkliste 1 zu User Story 3. Integration von dynamischem Logging-System
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

## Checkliste 1 zu User Story 6. Verringerung von Aufnahmetransformationen
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
	- [ ] als ganze Sätze umgesetzt
	- [ ] mit korrekter Grammatik und Rechtschreibung geschrieben
	- [x] nur als inline Kommentare (// statt /* ... \*/) umgesetzt
- ##### Dokumentationen von Funktionen 
	- [x] sind in englischer Sprache
	- [ ] sind als ganze Sätze umgesetzt
	- [ ] sind mit korrekter Grammatik und Rechtschreibung geschrieben
	- [ ] Kurze und präzise Beschreibung der Funktionalität nach `@brief` 
	- [ ] \[optional] Detailliertere Beschreibung, in der die Funktionsschritte durchgegangen und wichtige Implementationsdetails erklärt werden
	- [ ] \[optional] Folge von Extrainformationen, wie die Funktion benutzt werden sollte nach `@note` 
	- [ ] Folge der Parameter, in denen in einem kurzem Satz die Bedeutung des Parameters im Kontext der Funktion erklärt wird nach `@tparam` und `@param` geschrieben
	- [ ] \[falls die Funktion einen Rückgabewert hat] Bedeutung des Rückgabewerts wird im Kontext der Funktion nach `@return` beschrieben 
	- [x] Die Reihenfolge der Dokumentation ist: `@brief`, \[optional] detailliertere Beschreibung, \[optional] `@note`, `@tparam` und `@param`, \[falls die Funktion einen Rückgabewert hat] `@return`
	- [x] Alle Blöcke in der Dokumentation sind durch genau eine Leerzeile getrennt
	- [x] Die Dokumentation ist in einem Kommentarblock (/* ... \*/)
	- [x] Wenn C++ Typen referenziert werden, wird der Name monospaced nach `@c` geschrieben
- ##### Dokumentation von Klassen, Strukturen, Enumerations, Namespaces etc.
	- [x] sind in englischer Sprache
	- [ ] sind als ganze Sätze umgesetzt
	- [ ] sind mit korrekter Grammatik und Rechtschreibung geschrieben
	- [ ] Kurze und präzise Beschreibung der Funktionalität nach `@brief` 
	- [ ] \[optional] Detailliertere Beschreibung, in der die Funktionalitätsschritte durchgegangen und wichtige Implementation Details erklärt werden
	- [ ] \[optional] Folge von Extrainformationen, wie die Funktion benutzt werden sollte nach `@note` 
	- [ ] Die Reihenfolge der Dokumentation ist: `@brief`, \[optional] detailliertere Beschreibung, \[optional] `@note`
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


## Statusmeeting 1 zu User Story 3. Integration von dynamischem Logging-System und 6. Verringerung von Aufnahmetransformationen
- Datum: 08.12.2023
- Entwickler\*innen: Severin Pelikan
- Code Buddy: Ersatz durch Alicia Gleichmann
- [x] alle besprochenen Änderungen wurden umgesetzt 
- Kontext:
	- Dokumentation teils noch unvollständig
- Beispiel:
	- eig. überall
- Diagnose:
	- Dokumentation ist wichtig fürs Codeverständnis
- Aktion:
	- Dokumentation fertig schreiben
- Sonstiges:
	- Leonhard Steinecke wurde krank, deshalb ist Alicia Gleichmann Ersatz Code Buddy
	- Übrigen Logger Level wurden integriert und vorgeführt
		- keine Lesbarkeitsfehler im Code und Tests laufen durch
		- Demo der verschiedenen Logger Level
		- Dementsprechend keine weiteren Statusmeetings mehr notwendig
	- Verringerung der Aufnahmetransformationen
		- Implementation fast fertig, Doku und Tests fehlen noch
		- Vorhandene Dokumentation scheint Richtig, ist aber auch teils noch mehr stichpunktartig als Fließtext
- Nächstes Meeting am: 15.12.2023 um 16:00 Uhr

---

## Checkliste 1 zu User Story 7. Dynamisches Anpassen von Ein- und Ausgabepfaden über CLI
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
	- [ ] als ganze Sätze umgesetzt
	- [ ] mit korrekter Grammatik und Rechtschreibung geschrieben
	- [x] nur als inline Kommentare (// statt /* ... \*/) umgesetzt
- ##### Dokumentationen von Funktionen 
	- [x] sind in englischer Sprache
	- [ ] sind als ganze Sätze umgesetzt
	- [ ] sind mit korrekter Grammatik und Rechtschreibung geschrieben
	- [ ] Kurze und präzise Beschreibung der Funktionalität nach `@brief` 
	- [ ] \[optional] Detailliertere Beschreibung, in der die Funktionsschritte durchgegangen und wichtige Implementationsdetails erklärt werden
	- [ ] \[optional] Folge von Extrainformationen, wie die Funktion benutzt werden sollte nach `@note` 
	- [ ] Folge der Parameter, in denen in einem kurzem Satz die Bedeutung des Parameters im Kontext der Funktion erklärt wird nach `@tparam` und `@param` geschrieben
	- [ ] \[falls die Funktion einen Rückgabewert hat] Bedeutung des Rückgabewerts wird im Kontext der Funktion nach `@return` beschrieben 
	- [ ] Die Reihenfolge der Dokumentation ist: `@brief`, \[optional] detailliertere Beschreibung, \[optional] `@note`, `@tparam` und `@param`, \[falls die Funktion einen Rückgabewert hat] `@return`
	- [x] Alle Blöcke in der Dokumentation sind durch genau eine Leerzeile getrennt
	- [x] Die Dokumentation ist in einem Kommentarblock (/* ... \*/)
	- [x] Wenn C++ Typen referenziert werden, wird der Name monospaced nach `@c` geschrieben
- ##### Dokumentation von Klassen, Strukturen, Enumerations, Namespaces etc.
	- [x] sind in englischer Sprache
	- [ ] sind als ganze Sätze umgesetzt
	- [ ] sind mit korrekter Grammatik und Rechtschreibung geschrieben
	- [ ] Kurze und präzise Beschreibung der Funktionalität nach `@brief` 
	- [ ] \[optional] Detailliertere Beschreibung, in der die Funktionalitätsschritte durchgegangen und wichtige Implementation Details erklärt werden
	- [ ] \[optional] Folge von Extrainformationen, wie die Funktion benutzt werden sollte nach `@note` 
	- [ ] Die Reihenfolge der Dokumentation ist: `@brief`, \[optional] detailliertere Beschreibung, \[optional] `@note`
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


## Statusmeeting 1 zu User Story 7. Dynamisches Anpassen von Ein- und Ausgabepfaden über CLI
- Datum: 09.12.2023
- Entwickler\*innen: Alicia Gleichmann, Severin Pelikan
- Code Buddy: Simon Riese
- Kontext:
	- Dokumentation noch unvollständig
- Beispiel:
	- -
- Diagnose:
	- -
- Aktion:
	- fertig Dokumentieren
- Sonstiges:
	- arx Parser vollständig implementiert, Dokumentation noch unvollständig
	- Was an Dokumentation schon da ist, sieht gut aus
	- Kompiliert bei Severin, aber nicht bei Alicia
		- Herausfinden warum
- Nächstes Meeting am: 16.12.2023 um 12:30 Uhr

---

## Checkliste 1 zu User Story 6. Verringerung von Aufnahmetransformationen
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


## Statusmeeting 2 zu User Story 6. Verringerung von Aufnahmetransformationen
- Datum: 15.12.2023
- Entwickler\*innen: Severin Pelikan
- Code Buddy: Ersatz durch Alicia Gleichmann
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
	- Leonhard Steinecke ist krank, deshalb ist Alicia Gleichmann Ersatz Code Buddy
	- Tests laufen durch
	- Grob Änderungen noch mal besprochen
	- alle Punkte der Checkliste konnten abgehakt werden


Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: -

---

## Checkliste 1 zu User Story 7. Dynamisches Anpassen von Ein- und Ausgabepfaden über CLI
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
- [ ] Alle Identifiers sind passend gewählt
- [x] Es wurde `#pragma once` anstatt explizit eingebundenen Guards verwendet
- [x] In den includes wurde `<>` für Standard Bibliothek und `""` für den Rest verwendet 
- [x] `using namespace` wurde nur in kleinen Namespaces, über die die volle Kontrolle bestand, verwendet
- [x] Am Ende jeder Datei ist eine Leerzeile

### Code Formatter und Linter
- [x] clang-format ist korrekt am Code angewendet worden

- [x] clang-tidy ist korrekt in die IDE integriert und wirft keine Errors


## Statusmeeting 2 zu User Story 7. Dynamisches Anpassen von Ein- und Ausgabepfaden über CLI
- Datum: 16.12.2023
- Entwickler\*innen: Alicia Gleichmann, Severin Pelikan
- Code Buddy: Simon Riese
- [x] alle besprochenen Änderungen wurden umgesetzt 
- Kontext:
	- Flag Identifier sind nicht passend gewählt
- Beispiel:
	- --input und -i
- Diagnose:
	- Da Input und Output immer angegeben werden müssen und der Input aus mehreren Rosbags bestehen kann, sollten diese über die positional Arguments angegeben werden
- Aktion:
	- Input Pfade über positional Arguments angeben
- Sonstiges:
	- Hatte nicht kompiliert, weil Alicia gcc 10 und nicht 11 nutzt, deshalb andere Implementation von Span was zu Problemen geführt hat
		- Höchst mögliche Version in Ubuntu 20, deshalb Code angepasst 
	- Input über Positional Arguments angeben im Meeting umgesetzt

Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: 16.12.2023