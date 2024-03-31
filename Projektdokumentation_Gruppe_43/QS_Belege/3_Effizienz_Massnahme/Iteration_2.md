
>  **Datum:** 29.11.2023
>  **Durchgeführt von:** Leonhard Steinecke

### Komponenten im Fokus
-  Export zu UOS-Format (neu hinzugefügt)
- Geschwindigkeits-Entzerrung (neu hinzugefügt)
- Laden von Sensordaten aus Rosbags (**WICHTIG:** noch nicht vollständig implementiert, Performanz könnte sich noch ändern!)

### Befehle

```bash
# server settings
./drm_input_node_server

# desktop settings
./drm_input_node_desktop
```

### Messwerte

Relevante GNU Time Ergebnisse mit Server Einstellungen:
```go
Elapsed (wall clock) time (m:ss):   36:46.61
Maximum resident set size (kbytes): 25507416
Percent of CPU this job got:        111% / 4800%
```

Relevante GNU Time Ergebnisse mit Desktop Einstellungen:
```go
Elapsed (wall clock) time (m:ss):   45:03.11
Maximum resident set size (kbytes): 4313828
Percent of CPU this job got:        74% / 1200%
```

Server Cycle-Distribution:
![[it2_cycles_server.png]]

Desktop Cycle-Distribution:
![[it2_cycles_desktop.png]]

### Checkliste
- Server Limits
	- [x] Werden die Daten innerhalb der maximalen Laufzeit verarbeitet?
		Ja, da `36,78 min` < `133,758 min`.
	- [x] Bleibt die Speicherauslastung unter dem festgelegten Limit?
		Ja, da `23,76 GiB` < `50 GiB`.
- Desktop Limits
	- [x] Werden die Daten innerhalb der maximalen Laufzeit verarbeitet?
		Ja, da `45,05 min` < `267,516 min`.
	- [x] Bleibt die Speicherauslastung unter dem festgelegten Limit?
		Ja, da `4,02 GiB` < `10 GiB`.
- Cycle-Analyse
	- [x] Welche Codeabschnitte beanspruchen die meiste Zeit während des Durchlaufs?
	-  ~30%  Export zu UOS-Format
		- `__printf_fphex`, `_vrprint_internal`, `_itoa_word`, `std::ostream*`, `_itowa_word`, `std::basic_*`, `__vnsnprintf_internal`  
	-  ~11,45% Geschwindigkeits-Entzerrung (Interpolations, Matrix und Quaternion Operationen)
		- `__ieee754_acos_sse2`, `do_sin`, `__sin_avx`  `eval_catmull_rom_spline` `_mm_mul_pd` `_mm_set1_pd` 
	- ~4,37% Rosbag Laden und Dekompression
		-  `LZ4_decompress_safe`, `ROSLZ4_XXH32_update`, `__do_dyncast`
	- ~13,8 `__init_scratch_end` Ist Kernel Code und wird vorerst ignoriert, da ich diesen nicht klar zuweisen kann. (Falls Laufzeit Probleme entstehen, muss dies genauer überprüft werden)
	- [x] Werden in den Hotspot-Codeabschnitten essenzielle Operationen ausgeführt, oder stellen sie vermeidbare Engpässe dar?
	- Das Schreiben der UOS Dateien ist wegen der ASCII Representation von Zahlen unabhängig von der Implementation ein Performanzproblem und hält das Programm auf.  => Engpass
	- Die trigonometrischen Funktionen und Matrix Multiplikationen sind bei der Interpolation nicht zu vermeiden und sind bereits mit SIMD vektorisiert. => angemessen
	- Der Zeitaufwand für das Lesen der Rosbags ist gemessen an den Datenmengen und Dekompressionsoperationen adäquat. => angemessen
	- [x] Welche Teile des System sollten angepasst werden, um die Laufzeit oder Speicherauslastung zu reduzieren?
	- Das UOS Dateienformat sollte durch ein nicht ASCII Format ersetzt werden, um die Anzahl der nötigen Operationen zu verringern.
	- Alle drei Hotspot-Operationen sollten durch die Verwendung mehrerer Kerne beschleunigt werden. 
	- [x] Welche Dringlichkeit wird diesen Anpassungen zugewiesen?
	- Das Umsteigen auf ein effizienteres Dateinformat ist dringend, sollte aber zunächst mit unserem Arbeitgeber abgesprochen werden.
	- Multithreading ist sehr performanzrelvant, sollte aber erst Implementiert werden, wenn das gesamte System bekannt ist, um Refactorings auf ein Minimum zu halten.

### Konsequenzen
- Für das Meeting am 29.11.2023 wurde ein Agendapunkt hinzugefügt für die Diskussion eines neueren, effizienteren Datenformats.
- Eine User Story für die Parallelisierung des Programms wurde ausgearbeitet und wird unserem Arbeitgeber zur Priorisierung übergeben.