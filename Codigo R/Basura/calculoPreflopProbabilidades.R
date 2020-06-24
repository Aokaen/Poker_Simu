#funcion para calcular las probabilidades durante el preflop ante acción del oponente
#siendo valores para las acciones "V" para ver, "S" para subir y "P" para pasar

calculoPreflopProbabilidades<-function(accion,mazo,datos)
{
h<-0
valoresPreflop<-rbind(c(0,0.1,0.9),c(0,0.25,0.75),c(0.25,0.65,0.10),c(0.69,0.3,0.01),c(0.99,0.01,0))
n_mazo<-nrow(mazo)
modif<-datos

if(accion=="P")
{
a=1
}
if(accion=="V")
{
a=2
}
if(accion=="S")
{
a=3
}

parejas<-combinaMazo(mazo)
n_parejas<-nrow(parejas)
for(i in 1:n_parejas)
{
	mano<-rbind(c(parejas[i,1],parejas[i,2]),c(parejas[i,3],parejas[i,4]))
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
		}
		if (chen<3.5)
		{
		b=5
		}

		
	      valor=Leer(mano,modif)
		valorPreflop<-valoresPreflop[b,a]
		valor=valor*valorPreflop
		modif<-Modifica(mano,modif,valor)
	
	
}

return(modif)
}



