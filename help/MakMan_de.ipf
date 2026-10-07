.* MakMan/2 help - de
:userdoc.

:h1 res=2100.Ueber MakMan/2
:i1.Ueber MakMan/2
:p.
MakMan/2 ist ein Labyrinthspiel im Stil von PacMan fuer OS/2 und ArcaOS. Es wurde 1995 von Markellos J. Diorinos geschrieben; diese Version ist eine Open-Watcom-Portierung mit Menues in sechs Sprachen, Tastenkuerzeln, Online-Hilfe und gespeicherten Einstellungen.
:p.
Fuehren Sie MakMan durch das Labyrinth, fressen Sie alle Punkte und weichen Sie den Geistern aus.
:p.
Weitere Informationen&colon.
:p.
:link reftype=hd res=2101.Spielverlauf:elink.
.br
:link reftype=hd res=2102.Steuerung:elink.
.br
:link reftype=hd res=2103.Punktewertung:elink.
.br
:link reftype=hd res=2104.Menue Spiel:elink.
.br
:link reftype=hd res=2105.Menue Optionen:elink.
.br
:link reftype=hd res=2106.Menue Hilfe:elink.
.br
:link reftype=hd res=2107.Kommandozeile:elink.
.br
:link reftype=hd res=2108.Copyright:elink.


:h1 res=2101.Spielverlauf
:i1.Spielverlauf
:ul compact.
:li.Waehlen Sie Neu im Menue Spiel (Ctrl+N), um ein Spiel zu starten. MakMan beginnt mit drei Leben, die oben links im Labyrinth als kleine MakMan-Figuren angezeigt werden. Die Punktzahl steht oben rechts.
:li.Fressen Sie alle kleinen Punkte im Labyrinth, um den Level zu schaffen. Danach folgt ein neuer Level.
:li.Die Geister jagen MakMan. Die Beruehrung eines Geistes kostet ein Leben. Ist das letzte Leben verloren, ist das Spiel zu Ende.
:li.Die grossen blinkenden Punkte sind Kraftpunkte. Nach dem Fressen eines Kraftpunktes koennen die Geister kurze Zeit gefressen werden und bringen Punkte. Die Geister sehen anders aus, solange sie gefressen werden koennen.
:li.Von Zeit zu Zeit erscheint eine Frucht im Labyrinth. Fressen Sie sie, bevor sie verschwindet, fuer Bonuspunkte.
:li.Mit Ctrl+P pausieren Sie das Spiel, mit Ctrl+Q beenden Sie es.
:li.Laeuft kein Spiel, wird die Bestenliste angezeigt. Die besten 15 Ergebnisse werden gespeichert; reicht Ihre Punktzahl aus, werden Sie am Spielende nach Ihrem Namen gefragt.
:eul.

:h1 res=2102.Steuerung
:i1.Steuerung
:p.
Mit der Tastatur bewegen die Pfeiltasten links, rechts, oben und unten MakMan. Fuer einen Joystick waehlen Sie Joystick A oder Joystick B unter Optionen - Steuerung; dort kann der Joystick auch kalibriert werden. Solange ein Joystick aktiv ist, steuert die Tastatur MakMan nicht.
:p.
:dl break=all.
:dt.Pfeiltasten
:dd.Bewegen MakMan.
:dt.Ctrl+N
:dd.Neues Spiel.
:dt.Ctrl+P
:dd.Pause / Fortsetzen.
:dt.Ctrl+Q
:dd.Das aktuelle Spiel beenden.
:dt.Ctrl+X
:dd.MakMan/2 beenden.
:dt.Ctrl+B
:dd.Hintergrundlauf ein / aus.
:dt.Ctrl+F
:dd.Rahmenbedienung - Titelleiste und Menue verbergen / anzeigen.
:dt.F1
:dd.Hilfe.
:edl.

:h1 res=2103.Punktewertung
:i1.Punktewertung
:dl break=all.
:dt.Kleiner Punkt
:dd.10 Punkte.
:dt.Kraftpunkt
:dd.50 Punkte.
:dt.Geister, die mit einem Kraftpunkt gefressen werden
:dd.200, 400, 800 und 1600 Punkte, nacheinander.
:dt.Frucht
:dd.Der Wert erscheint beim Fressen und haengt vom Level ab.
:dt.Zusaetzliches Leben
:dd.Bei 10000 Punkten, dann bei 20000, 40000 usw. (jeweils das Doppelte).
:edl.

:h1 res=2104.Menue Spiel
:i1.Menue Spiel
:dl break=all.
:dt.Neu
:dd.Startet ein neues Spiel.
:dt.Pause
:dd.Pausiert das Spiel oder setzt es fort, wenn es bereits pausiert ist. Nur verfuegbar, solange ein Spiel laeuft.
:dt.Spiel Beenden
:dd.Beendet das aktuelle Spiel und kehrt zur Bestenliste zurueck. Nur verfuegbar, solange ein Spiel laeuft.
:dt.Beenden
:dd.Schliesst MakMan/2.
:edl.

:h1 res=2105.Menue Optionen
:i1.Menue Optionen
:dl break=all.
:dt.Kachelsatz
:dd.Waehlt die Grafik von Labyrinth und Figuren&colon. Klassisch, 3D-Stil oder Fufitos. Der Kachelsatz kann nur geaendert werden, wenn kein Spiel laeuft.
:dt.Steuerung
:dd.Waehlt Tastatur oder einen Joystick (Joystick A oder B) und kalibriert den Joystick.
:dt.Sound
:dd.Schaltet die Soundeffekte ein oder aus.
:dt.Prioritaet
:dd.Stellt die Prioritaet des Spiels ein (Normal, Kritisch oder Server). Verwenden Sie Kritisch oder Server nur, wenn das Spiel auf einem ausgelasteten System ruckelt.
:dt.Sprache
:dd.Aendert die Sprache der Menues und dieser Hilfe (English, Espanol, Nederlands, Deutsch, Francais, Italiano).
:dt.Hintergrundlauf
:dd.Ist die Option ausgeschaltet, pausiert das Spiel automatisch, wenn das Fenster den Fokus verliert.
:dt.Rahmenbedienung
:dd.Verbirgt oder zeigt Titelleiste und Menue. Druecken Sie erneut Ctrl+F, um sie wieder anzuzeigen.
:dt.Einstellungen beim Beenden speichern
:dd.Ist die Option markiert (Standard), werden die Einstellungen beim Beenden in MAKMAN.INI gespeichert. Die Bestenliste wird immer gespeichert.
:edl.

:h1 res=2106.Menue Hilfe
:i1.Menue Hilfe
:dl break=all.
:dt.Hilfeindex
:dd.Zeigt den Index dieser Hilfe.
:dt.Allgemeine Hilfe
:dd.Zeigt die allgemeine Hilfe, beginnend mit dem ersten Thema.
:dt.Hilfe verwenden
:dd.Erklaert, wie das Hilfefenster verwendet wird.
:dt.Ueber MakMan/2
:dd.Zeigt Versions- und Autoreninformationen.
:edl.

:h1 res=2107.Kommandozeile
:i1.Kommandozeile
:p.
MakMan/2 verwendet standardmaessig GPI-Grafik. Ein Parameter in der Kommandozeile waehlt den Grafikmodus&colon.
:dl break=all.
:dt.makman
:dd.GPI-Grafik (Standard, empfohlen).
:dt.makman gpi
:dd.Dasselbe wie oben.
:dt.makman dive
:dd.DIVE-Grafik. Erfordert einen DIVE-faehigen Grafiktreiber.
:edl.

:h1 res=2108.Copyright
:i1.Copyright
:p.
MakMan/2 Version 1.1
:p.
Copyright (C) 1995 Markellos J. Diorinos. Open-Watcom-Portierung und Erweiterungen, 2026.
:p.
Veroeffentlicht als Open Source unter der GNU General Public License Version 3. Siehe doc\License.txt.
:p.
Diese Software wird ohne jegliche Gewaehrleistung bereitgestellt.

:euserdoc.
