
# Statusmeeting Protokolle Iteration 4
---

## Checkliste 1 zu User Storie 8. Entfernen von Nick- und Schwankbewegungen aus Scans
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


## Statusmeeting 1 zu User Story 8. Entfernen von Nick- und Schwankbewegungen aus Scans
- Datum: 29.12.2023 12:30 Uhr - 13:00 Uhr
- Entwickler\*innen: Severin Pelikan
- Code Buddy: Leonhard Steinecke
- Kontext:
	- -
- Beispiel:
	- -
- Diagnose:
	- -
- Aktion:
	- -
- Sonstiges:
	- Passt alles so weit schon geschrieben
	- Dokumentation bei schon implementierten Teilen großteils fertig und korrekt
	- Noch fertig dokumentieren, aber da erst Zwischenstand ok
- Nächstes Meeting am: 06.01.2024 um 12:30 Uhr

---

## Checkliste 1 zu User Storie 9. Integration von Removert in Scan Combiner
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


## Statusmeeting 1 zu User Story 9. Integration von Removert in Scan Combiner
- Datum: 29.12.2023 10:00 Uhr - 10:45 Uhr
- Entwickler\*innen: Simon Riese
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
	- Umsetzung bis jetzt sehr ähnlich zu User Story 4, keine Fehler
	- Frage zu Kitti Format noch mal nachgeschaut bei KIT wegen Transformationsspeicherung in einem extra Ordner
- Nächstes Meeting am: 06.01.2024 um 10:00 Uhr

---

## Statusmeeting 1 zu User Story 10. Entfernung dynamischer Objekte mittels Removert
- Datum: 29.12.2023 15:00 Uhr - 15:15 Uhr
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
	- Removert wurde heruntergeladen
	- Angefangen den externen Testdatensatz auszuprobieren, scheint bisher gut
- Nächstes Meeting am: 07.01.2024 um 12:30 Uhr

---

## Checkliste 1 zu User Storie 11. Docker integration für Zielsystem 
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
	- [ ] als ganze Sätze umgesetzt
	- [ ] mit korrekter Grammatik und Rechtschreibung geschrieben
	- [x] nur als inline Kommentare (// statt /* ... \*/) umgesetzt
- ##### Dokumentationen von Funktionen 
	- [x] sind in englischer Sprache
	- [ ] sind als ganze Sätze umgesetzt
	- [ ] sind mit korrekter Grammatik und Rechtschreibung geschrieben
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
	- [ ] sind als ganze Sätze umgesetzt
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
- [x] Code Formatter ist korrekt am Code angewendet worden
- [x] Linter ist korrekt am Code angewendet worden


## Statusmeeting 1 zu User Story 11. Docker integration für Zielsystem 
- Datum: 29.12.2023 12:30 Uhr - 13:00 Uhr
- Entwickler\*innen: Leonhard Steinecke
- Code Buddy: Alicia Gleichmann
- Kontext:
	- Dokumentation in Fließtext
- Beispiel:
	- -
- Diagnose:
	- Fließtext 
- Aktion:
	- Stichpunkte Ausformulieren
- Sonstiges: 
	- kein C++ Code, deshalb mussten die spezifischen C++ Code Abschnitte in der Checkliste überspungen werden (gilt auch für zweites Statusmeeting)
	- Sieht bis jetzt gut aus 
	- Dokumentation ist bisher nur stichpunktartig, aber scheint korrekt
- Nächstes Meeting am: 06.01.2024 um 14:00 Uhr

---

## Checkliste 1 zu User Storie 12. Dynamisches Anpassen des Ausgabeformats über CLI
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
- [ ] Alle Identifiers sind passend gewählt
- [x] Es wurde `#pragma once` anstatt explizit eingebundenen Guards verwendet
- [x] In den includes wurde `<>` für Standard Bibliothek und `""` für den Rest verwendet 
- [x] `using namespace` wurde nur in kleinen Namespaces, über die die volle Kontrolle bestand, verwendet
- [x] Am Ende jeder Datei ist eine Leerzeile

### Code Formatter und Linter
- [x] Code Formatter ist korrekt am Code angewendet worden
- [x] Linter ist korrekt am Code angewendet worden


## Checkliste 1 zu User Storie 14. Anpassung der Arbeitsspeicherauslastung über CLI
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


## Statusmeeting 1 zu User Story 12. Dynamisches Anpassen des Ausgabeformats über CLI, 13. Dynamisches Anpassen der Loggerkonfiguration über CLI, 14. Anpassung der Arbeitsspeicherauslastung über CLI und 15. Dynamisches Anpassen der maximalen radialen und peripheren Distanzen über CLI
- Datum: 28.12.2023 12:30 Uhr - 13:30 Uhr
- Entwickler\*innen: Alicia Gleichmann
- Code Buddy: Severin Pelikan
- Kontext:
	- Identifier nicht passend gewählt
- Beispiel:
	-  --o_format
- Diagnose:
	- Weniger verständlich, was der Parameter macht
- Aktion:
	- Umbenennen
- Sonstiges: 
	- Bisher nur Anpassung des Ausgabeformats und Anpassung der Arbeitsspeicherauslastung angefangen
	- Anpassung des Ausgabeformats fertig bis auf Tests
	- Besprochen, wie alle restlichen Parameter heißen sollen: 
		- --frame-format
		- --log-level oder -l
		- --time-per-block
		- --max-radial-dist und --max-peripheral-dist
- Nächstes Meeting am: 06.01.2024 15:00 Uhr

---

## Statusmeeting 2 zu User Story 8. Entfernen von Nick- und Schwankbewegungen aus Scans
- Datum: 06.01.2024 12:30 Uhr - 13:00 Uhr
- Entwickler\*innen: Severin Pelikan
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
	- Tests gehen nicht durch
	- Herausgefunden die benötigten Daten des IMU-Sensors sind fehlerhaft, deshalb User Storie verworfen


Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: 
	- kein Abschluss der User Story und keine Änderungen, da die User Story nicht übernommen wird.

---

## Checkliste 2 zu User Storie 9. Integration von Removert in Scan Combiner
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


## Statusmeeting 2 zu User Story 9. Integration von Removert in Scan Combiner
- Datum: 06.01.2024 10:00 Uhr - 10:30 Uhr
- Entwickler\*innen: Simon Riese
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
	- Code zusammen durchgegangen
	- Keine Probleme in der Dokumentation und auch keine verbotenen Operationen verwendet


Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: -

---

## Statusmeeting 2 zu User Story 10. Entfernung dynamischer Objekte mittels Removert
- Datum: 07.01.2024 12:30 Uhr - 14:00 Uhr
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
	- Removert läuft auf unseren Daten durch
	- Braucht ziemlich lange zum Durchlaufen
	- Nach dem Durchlauf sind noch semi-dynamische Objekte zu erkennen (Bahn)
		- Übernahme in nächste Iteration


Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: 
	- User Story wurde in die nächste Iteration übernommen. Änderungen werden bis zum nächsten Code Buddy Meeting umgesetzt. 

---

## Checkliste 2 zu User Storie 11. Docker integration für Zielsystem 
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


## Statusmeeting 2 zu User Story 11. Docker integration für Zielsystem 
- Datum: 06.01.2024 14:00 Uhr - 14:30 Uhr
- Entwickler\*innen: Leonhard Steinecke
- Code Buddy: Alicia Gleichmann
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
	- Docker Container läuft und die Dokumentation ist auch korrekt


Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: -

---

## Checkliste 2 zu User Storie 12. Dynamisches Anpassen des Ausgabeformats über CLI
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


## Checkliste 2 zu User Storie 13. Dynamisches Anpassen der Loggerkonfiguration über CLI
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


## Checkliste 2 zu User Storie 14. Anpassung der Arbeitsspeicherauslastung über CLI
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


## Checkliste 2 zu User Storie 15. Dynamisches Anpassen der maximalen radialen und peripheren Distanzen über CLI
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


## Statusmeeting 2 zu User Story 12. Dynamisches Anpassen des Ausgabeformats über CLI, 13. Dynamisches Anpassen der Loggerkonfiguration über CLI, 14. Anpassung der Arbeitsspeicherauslastung über CLI und 15. Dynamisches Anpassen der maximalen radialen und peripheren Distanzen über CLI
- Datum: 06.01.2024 15:00 Uhr - 17:30 Uhr
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
	- Probleme mit Chrono Integration im arx 
		- Tests gingen nicht durch
		- Zusammen fertig implementiert
	- Die anderen User Stories sind Lesbar implementiert und dokumentiert


Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: 06.01.2024