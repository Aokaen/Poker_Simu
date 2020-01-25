
#funcion para generar cartas aleatorias de un mazo dado
ncartasRandom<-function(n,mazo)
{
n_mazo<-nrow(mazo)
return(mazo[sample(1:n_mazo,n,replace=F),])
}

