#Funcion para combinar las cartas del mazo

combinaMazo<-function(mazo)
{
combina<-c(0,0,0,0)
n_mazo<-nrow(mazo)
a<-n_mazo
b<-n_mazo-1
for(i in 1:b)
{
for(j in i:a)
{
if(mazo[i,1]!=mazo[j,1])
{
combina<-rbind(combina,c(mazo[i,],mazo[j,]))
}
if(mazo[i,1]==mazo[j,1])
{
if(mazo[i,2]!=mazo[j,2])
{
combina<-rbind(combina,c(mazo[i,],mazo[j,]))
}
}
}
}
combina<-combina[-1,]


return(combina)
}