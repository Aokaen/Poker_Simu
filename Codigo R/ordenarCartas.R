#funcion para juntar y ordenar las cartas de mano y mesa en una única jugada

ordenarCartas<-function(Mano,Mesa)
{
jugada<-rbind(Mano,Mesa)
tamano<-nrow(jugada)
a<-tamano-1
b<-tamano
for(i in 1:a)
{
for(j in i:b)
{
if(jugada[i,1]<jugada[j,1])
{
aux<-jugada[i,]
jugada[i,]<-jugada[j,]
jugada[j,]<-aux
}
}
}
return(jugada)

}

