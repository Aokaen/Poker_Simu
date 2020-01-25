#Funcion para descartar tanto los datos de una mano como de cualquier combinacion
#de cada una de las cartas de la mano para el framedata Triple Probabilidad

descarteTripleMano<-function(mano,mazo,datos)
{
valor<-c(0,0,0)
datos<-modificaTriple(mano,datos,valor)
datos<-descarteTripleCarta(mano[1,],mazo,datos)
datos<-descarteTripleCarta(mano[2,],mazo,datos)
}