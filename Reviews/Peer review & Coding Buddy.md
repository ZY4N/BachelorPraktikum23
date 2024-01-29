##### Vorteile von code reviews
- Wissen teilen
- Fehler früher finden
- Erhält einheitlichen coding style
- Erhöht die Sicherheit
- Erhöht Zusammenarbeit
- Erhöht Code Qualität

##### Faith Ansatz
- Faith, oder F.A.I.T.H. im peer review hat fünf core Attribute: **fairness in reviewing; appropriate expertise, identifiable reviewers, timely reviews; und helpful critiques**.

##### Focus auf code Qualität:
- Kann ich einfach verstehen was der Code tut?
	- Ist der Code genug dokumentiert?
	- Sind Duplikate im Code, die durch weitere Funktionen oder Klassen herausgenommen werden könnten?
	- Sind Funktionen und Klassen möglichst einfach gehalten, mit einer minimalen Anzahl an Parametern?
- Sind die erforderlichen Funktionalitäten ausreichend getestet?
- Wie einfach wäre es den Code zu verändern oder zu erweitern wenn nötig?
	- Sind high level parameter in speziellen configuration files?
	- Oder müsste man sich durch allen Code arbeiten und viele manuelle Veränderungen vornehmen um für einen neuen Durchlauf zu konfigurieren?
- Kann ich die selben Outputs erzeugen, die das Programm angibt?
	- Sind alle dependencies genug dokumentiert?
	- Sind Code Version, input data Version und configuration dokumentiert?

##### Cedar feedback Model
1. Kontext - beschreibe das Problem und die möglichen Konsequenzen
2. Beispiele - gebe spezifische Beispiele wann und wo die Probleme entstehen 
3. Diagnose - nutze die Beispiele um zu erläutern warum dieser Ansatz benutzt wurde, was anders getan werden könnte und warum diese Änderungen eine Verbesserung wären
4. Aktion - frag die Person die Feedback bekommt, wie die diese Probleme in Zukunft verhindern könnte
5. Review - schaue zu einem späterem Zeitpunkt ob und wie das Feedback umgesetzt wurde

Konsistentes Feedback mithilfe eines Templates 
- Beispiel Template:

-------
##  Code review

#### Dokumentation

Jeder neue Code beinhaltet die folgende Form der Dokumentation:

- [ ] **Functions Documentation** als docstrings in der Funktions Definition.
- [ ] **Beispiele** welche große Funktionalitäten demonstrieren, welche lokal erfolgreich laufen.
#### Funktionalität

- [ ] **Installation**: Installation oder build des Codes funktioniert.
- [ ] **Funktionalität**: Jede Funktionalität des neuen Codes, die beschrieben wird, funktioniert auch.
- [ ] **Automatisierte Tests**: Unit tests decken alle essentiellen Funktionen in einer annehmbaren Menge an Inputs und Bedingungen ab. Alle tests bestehen auf dem lokalem Gerät des Testenden. 
- [ ] **Packaging guidelines**: Neuer Code entspricht den Projekt Richtlinien.
---

### Review Kommentare

*Detaillierte Kommentare hier einfügen!*

Diese könnten beinhalten:

- Fehler/bugs die behoben werden müssen (funktioniert alles wie erwartet? funktioniert es zusammen mit anderem Code mit dem es interagiert?)
- alternative Methoden (könnte es effizienter oder klarer geschrieben sein?)
- Documentations Verbesserungen (Reflektiert die Dokumentation eir der Code tatsächlich funktioniert?)
- zusätzliche Tests die noch ergänzt werden sollten (do the tests effectively assure that it  works correctly?)
- code style improvements (könnte der Code allgemein klarer Formuliert sein?)

Die Vorschläge sollten an den Code der reviewed wird angepasst werden.
Sei kritisch und klar, jedoch nicht gemein.  Stelle Fragen und schlage Aktionen vor.

--------
- Wenn größere oder Vollständige Code Abschnitte reviewed werden müssen, ist es eventuell besser verschiedene Aspekte des Codes in verschiedenen Sessions zu reviewen. Zum Beispiel eine Session mit Fokus auf die Dokumentation und eine mit Fokus auf die Funktionalität.
###### Review durch pair programming möglich

##### Code Buddy Ansatz
1. Nach Verteilung der Aufgaben geht man mit seinem Buddy sowohl die eigenen als auch seine Aufgaben und Teilaufgaben durch. Je nach Task ist das in unterschiedlicher Gründlichkeit auszuführen.
2. Für die Aufgabe sollte ein eigener Branch erstellt werden und daraufhin ein Pull Request für diesen Branch. Ein Link zu diesem wird dann an den Code Buddy geschickt.
3. Danach arbeiten beide an ihren eigenen Aufgaben wie gewohnt, wobei in unregelmäßigen Abständen in den dazugehörigen Branch gepushed wird (wodurch auch den Code Buddy eine Benachrichtigung erhalten sollte).  
	- Der Vortschritt des Buddys sollte regelmäßig gereviewed werden (nach oben beschriebenem Vorgehen). Genauso auch umgekehrt.
	- Auch regelmäßiges Austauschen über allgemeinen Fortschritt über z.B. Anrufe sind Vorteilhaft um sich auszutauschen. ( Oder auch einfach ein kurzes, momentan alles gut oder ähnliches, wenn nichts ansteht )
	- Wenn beim Coden Probleme auftauchen oder einer der Partner nicht vorwärts kommt ist der Buddy die erste Anlaufstelle um diese zu lösen und das weitere Vorgehen zu besprechen. Wenn beide nicht weiter wissen, wird sich an die allgemeine Gruppe gewendet. 
4. Wenn nun die Aufgabe fertig ist, ist der Code automatisch schon gereviewed, und kann gemerged werden.
