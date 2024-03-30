# Checkliste für Code Buddy Reviews

### C API
- [ ] Keine manuelle Heapallokation benutzt
- [ ] Keine C-Arrays, sondern C++-Arrays zur Stack Allokation benutzt
- [ ] Keine Strings als null-terminierende char Pointer umgesetzt
- [ ] Casting nur durch Casting Operationen durchgeführt
- [ ] Keine Funktionen von cstdlib, sondern von STL Funktionen verwendet
- [ ] Keine raw Pointer, sondern Referenzen benutzen
- [ ] Logische Operatoren nur in der ausgeschriebenen Bezeichnung benutzt
- [ ] Keine Macros, sondern Templates und andere moderne Compile-time Konstruktionen verwendet

### Kompilieren
- [ ] nur CMake 3.16 verwendet
- [ ] kein Undefined Behavior vorhanden
- [ ] Alle Warnungen werden als Error behandelt
- [ ] Build -0fast ist aktiviert und funktioniert

### Dokumentation
- ##### Kommentare in Funktionen sind: 
	- [ ] in englischer Spreche 
	- [ ] als ganze Sätze umgesetzt
	- [ ] mit korrekter Grammatik und Rechtschreibung geschrieben
	- [ ] nur als inline Kommentare (// statt /* ... \*/) umgesetzt
- ##### Dokumentationen von Funktionen 
	- [ ] sind in englischer Sprache
	- [ ] sind als ganze Sätze umgesetzt
	- [ ] sind mit korrekter Grammatik und Rechtschreibung geschrieben
	- [ ] Kurze und präzise Beschreibung der Funktionalität nach `@brief` 
	- [ ] \[optional] Detailliertere Beschreibung, in der die Funktionsschritte durchgegangen und wichtige Implementationsdetails erklärt werden
	- [ ] \[optional] Folge von Extrainformationen, wie die Funktion benutzt werden sollte nach `@note` 
	- [ ] Folge der Parameter, in denen in einem kurzem Satz die Bedeutung des Parameters im Kontext der Funktion erklärt wird nach `@tparam` und `@param` geschrieben
	- [ ] \[falls die Funktion einen Rückgabewert hat] Bedeutung des Rückgabewerts wird im Kontext der Funktion nach `@return` beschrieben 
	- [ ] Die Reihenfolge der Dokumentation ist: `@brief`, \[optional] detailliertere Beschreibung, \[optional] `@note`, `@tparam` und `@param`, \[falls die Funktion einen Rückgabewert hat] `@return`
	- [ ] Alle Blöcke in der Dokumentation sind durch genau eine Leerzeile getrennt
	- [ ] Die Dokumentation ist in einem Kommentarblock (/* ... \*/)
	- [ ] Wenn C++ Typen referenziert werden, wird der Name monospaced nach `@c` geschrieben
- ##### Dokumentation von Klassen, Strukturen, Enumerations, Namespaces etc.
	- [ ] sind in englischer Sprache
	- [ ] sind als ganze Sätze umgesetzt
	- [ ] sind mit korrekter Grammatik und Rechtschreibung geschrieben
	- [ ] Kurze und präzise Beschreibung der Funktionalität nach `@brief` 
	- [ ] \[optional] Detailliertere Beschreibung, in der die Funktionalitätsschritte durchgegangen und wichtige Implementation Details erklärt werden
	- [ ] \[optional] Folge von Extrainformationen, wie die Funktion benutzt werden sollte nach `@note` 
	- [ ] Die Reihenfolge der Dokumentation ist: `@brief`, \[optional] detailliertere Beschreibung, \[optional] `@note`
	- [ ] Alle Blöcke in der Dokumentation sind durch genau eine Leerzeile getrennt
	- [ ] Die Dokumentation ist in einem Kommentarblock (/* ... \*/)
	- [ ] Wenn C++ Typen referenziert werden, wird der Name monospaced nach `@c` geschrieben

### Modernes C++
- [ ] `auto` benutzt bei Speicherung oder Referenz eines Rückgabewerts
- [ ] `auto` benutzt bei Variablendeklarationen
- [ ] In Schleifen nur Iterationen über Mengen genutzt
- [ ] Wenn existent STL Implementation verwändet
- [ ] Lambda statt benannter Funktion in STL API's verwendet
- [ ] Lambda statt Code Duplikation benutzt
- [ ] Variablen, wenn möglich konstant durch `const` gemacht
- [ ] Ausdrücke, wenn möglich konstant durch `constexpr` gemacht

### Style Guidelines
- [ ] Alle Identifiers außer Template Parameter sind in snake_case geschrieben
- [ ] Alle Template Parameter sind in PascalCase geschrieben
- [ ] Alle Identifiers sind passend gewählt
- [ ] Es wurde `#pragma once` anstatt explizit eingebundenen Guards verwendet
- [ ] In den includes wurde `<>` für Standard Bibliothek und `""` für den Rest verwendet 
- [ ] `using namespace` wurde nur in kleinen Namespaces, über die die volle Kontrolle bestand, verwendet
- [ ] Am Ende jeder Datei ist eine Leerzeile

### Code Formatter und Linter
- [ ] clang-format ist korrekt am Code angewendet worden
- [ ] clang-tidy ist korrekt am Code angewendet worden