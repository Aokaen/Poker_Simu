#Funcion para, en rondas posteriores al Flop, actualizar el valor del atributo mesa
#con la nueva carta

fijarMesaPostflop<-function(mesa,n1,p1)
{
mesa<-rbind(mesa,c(n1,p1))
return(mesa)
}