Hi ich bin Greys und stelle Ihnen heute unseren QS-Pitch vor. In Absprache mit unserem Arbeitgeber haben wir unseren Fokus auf Effizienz, Kompatibilität und Wartbarkeit gelegt. 

------------------------------------------------------------------------------------------------------------- 

Als erstes reden wir über Effizienz. 

Die InnoTram kann bis zu 5TB an Rohdaten pro Tag produzieren. Um diese großen Datenmengen ohne Zeitverzug  zu verarbeiten, ist gute Laufzeiteffizienz notwendig.  

Da unser Programm nicht das einzige ist, was auf dem FZD-Server läuft, ist dem AG eine effektive CPU-Auslastung wichtig.  

Da unser System auch mit einem 16GB großen Arbeitsspeicher auskommen muss, ist Speichereffizienz erforderlich.  

------------------------------------------------------------------------------------------------------------- 

Neben Effizienz legen wir auch einen Fokus auf Kompatibilität. 

Für das InnoTram Projekt ist besonders Interoperabilität sehr wichtig. Unsere Komponenten müssen mit den bisherigen Systemen zusammen arbeiten können. Dies bezieht sich besonders auf die Schnittstellen zur Eingabe der Sensordaten und zur Ausgabe der fertigen Karte.  

Da nach uns an dem Projekt noch weitergearbeitet wird, müssen zukünftige Komponenten leicht Informationen austauschen können. Daraus folgt, dass die interne Kommunikation zwischen Komponenten nachvollziehbar und über bekannte Formate verlaufen muss. 

------------------------------------------------------------------------------------------------------------- 

Letztendlich, wenden wir unseren Blick auf Wartbarkeit 

Da sich Ansprüche und die interne Herangehensweise an diese Forschung verändern können, muss unser Code besonders anpassbar sein. Darum haben wir uns auf das Unterziel Erweiterbarkeit geeinigt.  

Außerdem muss unser Code für Mitforschende verständlich und die Ergebnisse für Stakeholder nachvollziehbar sein. Dieses Interesse wird durch das Unterziel Lesbarkeit in unserem Projekt sicher gestellt.  

------------------------------------------------------------------------------------------------------------- 

Da Aspekte der Erweiterbarkeit bereits vor der eigentlichen Implementation geplant und von allen Team Mitgliedern überprüft werden müssen, ist dies ein expliziter Teil der Agenda beim Design Meeting am Anfang jeder Iteration. Um sicherzustellen, dass die Design Entscheidungen adäquat umgesetzt werden, setzen wir auf Code Reviews, da sich die Einhaltung nicht automatisiert testen lässt.  

------------------------------------------------------------------------------------------------------------- 

Um die Lesbarkeit zu erfüllen, haben wir uns auf 3 Maßnahmen geeinigt: 

    Erstens, benutzen wir clang-format. Dieses Werkzeug nutzt von uns festgelegte Regeln, um Code Dateien umzuformatieren.  

    Zweitens, nutzen wir ein Werkzeug zur statischen Code-Analyse: Clang-Tidy! Dies hilft mit der Erkennung von aus Semantik hervorgehenden stilistischen Problemen. 

    Und drittens das Code Buddy System 

------------------------------------------------------------------------------------------------------------- 

Alle Entwickelnde haben einen Code Buddy, der sich auch in dessen Thema einarbeiten muss. Diese halten wöchentliche Statusmeetings, besprechen den aktuellen Stand und geben bei Bedarf Hilfestellung. Bei jedem Push, reviewed der Buddy die Lesbarkeit des Codes, und wendet sich bei Problemen direkt an den Entwickelnden. So werden bereits während der Implementation Fehler gefunden und gelöst. Auch beim Mergen ist der Code Buddy der Hauptverantwortliche Reviewer. Jedes Feedback erfolgt nach dem Cedar-Feedback-Modell, wobei Cedar für Context, Examples, Diagnosis, Action und Review steht. 

Das ist unsere Bildquelle. Ich bedanke mich für Ihre Aufmerksamkeit. Und wir stehen nun für Fragen zur Verfügung 
