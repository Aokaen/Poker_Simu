igualaTriple<-function(original,nuevo)
{
  n_ori=nrow(original)
  n_nue=nrow(nuevo)
  j=1
    for(i in 1:n_ori)
    {if(j<=n_nue)
     { if(original[i,1]==nuevo[j,1])
      {
        if(original[i,2]==nuevo[j,2])
        {
          if(original[i,3]==nuevo[j,3])
          {
            if(original[i,4]==nuevo[j,4])
            {
              original[i,5]<-nuevo[j,5]
              original[i,6]<-nuevo[j,6]
              original[i,7]<-nuevo[j,7]
              j=j+1
            }
          }
        }
      }
     }
    }
  return(original)
}