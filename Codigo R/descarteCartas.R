#funcion para descartar cartas conocidas del mazo
descarteCartas<-function(cartas,Mazo)
{
n_cartas<-nrow(cartas)
n_Mazo<-nrow(Mazo)

for(i in 1:n_Mazo)
{
ni<-Mazo[i,1]
pi<-Mazo[i,2]
for(j in 1:n_cartas)
{
nj<-cartas[j,1]
pj<-cartas[j,2]

if(ni==nj && pi==pj)
{
Mazo[i,]=NA

}
}
}
Mazo<-na.omit(Mazo)
return(Mazo)
}

