# Design Meetings Protokolle Iteration 2:
---

## User Story(s): 0 - Einlese-Option für Rosbag-Dateien
#### Funktionalitäten
Es sollen folgende Daten aus Rosbags der Bahn extrahiert werden: Punktdaten, Transformationen, Geschwindigkeiten und IMU-Daten.
#### Schnittstellen
Hierfür soll eine Unbagger-Klasse implementiert werden.
Die Klasse soll eine Funktion zum öffnen der Rosbags haben.
In der Klasse soll pro gewünschte Topic eine Funktion zur extrahierung der Daten aus einem geöffneten Rosbag implementiert werden.
Die Extraktionsfunktion für Transformationen soll Invalide Transformationen heraus filtern.
Außerdem sollen Structs in denen die Daten der Topics mit ihrem Aufnahme Zeitpunkt gespeichert sind implementiert werden.
#### Erweiterbarkeit
Es soll möglich sein einfach weiter Topics zu extrahieren.
Das Einlesen wird für jede Topic in einer eigenen Funktion implementiert, daher können weitere  Extraktionsfunktionen konfliktlos hinzugefügt werden.
#### Wie wird Leistung und Ressourcenverwendung ins Design einbezogen?
- Die Implementation soll das Filtern in-place ausführen, um die Speicherauslastung minimal zu halten.
- Die Laufzeit des Filterns muss in O(N) in Anhängigkeit von der Anzahl der Punkte, Transformationen und Geschwindigkeiten umgesetzt werden.
- Die Implementation an sich muss nicht auf mehreren Threads laufen, sollte aber ein einfaches Interface bieten um Multithreading (falls nötig) noch hinzuzufügen. Dafür sollen alle Extraktionsfunktionen ein Zeitinterval entgegennehmen, um das gesamte Zeitintervall des Rosbags zwischen Threads aufteilen zu können.
- Alle Structs, in die die Punkte, Transformationen und Geschwindigkeiten gelesen werden, sollen kein Alignment-Padding enthalten und die Cache Line Größe von 64B restlos teilen.
#### Sonstiges:
Für interaktion mit den Rosbags soll das ROS-Framework genutzt werden.

---

## User Story(s): 1 - Distanzfilterung von Punktdaten
#### Funktionalitäten
Die Punkte der Punktwolke sollen anhand ihrer Distanz zur Bahn gefilter werden.
#### Schnittstellen
Die Extraktionsfunktionen für die Punktwolke wird als Template implementiert und ihr wird ein Prädikat für die Distanzfilterung übergeben womit die Punkte gefiltert werden.
#### Erweiterbarkeit
Es soll möglich sein die Art wie die Punkte gefiltert werden zu ändern.
Dies wird umgesetzt indem das Filtern über ein veränderbares Prädikat implementiert ist.
#### Wie wird Leistung und Ressourcenverwendung ins Design einbezogen?
- Die Funktion soll vom Compiler geinlinet werden können, um den Overhead eines Function-Calls vermeiden zu können.
- Die Funktion soll die Anzahl an Wurzelberechnungen möglichst geringhalten.

---

## User Story(s): 2 - Geschwindigkeits-Entzerrung
#### Funktionalitäten
Die Punkte in der Punktwolke sollen anhand den Geschwindigkeiten bei der Aufnahme neu ausgerichtet werden.
#### Schnittstellen
Dafür wird eine Funktion implementiert die mit den Aufnahmegeschwindigkeiten errechnet wie die Punkte verzerrt sind und dann entzerrt.
#### Erweiterbarkeit
Hier stehen die QS-Ziele Erweiterbarkeit und Effizienz im Konflikt.
Nach Absprache mit dem AG sind hier keine Erweiterungen vorgesehen und es werden entsprechend keine Designs festgelegt.
#### Wie wird Leistung und Ressourcenverwendung ins Design einbezogen?
- Der Algorithmus soll die zu verarbeitenden Punkte in gleichgroßen Intervallen unter allen zur Verfügung stehenden Threads aufteilen.
- Um die Speicherauslastung so gering wie möglich zu halten, sollen alle Punkt Transformationen In-Place vorgenommen werden.
- Die Suche von Punkten nach Zeitstempeln soll in  O(log2(N)) in Abhängigkeit von der Anzahl der verarbeiteten Punkte umgesetzt werden.
- Es soll sequentiell auf die Arrays mit Punkt-, Transformations- und Geschwindigkeitsdaten zugegriffen werden, um Cache-Misses zu minimieren.

---

## User Story(s): 3 - Integration von dynamischem Logging-System
#### Funktionalitäten
Es soll möglich sein über eine benutzerfreundliche API-Lognachrichten zuschreiben.
Über diese soll auf verschiedenen Log-Leveln ("mute", "error", "warn", "info", "log" und "debug") Nachrichten mit eingebetteten Werten geschreiben werden können.
Die Ausgabe soll auf die eigene Wünsche über Flagen anpassbar sein.
#### Schnittstellen
Es wird ein System  implementiert das eine API bereitstellt. Diese hat pro Log-Level eine Schreibfunktion.
Über diese kann eine Nachricht mit eingebetten Werten auf dem jeweiligen Log Level geschrieben werden.
#### Erweiterbarkeit
Es soll möglich sein das System um weitere Log-Level zu erweitern und die Formatierung weiter Datentypen zu definieren.
Die Log-Level werden über Structs definiert und es können weiter hinzugefügt werden. Die Formatierung von Datentypen wird über Templates gemacht, welche auch erweitert und angepasst werden können.
#### Wie wird Leistung und Ressourcenverwendung ins Design einbezogen?
- Der Logging-System, soll Spinlocks für die Synchronisation zwischen Threads nutzen, um die Latenz des Function-Calls möglichst gering zu halten.
- Das Formatieren verschiedener Typen soll mittels Templates umgesetzt werden. um den Overhead von (virtuellen) Function-Calls zu vermeiden.
- Um Overhead beim Ändern des Log-Levels sowie des Aktivieren/Deaktivieren verschiedener Flaggen zu Vermeiden, sollen diese Operationen jeweils durch das Setzen eines Integer-Werts umgesetzt werden.

---

## User Story(s): 4 - Integration von 3DTK People Remover in Scan Combiner
#### Funktionalitäten
Die verarbeiten Punkte sollen mit ihren Aufnahmeposition als Karte im UOS-Format ausgegeben werden.
#### Schnittstellen
Hierfür wird eine "Frame Exporter" Schnittstelle implementiert, in der Module zur Ausgabe der Karte hinterlget werden können. Diese können dann über eine Schreibefunktion ausgewählt und ausgeführt werden.
Es wird außerdem ein UOS-Modul für diese Schnittstelle erstellt, die die Karte im UOS-Format ausgibt.
#### Erweiterbarkeit
Es soll möglich sein weiter Ausgabeformate hinzuzufügen.
Dies wird über die "Frame Exporter" Schnittstelle und den Ausgabemodulen umgesetzt.
#### Wie wird Leistung und Ressourcenverwendung ins Design einbezogen?
- Die Schreibfunktion des Moduls und der Schnittstelle sollen Daten über eine `tcb::span` (C++ 17 Implementation von `std::span`) erhalten, um unnötiges Kopieren von Daten zu vermeiden.
- Das UOS-Format benutzt ASCII-Textdateien, um effizienter zu speichern, sollen die Daten als `std::hexfloat` geschrieben werden.

---
 
## User Story(s): 5 - Entfernung dynamischer Objekte mittels 3DTK People Remover
#### Funktionalitäten
N/A
#### Sonstiges
Hier wird kein Code geschrieben und daher ist kein Design notwendig.