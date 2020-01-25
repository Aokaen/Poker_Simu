#funcion de crear mazo de 52 cartas asignandoles numero y palo
crearMazo<-function()
{
return(matrix(c(rep( c(2:14),4),rep(c(1:4),rep(13,4))), ncol=2,dimnames=list(NULL,c("Num","Palo"))))
}
