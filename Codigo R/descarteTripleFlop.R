#Funcion para descartar los datos del framedata Triple Probabilidad con las cartas del Flop


descarteTripleFlop<-function(mesa,mazo,datos)
{
mazo1<-rbind(mazo,mesa[2,],mesa[3,])
datos<-descarteTripleCarta(mesa[1,],mazo,datos)
n_mazo<-nrow(mazo1)
mazo1<-mazo1[-n_mazo,]
datos<-descarteTripleCarta(mesa[2,],mazo,datos)
n_mazo<-nrow(mazo1)
mazo1<-mazo1[-n_mazo,]
datos<-descarteTripleCarta(mesa[3,],mazo,datos)
return(datos)
}