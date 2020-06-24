#Funcion para actualizar la tabla de probabilidad de algoritmo en caso de que se haya pasado una apuesta
accionBayes<-function(ronda,accion)
{

  prob<-read.csv("prob.csv",header=TRUE,row.names = NULL)

if(ronda==1)
{
  data<-read.csv("tablasprobpreflop.csv",header=TRUE,row.names = NULL)
}
else
{
  data<-read.csv("tablasprobpostflop.csv",header=TRUE,row.names = NULL)
}
pm<-prob[1,1]
if(is.na(pm))
{
  pm=0
}
pma<-data[1,accion]
pr<-prob[2,1]
pra<-data[2,accion]
pc<-prob[3,1]
pca<-data[3,accion]
if(is.na(pr))
{
  pr=0
}
if(is.na(pc))
{
  pc=0
}
maniaco<-(pm*pma)/(pm*pma + (1-pm)*(pra+pca))
roca<-(pr*pra)/(pr*pra + (1-pr)*(pma+pca))
calling<-(pc*pca)/(pc*pca + (1-pc)*(pra+pma))
prob[1,1]<-maniaco
prob[2,1]<-roca
prob[3,1]<-calling
write.csv(prob,"prob.csv",row.names = FALSE)
}