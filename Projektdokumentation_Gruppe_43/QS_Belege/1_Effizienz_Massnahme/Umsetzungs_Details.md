## Limits

> Laufzeitlimit:   `133,758 min`
> Desktop Thread Limit: `12`
> Server Thread Limit: `48`
> Desktop Arbeitspsicher Limit: `10 GiB`
> Server Arbeitspsicher Limit: `50 GiB`


## Struktur

```mad

>  **Datum:** D.M.Y
>  **Durchgeführt von:** ?

## Komponenten im Fokus
\<!--- Komponenten, die sich während der Iteration verändert haben und besonders überprüft werden müssen -->

### Befehle:
\`\`\`bash
# server settings
measure_exec "\<!--- Server Befehl -->" "/tmp/map_data" "/media/vault/test_results/it?/server"

# desktop settings
measure_exec "\<!--- Desktop Befehl -->" "/tmp/map_data" "/media/vault/test_results/it?/desktop"
\`\`\`

### Messwerte

Zusammengeführte Ergebnisse mit Server Einstellungen:
\`\`\`go
Elapsed (wall clock) time (m:ss):   ?:?.?
Maximum resident set size (kbytes): ?
Percent of CPU this job got:        ?% / 4800%
instructions per cycle:             ?
branch-misses:                      ?% of all branches
L1-dcache-load-misses:              ?% of all L1-dcache accesses
LLC-load-misses:                    ?% of all LL-cache accesses
\`\`\`

Zusammengeführte Ergebnisse mit Desktop Einstellungen:
\`\`\`go
Elapsed (wall clock) time (m:ss):   ?:?.?
Maximum resident set size (kbytes): ?
Percent of CPU this job got:        ?% / 1200%
instructions per cycle:             ?
branch-misses:                      ?% of all branches
L1-dcache-load-misses:              ?% of all L1-dcache accesses
LLC-load-misses:                    ?% of all LL-cache accesses
\`\`\`

Server Cycle-Distribution:
\<!--- Screenshot aus dem Program 'Hotspot' der mit 'perf record' aufgenommenen Cycle-Distribution des Server Durchlaufs -->

Desktop Cycle-Distribution:
\<!--- Screenshot aus dem Program 'Hotspot' der mit 'perf record' aufgenommenen Cycle-Distribution des Desktop Durchlaufs -->

### Checkliste
- Server Limits
	- [ ] Werden die Daten innerhalb der maximalen Laufzeit verarbeitet?
	- [ ] Bleibt die Speicherauslastung unter dem festgelegten Limit?
- Desktop Limits
	- [ ] Werden die Daten innerhalb der maximalen Laufzeit verarbeitet?
	- [ ] Bleibt die Speicherauslastung unter dem festgelegten Limit?
- Performanz Analyse
	- [ ] Werden in den Hotspot-Codeabschnitten essenzielle Operationen ausgeführt, oder stellen sie vermeidbare Engpässe dar?
	- [ ] Welche Teile des System sollten angepasst werden, um die Laufzeit oder Speicherauslastung zu reduzieren?
	- [ ] Welche Dringlichkeit wird diesen Anpassungen zugewiesen?

### Konsequenzen

```


## Script für Messungen

```bash
#!/bin/bash

clean_exec() {
	CMD=$1
    OUTPUT_DIR=$2

	mkdir $OUTPUT_DIR
	echo "Running command '${CMD}'"
        eval $CMD
	echo "Done running command '${CMD}'"
    echo "Clearing '${OUTPUT_DIR}'"
	rm -rf $OUTPUT_DIR
}

measure_exec() {
	COMMAND=$1
	OUTPUT_DIR=$2
	RESULT_DIR=$3

	mkdir $RESULT_DIR

	# measure memory usage + time
	clean_exec "(/usr/bin/time -v ${COMMAND}) > time_out.txt 2>&1" $OUTPUT_DIR
	mv time_out.txt $RESULT_DIR

	# measure brnach/cache misses etc.
	clean_exec "(perf stat -a -d ${COMMAND}) > perf_stat_out.txt 2>&1" $OUTPUT_DIR
	mv perf_stat_out.txt $RESULT_DIR

	# measure hotspots
	clean_exec "perf record -a -g ${COMMAND}" $OUTPUT_DIR
	mv perf.data $RESULT_DIR
}

ROSBAGS="/home/tester/Documents/rosbags/Recorder_2022-08-26-08-59-35_c_l.bag /home/tester/Documents/rosbags/Recorder_2022-08-26-10-25-02_c_l.bag /home/tester/Documents/rosbags/Recorder_2022-08-26-12-28-09_c_l.bag /home/tester/Documents/rosbags/Recorder_2022-08-28-12-28-55_c_l.bag /home/tester/Documents/rosbags/Recorder_2022-08-28-13-49-15_c_l.bag"

# function calls for given implementation:

```


## Evaluationssystem

```go
System:       PowerEdge T620
CPU(s):       24 Cores, 48 Threads 1,8Ghz - 3,5Ghz (2x Intel(R) Xeon(R) CPU E5-2697 v2)
Cache:        384KiB L1, 3MiB L2, 30MiB L3
Memory:       256GiB (16x 16GiB DDR3 ECC 1600 MT/s)
Drive:        223GiB SATA SSD
OS:           Ubuntu 20.04.6 LTS
Kernel:       Linux 5.15.0-101-generic
Architecture: x86-64
```
