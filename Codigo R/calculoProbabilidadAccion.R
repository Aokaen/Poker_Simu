#Funcion para calcular cada probabilidad de accion del oponente

calculoProbabilidadAccion<-function(mesa,mazo,triple,ronda)
{
  prob<-read.csv("prob.csv",header=TRUE,row.names = NULL)
  if(ronda==1)
  {
    data<-read.csv("tablaspreflop.csv",header=TRUE,row.names = NULL)
  }else{
    data<-read.csv("tablaspostflop.csv",header=TRUE,row.names = NULL)
  }
  combina<-combinaMazo(mazo)
  n<-nrow(combina)
  triple_aux<-c(0,0,0,0,0,0,0)
  
  if(is.na(prob[1,1]))
  {
    pm=0
  }
  else
  {
    pm=prob[1,1]
  }
  if(is.na(prob[2,1]))
  {
    pr=0
  }
  else
  {
    pr=prob[2,1]
  }
  if(is.na(prob[3,1]))
  {
    pc=0
  }
  else
  {
    pc=prob[3,1]
  }
  if(pm == 1)
  {
    mb=1
    rb=0
    cb=0
  }
  else if(pr==1)
  {mb=0
  rb=1
  cb=0}
  else if(pc==1)
  {mb=0
  rb=0
  cb=1}
  else if(prob[1,1]>prob[2,1] && prob[1,1]>prob[3,1])
  {
    mb=1
    rb=0
    cb=0
  }
  else if(prob[2,1]>prob[1,1]&&prob[2,1]>prob[3,1])
  {mb=0
  rb=1
  cb=0}
  
  else if(prob[3,1]>prob[2,1] && prob[3,1]>prob[1,1])
  {mb=0
  rb=0
  cb=1}
  for(i in 1:n)
  {
    mano_op<-fijarMano(combina[i,1],combina[i,2],combina[i,3],combina[i,4])
    value<-0
    
    if(mb==1)
    {
      if(ronda==1)
      {
        valor_op<-chenFormula(mano_op)
        if(valor_op>=12)
        {
          value=data[1,]
        }
        else if(valor_op>=10)
        {
          value=data[2,]
        }
        else if(valor_op==9)
        {
          value=data[3,]
        }
        else if(valor_op==8)
        {
          if(mano_op[1,2]==mano_op[2,2])
          {
            if(mano_op[1,1]==14 || mano_op[2,1]==14)
            {
              value=data[3,]
            }else{
              value=data[4,]
            }
          }else{
            value=data[4,]
          }
        }
        else if(valor_op>6)
        {
          value=data[5,]
        }
        else if(valor_op==6)
        {
          if(mano_op[1,2]==mano_op[2,2])
          {
            if(mano_op[1,1]==12 || mano_op[2,1]==12)
            {
              value=data[5,]
            }else{
              value=data[6,]
            }
          }else{
            value=data[6,]
          }
        }
        else if(valor_op==5.5)
        {
          value=data[6,]
        }
        else if(valor_op==5)
        {
          if(mano_op[1,1]==mano_op[2,1] && mano_op[2,1]==5)
          {
            value=data[6,]
          }
          else if(mano_op[1,1]==mano_op[2,1] && mano_op[2,1]!=5)
          {
            value=data[7,]
          }
          else if(mano_op[1,2]==mano_op[2,2])
          {
            if((mano_op[1,1]==9 && mano_op[2,1]==6)||((mano_op[2,1]==9 && mano_op[1,1]==6)))
            {
              value=data[8,]
            }
            else
            {
              value=data[7,]
            }
          }
          else
          {
            if(abs(mano_op[1,1]-mano_op[2,1])>5)
            {
              value=data[9,]
            }
            else
            {
              value=data[8,]
            }
          }
        }
        else if(valor_op==4.5)
        {
          if(mano_op[1,2]==mano_op[2,2])
          {
            value=data[8,]
          }else{
            if(abs(mano_op[1,1]-mano_op[2,1])==1)
            {value=data[8,]}
            else{
              value=data[9,]
            }
          }
        }
        else if(valor_op==4)
        {
          if(mano_op[1,2]==mano_op[2,2])
          {
            if(mano_op[1,1]+mano_op[2,1]==20)
            {
            value=data[7,]
            }
            else
            {
              value=data[8,]
            }
          }
          else
          {
            if(abs(mano_op[1,1]-mano_op[2,1])==2)
            {
              value=data[9,]
            }
            else
            {
              value=data[8,]
            }
          }
        }
        else if(valor_op==3.5)
        {
          if(mano_op[1,2]==mano_op[2,2])
          {
            if(abs(mano_op[1,1]-mano_op[2,1])==2)
            {
              value=data[7,]
            }
            else
            {
              value=data[8,]
            }
          }
          else
          {
            if(abs(mano_op[1,1]-mano_op[2,1])==2)
            {
              value=data[9,]
            }
            else
            {
              value=data[8,]
            }
          }
        }
        else
        {
          value=data[9,]
        }
      }
      else
      {
        jugada_op=ordenarCartas(mano_op,mesa)
        valor_op<-calcularJugada(jugada_op)
        j<-switch (valor_op+1,1,2,3,4,5,6,7,8,9,10)
        value=data[j,]
      }
    }
    
    if(rb==1)
    {
      if(ronda==1)
      {
        valor_op<-chenFormula(mano_op)
        if(valor_op>=12)
        {
          value=data[10,]
        }
        else if(valor_op>=10)
        {
          value=data[11,]
        }
        else if(valor_op==9)
        {
          value=data[12,]
        }
        else if(valor_op==8)
        {
          if(mano_op[1,2]==mano_op[2,2])
          {
            if(mano_op[1,1]==14 || mano_op[2,1]==14)
            {
              value=data[12,]
            }else{
              value=data[13,]
            }
          }else{
            value=data[13,]
          }
        }
        else if(valor_op>6)
        {
          value=data[14,]
        }
        else if(valor_op==6)
        {
          if(mano_op[1,2]==mano_op[2,2])
          {
            if(mano_op[1,1]==12 || mano_op[2,1]==12)
            {
              value=data[14,]
            }else{
              value=data[15,]
            }
          }else{
            value=data[15,]
          }
        }
        else if(valor_op==5.5)
        {
          value=data[15,]
        }
        else if(valor_op==5)
        {
          if(mano_op[1,1]==mano_op[2,1] && mano_op[2,1]==5)
          {
            value=data[15,]
          }
          else if(mano_op[1,1]==mano_op[2,1] && mano_op[2,1]!=5)
          {
            value=data[16,]
          }
          else if(mano_op[1,2]==mano_op[2,2])
          {
            if((mano_op[1,1]==9 && mano_op[2,1]==6)||((mano_op[2,1]==9 && mano_op[1,1]==6)))
            {
              value=data[17,]
            }
            else
            {
              value=data[16,]
            }
          }
          else
          {
            if(abs(mano_op[1,1]-mano_op[2,1])>5)
            {
              value=data[18,]
            }
            else
            {
              value=data[17,]
            }
          }
        }
        else if(valor_op==4.5)
        {
          if(mano_op[1,2]==mano_op[2,2])
          {
            value=data[17,]
          }else{
            if((mano_op[1,1]-mano_op[2,1])==1)
            {value=data[17,]}
            else{
              value=data[18,]
            }
          }
        }
        else if(valor_op==4)
        {
          if(mano_op[1,2]==mano_op[2,2])
          {
            if(mano_op[1,1]+mano_op[2,1]==20)
            {
              value=data[16]
            }
            else
            {
              value=data[17,]
            }
          }
          else
          {
            if(abs(mano_op[1,1]-mano_op[2,1])==2)
            {
              value=data[18,]
            }
            else
            {
              value=data[17,]
            }
          }
        }
        else if(valor_op==3.5)
        {
          if(mano_op[1,2]==mano_op[2,2])
          {
            if(abs(mano_op[1,1]-mano_op[2,1])==2)
            {
              value=data[16,]
            }
            else
            {
              value=data[17,]
            }
          }
          else
          {
            if(abs(mano_op[1,1]-mano_op[2,1])==2)
            {
              value=data[18,]
            }
            else
            {
              value=data[17,]
            }
          }
        }
        else
        {
          value=data[18,]
        }
      }
      else
      {
        jugada_op=ordenarCartas(mano_op,mesa)
        valor_op<-calcularJugada(jugada_op)
        j<-switch (valor_op+1,11,12,13,14,15,16,17,18,19,20)
        value=data[j,]
      }
    }
    if(cb==1)
    {
      
      if(ronda==1)
      {
        
        valor_op<-chenFormula(mano_op)
        if(valor_op>=12)
        {
          value=data[19,]
        }
        else if(valor_op>=10)
        {
          value=data[20,]
        }
        else if(valor_op==9)
        {
          value=data[21,]
        }
        else if(valor_op==8)
        {
          if(mano_op[1,2]==mano_op[2,2])
          {
            if(mano_op[1,1]==14 || mano_op[2,1]==14)
            {
              value=data[21,]
            }else{
              value=data[22,]
            }
          }else{
            value=data[22,]
          }
        }
        else if(valor_op>6)
        {
          value=data[23,]
        }
        else if(valor_op==6)
        {
          if(mano_op[1,2]==mano_op[2,2])
          {
            if(mano_op[1,1]==12 || mano_op[2,1]==12)
            {
              value=data[23,]
            }else{
              value=data[24,]
            }
          }else{
            value=data[24,]
          }
        }
        else if(valor_op==5.5)
        {
          value=data[24,]
        }
        else if(valor_op==5)
        {
          if(mano_op[1,1]==mano_op[2,1] && mano_op[2,1]==5)
          {
            value=data[24,]
          }
          else if(mano_op[1,1]==mano_op[2,1] && mano_op[2,1]!=5)
          {
            value=data[25,]
          }
          else if(mano_op[1,2]==mano_op[2,2])
          {
            if((mano_op[1,1]==9 && mano_op[2,1]==6)||((mano_op[2,1]==9 && mano_op[1,1]==6)))
            {
              value=data[26,]
            }
            else
            {
              value=data[25,]
            }
          }
          else
          {
            if(abs(mano_op[1,1]-mano_op[2,1])>5)
            {
              value=data[27,]
            }
            else
            {
              value=data[26,]
            }
          }
        }
        else if(valor_op==4.5)
        {
          if(mano_op[1,2]==mano_op[2,2])
          {
            value=data[26,]
          }else{
            if((mano_op[1,1]-mano_op[2,1])==1)
            {value=data[26,]}
            else{
              value=data[27,]
            }
          }
        }
        else if(valor_op==4)
        {
          if(mano_op[1,2]==mano_op[2,2])
          {
            if(mano_op[1,1]+mano_op[2,1]==20)
            {
              value=data[25,]
            }
            else
            {
              value=data[26,]
            }
          }
          else
          {
            if(abs(mano_op[1,1]-mano_op[2,1])==2)
            {
              value=data[27,]
            }
            else
            {
              value=data[26,]
            }
          }
        }
        else if(valor_op==3.5)
        {
          if(mano_op[1,2]==mano_op[2,2])
          {
            if(abs(mano_op[1,1]-mano_op[2,1])==2)
            {
              value=data[25,]
            }
            else
            {
              value=data[26,]
            }
          }
          else
          {
            if(abs(mano_op[1,1]-mano_op[2,1])==2)
            {
              value=data[27,]
            }
            else
            {
              value=data[8,]
            }
          }
        }
        else
        {
          value=data[27,]
        }
      }
      else
      {
        jugada_op=ordenarCartas(mano_op,mesa)
        valor_op<-calcularJugada(jugada_op)
        j<-switch (valor_op+1,21,22,23,24,25,26,27,28,29,30)
        value=data[j,]
      }
      
    }
    if(i==1)
    {
      triple_aux=c(combina[i,1],combina[i,2],combina[i,3],combina[i,4],value[1],value[2],value[3])
    }else{
      triple_aux=rbind(triple_aux,c(combina[i,1],combina[i,2],combina[i,3],combina[i,4],value[1],value[2],value[3]))
    }
  }
  triple<-igualaTriple(triple,triple_aux)
  return (triple)
}