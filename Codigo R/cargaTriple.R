#Funcion para crear el framedata "Triple Probabilidad" a partir de un .csv

cargaTriple<-function()
{
data<-read.csv("triple.csv",header=TRUE,row.names=1)
colnames(data)<-c("Num1","Palo1","Num2","Palo2","Pasar","Ver","Subir")
return(data)
}
