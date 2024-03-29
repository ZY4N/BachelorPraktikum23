
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

Relevante GNU Time Ergebnisse mit Server Einstellungen:
```go
Elapsed (wall clock) time (m:ss):   8:29.14
Maximum resident set size (kbytes): 18871712
Percent of CPU this job got:        279% / 4800%
```

Relevante GNU Time Ergebnisse mit Desktop Einstellungen:
```go
Elapsed (wall clock) time (m:ss):   9:13.45
Maximum resident set size (kbytes): 3043048
Percent of CPU this job got:        182% / 1200%
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
		Ja, da `9.22 min` < `267,516 min`.
	- [x] Bleibt die Speicherauslastung unter dem festgelegten Limit?
		Ja, da `2,83 GiB` < `10 GiB`.
- Performanz Analyse
	- Da keine der Performanzkritischen Komponenten verändert wurden und sich die Messwerte nicht signifikant verändert haben,
	  verzichten wir auf die genauere Performanz Analyse.

### Konsequenzen

Es wurden keine neuen Konsequenzen beschlossen.
