#Funcion para el cálculo de Odds de Mano

calculoOddMano<-function(mano,mesa,mazo)
{
cartamejora=0
jugada=ordenarCartas(mano,mesa)
valorjugador=calcularJugada(jugada)
n_mazo=nrow(mazo)
hj<-c(0,0,0)
for (i in 1:n_mazo)
{
	mesaaux<-rbind(mesa,mazo[i,])
	jugada_aux<-ordenarCartas(mano,mesaaux)
	valorjugador_aux<-calcularJugada(jugada_aux)
	if(valorjugador<valorjugador_aux)
	{
	cartamejora=cartamejora+1
	}

}
diferencia=n_mazo-cartamejora
OddMano=cartamejora/diferencia
return(OddMano)
}
