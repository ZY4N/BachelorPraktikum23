
>  **Datum:** 9.1.2024
>  **Durchgeführt von:** Leonhard Steinecke

### Komponenten im Fokus
- Export zu KITTI-Format (neu hinzugefügt)

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
Elapsed (wall clock) time (m:ss):   3:54.66
Maximum resident set size (kbytes): 17099280
Percent of CPU this job got:        538% / 4800%
```

Relevante GNU Time Ergebnisse mit Desktop Einstellungen:
```go
Elapsed (wall clock) time (m:ss):   4:49.00
Maximum resident set size (kbytes): 2445288
Percent of CPU this job got:        315% / 1200%
```

Server Cycle-Distribution:
![[it4_cycles_server.png]]

Desktop Cycle-Distribution:
![[it4_cycles_desktop.png]]

### Checkliste
- Server Limits
	- [x] Werden die Daten innerhalb der maximalen Laufzeit verarbeitet?
		Ja, da `3,91 min` < `133,758 min`.
	- [x] Bleibt die Speicherauslastung unter dem festgelegten Limit?
		Ja, da `15,92 GiB` < `50 GiB`.
- Desktop Limits
	- [x] Werden die Daten innerhalb der maximalen Laufzeit verarbeitet?
		Ja, da `4.82 min` < `267,516 min`.
	- [x] Bleibt die Speicherauslastung unter dem festgelegten Limit?
		Ja, da `2,28 GiB` < `10 GiB`.
- Cycle-Analyse
	- [x] Welche Codeabschnitte beanspruchen die meiste Zeit während des Durchlaufs?
	- ~36% Geschwindigkeitsentzerrung (Interpolations, Matrix und Quaternion Operationen)
		- `__ieee754_acos_sse2`, `do_sin`, `__sin_avx`,  `eval_catmull_rom_spline`, `advance_and_sample_...`, `slerp`, `approximate_step_sizes`, `doasin`
	- ~10.07% Export zu KITTI-Format (im Fokus, weil neu hinzugefügt)
		- `std::basic_*`, `std::ostream*`
	- ~5,89% Rosbag Dekompression
		-  `LZ4_decompress_safe`, `ROSLZ4_XXH32_update`
	- ~4,53% Verringerung von Aufnahmetransformationen
		-  `reframe_to_closest_scan_position`
	- [x] Werden in den Hotspot-Codeabschnitten essenzielle Operationen ausgeführt, oder stellen sie vermeidbare Engpässe dar?
	- Der KITTI-Format Exporter hat laut Ubuntus System Monitors in Schreibphasen die SATA SSD zu 100% ausgelastet (dies entspräche ca. `850Mbps`).
	  Zusätzlich stellt der Exporter im Vergleich zum alten UOS-Exporter beim Vergleichen der Teillaufzeiten eine Laufzeitverringerung um den Faktor 20 dar.
	  (Hierbei ist wichtig anzumerken, dass dies nur Abschätzungen sind, aber da sich das Programm in allen Limits befindet, werten wir dies als adäquat)  => angemessen
	- Durch die Reduktion in Export Laufzeit, nimmt die Geschwindigkeitsentzerrung nun einen signifikanten Anteil der Laufzeit an. 
	  Mit einem 1.5min Laufzeitanteil ist diese jedoch immer noch extrem weit unter dem Laufzeitlimit. => angemessen
	- [x] Welche Teile des System sollten angepasst werden, um die Laufzeit oder Speicherauslastung zu reduzieren?
	- die Laufzeit und Speicherauslastung sind so weit unter den Limits, dass Änderungen zur Zeit nicht nötig sind.
	- [x] Welche Dringlichkeit wird diesen Anpassungen zugewiesen?
	- Die Dringlichkeit des ausstehenden Änderungsvorschlags (Multithreading) liegt nach wie vor beim AG.  

### Konsequenzen

Es wurden keine neuen Konsequenzen beschlossen.