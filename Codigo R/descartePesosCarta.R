#Funcion para descartar los datos del framework Pesos de cualquier combinacion de cartas con dicha carta


descartePesosCarta<-function(carta,mazo,datos)
{
n_mazo<-nrow(mazo)
for(i in 1:n_mazo)
{
	if(mazo[i,1]>carta[1])
	{	
	mano<-rbind(as.numeric(mazo[i,]),carta)
	}
	else
	{
	mano<-rbind(carta,as.numeric(mazo[i,]))
	}
	datos<-modificaPesos(mano,datos,0)
}
return(datos)
}
