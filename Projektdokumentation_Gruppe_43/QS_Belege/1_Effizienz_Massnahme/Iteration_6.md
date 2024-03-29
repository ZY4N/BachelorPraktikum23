
>  **Datum:** 6.2.2024
>  **Durchgeführt von:** Leonhard Steinecke

### Komponenten im Fokus

In dieser Iteration wurden keine Veränderungen an Performanz relevanten Komponenten vorgenommen.
(Dies bedeutet auch, dass die Änderungen an der Chunk Bucket Anzahl nicht vorgenommen wurden.)
Die Messungen werden dennoch zur Sicherheit vorgenommen.

### Befehle

```bash
# server settings
measure_exec "./drm_input_node_server ${ROSBAGS} -o /tmp/map_data --max-radial-dist 30 --max-peripheral-dist 20 --time-per-block 1h --max-scan-pos-deviation 1 --chunk-size 30" "/tmp/map_data" "/media/vault/test_results/it6/server"

# desktop settings
measure_exec "./drm_input_node_desktop ${ROSBAGS} -o /tmp/map_data --max-radial-dist 30 --max-peripheral-dist 20 --time-per-block 5min --max-scan-pos-deviation 1 --chunk-size 30" "/tmp/map_data" "/media/vault/test_results/it6/desktop"
```

### Messwerte

Zusammengeführte Ergebnisse mit Server Einstellungen:
```go
Elapsed (wall clock) time (m:ss):   8:29.14
Maximum resident set size (kbytes): 18871712
Percent of CPU this job got:        279% / 4800%
instructions per cycle:             1,13
branch-misses:                      2,01% of all branches
L1-dcache-load-misses:              4,18% of all L1-dcache accesses
LLC-load-misses:                    31,68% of all LL-cache accesses
```

Zusammengeführte Ergebnisse mit Desktop Einstellungen:
```go
Elapsed (wall clock) time (m:ss):   9:13.45
Maximum resident set size (kbytes): 3043048
Percent of CPU this job got:        182% / 1200%
instructions per cycle:             1,15
branch-misses:                      1,89% of all branches
L1-dcache-load-misses:              3,61% of all L1-dcache accesses
LLC-load-misses:                    34,39% of all LL-cache accesses
```

Server Cycle-Distribution:
![[it6_cycles_server.png]]

Desktop Cycle-Distribution:
![[it6_cycles_desktop.png]]

## Checkliste
- Server Limits
	- [x] Werden die Daten innerhalb der maximalen Laufzeit verarbeitet?
		Ja, da `8,49 min` < `133,758 min`.
	- [x] Bleibt die Speicherauslastung unter dem festgelegten Limit?
		Ja, da `17,58 GiB` < `50 GiB`.
- Desktop Limits
	- [x] Werden die Daten innerhalb der maximalen Laufzeit verarbeitet?
		Ja, da `9.22 min` < `133,758 min`.
	- [x] Bleibt die Speicherauslastung unter dem festgelegten Limit?
		Ja, da `2,83 GiB` < `10 GiB`.
- Performanz Analyse
	- Da keine der Performanzkritischen Komponenten verändert wurden und sich die Messwerte nicht signifikant verändert haben,
	  verzichten wir auf die genauere Performanz Analyse.

### Konsequenzen

Es wurden keine neuen Konsequenzen beschlossen.
