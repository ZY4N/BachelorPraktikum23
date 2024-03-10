# Parameter und Programmanpassung

## Hilfeoption
Über die Eingabe `--help` als Parameter wird eine Liste aller Parameter mit einer kurzen Beschreibung und, falls vorhanden, Default Wert des Parameters ausgegeben. Das Programm wir daraufhin beendet.

## Datenspeicherorte zum Einlesen von Rosbags, Ausgeben der Ergebnisse und Angabe des Lidar Topics 
Die Datenspeicherorte der Rosbags werden als Input Path in das Programm eingegeben. Diese werden als Positional Arguments, also ohne Flagge, übergeben.
Der Ort, an dem die verarbeiteten Daten gespeichert werden sollen, wird als Output Path eingegeben. Dieser ist nach der Flag `-o` oder `--output` anzugeben.
Der Output Path darf auf eine schon existierende Speicherstelle verweisen, sofern die dort gespeicherten Chunks die gleiche Größe ([Chunk-size](#chunksize)) haben. Sollte die Chunkgröße eine andere sein, darf der Output Path nicht auf diesen Ortner zeigen. 
Das Programm bricht mit der Fehlermeldung `"No rosbag paths provided."` wenn Input Path fehlt, und mit der Fehlermeldung `"No output path provided."` wenn der Output Path fehlt, ab.
Der Pfad zu dem Lidar Topic wird über die Flags `-t` oder `--topics` angegeben. Der Default Pfad für diesen ist `/sensors/lidar/velodyne/velodyne_points`.
<a name="Zeitabschnitte"></a>
## Zeitabschnitte innerhalb der Rosbags auswählen
Wenn innerhalb der angegebenen Rosbags nur ein bestimmter Zeitabschnitt verarbeitet werden soll, dann lässt sich der Beginnzeitpunkt aller Rosbags über die Flag `--relative-begin`und der Endzeitpunkt über `--relative-end` festlegen. 
Die Zeitpunkte lassen sich als Zeit Literale angeben, also als Wert mit den Suffix *h* für Stunde, *min* für Minute, *s* für Sekunde, *ms* für Millisekunde, *ns* für Nanosekunde und *us* für Mikrosekunde. Ein Beispiel wäre `--relative-begin 5min` für einen Startzeitpunkt bei 5 Minuten in allen angegebenen Rosbags.
Der Default Wert für den Startzeitpunkt ist der Minimale Zeit Wert von Ros `ros::TIME_MIN`.
Der Default Wert für den Endzeitpunkt ist der Maximale Zeit Wert von Ros `ros::TIME_MAX`.
<a name="chunksize"></a>
## Größe der Abschnitte, in die die Karte aufgeteilt wird
Die Karte wird in Abschnitte geteilt, dessen physische Größe bei Programmstart als sogenannte Chunk Größe festgelegt werden kann. Diese wird mit dem Flag `--chunk-size`in Metern übergeben. Der Default Wert liegt bei 30m, wodurch die Chunks eine Größe von 30x30m haben.

## Distanz von Punkten angeben
Die maximale radiale und periphere Distanz können mit den Flags `--max-radial-dist` und `--max-peripheral-dist` in Metern angegeben.
Der Defaultwert für die maximale radiale Distanz liegt bei 50 Metern und der Defaultwert für die periphere Distanz liegt bei 20 Metern.

## Verhalten bei Abweichungen
Die maximal erlaubte Abweichung von Scan Positionen wird mit der Flag `--max-scan-pos-deviation` übergeben.
Die maximal erlaubte Abweichung von Positionen zwischen Transformationen von Punkten wird mit der Flag `--max-position-deviation` übergeben.
Der Defaultwert der erlaubten Abweichung von Scan Positionen liegt bei 1 Meter, während der Defaultwert der erlaubten Abweichung von Positionen zwischen Transformationen von Punkten bei 100m liegt.

## Anpassung an das eigene System
Damit das Program möglichst effizient parallel läuft, kann man die auf einmal zu verarbeitende Blockgröße und die Anzahl der verwendeten Threads für den Rechner, auf dem das Programm läuft, spezifisch angeben.
Die Blockgröße wird als Zeitblock, also wie viel Zeit einem Zeitabschnitt, der auf einmal verarbeitet wird, ist. Dieser wird mit der Flag `--time-per-block` als Zeit Literal wie bei [Zeitabschnitte innerhalb eines Rosbags](#Zeitabschnitte) angegeben.
Der Defaultwert der Blockgröße liegt bei 10min.
Die zu verwendete Threadanzahl ist durch das Flag `--threads` anzugeben.
Der Defaultwert der Threadanzahl liegt bei 1.
Beide Parameter sollten für einen möglichst effizienten Programmablauf gesetzt werden, auch wenn das Programm auch ohne Setzung der Parameter läuft.

## Menge der Informationen, die von dem Logger ausgegeben werden
Abhängig der Nutzung des Programms ist die Menge der Informationen die der Logger ausgibt relevant und kann über feste Level angepasst werden.
Das Level des Loggers wird über die Flags `-l`und `--logger-level`übergeben, wobei die möglichen level `mute`,`error`, `warn`, `info`, `log`und `debug`sind.
Das Default Level des Loggers ist `log`.