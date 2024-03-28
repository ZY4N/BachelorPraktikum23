## User Story: 1 - Distanzfilterung von Punktdaten
Datum: 28.11.2023
Entwickler*innen: Greys Fankyeyeva
Code Buddy: Simon Riese
#### Ergebnis des Reviews: 
* Wurden die Maßnahmen für Erweiterbarkeit korrekt umgesetzt?
    - Das Filtern mit einem änderbaren Filter-Prädikate wurde umgesetzt.
* Wurden die Maßnahmen für Leistung und Ressourcenverwendung korrekt umgesetzt?
    - Die Laufzeit und Speicherauslastung sind konstant.
    - Die Filter Funktionen werden mit einem Template geinlinet und arbeiten mit quadrierten Distanzen, um Wurzelberechnungen zu vermeiden.
    - Die Filter Funktionen können ohne Komplikationen von mehreren Threads gleichzeitig verwendet werden.
    - Die Filter Funktionen arbeiten auf eng-gepackten Vektoren und füllen so die Cache-Lines voll aus.
* Probleme, die im Code Review gefunden wurden: 
    - Es wurden keine Probleme im Code Review gefunden.

## User Story: 2 - Geschwindigkeits-Entzerrung
Datum: 28.11.2023
Entwickler*innen: Severin Pelikan
Code Buddy: Leonhard Steinecke
#### Ergebnis des Reviews: 
* Wurden die Maßnahmen für Erweiterbarkeit korrekt umgesetzt?
    - N/A
* Wurden die Maßnahmen für Leistung und Ressourcenverwendung korrekt umgesetzt?
    - Die Laufzeit und Speicherauslastung sind linear Abhängig von der Anzahl an zu verarbeitenden Punkte.
    - Es wurden keine vermeidbaren Berechnungen vorgenommen.
    - Die Implementation nutzt alle zur Verfügung stehenden Threads aus, indem die zu verarbeitenden Punkte nach Aufnahmezeitpunkten
    - Der Algorithmus nutzt die selben Cache-Line optimierten Datenstrukturen wie US-0.
* Probleme, die im Code Review gefunden wurden:
    - Es wurden keine Probleme im Code Review gefunden.

## User Story: 4 - Integration von 3DTK People Remover in Scan Combiner
Datum: 28.11.2023
Entwickler*innen: Greys Fankyeyeva, Simon Riese
Code Buddy: Alicia Gleichmann
#### Ergebnis des Reviews: 
* Wurden die Maßnahmen für Erweiterbarkeit korrekt umgesetzt?
    - Die Schnittstelle für weitere Ausgabemodule wurde wie besprochen implementiert und das UOS-Modul wurde in dieser Schnittstelle eingefügt.
* Wurden die Maßnahmen für Leistung und Ressourcenverwendung korrekt umgesetzt?
    - Der Schnittstelle und dem Modul werden die Punktdaten als`tcb:span` übergeben, um Kopien zu vermeiden.
    - Das UOS-Module schreibt die Punktdaten als `std::hexfloat`.
* Probleme, die im Code Review gefunden wurden:
    - Die Umrechnung von Eulerschen Winkeln in Grad wurde nicht korrekt implementiert.
    - Konsequenz: Die Berechnung wurde korrigiert, getestet und dann akzeptiert.