ajusteBayes<-function(triple, accion, ronda, valorJugada)
{
prob<-read.csv("prob.csv",header=TRUE,row.names = NULL)
p1=triple[1]
p2=triple[2]
p3=triple[3]
if(ronda==1)
{
  data<-read.csv("tablasprobpreflop.csv",header=TRUE,row.names = NULL)
}
else
{
data<-read.csv("tablasprobpostflop.csv",header=TRUE,row.names = NULL)
}
if(accion!=0)
{
a=accion+1
pm<-prob[1,1]
pma<-data[1,a]
pr<-prob[2,1]
pra<-data[2,a]
pc<-prob[3,1]
pca<-data[3,a]
maniaco<-(pm*pma)/(pm*pma + (1-pm)*(pra+pca))
roca<-(pr*pra)/(pr*pra + (1-pr)*(pma+pca))
calling<-(pc*pca)/(pc*pca + (1-pc)*(pra+pma))
dif<-0
sum<-0
if(maniaco == 1)
{
  mb=1
  rb=0
  cb=0
}
else if(maniaco>roca && maniaco>calling)
  {
  mb=1
  rb=0
  cb=0
}

else if(roca==1)
{mb=0
rb=1
cb=0}
else if(roca>maniaco&&roca>calling)
{mb=0
rb=1
cb=0}
else if(calling==1)
{mb=0
rb=0
cb=1}
else if(calling>roca && calling>maniaco)
{mb=0
rb=0
cb=1}
if(mb==1)
{
    if(ronda == 1)
    {
      if(valorJugada>6)
      {
        p1<-triple[1]*0.6
        p2<-triple[2]+triple[1]*0.2
        p3<-triple[3]+triple[1]*0.2
      }
      else
      {
        p1<-triple[1]+triple[2]*0.2+triple[3]*0.2
        p2<-triple[2]*0.8
        p3<-triple[3]*0.8
      }
    }
    else
    {
      if(valorJugada>1)
      {
        p1<-triple[1]*0.6
        p2<-triple[2]+triple[1]*0.2
        p3<-triple[3]+triple[1]*0.2
      }
      else
      {
        p1<-triple[1]+triple[2]*0.2+triple[3]*0.2
        p2<-triple[2]*0.8
        p3<-triple[3]*0.8
      }
    }
    dif=1-maniaco
    sum=roca+calling
    roca=(roca/sum)*dif
    calling=(calling/sum)*dif
  }
if(rb==1)
{
      if(accion==2)
      {
        if(ronda==1)
         { 
          if(jugada>7)
          {
          p1<-triple[1]*0.6
          p2<-triple[2]+triple[1]*0.2
          p3<-triple[3]+triple[1]*0.2
         }
         else
         {
          p1<-triple[1]+triple[2]*0.2+triple[3]*0.2
          p2<-triple[2]*0.8
          p3<-triple[3]*0.8
         }
        }
        else
        {
          if(jugada>4)
          {
            p1<-triple[1]*0.6
            p2<-triple[2]+triple[1]*0.2
            p3<-triple[3]+triple[1]*0.2
          }
          else
          {
            p1<-triple[1]+triple[2]*0.2+triple[3]*0.2
            p2<-triple[2]*0.8
            p3<-triple[3]*0.8
          }
        }
      }
      else
      {
        p1<-triple[1]*0.6
        p2<-triple[2]+triple[1]*0.2
        p3<-triple[3]+triple[1]*0.2
      }
    dif=1-roca
    sum=maniaco+calling
    maniaco=(maniaco/sum)*dif
    calling=(calling/sum)*dif
    
}
if(cb==1)
{
    if(ronda == 1)
    {
      if(valorJugada>5)
      {
        p1<-triple[1]*0.6
        p2<-triple[2]+triple[1]*0.2
        p3<-triple[3]+triple[1]*0.2
      }
      else
      {
        p1<-triple[1]+triple[2]*0.2+triple[3]*0.2
        p2<-triple[2]*0.8
        p3<-triple[3]*0.8
      }
    }
    else
    {
      if(valorJugada>1)
      {
        p1<-triple[1]*0.6
        p2<-triple[2]+triple[1]*0.2
        p3<-triple[3]+triple[1]*0.2
      }
      else
      {
        p1<-triple[1]+triple[2]*0.2+triple[3]*0.2
        p2<-triple[2]*0.8
        p3<-triple[3]*0.8
      }
    }
    dif=1-calling
    sum=roca+maniaco
    roca=(roca/sum)*dif
    maniaco=(maniaco/sum)*dif
}
prob[1,1]<-maniaco
prob[2,1]<-roca
prob[3,1]<-calling
}
ajuste<-c(p1,p2,p3)
write.csv(prob,"prob.csv",row.names = FALSE)
return(ajuste)

}