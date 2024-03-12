# Overview

Das Ziel des Dynamic Railmap Projekts ist es, automatisiert eine 3D-Karte aus den InnoTram-Sensordaten mehrerer Fahrten zu erstellen. Die Basis bilden dabei die Lidar-Daten. Im Zuge dieser Kartierung sollen alle dynamischen und semi-dynamischen Objekte entfernt werden. Außerdem soll die Karte für eine effiziente Handhabung in Chunks (Raster) aufgeteilt sein.

Das Projekt lässt sich in drei Pipelinestufen unterteilen:

1. **Reframer**: 
In der ersten Stufe werden die Lidar-Daten mehrerer Fahrten präzise ausgerichtet und anhand zusätzlicher Sensordaten in Chunks unterteilt, was die Grundlage für die Daten bildet.

2. **Dynamic Object Removal (wip)**: Im nächsten Schritt müssen alle dynamischen Objekte entfernt werden. Als dynamisches Objekt zählt alles, was sich während der Aufnahme bewegt, zum Beispiel fahrende Autos oder Fußgänger, die über den Luisenplatz laufen.

3. **Semi-Dynamic Object Removal (wip)**:
Bei dieser Stufe sollen auch alle semi-dynamischen Objekte entfernt werden. Dabei handelt es sich um Objekte, die in den Aufnahmen oft an denselben Stellen stehen, aber nicht verlässlicher Bestandteil der statischen Umgebung sind. Beispiele dafür sind Autos, die an roten Ampeln halten, Personen, die an Haltestellen warten oder auch die Stände des Weihnachtsmarkts.

**ACHTUNG**: Dynamic Object Removal und Semi-Dynamic Object Removal sind nicht funktionsfähig.