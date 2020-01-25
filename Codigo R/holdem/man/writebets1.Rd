\name{writebets1}
\alias{writebets1}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
Write the bets on the plot
}
\description{
Writes the players' bets on the current plot. Used in mygraphics1(), which 
in turn is used by tourn1().
}
\usage{
writebets1(b9, y1, numattable1, b3, playerseats1, chips1, chips2, over1, myfast1, name1)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{b9}{
%%     ~~Describe \code{b9} here~~
}
  \item{y1}{
%%     ~~Describe \code{y1} here~~
}
  \item{numattable1}{
%%     ~~Describe \code{numattable1} here~~
}
  \item{b3}{
%%     ~~Describe \code{b3} here~~
}
  \item{playerseats1}{
%%     ~~Describe \code{playerseats1} here~~
}
  \item{chips1}{
%%     ~~Describe \code{chips1} here~~
}
  \item{chips2}{
%%     ~~Describe \code{chips2} here~~
}
  \item{over1}{
%%     ~~Describe \code{over1} here~~
}
  \item{myfast1}{
%%     ~~Describe \code{myfast1} here~~
}
  \item{name1}{
%%     ~~Describe \code{name1} here~~
}
}
\author{
Frederic Paik Schoenberg
}

%% ~Make other sections like Warning with \section{Warning }{....} ~


\examples{
##---- Should be DIRECTLY executable !! ----
##-- ==>  Define data, use random,
##--	or do  help(data=index)  for the standard data sets.

## The function is currently defined as
function(b9,y1,numattable1,b3,playerseats1,chips1,chips2,over1,myfast1,name1){
    # cat("\n Round ",y1,"\n",b9$il1,"\n",b9$bl1,".\n")
    cardname1 = c(as.character(1:9),"T","J","Q","K","A")
    suitname1 = c(2,3,4,6)
    drawnyet1 = rep(0,numattable1)
    if((y1 == 1) || (over1<1)){
	ilen1 = length(b9$il1)
	rember1 = rep(-1,numattable1)
	if(ilen1 > 1.5) for(j in c(2:ilen1)){
	    i = b9$il1[j]
	    if((y1 == 1) && (drawnyet1[i] < 1) && (j>3.5)){
		    text(10*i,60,cardname1[b3$plnum1[i,1]],col=suitname1[b3$plsuit1[i,1]],cex=2)
		    text(10*i+2,60,cardname1[b3$plnum1[i,2]],col=suitname1[b3$plsuit1[i,2]],cex=2)
		    drawnyet1[i] = 2
		    if(myfast1<1) locator(1)
	    }
	    if(rember1[i] != b9$bl1[j]){
		text(10*i,50-5*y1,rember1[i],col="white")
		text(10*i,50-5*y1,rember1[i],col="white")
		if((y1>1) || (b9$bl1[j] > .5)) text(10*i,50-5*y1,b9$bl1[j])
	    }
	    rember1[i] = b9$bl1[j]
	    if(b9$out1[j] > 1.5){
		text(10*i,60,cardname1[b3$plnum1[i,1]],col="white",cex=2)
		text(10*i+2,60,cardname1[b3$plnum1[i,2]],col="white",cex=2)
		text(10*i,80,as.character(name1[playerseats1[i]]),cex=1+.1*b9$i1[i],col="white")
		text(10*i,50,"BETS:",col="white")
		text(10*i,50,"BETS:",col="white")
		if(chips1[i] == chips2[i]) text(10*i,75,paste("(",chips1[i],")"),col="white")
	    }	 
	    if((y1 > 1.5) || (j > 3.5))  if(myfast1<1) locator(1)
	}
    }
  } ## end of writebets1
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ~kwd1 }
\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
