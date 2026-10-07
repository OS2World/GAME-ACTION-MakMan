.* MakMan/2 help - es
:userdoc.

:h1 res=2100.Acerca de MakMan/2
:i1.Acerca de MakMan/2
:p.
MakMan/2 es un juego de laberinto al estilo de PacMan para OS/2 y ArcaOS. Fue escrito en 1995 por Markellos J. Diorinos; esta version es un port con Open Watcom con menus en seis idiomas, atajos de teclado, ayuda en linea y ajustes guardados.
:p.
Guia a MakMan por el laberinto, come todos los puntos y mantente lejos de los fantasmas.
:p.
Mas informacion&colon.
:p.
:link reftype=hd res=2101.Como jugar:elink.
.br
:link reftype=hd res=2102.Controles:elink.
.br
:link reftype=hd res=2103.Puntuacion:elink.
.br
:link reftype=hd res=2104.Menu Juego:elink.
.br
:link reftype=hd res=2105.Menu Opciones:elink.
.br
:link reftype=hd res=2106.Menu Ayuda:elink.
.br
:link reftype=hd res=2107.Linea de comandos:elink.
.br
:link reftype=hd res=2108.Copyright:elink.


:h1 res=2101.Como jugar
:i1.Como jugar
:ul compact.
:li.Elige Nuevo en el menu Juego (Ctrl+N) para empezar una partida. MakMan empieza con tres vidas, que se muestran como pequenas figuras de MakMan arriba a la izquierda del laberinto. La puntuacion se muestra arriba a la derecha.
:li.Come todos los puntos pequenos del laberinto para completar el nivel. Despues sigue un nuevo nivel.
:li.Los fantasmas persiguen a MakMan. Tocar un fantasma cuesta una vida. Cuando se pierde la ultima vida, la partida termina.
:li.Los puntos grandes parpadeantes son puntos de poder. Despues de comer uno, los fantasmas se pueden comer durante un tiempo corto y dan puntos. Los fantasmas tienen otro aspecto mientras se pueden comer.
:li.De vez en cuando aparece una fruta en el laberinto. Comela antes de que desaparezca para ganar puntos extra.
:li.Pausa la partida con Ctrl+P y detenla con Ctrl+Q.
:li.Cuando no hay ninguna partida en curso se muestra la tabla de mejores puntuaciones. Se guardan las 15 mejores; si tu puntuacion entra, al final de la partida se te pide tu nombre.
:eul.

:h1 res=2102.Controles
:i1.Controles
:p.
Con el teclado, las flechas izquierda, derecha, arriba y abajo mueven a MakMan. Para usar un joystick, elige Joystick A o Joystick B en Opciones - Controles; alli tambien se puede calibrar. Mientras un joystick esta activo, el teclado no dirige a MakMan.
:p.
:dl break=all.
:dt.Teclas de flecha
:dd.Mueven a MakMan.
:dt.Ctrl+N
:dd.Nueva partida.
:dt.Ctrl+P
:dd.Pausar / continuar.
:dt.Ctrl+Q
:dd.Terminar la partida actual.
:dt.Ctrl+X
:dd.Salir de MakMan/2.
:dt.Ctrl+B
:dd.Fondo Activo si / no.
:dt.Ctrl+F
:dd.Controles Marco - ocultar / mostrar la barra de titulo y el menu.
:dt.F1
:dd.Ayuda.
:edl.

:h1 res=2103.Puntuacion
:i1.Puntuacion
:dl break=all.
:dt.Punto pequeno
:dd.10 puntos.
:dt.Punto de poder
:dd.50 puntos.
:dt.Fantasmas comidos con un punto de poder
:dd.200, 400, 800 y 1600 puntos, uno tras otro.
:dt.Fruta
:dd.El valor aparece al comerla y depende del nivel.
:dt.Vida extra
:dd.A los 10000 puntos, luego a los 20000, 40000 y asi sucesivamente (se duplica cada vez).
:edl.

:h1 res=2104.Menu Juego
:i1.Menu Juego
:dl break=all.
:dt.Nuevo
:dd.Empieza una partida nueva.
:dt.Pausar Juego
:dd.Pausa la partida, o la reanuda si ya esta en pausa. Solo esta disponible mientras hay una partida en curso.
:dt.Terminar Juego
:dd.Detiene la partida actual y vuelve a la pantalla de mejores puntuaciones. Solo esta disponible mientras hay una partida en curso.
:dt.Salir
:dd.Cierra MakMan/2.
:edl.

:h1 res=2105.Menu Opciones
:i1.Menu Opciones
:dl break=all.
:dt.Conjunto de Fichas
:dd.Elige los graficos del laberinto y de los personajes&colon. Clasico, 3D o Fufitos. El conjunto de fichas solo se puede cambiar cuando no hay ninguna partida en curso.
:dt.Controles
:dd.Elige Teclado o un joystick (Joystick A o B) y calibra el joystick.
:dt.Sonido
:dd.Activa o desactiva los efectos de sonido.
:dt.Prioridad
:dd.Fija la prioridad del juego (Normal, Critica o Servidor). Usa Critica o Servidor solo si el juego va irregular en un sistema ocupado.
:dt.Idioma
:dd.Cambia el idioma de los menus y de esta ayuda (English, Espanol, Nederlands, Deutsch, Francais, Italiano).
:dt.Fondo Activo
:dd.Si esta desactivado, la partida se pausa automaticamente cuando la ventana pierde el foco.
:dt.Controles Marco
:dd.Oculta o muestra la barra de titulo y el menu. Pulsa Ctrl+F otra vez para mostrarlos de nuevo.
:dt.Guardar ajustes al salir
:dd.Si esta marcado, que es lo normal, los ajustes se guardan en MAKMAN.INI al salir. Las mejores puntuaciones se guardan siempre.
:edl.

:h1 res=2106.Menu Ayuda
:i1.Menu Ayuda
:dl break=all.
:dt.Indice de ayuda
:dd.Muestra el indice de esta ayuda.
:dt.Ayuda general
:dd.Muestra la ayuda general, empezando por el primer tema.
:dt.Usar la ayuda
:dd.Explica como usar la ventana de ayuda.
:dt.Acerca de MakMan/2
:dd.Muestra la version y los datos del autor.
:edl.

:h1 res=2107.Linea de comandos
:i1.Linea de comandos
:p.
MakMan/2 usa graficos GPI de forma predeterminada. Un parametro en la linea de comandos elige el modo grafico&colon.
:dl break=all.
:dt.makman
:dd.Graficos GPI (predeterminado, recomendado).
:dt.makman gpi
:dd.Igual que lo anterior.
:dt.makman dive
:dd.Graficos DIVE. Necesita un controlador de pantalla compatible con DIVE.
:edl.

:h1 res=2108.Copyright
:i1.Copyright
:p.
MakMan/2 version 1.1
:p.
Copyright (C) 1995 Markellos J. Diorinos. Port a Open Watcom y mejoras, 2026.
:p.
Publicado como codigo abierto bajo la Licencia Publica General GNU version 3. Vease doc\License.txt.
:p.
Este programa se ofrece tal cual, sin garantia de ningun tipo.

:euserdoc.
