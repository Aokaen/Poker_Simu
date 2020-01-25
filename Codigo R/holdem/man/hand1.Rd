\name{hand1}
\alias{hand1}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
Play a hand of Texas Hold'em
}
\description{
Used in tourn1() to play a single hand of Texas Hold'em.
}
\usage{
hand1(numattable1, playerseats1, chips1, blinds1, dealer1, ntable1, 
myfast1, t1, t2, chipstart1, lowercut1, decision1, 
name1 = c("vera","william","xena","yosef","zelda"))
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{numattable1}{
number of players at the table
}
  \item{playerseats1}{
list of indices, who's in seat 1, seat 2, etc.
}
  \item{chips1}{
list of chips left, for players at this table only.
}
  \item{blinds1}{
vector of small and big blind
}
  \item{dealer1}{
seat that the dealer is in
}
  \item{ntable1}{
how many tables remain in the tournament
}
  \item{myfast1}{
2 = fast, or 0 = slow, i.e. 2 means it will not show the hand graphically.
}
  \item{t1}{
probability of showing the hand graphically if there is a double up
}
  \item{t2}{
probability of showing the hand graphically if there is an elimination
}
  \item{chipstart1}{
starting number of chips everyone has
}
  \item{lowercut1}{
lower plotting threshold for a player's number of chips (the y axis)
}
  \item{decision1}{
a vector of the players' codes
}
  \item{name1}{
names of the players
}
}
\value{
%%  ~Describe the value returned
%%  If it is a LIST, use
  \item{chips2 }{how many chips everyone has after the hand}
  \item{draw1 }{2 if the hand is to be shown graphically, or 0 if not}
%% ...
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
function(numattable1, playerseats1, chips1, blinds1, dealer1, 
ntable1,myfast1,t1,t2,chipstart1,lowercut1, decision1){
    ## numattable1 = number of players at the table
    ## playerseats1 = list of indices, who's in seat 1, seat 2, etc.
    ## chips1 = list of chips left, FOR PLAYERS AT THIS TABLE ONLY!
    ## blinds = vector of small and then big blind
    ## dealer1 = seat that the dealer is in.    
    ## ntable1 = how many tables remain.
    chips2 = chips1 ## this will be the revised chips counts, at the end
    if(numattable1 < 1.5) return(chips2)  
          ## want to return other stuff too, liks who's left?
          ## No need... can do that within main loop. Just check for zeros.
    b3 = deal1(numattable1)
    b4 = bid1(numattable1,playerseats1, chips1, blinds1, dealer1, b3, ntable1, decision1)
    # cat("\n...",b4$bl1,"\n....",b4$il1,"\n")
    b5 = bid2(numattable1,playerseats1, blinds1, dealer1, b3,b4,2, ntable1, decision1)
    b6 = bid2(numattable1,playerseats1, blinds1, dealer1, b3,b5,3, ntable1, decision1)
    b7 = bid2(numattable1,playerseats1, blinds1, dealer1, b3,b6,4, ntable1, decision1)
    chips2 = calcwin1(numattable1,playerseats1, b3, b7) 
    draw1 = 0
    u21 = runif(1)
    if(((max(chips2/(chips1+.01)) > 1.99) && 
    (u21 < t1)) || ((max(chips1/(chips2+.01)) > 99) && (u21 < t2))) {
	if(myfast1 < 1) {
	    text(1,lowercut1,"click to continue",cex=.7)
	    locator(1)
	}
	mygraphics1(numattable1,playerseats1,chips1,blinds1,dealer1,
	b3,b4,b5,b6,b7,chips2,ntable1,myfast1,chipstart1,
		    name1,lowercut1) 
	draw1 = 2
    }
    list(chips2=chips2,draw1=draw1)
  }  ## end of hand1
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ~kwd1 }
\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
