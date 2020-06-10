#Función para, recibiendo 3 cartas, formar un atributo mesa

fijarMesaFlop<-function(n1,p1,n2,p2,n3,p3)
{
mesa<-rbind(c(as.numeric(n1),as.numeric(p1)),c(as.numeric(n2),as.numeric(p2)),c(as.numeric(n3),as.numeric(p3)))
return(mesa)
}