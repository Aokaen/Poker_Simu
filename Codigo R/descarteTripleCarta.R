#Funcion para descartar los datos del framework Triple probabilidad


descarteTripleCarta<-function(carta,mazo,datos)
{
n_mazo<-nrow(mazo)
ceros<-c(0,0,0)
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
	datos<-modificaTriple(mano,datos,ceros)
}
return(datos)
}