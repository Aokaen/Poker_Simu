#Funcion para el calculo de Odds del bote

calculoOddsBote<-function(ap_jugador,ap_oponente)
{
diferencia=ap_oponente-ap_jugador
pot=ap_oponente+ap_jugador+diferencia
OddBote=diferencia/pot
return(OddBote)
}


