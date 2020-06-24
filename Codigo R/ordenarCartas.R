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
  ni<-as.numeric(jugada[i,1])
  nj<-as.numeric(jugada[j,1])
if(ni<nj)
{
aux<-jugada[i,]
jugada[i,]<-jugada[j,]
jugada[j,]<-aux
}
}
}
return(jugada)

}

