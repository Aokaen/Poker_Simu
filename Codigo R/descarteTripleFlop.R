#Funcion para descartar los datos del framedata Triple Probabilidad con las cartas del Flop


descarteTripleFlop<-function(mesa,mazo,datos)
{
datos<-descarteTripleCarta(mesa[1,],mazo,datos)
datos<-descarteTripleCarta(mesa[2,],mazo,datos)
datos<-descarteTripleCarta(mesa[3,],mazo,datos)
return(datos)
}