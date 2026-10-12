.* MakMan/2 help - it
:userdoc.

:h1 res=2100.Informazioni su MakMan/2
:i1.Informazioni su MakMan/2
:p.
MakMan/2 e un gioco di labirinto nello stile di PacMan per OS/2 e ArcaOS. E stato scritto nel 1995 da Markellos J. Diorinos; questa versione e un port Open Watcom con menu in sei lingue, scorciatoie da tastiera, guida in linea e impostazioni salvate.
:p.
Guida MakMan nel labirinto, mangia tutti i punti ed evita i fantasmi.
:p.
Altre informazioni&colon.
:p.
:link reftype=hd res=2101.Come giocare:elink.
.br
:link reftype=hd res=2102.Comandi:elink.
.br
:link reftype=hd res=2103.Punteggio:elink.
.br
:link reftype=hd res=2104.Menu Gioco:elink.
.br
:link reftype=hd res=2105.Menu Opzioni:elink.
.br
:link reftype=hd res=2106.Menu Guida:elink.
.br
:link reftype=hd res=2107.Riga di comando:elink.
.br
:link reftype=hd res=2108.Copyright:elink.


:h1 res=2101.Come giocare
:i1.Come giocare
:ul compact.
:li.Scegli Nuovo dal menu Gioco (Ctrl+N) per iniziare una partita. MakMan inizia con tre vite, mostrate come piccole figure di MakMan in alto a sinistra del labirinto. Il punteggio e in alto a destra.
:li.Mangia tutti i punti piccoli del labirinto per completare il livello. Segue un nuovo livello.
:li.I fantasmi inseguono MakMan. Toccare un fantasma costa una vita. Quando l'ultima vita e persa, la partita e finita.
:li.I punti grandi lampeggianti sono punti potenza. Dopo averne mangiato uno, i fantasmi possono essere mangiati per breve tempo e danno punti. I fantasmi hanno un aspetto diverso finche possono essere mangiati.
:li.Ogni tanto appare un frutto nel labirinto. Mangialo prima che scompaia per ottenere punti bonus.
:li.Metti in pausa la partita con Ctrl+P e interrompila con Ctrl+Q.
:li.Quando non c'e una partita in corso viene mostrata la classifica. Si conservano i 15 punteggi migliori; se il tuo punteggio rientra, alla fine della partita ti viene chiesto il nome.
:eul.

:h1 res=2102.Comandi
:i1.Comandi
:p.
Per impostazione predefinita le frecce sinistra, destra, su e giu muovono MakMan. Opzioni - Assegnazione tasti... apre una finestra in cui scegli il tasto per ogni direzione (pagina Tastiera) e configuri un joystick (pagina Joystick)&colon. attiva Attiva joystick, scegli Joystick A o B, assegna a ogni direzione un pulsante del joystick o una direzione della leva e usa Calibra A / B per impostare il centro della leva. Tastiera e joystick funzionano insieme. L'assegnazione viene salvata con le altre impostazioni.
:p.
:dl break=all.
:dt.Frecce
:dd.Muovono MakMan.
:dt.Ctrl+N
:dd.Nuova partita.
:dt.Ctrl+P
:dd.Pausa / riprendi.
:dt.Ctrl+Q
:dd.Interrompi la partita in corso.
:dt.Ctrl+X
:dd.Esci da MakMan/2.
:dt.Ctrl+B
:dd.Sfondo Attivo si / no.
:dt.Ctrl+F
:dd.Controlli Cornice - nascondi / mostra la barra del titolo e il menu.
:dt.F1
:dd.Guida.
:edl.

:h1 res=2103.Punteggio
:i1.Punteggio
:dl break=all.
:dt.Punto piccolo
:dd.10 punti.
:dt.Punto potenza
:dd.50 punti.
:dt.Fantasmi mangiati con un punto potenza
:dd.200, 400, 800 e 1600 punti, uno dopo l'altro.
:dt.Frutto
:dd.Il valore appare quando viene mangiato e dipende dal livello.
:dt.Vita extra
:dd.A 10000 punti, poi a 20000, 40000 e cosi via (raddoppia ogni volta).
:edl.

:h1 res=2104.Menu Gioco
:i1.Menu Gioco
:dl break=all.
:dt.Nuovo
:dd.Inizia una nuova partita.
:dt.Pausa Gioco
:dd.Mette in pausa la partita, o la riprende se e gia in pausa. Disponibile solo durante una partita.
:dt.Esci dal Gioco
:dd.Interrompe la partita in corso e torna alla schermata della classifica. Disponibile solo durante una partita.
:dt.Esci
:dd.Chiude MakMan/2.
:edl.

:h1 res=2105.Menu Opzioni
:i1.Menu Opzioni
:dl break=all.
:dt.Set di Tessere
:dd.Sceglie la grafica del labirinto e dei personaggi&colon. Classico, 3D o Fufitos. Il set di tessere si puo cambiare solo quando non c'e una partita in corso.
:dt.Assegnazione tasti
:dd.Apre la finestra di assegnazione dei tasti&colon. tasti per le quattro direzioni, scelta del joystick, pulsanti e calibrazione.
:dt.Suono
:dd.Attiva o disattiva gli effetti sonori.
:dt.Priorita
:dd.Imposta la priorita del gioco (Normale, Critico o Server). Usa Critico o Server solo se il gioco procede a scatti su un sistema carico.
:dt.Lingua
:dd.Cambia la lingua dei menu e delle finestre di dialogo. Le lingue sono i file nella cartella lang (English, Espanol, Nederlands, Deutsch, Francais, Italiano, Japanese, Chinese, Korean, Russian, Greek). Questa guida esiste nelle prime sei lingue; per le altre viene mostrata la guida in inglese.
:dt.Sfondo Attivo
:dd.Se e disattivato, la partita va in pausa automaticamente quando la finestra perde il fuoco.
:dt.Controlli Cornice
:dd.Nasconde o mostra la barra del titolo e il menu. Premi di nuovo Ctrl+F per mostrarli.
:dt.Salva impostazioni all'uscita
:dd.Se e selezionato, come per impostazione predefinita, le impostazioni vengono salvate in MAKMAN.INI all'uscita. La classifica viene sempre salvata.
:edl.

:h1 res=2106.Menu Guida
:i1.Menu Guida
:dl break=all.
:dt.Indice dell'aiuto
:dd.Mostra l'indice di questa guida.
:dt.Aiuto generale
:dd.Mostra la guida generale, a partire dal primo argomento.
:dt.Usare l'aiuto
:dd.Spiega come usare la finestra della guida.
:dt.Informazioni su MakMan/2
:dd.Mostra la versione e le informazioni sull'autore.
:edl.

:h1 res=2107.Riga di comando
:i1.Riga di comando
:p.
MakMan/2 usa la grafica GPI per impostazione predefinita. Un parametro sulla riga di comando sceglie la modalita grafica&colon.
:dl break=all.
:dt.makman
:dd.Grafica GPI (predefinita, consigliata).
:dt.makman gpi
:dd.Uguale a sopra.
:dt.makman dive
:dd.Grafica DIVE. Richiede un driver video compatibile con DIVE.
:dt.makman -plainmenus
:dd.Le voci di menu non vengono mai disegnate dal programma; i caratteri assenti nella tabella codici appaiono come ?.
:dt.makman -unicodemenus
:dd.Tutte le voci di menu sono disegnate con testo Unicode (normalmente solo quelle che ne hanno bisogno).
:edl.

:h1 res=2108.Copyright
:i1.Copyright
:p.
MakMan/2 versione 1.3
:p.
Copyright (C) 1995 Markellos J. Diorinos. Port Open Watcom e miglioramenti, 2026.
:p.
Rilasciato come open source con la GNU General Public License versione 3. Vedi doc\License.txt.
:p.
Questo software e fornito cosi com'e, senza garanzie di alcun tipo.

:euserdoc.
