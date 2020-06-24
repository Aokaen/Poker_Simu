#Funcion para descartar los datos del framedata Pesos con las cartas del Flop


descartePesosFlop<-function(mesa,mazo,datos)
{
datos<-descartePesosCarta(mesa[1,],mazo,datos)
datos<-descartePesosCarta(mesa[2,],mazo,datos)
datos<-descartePesosCarta(mesa[3,],mazo,datos)
return(datos)
}