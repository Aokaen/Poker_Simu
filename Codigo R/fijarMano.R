#Funcion para, dadas dos combinaciones de cartas, juntar un atributo mano
fijarMano<-function(n1,p1,n2,p2)
{
mano<-rbind(c(n1,p1),c(n2,p2))
return(mano)
}