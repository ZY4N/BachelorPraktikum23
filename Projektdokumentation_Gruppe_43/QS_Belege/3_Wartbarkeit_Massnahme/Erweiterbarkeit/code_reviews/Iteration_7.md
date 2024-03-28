## User Story: 23 - PCD Converter
Datum: 20.02.2024
Entwickler*innen: Greys Fankyeyeva
Code Buddy: Alicia Gleichmann
#### Ergebnis des Reviews: 
* Wurden die Maßnahmen für Erweiterbarkeit korrekt umgesetzt?
    - Es wurde die Bibliothek "PCL" genutzt, um das Schreiben zu implementieren. Somit kann der Konverter um andere PCD-Varianten erweitert werden. 
* Wurden die Maßnahmen für Leistung und Ressourcenverwendung korrekt umgesetzt?
    - 
* Probleme, die im Code Review gefunden wurden: 
    - Es wurde nicht überprüft, ob Dateien im Eingabepfad liegen. Dies wurde im Review behoben und dann akzeptiert.


## User Story: 24 - Programm parallelisieren
Datum: 20.02.2024
Entwickler*innen: Severin Pelikan
Code Buddy: Greys Fankyeyeva
#### Ergebnis des Reviews: 
* Wurden die Maßnahmen für Erweiterbarkeit korrekt umgesetzt?
    - Da wir schon vorher auf die Erweiterung mit Unterstüzung für Multithreading geachtet habne konnte dies gut umgesetzt werden.
* Wurden die Maßnahmen für Leistung und Ressourcenverwendung korrekt umgesetzt?
    - Die Implementation nutzt separate Threads pro Rosbag-Topic sowie mehrere Verarbeitungs-Threads um die Daten zu verarbeiten.
    - Die Anzahl der Threads wrd mittels prozentualen Anteilen effektiv zwischen den Rosbag-Topics aufgeteilt.
    - Die Implementation nutzt `std::mutex` und `std::condition_variable` um die Synchronisation möglichst ressourcenschonend umzusetzen.
    - Die von einem Thread geladenen Punkte werden mittels eines Multipliers unter mehreren Verarbeitungsthreads aufgeteilt, um das Kombinieren der Punkt-Buffer vermeiden zu können.
* Probleme, die im Code Review gefunden wurden: 
    - Bei einer geringen Thread-Zahl wurden für einen Programmteil keine Threads zugewiesen. 
    - Konsequenz: Es wurde eine minimal Anzahl an Threads pro Programmteil gesetzt.

## User Story: 28,29,30 - Erweiterung der CLI-Parameter 
Datum: 20.02.2024
Entwickler*innen: Alicia Gleichmann
Code Buddy: Severin Pelikan
#### Ergebnis des Reviews: 
* Wurden die Maßnahmen für Erweiterbarkeit korrekt umgesetzt?
     - Durch den in US 7 implementierten "Arx-System" konnten diese Erweiterungen effektiv umgesetzt werden.
* Wurden die Maßnahmen für Leistung und Ressourcenverwendung korrekt umgesetzt?
    - N/A
* Probleme, die im Code Review gefunden wurden: 
    - Es wurden keine Probleme im Code Review gefunden.