#Funcion para calcular cada probabilidad de accion del oponente

calculoProbabilidadAccion<-function(mesa,mazo,triple,ronda)
{
prob<-read.csv("prob.csv",header=TRUE,row.names = NULL)
if(ronda==1)
{
  data<-read.csv("tablaspreflop.csv",header=TRUE,row.names = NULL)
}
else
{
  data<-read.csv("tablaspostflop.csv",header=TRUE,row.names = NULL)
}
combina<-combinaMazo(mazo)
n<-nrow(combina)

for(i in 1:n)
{
  mano_op<-fijarMano(combina[i,1],combina[i,2],combina[i,3],combina[i,4])
  value<-0

 if(prob[1,1]>prob[2,1])
 {
   if(prob[1,1]>prob[3,1])
   {
     if(ronda==1)
     {
       valor_op<-chenFormula(mano_op)
       if(valor_op>=3.5)
       {
         value=data[1,]
       }
       else
       {
         value=data[2,]
       }
     }
     else
     {
       value=data[1,]
     }
   }
 }
  
  if(prob[2,1]>prob[1,1])
  {
    if(prob[2,1]>prob[3,1])
    {
      if(ronda==1)
      {
        valor_op<-chenFormula(mano_op)
        if(valor_op>=12)
        {
          value=data[3,]
        }
        else if(valor_op>=7)
        {
          value=data[4,]
        }
        else
        {
          value=data[5,]
        }
      }
      else
      {
        jugada_op=ordenarCartas(mano_op,mesa)
        valor_op<-calcularJugada(jugada_op)
        if(valor_op>=7)
        {
          value=data[2,]
        }
        else if(valor_op>=2)
        {
          value=data[3,]
        }
        else
        {
          value=data[4,]
        }
      }
    }
  }
  if(prob[3,1]>prob[2,1])
  {
    if(prob[3,1]>prob[1,1])
    {
      if(ronda==1)
      {
        
          value=data[6,]
      }
      else
      {
        value=data[5,]
      }
    }
}
triple<-modificaTriple(mano_op,triple,value)
}
	
return (triple)
}