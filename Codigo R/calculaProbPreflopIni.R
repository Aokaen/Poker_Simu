calculaProbPreflopIni<-function(mano,mazo)
{
  
  valoresPreflop<-rbind(c(0,0.1,0.9),c(0,0.25,0.75),c(0.25,0.65,0.10),c(0.69,0.3,0.01),c(0.99,0.01,0))

  b<-0
  chen<-chenFormula(mano)
  if (chen>=12)
  {
    b=1
  }
  if (chen==11)
  {
    b=2
  }
  if (chen ==10)
  {
    b=2
  }
  if(chen<10)
  {
    if (chen>5)
    {
      b=3
    }
  }
  
  if(chen ==5)
  {
    if(mano[1,1]==mano[2,1])
    {
      b=3
    }
    else
    {
      b=4
    }
  }
  if (chen<5)
  {
    if(chen>=3.5)
    {
    b=4
    }
    else
    {
      b=5
    }
  }
  prob<-valoresPreflop[b,]		
  salida<-ajusteBayes(prob, 0, 1, chen)
  
  return(salida)
  
  
}
