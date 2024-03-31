
>  **Datum:** 22.1.2024
>  **Durchgeführt von:** Leonhard Steinecke

### Komponenten im Fokus
- Export zu segmentierten Karten Format (neu hinzugefügt)

### Befehle

```bash
# server settings
./drm_input_node_server $ROSBAGS -o /tmp/map_data --max-radial-dist 30 --max-peripheral-dist 20 --time-per-block 1h

# desktop settings
./drm_input_node_desktop $ROSBAGS -o /tmp/map_data --max-radial-dist 30 --max-peripheral-dist 20 --time-per-block 5min
```

### Messwerte

Relevante GNU Time Ergebnisse mit Server Einstellungen:
```go
Elapsed (wall clock) time (m:ss):   8:34.36
Maximum resident set size (kbytes): 18871688
Percent of CPU this job got:        276% / 4800%
```

Relevante GNU Time Ergebnisse mit Desktop Einstellungen:
```go
Elapsed (wall clock) time (m:ss):   9:12.24
Maximum resident set size (kbytes): 3043060
Percent of CPU this job got:        184% / 1200%
```

Server Cycle-Distribution:
![[it5_cycles_server.png]]

Desktop Cycle-Distribution:
![[it5_cycles_desktop.png]]

### Checkliste
- Server Limits
	- [x] Werden die Daten innerhalb der maximalen Laufzeit verarbeitet?
		Ja, da `8,57 min` < `133,758 min`.
	- [x] Bleibt die Speicherauslastung unter dem festgelegten Limit?
		Ja, da `17,59 GiB` < `50 GiB`.
- Desktop Limits
	- [x] Werden die Daten innerhalb der maximalen Laufzeit verarbeitet?
		Ja, da `9,20 min` < `267,516 min`.
	- [x] Bleibt die Speicherauslastung unter dem festgelegten Limit?
		Ja, da `2,83 GiB` < `10 GiB`.
- Cycle-Analyse
	- [x] Welche Codeabschnitte beanspruchen die meiste Zeit während des Durchlaufs?
	- **WICHTIG:**
		- Das Synchronisieren des Schreibens der Punkte in Zellen wird über eine komplexes, auf mehreren Kernen laufendes System umgesetzt.
		  Der Code dieses Systems verbindet mehrere Komponenten und wird so nicht als einzelner Hotspot in `perf record` festgehalten.
		  Dennoch kann über das Vergleichen der Laufzeiten mit der letzten Iteration ein maximaler Anteil von ca. 40% abgeschätzt werden.
	- ~36% Geschwindigkeitsentzerrung (Interpolations, Matrix und Quaternion Operationen)
		- `__ieee754_acos_sse2`, `do_sin`, `__sin_avx`,  `eval_catmull_rom_spline`, `advance_and_sample_...`, `slerp`, `approximate_step_sizes`
	- ~8.63% Export zu KITTI-Format
		- `std::basic_*`, `std::ostream*`
	- ~6,44% Aufteilen der Punkte in Zellen (im Fokus, weil neu hinzugefügt)
		- `std::introsort_loop`, `drm::lord_tachunker::process_points`
	- ~6,08% Rosbag Dekompression
		-  `LZ4_decompress_safe`, `ROSLZ4_XXH32_update`
	- ~3,64% Verringerung von Aufnahmetransformationen
		-  `reframe_to_closest_scan_position`
	- [x] Werden in den Hotspot-Codeabschnitten essenzielle Operationen ausgeführt, oder stellen sie vermeidbare Engpässe dar?
	- Die Einschätzung der Performanzanalyse letzter Iteration bezüglich "Export zu KITTI-Format", "Geschwindigkeitsentzerrung", "Verringerung von Aufnahmetransformationen" und "Rosbag Dekompression" bleibt gleich.
	- Die Laufzeit des Aufteilen der Punkte in Zellen scheint im Kontext der anderen Komponenten angemessen. Jedoch ist der Laufzeitanteil, der in `std::sort` verbracht wird, mit ca. 67% relativ hoch, für eine Operation, die nur angewendet werden sollte, falls nicht genügend Buckets zur Verfügung stehen. => angemessen, hat jedoch noch Raum für Optimierung
	- Die Zeit, die mit der Synchronisation des Schreibens der Punkte in Zellen verbracht wird, scheint hoch.
	  Leider bieten die Messdaten keine einfachen Anhaltspunkte, um zu ermitteln, ob konkrete Anteile des Systems Probleme darstellen, oder ob das System seine Aufgabe effizient umsetzt.
	  Weitere Tests könnten diese Fragen beantworten, da jedoch das System immer noch weit unter allen Laufzeit und Speicherauslastungslimits liegt, scheint die Zeit an anderen Stellen besser investiert.
	- [x] Welche Teile des System sollten angepasst werden, um die Laufzeit oder Speicherauslastung zu reduzieren?
	- Da das System noch deutlich unter der maximalen Speicherauslastung operiert, wäre es möglich die Anzahl der Buckets für das Sortieren in Chunks zu erhöhen, um die `std::sort` Aufrufe zu verringern.
	- Wie die Synchronisation des Schreibens der Punkte in Zellen verbessert werden kann, ist nicht trivial und würde weitere Tests erfordern.
	- [x] Welche Dringlichkeit wird diesen Anpassungen zugewiesen?
	- Das Erhöhen der genutzten Buckets stellt nur einen geringen Arbeitsaufwand dar und kann in der nächsten Iteration umgesetzt werden.
	- Das Verbessern der Synchronisation des Schreibens der Punkte in Zellen, kann mit unserem Arbeitgeber abgesprochen werden.
	  Da aber alle Limits eingehalten werden und die Parallelisierungs-US potentiell einen höheren Einfluss auf die Laufzeit haben kann, ist eine Priorisierung dieser Verbesserung unwahrscheinlich.

### Konsequenzen
- Severin Pelikan wurde mit der Vergrößerung der Bucket Anzahl beauftragt.
- Das Verbessern der Synchronisation des Schreibens der Punkte in Zellen wurde als Agendapunkt für das Meeting am 22.1.2024 aufgenommen.
