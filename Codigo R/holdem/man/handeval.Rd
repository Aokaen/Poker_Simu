\name{handeval}
\alias{handeval}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
Evaluates your hand.
}
\description{
Returns a number corresponding to the strength of your best 5-card poker 
hand.
}
\usage{
handeval(num1, suit1)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{num1}{
vector of numbers of your cards and the board cards.
}
  \item{suit1}{
corresponding suits of your cards and the board cards.
}
}

\value{
If you have a straight flush, then it will return a value in 
the 8 million to 9 million range, if you have four of a kind, then it will 
return a value between 7 million and 8 million, etc., according to the 
list below.

Straight Flush: 8,000,000 - 8,999,999
Four of a kind: 7,000,000 - 7,999,999.
Full House: 6,000,000 - 6,999,999.
Flush: 5,000,000 - 5,999,999.
Straight: 4,000,000 - 4,999,999.
3 of a kind: 3,000,000 - 3,999,999.
Two pairs: 2,000,000 - 2,999,999.
One pair: 1,000,000 - 1,999,999.
No pairs: 0 - 999,999.
If one player's hand beats that of another, 
then the value returned by this function will 
be higher for the first player than the second.
%%  ~Describe the value returned
%%  If it is a LIST, use
%%  \item{comp1 }{Description of 'comp1'}
%%  \item{comp2 }{Description of 'comp2'}
%% ...
}

\author{
Frederic Paik Schoenberg
}

%% ~Make other sections like Warning with \section{Warning }{....} ~

\examples{
boardcards = c(4,5,6,8,13)
boardsuits = c(2,3,2,2,2)
player1cards = c(2,3)
player1suits = c(2,1)
player2cards = c(7,3)
player2suits = c(2,4)
handeval(c(boardcards,player1cards),c(boardsuits,player1suits)) ## pl.1's value
handeval(c(boardcards,player2cards),c(boardsuits,player2suits)) ## pl.2's value

##---- Should be DIRECTLY executable !! ----
##-- ==>  Define data, use random,
##--	or do  help(data=index)  for the standard data sets.

## The function is currently defined as
function(num1,suit1){
    a1 = strflsh1(num1,suit1) 
    if(a1>0.5) return(8000000+a1)
    a1 = four1(num1)
    if(a1>0.5) return(7000000+a1)
    a1 = full1(num1)
    if(a1>0.5) return(6000000+a1)
    a1 = flush1(num1,suit1)
    if(a1>0.5) return(5000000+a1)
    a1 = straight1(num1)
    if(a1>0.5) return(4000000+a1)
    a1 = trip1(num1)
    if(a1>0.5) return(3000000+a1)
    a1 = twopair1(num1)
    if(a1>0.5) return(2000000+a1)
    a1 = onepair1(num1)
    if(a1>0.5) return(1000000+a1)
    a1 = nothing1(num1)
    return(a1)
  } ## end of handeval
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ~kwd1 }
\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
