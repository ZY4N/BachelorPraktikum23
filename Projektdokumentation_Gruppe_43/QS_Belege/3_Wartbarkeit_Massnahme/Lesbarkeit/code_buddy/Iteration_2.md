# Statusmeeting Protokolle

#TODO: geplante Userstories löschen, Rechtschreibung prüfen
geplante Userstories:
0. Einlese-Option für Rosbag-Dateien x 2 Push
1. Distanzfilterung von Punktdaten x 2 Push
2. Geschwindigkeits-Entzerrung x 3 Push
3. Integration von dynamischem Logging-System x 2 Push
4. Integration von 3DTK People Remover in Scan Combiner x 3 Push
5. Entfernung dynamischer Objekte mittels 3DTK People Remover x 0 Push

## Statusmeeting 1 zu User Story 0. Einlese-Option für Rosbag-Dateien
- Datum: 20.11.2023 16:00 Uhr - 17:30 Uhr
- Entwickler\*innen: Leonhard Steinecke
- Code Buddy: Severin Pelikan
- Kontext:
	- Ausgeschaltet das alle Warnungen als Error betrachtet werden
- Beispiel:
	- alte Version von Eigen verwendet
- Diagnose:
	- z.B. Funktionen der alten Version von Eigen sind deprecated und werfen warnings 
- Aktion:
	- Schalte das wieder an! Und nutz die neuere Version von Eigen
- Sonstiges: 
	- Code grob besprochen 
	- die aktuelle Version von Eigen runter geladen
	- Einige Fragen zu C++ geklärt (warum es wichtig ist Werror nicht zu deaktivieren)

hier Checkliste einfügen

---

## Statusmeeting 1 zu User Story 1. Distanzfilterung von Punktdaten 
- Datum: 20.11.2023 15:30 Uhr - 16:30 Uhr
- Entwickler\*innen: Greys Fankyeyeva
- Code Buddy: Simon Riese
- Kontext: 
	- Variable nicht const gesetzt
- Beispiel
	- distance_filtering.ipp distance_sq, peripheral_distance_sq, radial_distance_sq
- Diagnose:
	- Schlechtere Performance wenn Variablen nicht als Konstant markiert sind
- Aktion:
	- die Variablen const setzen
- Sonstiges:
	- Implementation ist schon fertig
	- Tests gehen durch
	- Variablen direkt Konstant gesetzt
	- Kein weiteres Statusmeeting notwendig

- Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: 20.11.2023

hier Checkliste einfügen

---

## Statusmeeting 1 zu User Story 2. Geschwindigkeits-Entzerrung und 3. Integration von dynamischem Logging-System
- Datum: 21.11.2023 14:00 Uhr - 15:30 Uhr
- Entwickler\*innen: Severin Pelikan
- Code Buddy: Leonhard Steinecke
- Kontext:
	- Grammatikfehler
	- Leerzeile in Dokumentation von Funktion vergessen
- Beispiel:
	- Logger.hpp
	- Refraimer.hpp refraime_to_closest_scan_position
- Diagnose:
	- -
	- Verschlechtert die Lesbarkeit
- Aktion:
	- Korrektur der Grammatik
	- Leerzeile einfügen
- Sonstiges:
	- Code durchgesprochen von beiden User Storys
	- Demonstration das 90% der Geschwindigkeiten Duplikate von vorherigen Geschwindigkeiten sind
	- Geklärt ob Informationen zur Anzahl der Transformationsmatrizen vom Logger ausgegeben werden sollten, sind zum Schluss gekommen ja
	- Grammatikfehler Korrektur und Leerzeile direkt eingefügt

hier Checkliste einfügen

---

## Statusmeeting 1 zu User Story 4. Integration von 3DTK People Remover in Scan Combiner 
- Datum: 20.11.2023 18:00 Uhr - 19:15 Uhr
- Entwickler\*innen: Greys Fankyeyeva, Simon Riese
- Code Buddy: Alicia Gleichmann
- Kontext: 
	- Am Ende Datei wurde die Leerzeile vergessen
- Beispiel:
	- frame_exporter.cpp 
- Diagnose:
	- -
- Aktion:
	- Leerzeile einfügen
- Sonstiges
	- Code wurde durchgegangen
	- Leerzeile wurde direkt eingefügt
	- Simon ist großteils fertig, Greys ist für Tests zuständig und hat deshalb noch nicht begonnen

hier Checkliste einfügen

---

## Statusmeeting 1 zu User Story 5. Entfernung dynamischer Objekte mittels 3DTK People Remover
- Datum: 21.11.2023 13:30 Uhr - 14:30 Uhr
- Entwickler\*innen: Alicia Gleichmann
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
	- Probleme beim Einrichten durch falsche Hardware von Alicia, dann Wechsel
	- Programm scheint richtig Heruntergeladen und auf Gerät eingerichtet
	- User Story 4 noch nicht fertig, deshalb noch keine Tests möglich

hier Checkliste einfügen

---

## Statusmeeting 2 zu User Story 0. Einlese-Option für Rosbag-Dateien
- Datum: 26.11.2023 15:00 Uhr - 18:30 Uhr
- Entwickler\*innen:  Leonhard Steinecke
- Code Buddy: Severin Pelikan
- [x] alle besprochenen Änderungen wurden umgesetzt 
- Kontext: 
	- Grammatikfehler
- Beispiel: 
	- Unbagger 
- Diagnose: 
	- -
- Aktion:
	- Korrektur dieser
- Sonstiges:
	- Tests laufen nicht durch
	- Code durchgeschaut um potetielle Ursachen für die nicht durchlaufenden Tests zu finden
	- User Story kann nicht abgenommen werden durch die fehlschlagenden Tests und wird mit in die nächste Iteration übernommen.

- Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: 
	- User Story wurde in die nächste Iteration übernommen. Änderungen werden bis zum nächsten Code Buddy Meeting umgesetzt.

hier Checkliste einfügen

---

## Statusmeeting 2 zu User Story 2. Geschwindigkeits-Entzerrung und 3. Integration von dynamischem Logging-System
- Datum: 26.11.2024 12:30 Uhr - 14:30 Uhr
- Entwickler\*innen: Severin Pelikan
- Code Buddy: Leonhard Steinecke
- [x] alle besprochenen Änderungen wurden umgesetzt 
- Kontext: 
	- std Typ nicht genutzt
- Beispiel:
	- refraimer.cpp num_points_in_pose
- Diagnose:
	- std Typen sind effizienter
- Aktion:
	- size_t zu std::size_t ändern
- Sonstiges:
	- Demo des aktuellen Stands des Loggers
		- Alles ausgeben ist fertig -> debug level
		- Angeben können ob farbig oder nicht ist fertig
		- Anderen Level in denen nur eine spezifische Detail Tiefe ausgegeben wird ist nicht fertig
		- User Story 3 kann nicht abgenommen werden, da die unterschiedlichen Log-Level nicht fertig implementiert sind
	- Code für Geschwindigkeitsentzerrung durchgegangen
		- Typ direkt geändert
		- Keine Probleme im Code
		- Tests laufen durch

- Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: 
	- User Story 2: 26.11.2023
	- User Story 3 wurde in die nächste Iteration übernommen. Änderungen werden bis zum nächsten Code Buddy Meeting umgesetzt. 

hier Checkliste einfügen

---

## Statusmeeting 2 zu User Story 4. Integration von 3DTK People Remover in Scan Combiner 
- Datum: 25.11.2024 12:30 Uhr - 13:00 Uhr
- Entwickler\*innen: Greys Fankyeyeva, Simon Riese
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
	- Tests gehen durch
	- Fertigen Code durchgegangen
	- Sieht alles gut aus

- Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: -

hier Checkliste einfügen

---

## Statusmeeting 2 zu User Story 5. Entfernung dynamischer Objekte mittels 3DTK People Remover
- Datum: 27.11.2023 15:30 Uhr - 18:00 Uhr
- Entwickler\*innen: Alicia Gleichmann
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
	- Programm scheint mit den eigenen Testdatensätzen gut zu funktionieren
	- Programm stürzt entweder ab oder erzeugt ungültige Outputs mit unseren Daten
	- Verschiedene Kombinationen der Variablen noch mal jetzt ausprobiert, selbes Ergebnis
	- Wird verworfen, da keine brauchbaren Resultate

- Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: 
	- kein Abschluss der User Story und keine Änderungen, da die User Story nicht übernommen wird.

hier Checkliste einfügen
