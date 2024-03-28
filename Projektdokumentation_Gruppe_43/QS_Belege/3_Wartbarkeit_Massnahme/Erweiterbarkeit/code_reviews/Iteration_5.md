## User Story: 16 - Export zu segmentierten Kartenformat
Datum: 21.01.2024
Entwickler*innen: Severin Pelikan, Alicia Gleichmann
Code Buddy: Greys Fankyeyeva
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
    - Kommentare für komplexe Codeabschnitte waren nicht ausführlich genug. Diese wurde im Review angepasst und dann akzeptiert.



## User Story: 17 - Sammeln von Metadaten
Datum: 21.01.2024
Entwickler*innen: Leonhard Steinecke
Code Buddy: Simon Riese
#### Ergebnis des Reviews: 
* Wurden die Maßnahmen für Erweiterbarkeit korrekt umgesetzt?
    - Es wurde eine übersichtliche Struktur im Struct genutzt, daher ist es einfach weitere Felder hinzuzufügen. 
* Wurden die Maßnahmen für Leistung und Ressourcenverwendung korrekt umgesetzt?
    - Die Eintragefunktion wurde umgesetzt und erlaubt nur einzigartige Einträge.
* Probleme, die im Code Review gefunden wurden: 
    - Es wurden keine Probleme im Code Review gefunden.