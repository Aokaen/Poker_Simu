\name{ursula}
\alias{ursula}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{
A sample function that goes all in or folds
}
\description{
Goes all in with a pocket pair of 9s or better.
}
\usage{
ursula(numattable1, crds1, board1, round1, currentbet, mychips1, 
pot1, roundbets, blinds1, chips1, ind1, dealer1, tablesleft)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{numattable1}{
(integer) number of players at the table
}
  \item{crds1}{
(2x2 matrix) your hole cards.
cards1[1,1] = the number of card 1 (between 2 and 14). 
cards[1,2] = suit of card 1 (between 1 and 4).
cards1[2,1] = the number (2-14) of card 2. 
cards[2,2] = suit of card 2 (1-4).
}
  \item{board1}{
(5x2 matrix) the board cards.
board1[1,1] = number of first card (2-14).
board1[1,2] = suit (1-4) of first card. 
Both are zero if the card hasn't been seen yet. 
For instance, if bettinground1 < 3, then board[4,1] = board1[4,2] = 0.
}
  \item{round1}{
(integer) which betting round it is.
1 = preflop, 2 = after flop, 3 = after turn, 4 = after river.
}
  \item{currentbet}{
(integer) how much more it is to you to stay in, right now.
}
  \item{mychips1}{
(integer) how many chips you have left at the moment.
}
  \item{pot1}{
(integer) how much is in the pot at the moment.
}
  \item{roundbets}{
(numattable1 x 4 matrix) matrix of all past bets during this hand.
roundbets[i,j] = total amount the player in seat i put in, in betting round j.
}
  \item{blinds1}{
(integer) big blind amount.
}
  \item{chips1}{
(vector of length numattable1) list of how many chips everyone has.
chips1[i] = how many chips the player in seat i has left.
}
  \item{ind1}{
(integer) which seat you're in.  
(So, mychips1 = chips1[ind1]).
}
  \item{dealer1}{
(integer) which seat the dealer is in. 
}
  \item{tablesleft}{
(integer) how many tables are left in the tournament (including yours). 
}
}
\details{
When this function is called from tourn1(),
cards1[2,1] is always less than or equal to cards1[1,1].
If the player in the big blind seat does not have enough chips to pay the 
big blind, then blinds1 is still the amount that the big blind would have 
been.
If only 2 players are left, then tourn1() uses the convention that the "dealer" 
is the big blind in determining dealer1.
}
\value{
integer indicating the number of chips you are betting. 0 means fold.
}
\references{
Schoenberg, F. (2011). An Introduction to Probability with Texas Holdem 
Examples. Taylor and Francis, New York.
}

%% ~Make other sections like Warning with \section{Warning }{....} ~


\examples{
##---- Should be DIRECTLY executable !! ----
##-- ==>  Define data, use random,
##--	or do  help(data=index)  for the standard data sets.

## The function is currently defined as
function(numattable1, crds1, board1,  round1, currentbet, mychips1, 
    pot1, roundbets, blinds1, chips1, ind1, dealer1, tablesleft){
    ## if pair of 9s or better, then all in    
    a1 = 0
    if((crds1[1,1] == crds1[2,1]) && (crds1[2,1] > 8.5)) a1 = mychips1
    a1
  } ## end of ursula
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ~kwd1 }
\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
