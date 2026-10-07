.* MakMan/2 help - fr
:userdoc.

:h1 res=2100.A propos de MakMan/2
:i1.A propos de MakMan/2
:p.
MakMan/2 est un jeu de labyrinthe dans le style de PacMan pour OS/2 et ArcaOS. Il a ete ecrit en 1995 par Markellos J. Diorinos ; cette version est un portage Open Watcom avec des menus en six langues, des raccourcis clavier, une aide en ligne et des reglages sauvegardes.
:p.
Guidez MakMan dans le labyrinthe, mangez tous les points et evitez les fantomes.
:p.
Plus d'informations &colon.
:p.
:link reftype=hd res=2101.Comment jouer:elink.
.br
:link reftype=hd res=2102.Commandes:elink.
.br
:link reftype=hd res=2103.Score:elink.
.br
:link reftype=hd res=2104.Menu Jeu:elink.
.br
:link reftype=hd res=2105.Menu Options:elink.
.br
:link reftype=hd res=2106.Menu Aide:elink.
.br
:link reftype=hd res=2107.Ligne de commande:elink.
.br
:link reftype=hd res=2108.Copyright:elink.


:h1 res=2101.Comment jouer
:i1.Comment jouer
:ul compact.
:li.Choisissez Nouveau dans le menu Jeu (Ctrl+N) pour commencer une partie. MakMan commence avec trois vies, affichees sous forme de petites figures de MakMan en haut a gauche du labyrinthe. Le score est affiche en haut a droite.
:li.Mangez tous les petits points du labyrinthe pour terminer le niveau. Un nouveau niveau suit.
:li.Les fantomes poursuivent MakMan. Toucher un fantome coute une vie. Quand la derniere vie est perdue, la partie est terminee.
:li.Les gros points clignotants sont des points de puissance. Apres en avoir mange un, les fantomes peuvent etre manges pendant un court moment et rapportent des points. Les fantomes changent d'aspect tant qu'ils peuvent etre manges.
:li.De temps en temps, un fruit apparait dans le labyrinthe. Mangez-le avant qu'il ne disparaisse pour gagner des points bonus.
:li.Mettez la partie en pause avec Ctrl+P et arretez-la avec Ctrl+Q.
:li.Quand aucune partie n'est en cours, le tableau des meilleurs scores est affiche. Les 15 meilleurs scores sont conserves ; si votre score en fait partie, votre nom vous est demande a la fin de la partie.
:eul.

:h1 res=2102.Commandes
:i1.Commandes
:p.
Au clavier, les fleches gauche, droite, haut et bas deplacent MakMan. Pour utiliser un joystick, choisissez Joystick A ou Joystick B dans Options - Controles ; vous pouvez aussi l'y calibrer. Tant qu'un joystick est actif, le clavier ne dirige pas MakMan.
:p.
:dl break=all.
:dt.Fleches
:dd.Deplacent MakMan.
:dt.Ctrl+N
:dd.Nouvelle partie.
:dt.Ctrl+P
:dd.Pause / reprise.
:dt.Ctrl+Q
:dd.Arreter la partie en cours.
:dt.Ctrl+X
:dd.Quitter MakMan/2.
:dt.Ctrl+B
:dd.Arriere-plan Actif oui / non.
:dt.Ctrl+F
:dd.Controles Cadre - masquer / afficher la barre de titre et le menu.
:dt.F1
:dd.Aide.
:edl.

:h1 res=2103.Score
:i1.Score
:dl break=all.
:dt.Petit point
:dd.10 points.
:dt.Point de puissance
:dd.50 points.
:dt.Fantomes manges avec un point de puissance
:dd.200, 400, 800 puis 1600 points, l'un apres l'autre.
:dt.Fruit
:dd.La valeur apparait quand il est mange et depend du niveau.
:dt.Vie supplementaire
:dd.A 10000 points, puis a 20000, 40000, etc. (le double a chaque fois).
:edl.

:h1 res=2104.Menu Jeu
:i1.Menu Jeu
:dl break=all.
:dt.Nouveau
:dd.Demarre une nouvelle partie.
:dt.Pause Jeu
:dd.Met la partie en pause, ou la reprend si elle est deja en pause. Disponible seulement pendant une partie.
:dt.Quitter Jeu
:dd.Arrete la partie en cours et revient a l'ecran des meilleurs scores. Disponible seulement pendant une partie.
:dt.Sortir
:dd.Ferme MakMan/2.
:edl.

:h1 res=2105.Menu Options
:i1.Menu Options
:dl break=all.
:dt.Jeu de Carreaux
:dd.Choisit les graphismes du labyrinthe et des personnages&colon. Classique, 3D ou Fufitos. Le jeu de carreaux ne peut etre change que lorsqu'aucune partie n'est en cours.
:dt.Controles
:dd.Choisit Clavier ou un joystick (Joystick A ou B) et calibre le joystick.
:dt.Son
:dd.Active ou desactive les effets sonores.
:dt.Priorite
:dd.Definit la priorite du jeu (Normale, Critique ou Serveur). N'utilisez Critique ou Serveur que si le jeu saccade sur un systeme charge.
:dt.Langue
:dd.Change la langue des menus et de cette aide (English, Espanol, Nederlands, Deutsch, Francais, Italiano).
:dt.Arriere-plan Actif
:dd.Si cette option est desactivee, la partie se met automatiquement en pause quand la fenetre perd le focus.
:dt.Controles Cadre
:dd.Masque ou affiche la barre de titre et le menu. Appuyez de nouveau sur Ctrl+F pour les afficher.
:dt.Sauver les reglages a la sortie
:dd.Si elle est cochee, ce qui est le cas par defaut, les reglages sont sauvegardes dans MAKMAN.INI a la sortie. Les meilleurs scores sont toujours sauvegardes.
:edl.

:h1 res=2106.Menu Aide
:i1.Menu Aide
:dl break=all.
:dt.Index de l'aide
:dd.Affiche l'index de cette aide.
:dt.Aide generale
:dd.Affiche l'aide generale, en commencant par le premier sujet.
:dt.Utiliser l'aide
:dd.Explique comment utiliser la fenetre d'aide.
:dt.A propos de MakMan/2
:dd.Affiche la version et les informations sur l'auteur.
:edl.

:h1 res=2107.Ligne de commande
:i1.Ligne de commande
:p.
MakMan/2 utilise par defaut les graphismes GPI. Un parametre sur la ligne de commande choisit le mode graphique &colon.
:dl break=all.
:dt.makman
:dd.Graphismes GPI (par defaut, recommande).
:dt.makman gpi
:dd.Identique a ci-dessus.
:dt.makman dive
:dd.Graphismes DIVE. Necessite un pilote d'affichage compatible DIVE.
:edl.

:h1 res=2108.Copyright
:i1.Copyright
:p.
MakMan/2 version 1.1
:p.
Copyright (C) 1995 Markellos J. Diorinos. Portage Open Watcom et ameliorations, 2026.
:p.
Diffuse en logiciel libre sous la licence GNU General Public License version 3. Voir doc\License.txt.
:p.
Ce logiciel est fourni tel quel, sans garantie d'aucune sorte.

:euserdoc.
