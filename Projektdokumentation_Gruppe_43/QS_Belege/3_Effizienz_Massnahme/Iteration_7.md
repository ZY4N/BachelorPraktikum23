
>  **Datum:** 21.2.2024
>  **Durchgeführt von:** Leonhard Steinecke

### Komponenten im Fokus
- Programm Parallelisierung (neu hinzugefügt)
- Erhöhen der Bucket Anzahl für die Sortierung von Punkten in Zellen (verändert)
### Befehle

```bash
# server settings
./scan_combiner $ROSBAGS -o /tmp/map_data --max-radial-dist 30 --max-peripheral-dist 20 --time-per-block 1h --max-scan-pos-deviation 1 --chunk-size 30 --threads 48

# desktop settings
./scan_combiner $ROSBAGS -o /tmp/map_data --max-radial-dist 30 --max-peripheral-dist 20 --time-per-block 5min --max-scan-pos-deviation 1 --chunk-size 30 --threads 12
```

### Messwerte

Relevante GNU Time Ergebnisse mit Server Einstellungen:
```go
Elapsed (wall clock) time (m:ss):   2:12.75
Maximum resident set size (kbytes): 28439196
Percent of CPU this job got:        3239% / 4800%
```

Relevante GNU Time Ergebnisse mit Desktop Einstellungen:
```go
Elapsed (wall clock) time (m:ss):   2:17.90
Maximum resident set size (kbytes): 6581048
Percent of CPU this job got:        1178% / 1200%
```

Server Cycle-Distribution:
![[it7_cycles_server.png]]

Desktop Cycle-Distribution:
![[it7_cycles_desktop.png]]

### Checkliste
- Server Limits
	- [x] Werden die Daten innerhalb der maximalen Laufzeit verarbeitet?
		Ja, da `2,21 min` < `133,758 min`.
	- [x] Bleibt die Speicherauslastung unter dem festgelegten Limit?
		Ja, da `26,49 GiB` < `50 GiB`.
- Desktop Limits
	- [x] Werden die Daten innerhalb der maximalen Laufzeit verarbeitet?
		Ja, da `2.30 min` < `267,516 min`.
	- [x] Bleibt die Speicherauslastung unter dem festgelegten Limit?
		Ja, da `6,13 GiB` < `10 GiB`.
- Performanz Analyse
	- [x] Welche Codeabschnitte beanspruchen die meiste Zeit während des Durchlaufs?
		- Server spezifisch:
			Bei den Messungen fällt besonders auf, dass die Laufzeit der Server-Konfiguration nur minimal kürzer ist, als die der Desktop-Konfiguration.
			Dies ist besonders alarmierend, da der Server trotzdem mit annähernd voller Auslastung lief.
			Eine genauere Analyse der Cycle-Distribution zeigt, dass der Server-Durchlauf eine hohen Anteil der Laufzeit (57,7%) im Kernel-Space verbringt.
			Im "Flame-Graph" Tab lässt sich erkennen, dass diese System Calls bei der Synchronisation mittels `std::mutex` entstehen.
			  
			Server Graph:
			![[it7_graph_server.png]]
		
			Diese langen System Calls sind jedoch nicht bei dem Durchlauf der Desktop-Konfiguration zu sehen:
		
			Desktop Graph:
			![[it7_graph_desktop.png]]
		- Desktop spezifisch (representativ für Anteil von Server ohne Mutex Hotspot):
			- ~36% Geschwindigkeitsentzerrung (Interpolations, Matrix und Quaternion Operationen)
				- `__ieee754_acos_sse2`, `log_inline`, `exp_inline`, `do_sin`, `_mm_set1_pd`, `__sin_avx`, `eval_catmull_rom_spline`, `_mm_mul_pd`, `toRotationMatrix`, `approximate_step_sizes`, `slerp`, `quaterniaon`, `advance_and_sample_velocity`
			- ~15,5% Rosbag Dekompression
				-  `LZ4_decompress_safe`, `ROSLZ4_XXH32_update`
			- ~6.83% Export zu KITTI-Format
				- `std::basic_*`, `std::ostream*`
			- ~ 1,67% Aufteilen der Punkte in Zellen (im Fokus, weil angepasst)
				- `drm::chunker::calc_chunk_position`
	- [x] Werden in den Hotspot-Codeabschnitten essenzielle Operationen ausgeführt, oder stellen sie vermeidbare Engpässe dar?
		- Server Mutex Hotspot
			- Hypothese 1
				Beim Laden der Daten aus den Rosbags stößt der Server auf das Limit der Lesegeschwindigkeit der SATA SSD.
				Da das Verarbeiten der Daten aber gut auf den vielen Kernen skaliert, können nun die Lade-Threads nicht mehr schnell genug Daten für die Verarbeitungs-Threads bereitstellen.
				Folglich verbringen die  Verarbeitungs-Threads einen signifikanten Anteil der Zeit mit dem Warten auf die Freigabe des Synchronisations-Mutex.
			- Hypothese 2
				Das bereits in Iteration 5 als potentiell problematisch identifizierte System zur Synchronisation des Schreibens der Punkte in Zellen, skaliert nicht gut auf mehrere Threads.
				Da die Laufzeit der anderen Komponenten sich so dramatisch verringert hat, fällt dieser Aspekt nun besonders auf.
		- Die Laufzeit der Geschwindigkeitsentzerrung nimmt nun einen Großteil der Laufzeit ein. Der Zeitaufwand scheint dennoch adäquat,
		  da die vorzunehmenden Berechnungen in diesem Teil von Grund auf teuer sind. => angemessen
		-  Das Erhöhen der Bucket Anzahl scheint die Aufrufe zu `std::sort` so weit reduziert zu haben, dass diese nicht mehr in den größten Hotspots auftaucht. => angemessen
	- [x] Welche Teile des System sollten angepasst werden, um die Laufzeit oder Speicherauslastung zu reduzieren?
		- Die Mutex Hotspots müssen weiter überprüft werden, um zwischen Hypothese 1 und 2 entscheiden können. Falls Hypothese....
			- ... 1 sich bewahrheitet, sollte das statische Aufteilen der Aufgaben unter den Threads durch ein dynamisches ersetzt werden.
			- ... 2 sich bewahrheitet, sollte ein neues Multithreading Model für das Schreiben der Chunk Punkte ausgearbeitet werdern.
		- Durch Veränderungen am Algorithmus, könnten die Laufzeiten der Geschwindigkeitsentzerrung wahrscheinlich weiter reduziert werden.
		  Dies scheint jedoch im Kontext der Anforderungen an dieses Projekt nicht weiter relevant.
	- [x] Welche Dringlichkeit wird diesen Anpassungen zugewiesen?
		- Die Mutex Hotspots sollten so bald wie möglich überprüft werden, um die Quelle des Problems zu identifizieren.
		  Veränderungen am Programm sind jedoch unwahrscheinlich, da die Behebung beider möglichen Fälle mit einem signifikanten Implementationsaufwand verbunden sind,
		  und kaum noch Zeit im Bachelorpraktikum bleibt. Diese Thematik sollte im nächsten Meeting mit dem AG abgeklärt werden.
		- Die Dringlichkeit für weitere Optimierungen der Geschwindigkeitsentzerrung scheinen im Kontext vorerst nicht dringlich.

### Konsequenzen

Die unerwarteten Leistungsmerkmale haben zu einem Notfall-Meeting geführt, an dem alle Teammitglieder teilnahmen, um die Quelle des Problems zu finden.
In dem Meeting wurden die aufgestellten Hypothesen mit weiteren Durchläufen und Messungen überprüft und Hypothese 1 als am wahrscheinlichsten identifiziert.
Wie in folgendem Screenshot zu erkennen, wartet der Hauptverarbeitungsthread nach der Zeile `Handing off next buffer to extraction threads...` 15 Sekunden lang darauf,
dass diese den vorherigen Block verarbeitet haben. Auf der rechten Seite ist im System Monitor zu erkennen, wie in der gleichen Phase die Systemauslastung beträchtlich sinkt.   

![[system_load.png]]

Beim Lesen der Logs der Desktop Konfiguration wurde zusätzlich ein Programmierfehler in einer ungetesteten Funktion gefunden.
Der Fehler (ein `<=` anstelle eines `>=`) bewirkte, dass regelmäßig mehr Daten geladen wurden, als nötig zur Verarbeitung:

![[padding_error.png]]

Der Fehler wurde behoben, die fehlenden Tests ergänzt und die Performanz-Tests wiederholt.

### Nach der Korrektur des Fehlers:

### Messwerte

Zusammengeführte Ergebnisse mit Server Einstellungen:
```go
Elapsed (wall clock) time (m:ss):   2:04.57
Maximum resident set size (kbytes): 28730168
Percent of CPU this job got:        3488% / 4800%
instructions per cycle:             0,56
branch-misses:                      0,95% of all branches
L1-dcache-load-misses:              3,06% of all L1-dcache accesses
LLC-load-misses:                    33,41% of all LL-cache accesses
```

Zusammengeführte Ergebnisse mit Desktop Einstellungen:
```go
Elapsed (wall clock) time (m:ss):   1:54.60
Maximum resident set size (kbytes): 6516476
Percent of CPU this job got:        1195% / 1200%
instructions per cycle:             1,13
branch-misses:                      1,30% of all branches
L1-dcache-load-misses:              2,82% of all L1-dcache accesses
LLC-load-misses:                    30,76% of all LL-cache accesses
```

Server Cycle-Distribution:
![[it7b_cycles_server.png]]

Desktop Cycle-Distribution:
![[it7b_cycles_desktop.png]]

### Checkliste
- Server Limits
	- [x] Werden die Daten innerhalb der maximalen Laufzeit verarbeitet?
		Ja, da `2,08 min` < `133,758 min`.
	- [x] Bleibt die Speicherauslastung unter dem festgelegten Limit?
		Ja, da `26,76 GiB` < `50 GiB`.
- Desktop Limits
	- [x] Werden die Daten innerhalb der maximalen Laufzeit verarbeitet?
		Ja, da `1.91 min` < `133,758 min`.
	- [x] Bleibt die Speicherauslastung unter dem festgelegten Limit?
		Ja, da `6,07 GiB` < `10 GiB`.
- Performanz Analyse
	- Wie erwartet führte die Behebung des Programmierfehlers zu einer Laufzeitverringerung für die Desktop-Konfiguration und keine für die Server-Konfiguration.
	  Dies liegt daran, dass in der Server-Konfiguration ein ganzer Rosbag in einem Block verarbeitet wird und folglich nicht mehr Daten als nötig geladen werden können.
	  Die Desktop-Konfiguration hingegen verarbeitet einen Rosbag in mehreren Blöcken und wurde deshalb vom Laden aller Daten im Rosbag pro Block zurückgehalten.
	- Die Probleme und Änderungsvorschläge für mit dem Load-Balancing bleiben bestehen.

### Konsequenzen
- Das Load-Balancing Problem wird als Diskussionspunkt mit dem AG für das nächste Meeting am 22.2.2024 festgelegt.
  Der AG soll entscheiden, ob die nötige Zeit investiert werden soll, um das Problem zu beheben, oder ob andere US vorgezogen werden sollen.
