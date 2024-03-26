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

## Checkliste 1 zu User Storie 16. Export zu segmentierten Karten Format 



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