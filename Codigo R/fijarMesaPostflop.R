#Funcion para, en rondas posteriores al Flop, actualizar el valor del atributo mesa
#con la nueva carta

fijarMesaPostflop<-function(mesa,n1,p1)
{
mesa<-rbind(mesa,c(as.numeric(n1),as.numeric(p1)))
return(mesa)
}