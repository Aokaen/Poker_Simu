#Funcion para convertir numeros en texto para manejo de tablas de peso
NumtoChar<-function(n1,n2)
{
if(n2>n1)
{
	total<-n2*100+n1
}
else
{
	total<-n1*100+n2
}
salida<-as.character(total)
return(salida)
}

