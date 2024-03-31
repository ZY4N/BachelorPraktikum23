
>  **Datum:** 17.12.2023
>  **Durchgeführt von:** Leonhard Steinecke

### Komponenten im Fokus
- Laden von Sensordaten aus Rosbags (vollständig implementiert)
- Verringern von Aufnahmepositionen (neu hinzugefügt)

### Befehle

```bash
# server settings
./drm_input_node_server $ROSBAGS -o /tmp/map_data

# desktop settings
./drm_input_node_desktop $ROSBAGS -o /tmp/map_data
```

### Messwerte

Relevante GNU Time Ergebnisse mit Server Einstellungen:
```go
Elapsed (wall clock) time (m:ss):   27:26.82
Maximum resident set size (kbytes): 16973260
Percent of CPU this job got:        149% / 4800%
```

Relevante GNU Time Ergebnisse mit Desktop Einstellungen:
```go
Elapsed (wall clock) time (m:ss):   37:16.78
Maximum resident set size (kbytes): 2262624
Percent of CPU this job got:        103% / 1200%
```

Server Cycle-Distribution:
![[it3_cycles_server.png]]

Desktop Cycle-Distribution:
![[it3_cycles_desktop.png]]
		
### Checkliste
- Server Limits
	- [x] Werden die Daten innerhalb der maximalen Laufzeit verarbeitet?
		Ja, da `27,45 min` < `133,758 min`.
	- [x] Bleibt die Speicherauslastung unter dem festgelegten Limit?
		Ja, da `15,81 GiB` < `50 GiB`.
- Desktop Limits
	- [x] Werden die Daten innerhalb der maximalen Laufzeit verarbeitet?
		Ja, da `37.28 min` < `267,516 min`.
	- [x] Bleibt die Speicherauslastung unter dem festgelegten Limit?
		Ja, da `2,11 GiB` < `10 GiB`.
- Cycle-Analyse
	- [x] Welche Codeabschnitte beanspruchen die meiste Zeit während des Durchlaufs?
	- ~28%  Export zu UOS-Format
		- `__printf_fphex`, `_vrprint_internal`, `_itoa_word`, `std::ostream*`, `_itowa_word`, `std::basic_*`, `__vnsnprintf_internal`  
	-  ~9,22% Geschwindigkeitsentzerrung (Interpolations, Matrix und Quaternion Operationen)
		- `__ieee754_acos_sse2`, `do_sin`, `__sin_avx`,  `eval_catmull_rom_spline`, `_mm_mul_pd`, `_mm_set1_pd` 
	- ~4,26% Rosbag Laden und Dekompression
		-  `LZ4_decompress_safe`, `ROSLZ4_XXH32_update`, `__do_dyncast
	- ~1,42% Verringerung von Aufnahmetransformationen (im Fokus, weil neu hinzugefügt)
		- `reframe_to_closest_scan_positions`
	- ~18% `__init_scratch_end` Ist Kernel Code und wird vorerst ignoriert, da ich diesen nicht klar zuweisen kann. (Falls Laufzeit Probleme entstehen, muss dies genauer überprüft werden)
	- [x] Werden in den Hotspot-Codeabschnitten essenzielle Operationen ausgeführt, oder stellen sie vermeidbare Engpässe dar?
	- Die Einschätzung der Performanzanalyse letzter Iteration bezüglich "Export zu UOS-Format", "Geschwindigkeitsentzerrung" und "Rosbag Laden und Dekompression" bleibt gleich.
	- Die Laufzeit der Verringerung von Aufnahmetransformationen ist im Vergleich zu der verarbeiteten Datenmenge adäquat. => angemessen
	- [x] Welche Teile des System sollten angepasst werden, um die Laufzeit oder Speicherauslastung zu reduzieren?
	- Die in der letzten Iteration vorgeschlagenen Änderungen gelten auch für diese Iteration
	- [x] Welche Dringlichkeit wird diesen Anpassungen zugewiesen?
	- Da beide in letzer Iteration angemerkten Änderungsvorschläge in User Stories aufgenommen wurden, liegt die Einschätzung der Dringlichkeit nun bei unserem Arbeitgeber.

### Konsequenzen

Es wurden keine neuen Konsequenzen beschlossen.
