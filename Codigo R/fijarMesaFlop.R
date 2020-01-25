#Función para, recibiendo 3 cartas, formar un atributo mesa

fijarMesaFlop<-function(n1,p1,n2,p2,n3,p3)
{
mesa<-rbind(c(n1,p1),c(n2,p2),c(n3,p3))
return(mesa)
}