#Funcion para crear el framedata Pesos a partir de un archivo .csv

cargaPesos<-function()
{
data<-read.csv("data.csv",header=TRUE, row.names=1)
colnames(data)<-c(11:14,21:24,31:34,41:44)
return(data)
}
