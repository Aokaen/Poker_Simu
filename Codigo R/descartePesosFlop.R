#Funcion para descartar los datos del framedata Pesos con las cartas del Flop


descartePesosFlop<-function(mesa,mazo,datos)
{
mazo1<-rbind(mazo,mesa[2,],mesa[3,])
datos<-descartePesosCarta(mesa[1,],mazo,datos)
n_mazo<-nrow(mazo1)
mazo1<-mazo1[-n_mazo,]
datos<-descartePesosCarta(mesa[2,],mazo,datos)
n_mazo<-nrow(mazo1)
mazo1<-mazo1[-n_mazo,]
datos<-descartePesosCarta(mesa[3,],mazo,datos)
return(datos)
}