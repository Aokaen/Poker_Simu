#Formula de Chen 

chenFormula<-function(mano)
{
#valor carta alta
if(mano[1,1]<mano[2,1])
{
a=valorCartaAlta(mano[2,1])
}
else
{
a=valorCartaAlta(mano[1,1]) 
}
#valor parejas
if (mano[1,1]==mano[2,1])
{
a=a*2
if(a<5)
{
a=5
}
}
#valor color
if (mano[1,2]==mano[2,2])
{
a=a+2
}
#valor gaps
if(mano[1,1]<mano[2,1])
{
gap = mano[2,1]-mano[1,1]
}
else
{
gap = mano[1,1]-mano[2,1] 
}
gap=gap-1
if (gap==1)
{
a=a-1
}
if (gap==2)
{
a=a-2
}
if (gap==3)
{
a=a-4
}
if (gap>3)
{
a=a-5
}

#bonus Q
if(mano[1,1]<mano[2,1])
{
c_alta = mano[2,1]
}
else
{
c_alta = mano[1,1] 
}
if(c_alta<12 & (gap==0|gap==1))
{
a=a+1
}

return(a)
}
