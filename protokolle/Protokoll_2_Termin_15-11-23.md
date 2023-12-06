###  Einführung von AG

- Zugriff auf das "Daten Silo" per VPN, und auf GitLab Projekt
- Einführung in das Gesamtprojekt "MAAS"
	- Control_* : Hardwaresteuerung
	- Map: 2D Karte
		- Hat die fast korrekten Schienen Splines
		- Sind aufgeteilt mit Segment ID
			- Diese sollten auf die Chunks mappen.
		- Hat ein Live-Dashboard für die Bahn
		- Map nur über VPN erreichbar (VPN-Zugang bekommen wir laut AG noch)
	- ROS: komplett alles was ROS enthält (Bahn und eigene Server)
	- rqt Image Viewer: Kameras ansteuern
         
### Vorstellung von people-remover

#### AG Anmerkung
- GPS, IMU und Lidar, um Position herauszubekommen. ***Name und Paper wollte AG noch in Matrix veröffentlichen.***

###  Pipeline vom AG
- Nick/Wank-Bewegungen raus rechen, Lokalisierung funktionieren
	- Mit Grade nach unten rechnen
	- Localized Daten benutzen
- Herausfiltern von dynamischen Projekten

## Vorstellung von unserem Konzept

- Proof of Concept:
	- rosbag Unbagger → Dynamic Object Remover
- Minimal viable Concept:
	- rosbag Unbagger → Data Correction → D-O-R → Map Maker

#### Anmerkung des AG
- Für ihn ist Korrigieren der Daten sehr wichtig.
- Springenden Lidar-Daten
- Daten abschneiden nach x Meter
-  Annehmen, dass Karte flach ist, ist viable. (Lokale Fehler sind sehr gering)
	- Koordinatensystem der 2D-Map (siehe oben) nimmt Erdkrümmung nicht mit
- Ganze Rog-Bags reinladen (erstmal) ist sinnvoller.
- LIZENZ ist verhandelbar. Veröffentlichung wäre cool. Schauen, was geht und dann mit AG absprechen. (Bezug: Angedachte Lizenz unseres Projekt ist nicht kompatible mit PPL-Remover)
- Einbezug von mehreren Lidar ist nice to have
- Müssen nicht jeden Edgecase sofort abfangen.

### Anwendungsfälle des Projekts
- Bei ML für Hintergrund
- Und live für Objekterkennung der Bahn

### Vorstellung der Daten
→ Sehen live Lidar-Daten von der Bahn über rViz
###### Potenziell wichtige Anmerkungen
- Genaue Einstellungen für rViz schickt AG noch über Elements.
- Merkwürdige Dinge passieren bei zu langem Stillstand der Bahn.

#### Continues integration Server:
> Bekommen wir einen continues integration Server? Ist wichtig für Qs
- AG schaut mal, ob er es hinbekommt.

### User Storys
Absprache mit AG war, dass wir diese über Elements schreiben und sie dort von ihm abgesegnet werden.

### QS
→  Sortieren QS Möglichkeiten nach Wichtigkeit nach Einschätzung des Qs

Wichtig:
- Wartbarkeit
- Kompatibilität
- Effizienz

Unwichtig:
- Benutzbarkeit
- Datensicherheit
- Vollständigkeit
- Zuverlässigkeit

Neutral:
- Funktionalität

Wir werden natürlich die drei als wichtig eingeordneten QS als die nehmen, die wir für die BP-Dokumentation aufschreiben und nachweisen.

### Übergabe von zwei Roh-Datensätzen der Tram als rosbags
##### Slams
- Hektor
- arwes
- Slam von ppl remover

#### Neuer Termin: 29.11.2,3 9 Uhr, gleicher Ort.