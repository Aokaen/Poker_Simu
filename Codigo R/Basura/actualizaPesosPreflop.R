actualizaPesos<-function(mazo,pesos,triple,accion)
{
n_mazo<-nrow(mazo)
modif<-pesos

if(accion==0)
{
a=1
}
if(accion==1)
{
a=2
}
if(accion==2)
{
a=3
}
parejas<-combinaMazo(mazo)
n_parejas<-nrow(parejas)

for(i in 1:n_parejas)
{
mano<-rbind(c(parejas[i,1],parejas[i,2]),c(parejas[i,3],parejas[i,4]))
tripleMano<-leerTriple(mano,triple)
valorTriple<-tripleMano[a]
valor<-leerPesos(mano,modif)		
valor=valor*valorTriple
modif<-modificaPesos(mano,modif,valor)		
}
return(modif)
}