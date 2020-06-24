total=c(0,0)
bool=0
for(i in 1:91)
{
  for(j in 1:16)
  {
    peso=pesos[i,j]
    bool=0
    if(peso==0)
    {
      descarte=descarte+1
    }
    else
    {
      aceptado=aceptado+1
    }
    if(is.null(nrow(total)))
    {
      total=rbind(total,c(peso,1))
    }
    else
    {
      h=nrow(total)
      for (k in 1:h)
      {
        if(total[k,1]==peso)
        {
          total[k,2]=total[k,2]+1
          bool=1
        }
      }
      if(bool==0)
      {
       total= rbind(total,c(peso,1))
      }
    }
  }
}

total=total[-1,]