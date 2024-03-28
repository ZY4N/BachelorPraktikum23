
## Zeitliche Aufteilung in Blöcke

Da häufig die Daten eines ganzen Rosbags nicht vollkommen in den Arbeitsspeicher passen, unterteilt der Reframer zunächst jeden Rosbag zeitlich in Blöcke, wobei jeder Block die vom Nutzer mit `--time-per-block` angegebene maximal Dauer hat.
Für Transformations- und Geschwindigkeitsdaten wird das Zeitinterval auf `--transform-padding` Minuten vor und nach dem eigentlichen Block erweitert, um die zusätzlich benötigten Daten für die Spline Interpolation in einem späteren Schritt bereitzustellen.


## Laden und Korregieren der Sensor Daten

Das Laden der Sensor Daten aus den Rosbags wird mittels der unbagger Klasse umgesetzt und ist unterteilt in das Laden von LiDAR Frames (den Punkten), den Transformationen und Geschwindigkeitsdaten.


### Laden von LiDAR Frames

Das parsen von LiDAR Daten aus einem gegebenen Rosbag Topic ist stark von dem verwendeten LiDAR Sensor abhängig und benötigt einen eigenen Parser für jeden Sensor Typen.
Zur Zeit ist ein Parser für den `/velodyne` topic definiert, es können jedoch weitere Parser hinzugefügt  (Siehe #TODO) und mit dem Parameter `--lidar-sensor-type` ausgewählt werden.
Um ein effizientes Filtern von Punkten zu ermöglichen bekommt jeder Parser ein Prädikat übergeben, welches hauptsächlich zur Filterung von Punkten auf Distanz vom LiDAR Sensor verwendet wird.
Die Ausgabe eines solchen Parsers ist eine Liste von Punkten wobei jeder Punkt neben den XYZ Koordinaten relativ zum Sensor auch mit einem 64bit Unix Timestamp mit Nanosekunden Genauigkeit verbunden sein muss.


### Laden von Transformationen

Die Transformationen aus dem `/tf` Topic werden direkt beim Laden in `unbagger::extract_transforms`  relativ zu dem `luisenplatz`  Marker in `/tf_static` transformiert.
Die bereitgestellten Daten im `/tf` Topic beinhalten Fehler in Form von einigen Transformationen, die von der Position der Bahn zum Teils Kilometer weit entfernten langen Ludwig springen.
Dieses Problem wurde vorübergehend behoben, indem Transformationen, die in einem geringen Radius (1m) um den Marker liegen, entfernt werden.
Aus offensichtlichen Gründen ist das keine gute Langzeitlösung und sollte nachdem die Probleme mit dem Topic gelöst wurden, entfernt werden.


### Laden von Geschwindigkeiten

Das Laden der Geschwindigkeiten extrahiert Daten aus dem `/odom` Topic mittels der `unbagger::extract_velocities` Funktion.
Hierbei wird lediglich die Norm der "linearen" Geschwindigkeit gemeinsam mit dem Zeitstempel der Aufnahme gespeichert.

Jedoch müssen auch hier die Daten aus dem Topic zunächst gefiltert werden, da im Durchschnitt über 90% der angegebenen Geschwindigkeiten Duplikate sind.
Das heißt anstelle von einer langsam steigenden Geschwindigkeit bleibt die Geschwindigkeit (und Richtung) gleich bis sie sich von einer auf die andere Odometer Nachricht abrupt ändert.
Hier wieder der Appell: die Fehler in der Datenpipeline fixen und diesen Filter entfernen. 


## Reframing

Das Reframing findet  im Namespace `drm::reframer` statt und besteht aus zwei Schritten:
1. Dem Interpolieren der Sensor Transformationen und LiDAR Punkte im World Space relativ zum Marker (Luisenplatz).
2. Dem Packen von Punkten in neue Frames, wobei alle Sensor Positionen, von denen die Punkte aufgenommen wurden, nur um  maximal `--max-scan-pos-deviation` Meter von einander abweichen.


### Schritt 1: Interpolation
Um eine Entfernungsmessung des LiDAR Sensors zu einem Punkt im World Space transformieren zu können, muss die exakte Position der Bahn zum Zeitpunkt der Aufnahme ermittelt werden.
Während jedoch der Velodyne Sensor durchschnittlich jede Mikrosekunde eine Entfernungsmessung aufnimmt, erreichen den Reframer Transformations informationen nur alle hundert Millisekunden und Geschwindigkeitsmessungen sogar nur alle zwei Sekunden.
Folglich ist Interpolation von Nöten, um die Position der Bahn zwischen den Messungen approximieren zu können.
(Der Reframer nutzt 64bit floating Point Values intern)

Die folgende Grafik zeigt eine vereinfachte Ansicht der vom Reframer eingesetzten Spline Interpolation aus der Vogelperspektive.

![[spline_interpolation_notated.png]]

Für diese betrachtet der Reframer nach einander alle Entfernungsmessungen (Aufnahmepunkte in blau), die zwischen zwei aufeinanderfolgenden Transformationen (im Bild `T1` und `T2`) von denen aus Entfernungsmessungen aufgenommen.
Für eine bessere Approximation von Kurven nutzt der Reframer neben `T1` und `T2` auch die vorherige Transformation `C1` und folgende `C2`, um einen zentripetalen Catmull–Rom Spline aufzubauen.
Dieser Spline-Typ bietet den Vorteil, dass eine Änderung des Interpolationsparameters `dt` an jeder Stelle des Splines eine gleichbleibende Distanzänderung `dxy` bewirkt, was das Abtasten erleichtert.

Doch zunächst muss die sich ändernde Geschwindigkeit mit einbezogen werden, da diese einen Einfluss auf die Abstände zwischen den Messpunkten hat.

Diese vereinfachte Grafik zeigt diesen Einfluss qualitativ. 
![[velocity_correciton.png]]
Besonders gut zu erkennen ist die geringe Geschwindigkeit in der Mitte der Strecke, da dort die Messpunkte sehr nahe beieinander liegen.

Um diese Abstände korrekt zu berechnen wird erneut ein Catmull–Rom Spline durch die Geschwindigkeitsmessungen gelegt und die Geschwindigkeiten zum Zeitpunkt jeder Entfernungsmessungen abgetastet.
Diese Geschwindigkeitswerte werden mit der Trapezregel integriert, um für jeden Messpunkt eine Entfernung entlang des Splines zu `T1` zu erhalten.
Da diese integrierten Werte keine verlässlichen Distanzen darstellen, wird eine letzte Messung zwischen dem letzten Messpunkt und `T2` durchgeführt, um die Distanzen auf Werte `t1, ..., tn` zwischen `0` und `1` zu normalisieren.
Diese Werte können dann wegen der vorher erwähnte Linearität des Transformationssplines als Interpolationsparameter mit genau diesem Spline verwendet werden.
Die Rotationen der Transformationen sind als Quaternions dargestellt und werden deshalb mit linearer spherischer Interpolation mit den gleichen Interpolationsparametern `t1, ..., tn` interpoliert.
Bei der Interpolation müssen schließlich noch folgende Sonderfälle beachtet werden:
Wenn die Bahn steht, gilt `T1_ij ​− T2_ij​∣ ≤ ϵ` und alle Messpunkte werden mit `T1` transformiert.
Wenn die absolute integrierte Distanz kleiner als `ϵ` ist, wird linear zwischen den `T1` und `T2` interpoliert.

Nun wird jede Entfernungsmessung mit der interpolierten Bahn Transformation sowie der Sensor Transformation zu einem Punkt im World Space transformiert.


### Schritt 2: Reframing
Weil die interpolierten Sensor Position sehr wichtig für die Entfernung dynamischer Objekte sind, müssen diese mit der Punktwolke exportiert werden.
Da jedoch, wie zuvor erklärt, jeder Punkt zu einem anderen Zeitpunkt und dementsprechend auch (normalerweise) von einer andere Position aufgenommen wurde, wäre das Speichern jeder einzelnen Aufnahmeposition bei Punktwolken im Milliardenbereich ungeeignet.

In dieser Grafik sind aufeinanderfolgende Punkte mit der selben Aufnahmeposition gleich gefärbt.
![[before_reframing.png]]

Um die Anzahl der exportierten Aufnahmeposition zu verringern vereint der Reframer die Aufnahmeposition aufeinanderfolgender Punkte in so genannte Frames.
Hierbei werden aufeinanderfolgende Punkte in einen Frame aufgenommen, wenn deren Aufnahmeposition um weniger als  `--max-scan-pos-deviation` Meter von der durchschnittlichen Aufnahmeposition des Frames divergieren.

Hier eine qualitative Visualisierung der Punkte und ihrer Aufnahmeposition nach dem Reframing Schritt. 
![[after_reframing.png]]


## Chunking
Zuletzt müssen die Punkte der generierten Frames auf Zellen aufgeteilt werden, um spätere Verarbeitung zu erleichtern.
Zellen stehen hierbei für quadratische achsenausgerichtete Flächen mit Seitenlängen von `--chunk-size` Metern, die sich rund um das Zentrum des Koordinatensystems im langen Ludwig ausbreiten.

Hier eine qualitative Visualisierung:
![[after_chunking.png]]

Für diesen Vorgang sortiert der Reframer die Punkte eines Frames in eine feste Anzahl an Chunk Buckets.
Falls die vom Frame abgedeckten Punkte diese Anzahl übertreffen, wird eine Flagge gesetzt und die Punkte des Buckets in einem weiteren Schritt sortiert.
Danach werden die Punkte jedes Chunk Bucket in eine separate Frame Datei im Chunk Ordner geschrieben und Pose Dateien jedes Chunks um einen Eintrag zur Aufnahmeposition des Frames erweitert. 


## Multithreading Modell

Damit das Laden und Verarbeiten eines Blocks die Hardware möglichst voll ausnutzt, setzt der Reframer auf ein umfangreiches Multithreading Modell:
![[Multithreading.png]]

Jeder Datentyp bekommt einen Anteil der insgesamt verfügbaren Threads zugeteilt.
Jedes Block Interval wird für jeden Daten Typen nach der Anzahl der Threads aufgeteilt und die Buffer für Transformationen und Geschwindigkeiten nach dem Laden kombiniert.
Da das Kombinieren der Punktdaten viel zusätzlichen Speicher benötigen würde und dieser minimal gehalten werden soll, werden die separat geladenen Teile des Blocks auch separat von verschiedenen Threads verarbeitet. Hierbei bestimmt ein Multiplier wie viele Threads eines dieser Teilsegmente des Blocks verarbeiten.
Nachdem die Daten des Blocks verarbeitet wurde werden die entstandenen Metadaten von mehreren Threads auf die Fesplatte geschrieben.
Wie auf der Grafik zu erkennen, beginnt das Laden der Daten des nächsten Blocks bereits, während der vorherige noch in Bearbeitung ist. Dies sorgt für zusätzlichen Arbeitsspeicher Verbrauch, da nun zwei Buffer verwendetet werden müssen (einen zum Laden, einen zum Verarbeiten).
Doch selbst nach dem Verringern der Blockgröße (damit zwei Buffer in den Arbeitsspeicher passen) hat dieses System in unseren Tests den Durchsatz verdoppelt.
