.* MakMan/2 help - nl
:userdoc.

:h1 res=2100.Over MakMan/2
:i1.Over MakMan/2
:p.
MakMan/2 is een doolhofspel in de stijl van PacMan voor OS/2 en ArcaOS. Het werd in 1995 geschreven door Markellos J. Diorinos; deze versie is een Open Watcom-port met menu's in zes talen, sneltoetsen, online help en opgeslagen instellingen.
:p.
Leid MakMan door het doolhof, eet alle stippen op en blijf uit de buurt van de spoken.
:p.
Meer informatie&colon.
:p.
:link reftype=hd res=2101.Hoe te spelen:elink.
.br
:link reftype=hd res=2102.Besturing:elink.
.br
:link reftype=hd res=2103.Puntentelling:elink.
.br
:link reftype=hd res=2104.Menu Spel:elink.
.br
:link reftype=hd res=2105.Menu Opties:elink.
.br
:link reftype=hd res=2106.Menu Help:elink.
.br
:link reftype=hd res=2107.Opdrachtregel:elink.
.br
:link reftype=hd res=2108.Copyright:elink.


:h1 res=2101.Hoe te spelen
:i1.Hoe te spelen
:ul compact.
:li.Kies Nieuw in het menu Spel (Ctrl+N) om een spel te starten. MakMan begint met drie levens, getoond als kleine MakMan-figuren linksboven in het doolhof. De score staat rechtsboven.
:li.Eet alle kleine stippen in het doolhof op om het niveau te voltooien. Daarna volgt een nieuw niveau.
:li.De spoken jagen op MakMan. Een spook aanraken kost een leven. Als het laatste leven verloren is, is het spel afgelopen.
:li.De grote knipperende stippen zijn krachtstippen. Na het opeten van een krachtstip kunnen de spoken korte tijd worden opgegeten en leveren ze punten op. De spoken zien er anders uit zolang ze eetbaar zijn.
:li.Af en toe verschijnt er fruit in het doolhof. Eet het op voordat het verdwijnt voor bonuspunten.
:li.Pauzeer het spel met Ctrl+P en stop het met Ctrl+Q.
:li.Als er geen spel bezig is, wordt de lijst met hoogste scores getoond. De beste 15 scores worden bewaard; haalt uw score de lijst, dan wordt aan het einde van het spel om uw naam gevraagd.
:eul.

:h1 res=2102.Besturing
:i1.Besturing
:p.
Met het toetsenbord bewegen de pijltoetsen links, rechts, omhoog en omlaag MakMan. Kies voor een joystick Joystick A of Joystick B in Opties - Besturing; daar kunt u de joystick ook kalibreren. Zolang een joystick actief is, stuurt het toetsenbord MakMan niet.
:p.
:dl break=all.
:dt.Pijltoetsen
:dd.Bewegen MakMan.
:dt.Ctrl+N
:dd.Nieuw spel.
:dt.Ctrl+P
:dd.Pauzeren / hervatten.
:dt.Ctrl+Q
:dd.Het huidige spel stoppen.
:dt.Ctrl+X
:dd.MakMan/2 afsluiten.
:dt.Ctrl+B
:dd.Achtergrond Actief aan / uit.
:dt.Ctrl+F
:dd.Raambediening - titelbalk en menu verbergen / tonen.
:dt.F1
:dd.Help.
:edl.

:h1 res=2103.Puntentelling
:i1.Puntentelling
:dl break=all.
:dt.Kleine stip
:dd.10 punten.
:dt.Krachtstip
:dd.50 punten.
:dt.Spoken gegeten met een krachtstip
:dd.200, 400, 800 en 1600 punten, achtereenvolgens.
:dt.Fruit
:dd.De waarde verschijnt bij het opeten en hangt van het niveau af.
:dt.Extra leven
:dd.Bij 10000 punten, daarna bij 20000, 40000 enzovoort (telkens het dubbele).
:edl.

:h1 res=2104.Menu Spel
:i1.Menu Spel
:dl break=all.
:dt.Nieuw
:dd.Start een nieuw spel.
:dt.Pauze Spel
:dd.Pauzeert het spel, of hervat het als het al gepauzeerd is. Alleen beschikbaar terwijl een spel bezig is.
:dt.Spel Stoppen
:dd.Stopt het huidige spel en keert terug naar het scherm met de hoogste scores. Alleen beschikbaar terwijl een spel bezig is.
:dt.Afsluiten
:dd.Sluit MakMan/2 af.
:edl.

:h1 res=2105.Menu Opties
:i1.Menu Opties
:dl break=all.
:dt.Tegelset
:dd.Kiest de afbeeldingen van het doolhof en de figuren&colon. Klassiek, 3D-Stijl of Fufitos. De tegelset kan alleen worden gewijzigd als er geen spel bezig is.
:dt.Besturing
:dd.Kiest Toetsenbord of een joystick (Joystick A of B) en kalibreert de joystick.
:dt.Geluid
:dd.Zet de geluidseffecten aan of uit.
:dt.Prioriteit
:dd.Stelt de prioriteit van het spel in (Normaal, Kritiek of Server). Gebruik Kritiek of Server alleen als het spel onregelmatig loopt op een druk systeem.
:dt.Taal
:dd.Wijzigt de taal van de menu's en van deze help (English, Espanol, Nederlands, Deutsch, Francais, Italiano).
:dt.Achtergrond Actief
:dd.Als dit uit staat, pauzeert het spel automatisch wanneer het venster de focus verliest.
:dt.Raambediening
:dd.Verbergt of toont de titelbalk en het menu. Druk nogmaals op Ctrl+F om ze weer te tonen.
:dt.Instellingen opslaan bij afsluiten
:dd.Als dit is aangevinkt, wat standaard zo is, worden de instellingen bij het afsluiten opgeslagen in MAKMAN.INI. De hoogste scores worden altijd opgeslagen.
:edl.

:h1 res=2106.Menu Help
:i1.Menu Help
:dl break=all.
:dt.Helpindex
:dd.Toont de index van deze help.
:dt.Algemene help
:dd.Toont de algemene help, beginnend bij het eerste onderwerp.
:dt.Help gebruiken
:dd.Legt uit hoe het helpvenster werkt.
:dt.Over MakMan/2
:dd.Toont versie- en auteursinformatie.
:edl.

:h1 res=2107.Opdrachtregel
:i1.Opdrachtregel
:p.
MakMan/2 gebruikt standaard GPI-graphics. Een parameter op de opdrachtregel kiest de grafische modus&colon.
:dl break=all.
:dt.makman
:dd.GPI-graphics (standaard, aanbevolen).
:dt.makman gpi
:dd.Hetzelfde als hierboven.
:dt.makman dive
:dd.DIVE-graphics. Vereist een DIVE-compatibel beeldschermstuurprogramma.
:edl.

:h1 res=2108.Copyright
:i1.Copyright
:p.
MakMan/2 versie 1.1
:p.
Copyright (C) 1995 Markellos J. Diorinos. Open Watcom-port en verbeteringen, 2026.
:p.
Uitgebracht als open source onder de GNU General Public License versie 3. Zie doc\License.txt.
:p.
Deze software wordt geleverd zoals ze is, zonder enige garantie.

:euserdoc.
