# Poker_Simu
 
EXPLICACION DE LOS ARCHIVOS
Carpeta Memoria: Incluye la Memoria del Proyecto
Carpeta R: Incluye todo el código R de la implementación del algoritmo
Carpeta Debug: incluye todos los archivos de depuracion de Visual Studio

Carta.h/Carta.cpp: Incluye las funciones relativas a una única carta (Asignar su valor, asignar su palo e imprimirla por pantalla)
Jugador.h/Jugador.cpp: Incluye las funciones relativas al jugador (modificar su Mano, calcular el valor de su jugada y establecer Dinero y apuestas)
Mesa.h/Mesa.cpp: Incluye las funciones relativas a la mesa de juego: creación de Mazo, su aleatorización y el reparto de cartas; gestión de los índices de ronda y cálculo de la apuesta total. También incluye las funciones de representación gráfica.
Poker_Simu.cpp: Incluye las funciones relativas al flujo de juego: funcionamiento de las rondas, procesos de apuestas y determinar ganador.

Inicio de la partida:
1ºElegir el modo de juego: introducir por teclado "J" si se quiere jugar Jugador contra Algoritmo  o introducir "A" para jugar Algoritmo contra algoritmo.
	1º.a) Si se eligió el modo Algoritmo contra Algoritmo, elegir cuál de los tres algoritmos.
2ºIntroducir el importe inicial de dinero para ambos jugadores así como el importe que será la Ciega Grande.

Desarrollo de la partida (Jugador Contra Algoritmo):
*Se muestra por pantalla las cartas de cuya información dispone el jugador en este formato:
NP
Siendo N el valor de la carta (2, 3, 4, 5, 6, 7, 8, 9,T para el valor de 10, J, Q, K o A) y P la inicial del palo de la carta (Treboles, Picas, Diamantes y Corazones).

*Por pantalla también se muestra el dinero restante de cada jugador, la apuesta total y el valor numérico de la mejor jugada disponible.
a) Se le pedirá al jugador la entrada de su acción:
	1º Se pedirá al jugador si desea Apostar (introduciendo una "A") o Pasar (introduciendo una "P").
	2º Si se ha elegido la opción de Pasar, se acaba la ronda, si no, se habré una nueva elección posible: Subir la apuesta (introduciendo una "S") o Ver la apuesta (introduciendo una "V").
	3º Si se ha elegido Subir la apuesta, se pide que se introduzca una apuesta numérica, que será la nueva apuesta del jugador. Esta nueva apuesta debe ser mayor a la apuesta del oponente.
*Si el algorimo decide Subir la apuesta, se debe repetir el paso a) hasta que tanto jugador como oponente tengan la misma apuesta.

Este proceso se repite durante las 4 rondas de apuestas (Preflop, Flop, Turn y River).
Tras el River, y si ambos jugadores han Visto la apuesta, se produce el Showdown donde se determina el ganador de la Ronda.
Después se pide al jugador si desea seguir jugando (Y) o si desea parar el juego (N).

Si, durante las apuestas, al menos uno de los dos participantes en el juego (jugador y/u oponente) intentan apostar más dinero del que disponen, se produce un All In, donde apuestan todo el dinero del que disponen.
Tras un All in, si el dinero de uno de los participantes es 0, el otro participante gana la partida y se da por finalizado el juego.