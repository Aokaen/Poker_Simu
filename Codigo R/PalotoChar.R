#Funcion para convertir palos en texto para manejo de tablas de peso
PalotoChar<-function(p1,p2)
{
total<-p1*10+p2
salida<-as.character(total)
return(salida)
}
