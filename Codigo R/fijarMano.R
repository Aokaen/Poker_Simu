#Funcion para, dadas dos combinaciones de cartas, juntar un atributo mano
fijarMano<-function(n1,p1,n2,p2)
{
mano<-rbind(c(as.numeric(n1),as.numeric(p1)),c(as.numeric(n2),as.numeric(p2)))
return(mano)
}