## User Story(s):  23 - PCD Converter
#### Funktionalitäten
Die ausgegebene Karte soll von dem KITTI-Format in das PCD-Format überführt werden.
#### Schnittstellen
Dies wird mit einem eigenem Konverter umgesetzt.
Über CLI-Parameter müssen für den Konverter die Eingabedateien und der Ausgabeort festgelegt werden. Die Ausgwählten Daten werden dann von dem KITTI-Format zu einem PCD-Format mit der Library „PCL“ konvertiert und dann ausgeben.
#### Erweiterbarkeit
Es ist die Erweiterung um andere PCD-Varianten vorgesehen. Da für das Schreiben die Library „PCL“ genutzt wird die diese Optionen bietet, wird dies umgesetzt.
#### Wie wird Leistung und Ressourcenverwendung ins Design einbezogen?
- Die Implementation soll `std::vector::clear` verwenden, damit die Capacity des "Frame Punktwolken" Vektors behalten wird um möglichst wenige Heap-Allocations zu benutzen.

## User Story(s): 24 - Programm parallelisieren
#### Funktionalitäten
Das Programm soll Multithreading unterstützen.
#### Schnittstellen
Hier für wird ein Anzahl an maximal erlaubten Threads angegeben. Das Programm verteilt die Threads auf Funktionalitäten und nutzt diese bestmöglich aus.
#### Erweiterbarkeit
Da bisher schon auf die Möglichkeit von Multithreading geachtet wurde ist dies gut Umzusetzten.
#### Wie wird Leistung und Ressourcenverwendung ins Design einbezogen?
- Die Implementation soll mehrere Threads verwenden um gleichzeitig Daten Laden und verarbeiten zu können.
- Die Anzahl der Threads, die für das Laden verschiedener Rosbag-Topics verwendet werden, müssen für beliebige Thread-Limits angemessen zugeteilt werden. 
- Die Implementation soll Double Buffer verwenden, um Daten effizient zwischen Extraktions- und Verabreitungsthreads asuzutauschen.
- Zur Synchronisation sollen Mutexes verwendet werden, um Busy-Waiting zu verhindern und die Hardware wenn möglich zu entlasten.
- Die geladenen von verschiedenen Threads geladenen Punkte müssen In-Place verarbeitet werden, da das Kombinieren der Arrays für eine zu hohe Speicherauslastung führen würde.


## User Story(s): 25 - Unterstützung weiterer LiDAR-Sensoren
#### Funktionalitäten
Es sollen weitere LiDAR-Sensoren einfach unterstützt werden können.
#### Schnittstellen
Es wird eine Schnittstelle implementiert über die Unterstützung für neue LiDAR-Sensoren als Modul hinzugefügt werden können.
Diese Module können dann über eine Parsefunktion ausgewählt und ausgeführt werden.
#### Erweiterbarkeit
Auf Erweiterbarkeit wird über Nutzung und Erstellung eben dieser Schnittstelle geachtet.
#### Wie wird Leistung und Ressourcenverwendung ins Design einbezogen?
- Die Implementation der Parsefunktion der Schnittstelle soll mittels Templates umgesetzt werden. um den Overhead von (virtuellen) Function-Calls zu vermeiden.

## User Story(s):  26 - Erweiterung der Metadaten um Sensortypen und Rosbag-Topic
#### Funktionalitäten
Die gesammelten Metadaten sollen um Begin- und Endzeiten der Rosbags und den Zeitstempel der Scans erweitert werden.
#### Schnittstellen
Es werden weitere Einträge in dem Struct der gesammelten Metadaten hinzugefügt und das JSON-Modul wird entsprechend angepasst.
#### Erweiterbarkeit
Durch den Fokus auf Erweiterbarkeit in US-17 und US-18 können diese Erweiterungen effektiv umgesetzt werden.
#### Wie wird Leistung und Ressourcenverwendung ins Design einbezogen?
- Da diese kleine Erweiterung der Metadaten keinen messbaren Einfluss auf Leistung haben wird, braucht nicht besonders auf Effizienz geachtet werden.

## User Story(s): 27 - Erstellung von Testdatensätzen
#### Was wird implementiert?
N/A
#### Sonstiges
Hier wird kein Code geschrieben und daher ist kein Design notwendig.

## User Story(s): 28,29,30 - Erweiterung der CLI-Parameter 
#### Funktionalitäten
Einige bisher im Code festgelegten Werte(LiDAR Topic, LiDAR Sensortyp und Threadanzahl) sollen dynamisch über CLI Parameter festgelegt werden.
Außerdem soll ein Helpbefehl hinzugefügt werden der Informationen über die CLI-Parameter bereitstellt.
#### Schnittstellen
Die neuen CLI Parameter werden mit dem "Arx-System" aus US-7 implementiert.
Über “--lidar-topic” kann das Topic für den Punkdaten angepasst werden.
Über “--lidar-sensor-type" kann der Sensor, von dem die Punktdaten aufgenommen werden, angepasst werden.
Über “--threads” kann die Anzahl der Threads angepasst werden
Mit “--help” werden die Beschreibungen der Parameter sowie deren voreingestellte Werte in der Konsole ausgegeben. 
#### Erweiterbarkeit
Durch den in US 7 implementierten Argumentparser können diese Erweiterungen effektiv umgesettz werden.
#### Wie wird Leistung und Ressourcenverwendung ins Design einbezogen?
- Da das "Arx-System" nur einmal zu Programmbeginn ausgeführt wird hat es eine vernachlässigbare Auswirkung auf Leistung, daher braucht nicht besonders auf Leistung geachtet werden.
#### Sonstiges
Bei der Ausführung mit "--help" soll die Pipeline nicht gestartet werden.