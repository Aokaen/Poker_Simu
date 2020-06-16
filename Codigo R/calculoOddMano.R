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
	mesaaux<-rbind(mesa,c(as.numeric(mazo[i,1]),as.numeric(mazo[i,2])))
	jugada_aux<-ordenarCartas(mano,mesaaux)
	valorjugador_aux<-calcularJugada(jugada_aux)
	if(valorjugador<valorjugador_aux)
	{
	cartamejora=cartamejora+1
	}

}

OddMano=cartamejora/n_mazo
return(OddMano)
}
